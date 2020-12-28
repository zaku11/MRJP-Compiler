#include <string>
#include <iostream>
#include <variant>
#include <map>
#include <set>
#include <algorithm>
#include <tuple>
#include <vector>
#include "LLVM.H"

using std :: cerr;
using std :: vector;
using std :: string;
using std :: set;
using std :: map;
using std :: to_string;

const String TYPE_INT = "i32";
const String TYPE_BOOL = "i1";
const String TYPE_STRING = "i8*";

string transform_type_name(Type &type) {
  if(dynamic_cast<Int*>(&type)) return "i32";
  if(dynamic_cast<Bool*>(&type)) return "i1";
  if(dynamic_cast<Str*>(&type)) return "i8*";
  if(dynamic_cast<Void*>(&type)) return "void";
  if(auto str = dynamic_cast<Struct*>(&type))
    return str->ident_;
  return "";
}

string cpp_to_llvm_types(String cpp_type) {
  if(cpp_type == "int") return "i32";
  if(cpp_type == "boolean") return "i1";
  if(cpp_type == "string") return "i8*";
  return cpp_type;
}


vector<Type*> extract_types_from_args(ListArg* listarg) {
  vector<Type*> ans;
  for (ListArg::const_iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    if(auto arg = dynamic_cast<ArgDef*>(*i))
      ans.push_back(arg->type_); 
  }
  return ans;
}

void LLVM::addToOutput(string text) {
  this->output += text;
}

void LLVM::addConstant(string text) {

  string text_escaped = "";
  int ptr = 0;
  while(ptr < text.size()) {
    if(text[ptr] == '\"') {
      text_escaped += "\\22"; 
    // } else if(text[ptr] == '\'') {
    //   text_escaped += "\\'";
    // } else if(text[ptr] == '\"') {
    //   text_escaped += "\"";
    } else {
      text_escaped += text[ptr];
    }
    ptr++;
  }
  // cerr << text << "\n";
  // cerr << text_escaped << "\n";
  auto type = "[" + to_string(text.size() + 1) + " x i8]";

  string full_message = "@s" + to_string(last_var + 1) + " = private constant " + type + " c\"" + text_escaped + "\\00\" \n";
  this->output = full_message + output;

}

void LLVM::addReference(string id) {
  reference_map[id]++;
}

void LLVM::deleteReference(string id) {
  reference_map[id]--;
  if(reference_map[id] == 0) {
    addToOutput("call void @free(i8* " + id + ")\n");
  }
}

bool LLVM::doesEndWithReturn() {
  int ptr = output.size() - 1;
  int counter = 2;
  while(ptr > 0 && counter > 0) {
    if(output[ptr] == '\n') counter--;
    ptr--;
  }
  ptr+=2;
  return output.compare(ptr, 3, "ret") == 0;
}


string LLVM::getCurrentVarNum(Ident id) {
  return "_" + id + "_" + to_string(current_var_number[id]);
}

string LLVM::getCurrentVarNum(IdentExpan &id) {
  auto simple_ident = dynamic_cast<IdentExpSimple*>(&id)->ident_;
  return "_" + simple_ident + "_" + to_string(current_var_number[simple_ident]);
}

string LLVM::genLabel(string text) {
  last_label_num++;
  return text + to_string(last_label_num);
}

string LLVM::genTmpVar(string text) {
  last_label_num++;
  return text + to_string(last_label_num);
}



LLVM::LLVM(void)
{
}

LLVM::~LLVM(void)
{
}

void LLVM::run(Visitable *v)
{
  auto single_void = Void();
  auto single_int = Int();
  auto single_string = Str();

  vector <Type*> single_int_vec;
  single_int_vec.push_back(&single_int);

  vector <Type*> single_str_vec;
  single_str_vec.push_back(&single_string);

  function_data["printInt"] = std :: make_pair(&single_void, single_int_vec);
  function_data["printString"] = std :: make_pair(&single_void, single_str_vec);

  vector <Type*> empty_vec;

  function_data["readInt"] = std :: make_pair(&single_int, empty_vec);
  function_data["readString"] = std :: make_pair(&single_string, empty_vec);

  function_data["error"] = std :: make_pair(&single_void, empty_vec);



  v->accept(this);
  std :: cout << this->output;

}

void LLVM::visitProgram(Program *p) {} //abstract class

void LLVM::visitProgramDef(ProgramDef *p)
{
  if(p->listtopdef_) {
    p->listtopdef_->accept(this);
  }
}

void LLVM::visitTopDef(TopDef *p) {} //abstract class

void LLVM::visitFnDef(FnDef *p)
{

  string type = transform_type_name(*p->type_);
  // addToOutput("declare void @printString(i32 %x)\n");
  addToOutput("define " + type + " @" + p->ident_);
  p->listarg_->accept(this);
  addToOutput(" {\n");

  for (ListArg::const_iterator i = p->listarg_->begin() ; i != p->listarg_->end() ; ++i)
  {
    if(auto arg = dynamic_cast<ArgDef*>(*i)) {
      auto type_in_string = transform_type_name(*arg->type_);
      addToOutput("%" + getCurrentVarNum(arg->ident_) + " = alloca " + type_in_string + "\n");
      addToOutput("store " + type_in_string + " %" + arg->ident_ + ", " + type_in_string + "* %" + getCurrentVarNum(arg->ident_) + "\n");
    }
  }


  p->block_->accept(this);
  
  skipping_instructions = false;

  if(!doesEndWithReturn()) {
    if(type == "void") 
      addToOutput("ret void\n");
    if(type == "i32") 
      addToOutput("ret i32 0\n");
    if(type == "i1") 
      addToOutput("ret i1 0\n");
    if(type == "i8*") {
      addToOutput("%tmp" + to_string(last_var + 1) + " = bitcast [0 x i8]* @emptyStr to i8*\n");
      addToOutput("ret i8* %tmp" + to_string(last_var + 1));
      last_var++; 
    }
  }

  addToOutput("}\n");
}

void LLVM::visitStructDef(StructDef *p) {
  // TODO
}

void LLVM::visitEmptyStructDef(EmptyStructDef *p) {
  // TODO
}


void LLVM::visitStructMember(StructMember *p) {} //abstract class

void LLVM::visitStructMemNoInit(StructMemNoInit *p)
{
}

void LLVM::visitStructMemInit(StructMemInit *p)
{
}

void LLVM::visitListStructMember(ListStructMember *liststructmember)
{
}

void LLVM::visitIdentExpan(IdentExpan *p) {} /* abstract class */

void LLVM::visitIdentExp(IdentExp *p) {
  if(p->identexpan_)
    p->identexpan_->accept(this);
  
  // TODO
}

void LLVM::visitIdentExpSimple(IdentExpSimple *p) {
  // TODO
}



void LLVM::visitListTopDef(ListTopDef *listtopdef)
{
  addToOutput("@emptyStr = internal constant [0 x i8] c\"\"\n");
  addToOutput("declare void @free(i8*)\n");
  addToOutput("declare i8* @concat(i8*, i8*)\n");
  addToOutput("declare void @error()\n");

  addToOutput("declare void @printInt(i32 %x)\n");
  addToOutput("declare void @printString(i8* %s)\n");
  addToOutput("declare i32 @readInt()\n");
  addToOutput("declare i8* @readString()\n");

  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i) {
    if(auto fn_def = dynamic_cast<FnDef*>(*i)) {
      function_data[fn_def->ident_] = make_pair(fn_def->type_, extract_types_from_args(fn_def->listarg_));
    }
  }

  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
  }

}

void LLVM::visitArg(Arg *p) {} //abstract class

void LLVM::visitArgDef(ArgDef *p)
{
  
  addToOutput(transform_type_name(*p->type_) + " %" + p->ident_);
}

void LLVM::visitListArg(ListArg *listarg)
{
  bool fst = true;
  addToOutput("(");
  for (ListArg::const_iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    if(!fst) {
      addToOutput(", ");
    }
    (*i)->accept(this);
    fst = false;
  }
  addToOutput(")");
}

void LLVM::visitBlock(Block *p) {} //abstract class

void LLVM::visitBlockDef(BlockDef *p)
{
  if(p->liststmt_) {
    // auto rollback_new_things_added = new_things_added;
    // new_things_added.clear();

    run_with_rollback(p->liststmt_);
    
    // for(auto thing : new_things_added) {
    //   deleteReference(thing);
    // }

    // new_things_added = rollback_new_things_added;

  }
}

void LLVM::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    if(skipping_instructions)
      break;
    (*i)->accept(this);
  }
}

void LLVM::visitStmt(Stmt *p) {} //abstract class

void LLVM::visitEmpty(Empty *p)
{

}

void LLVM::run_with_rollback(Visitable* v) {
  auto cur_var_num = current_var_number;
  v->accept(this);
  current_var_number = cur_var_num;
}

void LLVM::visitBStmt(BStmt *p)
{
  p->block_->accept(this);
}

void LLVM::visitDecl(Decl *p)
{
  for (ListItem::const_iterator i = p->listitem_->begin() ; i != p->listitem_->end() ; ++i) {
    if(auto no_init = dynamic_cast<NoInit*>(*i)) {
      current_var_number[no_init->ident_] = last_var_numbers[no_init->ident_] + 1;
      last_var_numbers[no_init->ident_] += 1;

      if(dynamic_cast<Int*>(p->type_)) {
        addToOutput("%" + getCurrentVarNum(no_init->ident_) + " = alloca i32\n");
        addToOutput("store i32 0, i32* %" + getCurrentVarNum(no_init->ident_) + "\n");
      }
      if(dynamic_cast<Bool*>(p->type_)) {
        addToOutput("%" + getCurrentVarNum(no_init->ident_) + " = alloca i1\n");
        addToOutput("store i1 0, i1* %" + getCurrentVarNum(no_init->ident_) + "\n");
      }
      if(dynamic_cast<Str*>(p->type_)) {
        addToOutput("%" + getCurrentVarNum(no_init->ident_) + " = alloca i8*\n");
        addToOutput("%i" + to_string(last_var + 1) + " = bitcast [0 x i8]* @emptyStr to i8*\n");
        addToOutput("store i8* %i" + to_string(last_var + 1) +  ", i8** %" + getCurrentVarNum(no_init->ident_) + "\n");
        last_var++;
      }
    }
    if(auto init = dynamic_cast<Init*>(*i)) {
      auto ans = processSingle(init->expr_);
      auto type = cpp_to_llvm_types(init->expr_->expr_type_); 

      current_var_number[init->ident_] = last_var_numbers[init->ident_] + 1;
      last_var_numbers[init->ident_] += 1;

      addToOutput("%" + getCurrentVarNum(init->ident_) + " = alloca " + type + "\n");
      addToOutput("store " + type + " " + ans + ", " + type + "* %" + getCurrentVarNum(init->ident_) + "\n");

      // if(dynamic_cast<Int*>(p->type_)) {
      //   addToOutput("%" + getCurrentVarNum(init->ident_) + " = alloca i32\n");
      //   addToOutput("store i32 " + ans + ", i32* %" + getCurrentVarNum(init->ident_) + "\n");
      // }
      // if(dynamic_cast<Bool*>(p->type_)) {
      //   addToOutput("%" + getCurrentVarNum(init->ident_) + " = alloca i1\n");
      //   addToOutput("store i1 " + ans + ", i1* %" + getCurrentVarNum(init->ident_) + "\n");
      // }

    }
  }

}

void LLVM::visitNewStruct(NewStruct *p) {
  // Here identexpan_ is a id of a variable
  // And ident_ is a name of the struct
  // TODO
}

String LLVM::processSingle(Expr* expr) {
  String ans = "";
  if(auto stmt = dynamic_cast<ELitInt*>(expr)) {
    ans = to_string(stmt->integer_);
    return ans;
  } 
  if(auto stmt = dynamic_cast<ELitTrue*>(expr)) {
    ans = "1";
    return ans;
  }
  if(auto stmt = dynamic_cast<ELitFalse*>(expr)) {
    ans = "0";
    return ans;
  } 
  // if(auto stmt = dynamic_cast<EString*>(expr)) {
  //   ans = stmt->string_;
  //   return ans;
  // } 
  
  expr->accept(this);
  if(auto stmt = dynamic_cast<EVar*>(expr)) {
    ans = "%i" + to_string(last_var);
  } 
  if(ans == "") {
    ans = "%i" + to_string(last_var);
  }
  return ans;
}

std :: pair<String, String> LLVM::process(Expr* e1, Expr* e2) {
  string s1 = processSingle(e1);
  string s2 = processSingle(e2);
  return make_pair(s1, s2);
}


void LLVM::visitAss(Ass *p)
{
  auto ans = processSingle(p->expr_);
  auto type = cpp_to_llvm_types(p->expr_->expr_type_);
  addToOutput("store " + type + " " + ans + ", " + type + "* %" + getCurrentVarNum(*p->identexpan_) + "\n");
  // if(type == TYPE_STRING) 
  //   addReference(ans);
}

void LLVM::visitIncr(Incr *p)
{
  addToOutput("%i" + to_string(last_var + 1) + " = load i32, i32* %" + getCurrentVarNum(*p->identexpan_) + "\n");
  addToOutput("%i" + to_string(last_var + 2) + " = add i32 %i" + to_string(last_var + 1) + ", 1\n");
  addToOutput("store i32 %i" + to_string(last_var + 2) + ", i32* %" + getCurrentVarNum(*p->identexpan_) + "\n");

  last_var += 2;
}

void LLVM::visitDecr(Decr *p)
{
  addToOutput("%i" + to_string(last_var + 1) + " = load i32, i32* %" + getCurrentVarNum(*p->identexpan_) + "\n");
  addToOutput("%i" + to_string(last_var + 2) + " = sub i32 %i" + to_string(last_var + 1) + ", 1\n");
  addToOutput("store i32 %i" + to_string(last_var + 2) + ", i32* %" + getCurrentVarNum(*p->identexpan_) + "\n");

  last_var += 2;

}

void LLVM::visitRet(Ret *p)
{
  auto ans = processSingle(p->expr_);
  addToOutput("ret " + cpp_to_llvm_types(p->expr_->expr_type_) + " " + ans + "\n");
  // if(cpp_to_llvm_types(p->expr_->expr_type_) == TYPE_STRING)
  //   addReference(ans);

  skipping_instructions = true;
  // TODO
}

void LLVM::visitVRet(VRet *p)
{
  addToOutput("ret void\n");
  skipping_instructions = true;
  // TODO
}

void LLVM::visitCond(Cond *p)
{
  auto ans = processSingle(p->expr_);

  auto label_true = genLabel("IfTrue");
  auto label_end = genLabel("IfEnd");

  addToOutput("br i1 " + ans + ", label %"  + label_true + ", label %" + label_end + "\n");

  addToOutput(label_true + ":\n");
  p->stmt_->accept(this);
  skipping_instructions = false;

  addToOutput("br label %" + label_end + "\n");
  addToOutput(label_end + ":\n");
}


void LLVM::visitCondElse(CondElse *p)
{
  auto label_true = genLabel("IfElseTrue");
  auto label_false = genLabel("IfElseFalse");
  auto label_end = genLabel("IfElseEnd");
  
  auto ans = processSingle(p->expr_);

  addToOutput("br i1 " + ans + ", label %"  + label_true + ", label %" + label_false + "\n");
  
  addToOutput(label_true + ":\n");
  p->stmt_1->accept(this);
  skipping_instructions = false;

  addToOutput("br label %" + label_end + "\n");
  addToOutput(label_false + ":\n");
  p->stmt_2->accept(this);
  skipping_instructions = false;

  addToOutput("br label %" + label_end + "\n");
  addToOutput(label_end + ":\n");
}

void LLVM::visitWhile(While *p)
{
  auto label_cond = genLabel("CondCalc");
  auto label_true = genLabel("CondTrue");
  auto label_false = genLabel("CondEnd");

  addToOutput("br label %" + label_cond + "\n");
  addToOutput(label_cond + ":\n");

  auto ans = processSingle(p->expr_); 
  // p->expr_->accept(this);


  // addToOutput("br i1 %i" + to_string(last_var) + ", label %"  + label_true + ", label %" + label_end + "\n");
  addToOutput("br i1 " + ans + ", label %"  + label_true + ", label %" + label_false + "\n");

  addToOutput(label_true + ":\n");
  p->stmt_->accept(this);
  skipping_instructions = false;

  addToOutput("br label %" + label_cond + "\n");
  
  addToOutput(label_false + ":\n");

}

void LLVM::visitSExp(SExp *p)
{
  p->expr_->accept(this);
}

void LLVM::visitItem(Item *p) {} //abstract class

void LLVM::visitNoInit(NoInit *p)
{  
}

void LLVM::visitInitStruct(InitStruct *p) {

}

void LLVM::visitInit(Init *p)
{
}

void LLVM::visitListItem(ListItem *listitem)
{
}

void LLVM::visitType(Type *p) {} //abstract class

void LLVM::visitInt(Int *p)
{
}

void LLVM::visitStr(Str *p)
{
}

void LLVM::visitBool(Bool *p)
{
}

void LLVM::visitVoid(Void *p)
{
}

void LLVM::visitStruct(Struct *p)
{
}

void LLVM::visitFun(Fun *p)
{
}

void LLVM::visitListType(ListType *listtype)
{
}

void LLVM::visitExpr(Expr *p) {} //abstract class

void LLVM::visitENullCast(ENullCast *p) {
  //TODO
}

void LLVM::visitEVar(EVar *p)
{
  auto type = cpp_to_llvm_types(p->expr_type_);
  addToOutput("%i" + to_string(last_var + 1) + " = load " + type + ", " + type + "* %" + getCurrentVarNum(*p->identexpan_) + "\n");
  last_var++;
}

void LLVM::visitELitInt(ELitInt *p)
{
}

void LLVM::visitELitTrue(ELitTrue *p)
{
}

void LLVM::visitELitFalse(ELitFalse *p)
{
}

void LLVM::visitEApp(EApp *p)
{

  vector <string> computed_args;
  for (ListExpr::const_iterator i = p->listexpr_->begin() ; i != p->listexpr_->end() ; ++i)
  {
    computed_args.push_back(processSingle(*i));
  }


  if(!dynamic_cast<Void*>(function_data[p->ident_].first)) {
    addToOutput("%i" + to_string(last_var + 1) + " = ");
    last_var++;
  }

  vector<Type*> listarg = function_data[p->ident_].second;
  addToOutput("call " + transform_type_name(*function_data[p->ident_].first) + " @" + p->ident_ + "(");
  for (int i = 0 ; i < listarg.size() ; ++i)
  {
    if(i > 0) addToOutput(", ");
    addToOutput(transform_type_name(*listarg[i]) + " " + computed_args[i]);
  }


  addToOutput(")\n");

}

void LLVM::visitEString(EString *p)
{
  // addToOutput("%i" + to_string(last_var + 1) + " = call i8* @malloc(i32 " + to_string(p->string_.size()) + ")\n");

  addConstant(p->string_);
  
  int text_size = p->string_.size();
  string arr_type = "[" + to_string(text_size + 1) + " x i8]";
  
  addToOutput("%i" + to_string(last_var + 1) + " = bitcast " + arr_type + "* @s" + to_string(last_var + 1) + " to i8*\n");
  last_var++;
}


void LLVM::visitNeg(Neg *p)
{
  auto ans = processSingle(p->expr_);
  addToOutput("%i" + to_string(last_var + 1) + " = fneg i32 " + ans + "\n");
  last_var++;
}

void LLVM::visitNot(Not *p)
{
  auto ans = processSingle(p->expr_);
  addToOutput("%i" + to_string(last_var + 1) + " = sub i1 1, " + ans + "\n");
  last_var++;  
}

void LLVM::visitEMul(EMul *p)
{
  auto res = process(p->expr_1, p->expr_2);
  String s1 = res.first, s2 = res.second;
  if(dynamic_cast<Times*>(p->mulop_))
    addToOutput("%i" + to_string(last_var + 1) + " = mul i32 " + s1 + ", " + s2 + "\n");
  if(dynamic_cast<Div*>(p->mulop_))
    addToOutput("%i" + to_string(last_var + 1) + " = sdiv i32 " + s1 + ", " + s2 + "\n");
  if(dynamic_cast<Mod*>(p->mulop_)) { 
    addToOutput("%i" + to_string(last_var + 1) + " = sdiv i32 " + s1 + ", " + s2 + "\n");
    addToOutput("%i" + to_string(last_var + 2) + " = mul i32 %i" + to_string(last_var + 1) + ", " + s2 + "\n");
    addToOutput("%i" + to_string(last_var + 3) + " = sub i32 " + s1 + ", %i" + to_string(last_var + 2) + "\n");

    last_var += 2;
  }
  

  last_var++; 

}

void LLVM::visitEAdd(EAdd *p)
{
  auto res = process(p->expr_1, p->expr_2);
  String s1 = res.first, s2 = res.second;
  if(dynamic_cast<Plus*>(p->addop_)) {
    if(cpp_to_llvm_types(p->expr_1->expr_type_) == TYPE_STRING) {
      string new_malloced_thing = "%i" + to_string(last_var + 1);
      addToOutput(new_malloced_thing + " = call i8* @concat(i8* " + s1 + ", i8* " + s2 + ")\n");
      // new_things_added.push_back(new_malloced_thing);
      // addReference(new_malloced_thing);
    } else {
      addToOutput("%i" + to_string(last_var + 1) + " = add " + cpp_to_llvm_types(p->expr_1->expr_type_) + " " + s1 + ", " + s2 + "\n");
    }
  }
  if(dynamic_cast<Minus*>(p->addop_))
    addToOutput("%i" + to_string(last_var + 1) + " = sub " + cpp_to_llvm_types(p->expr_1->expr_type_) + " " + s1 + ", " + s2 + "\n");
  
  last_var++; 
}

void LLVM::visitERel(ERel *p)
{
  auto res = process(p->expr_1, p->expr_2);
  String s1 = res.first, s2 = res.second;

  if(dynamic_cast<LTH*>(p->relop_))
    addToOutput("%i" + to_string(last_var + 1) + " = icmp slt " + cpp_to_llvm_types(p->expr_1->expr_type_) + " " + s1 + ", " + s2 + "\n");
  if(dynamic_cast<LE*>(p->relop_))
    addToOutput("%i" + to_string(last_var + 1) + " = icmp sle " + cpp_to_llvm_types(p->expr_1->expr_type_) + " " + s1 + ", " + s2 + "\n");
  if(dynamic_cast<GTH*>(p->relop_))
    addToOutput("%i" + to_string(last_var + 1) + " = icmp sgt " + cpp_to_llvm_types(p->expr_1->expr_type_) + " " + s1 + ", " + s2 + "\n");
  if(dynamic_cast<GE*>(p->relop_))
    addToOutput("%i" + to_string(last_var + 1) + " = icmp sge " + cpp_to_llvm_types(p->expr_1->expr_type_) + " " + s1 + ", " + s2 + "\n");
  if(dynamic_cast<EQU*>(p->relop_))
    addToOutput("%i" + to_string(last_var + 1) + " = icmp eq " + cpp_to_llvm_types(p->expr_1->expr_type_) + " " + s1 + ", " + s2 + "\n");
  if(dynamic_cast<NE*>(p->relop_))
    addToOutput("%i" + to_string(last_var + 1) + " = icmp ne " + cpp_to_llvm_types(p->expr_1->expr_type_) + " " + s1 + ", " + s2 + "\n");

  last_var++;
}

void LLVM::visitEAnd(EAnd *p)
{
  auto label_maybe_true = genLabel("AndMaybeTrue");
  auto label_false = genLabel("AndFalse");
  auto label_true = genLabel("AndTrue");
  auto label_end = genLabel("AndEnd");
  auto tmp_var = genTmpVar("tmp");

  addToOutput("%" + tmp_var + " = alloca i1 \n");

  auto val1 = processSingle(p->expr_1);
  addToOutput("br i1 " + val1 + ", label %"  + label_maybe_true + ", label %" + label_false + "\n");
  addToOutput(label_maybe_true + ":\n");

  auto val2 = processSingle(p->expr_2);
  addToOutput("br i1 " + val2 + ", label %"  + label_true + ", label %" + label_false + "\n");
  addToOutput(label_true + ":\n");
  addToOutput("store i1 1, i1* %" + tmp_var + "\n");
  addToOutput("br label %" + label_end + "\n");

  addToOutput(label_false + ":\n");
  addToOutput("store i1 0, i1* %" + tmp_var + "\n");
  addToOutput("br label %" + label_end + "\n");
  addToOutput(label_end + ":\n");
  addToOutput("%i" + to_string(last_var + 1) + " = load i1, i1* %" + tmp_var + "\n");
  last_var++;
}

void LLVM::visitEOr(EOr *p)
{
  auto label_maybe_false = genLabel("OrMaybeFalse");
  auto label_false = genLabel("OrFalse");
  auto label_true = genLabel("OrTrue");
  auto label_end = genLabel("OrEnd");
  auto tmp_var = genTmpVar("tmp");

  addToOutput("%" + tmp_var + " = alloca i1 \n");

  auto val1 = processSingle(p->expr_1);
  addToOutput("br i1 " + val1 + ", label %"  + label_true + ", label %" + label_maybe_false + "\n");
  addToOutput(label_maybe_false + ":\n");

  auto val2 = processSingle(p->expr_2);
  addToOutput("br i1 " + val2 + ", label %"  + label_true + ", label %" + label_false + "\n");
  addToOutput(label_true + ":\n");
  addToOutput("store i1 1, i1* %" + tmp_var + "\n");
  addToOutput("br label %" + label_end + "\n");

  addToOutput(label_false + ":\n");
  addToOutput("store i1 0, i1* %" + tmp_var + "\n");
  addToOutput("br label %" + label_end + "\n");
  addToOutput(label_end + ":\n");
  addToOutput("%i" + to_string(last_var + 1) + " = load i1, i1* %" + tmp_var + "\n");
  last_var++;
}

void LLVM::visitListExpr(ListExpr *listexpr)
{
}

void LLVM::visitAddOp(AddOp *p) {} //abstract class

void LLVM::visitPlus(Plus *p) {}

void LLVM::visitMinus(Minus *p) {}

void LLVM::visitMulOp(MulOp *p) {} //abstract class

void LLVM::visitTimes(Times *p) {}

void LLVM::visitDiv(Div *p) {}

void LLVM::visitMod(Mod *p) {}

void LLVM::visitRelOp(RelOp *p) {} //abstract class

void LLVM::visitLTH(LTH *p) {}

void LLVM::visitLE(LE *p) {}

void LLVM::visitGTH(GTH *p) {}

void LLVM::visitGE(GE *p) {}

void LLVM::visitEQU(EQU *p) {}

void LLVM::visitNE(NE *p) {}

void LLVM::visitInteger(Integer i)
{
}

void LLVM::visitDouble(Double d)
{
}

void LLVM::visitChar(Char c)
{
}

void LLVM::visitString(String s)
{
}

void LLVM::visitIdent(String s)
{
}