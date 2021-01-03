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

const String LLVM_TYPE_INT = "i32";
const String LLVM_TYPE_BOOL = "i1";
const String LLVM_TYPE_STRING = "i8*";
const String LLVM_TYPE_VOID = "void";

void LLVM::deleteLastLine() {
  int ptr = output.size() - 2;
  while(ptr > 0 && output[ptr] != '\n') ptr--;
  ptr++;

  output = output.substr(0, ptr);
  last_var--;
}

string transform_type_name(Type &type) {
  if(dynamic_cast<Int*>(&type)) return "i32";
  if(dynamic_cast<Bool*>(&type)) return "i1";
  if(dynamic_cast<Str*>(&type)) return "i8*";
  if(dynamic_cast<Void*>(&type)) return "void";
  if(auto str = dynamic_cast<Class*>(&type))
    return "%" + str->ident_ + "*";
  return "";
}

string trim_if_class(string type) {
  if(type[0] == '%')
    return type.substr(1, type.size() - 2);
  return type;
}

string cpp_to_llvm_types(String cpp_type) {
  if(cpp_type == "int") return "i32";
  if(cpp_type == "boolean") return "i1";
  if(cpp_type == "string") return "i8*";
  return "%" + cpp_type + "*";
}


bool test_ancestership(Ident son, Ident father, ClassEnv& class_env) {
  while(son != "") {
    if(son == father)
      return true;
  
    son = class_env[son].second;
  }
  return false;
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

  string full_message = "@s" + to_string(last_var + 1) + " = internal constant " + type + " c\"" + text_escaped + "\\00\" \n";
  this->output = full_message + output;

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

void LLVM::addToInject(string text) {
  inject += text;
}

string LLVM::getCurrentVarNum(Ident id) {
  return "_" + id + "_" + to_string(current_var_number[id]);
}

string LLVM::getCurrentVarNum(IdentExpan &id) {
  if(auto simple_ident = dynamic_cast<IdentExpSimple*>(&id))
    return "_" + simple_ident->ident_ + "_" + to_string(current_var_number[simple_ident->ident_]);
  if(auto ident_exp = dynamic_cast<IdentExp*>(&id))
    return getCurrentVarNum(*ident_exp->identexpan_);
  return "";
}

string LLVM::genLabel(string text) {
  last_label_num++;
  return text + to_string(last_label_num);
}

string LLVM::genTmpVar(string text) {
  last_label_num++;
  return text + to_string(last_label_num);
}

string mangle_fn_name(string fn_name) {
  if(fn_name == "main" || fn_name == "printInt" || fn_name == "printString" || fn_name == "error" || fn_name == "readInt" || fn_name == "readString")
    return fn_name;
  return "USR_DEF_" + fn_name;
}

void LLVM::go_upward_in_inheritance(string actual_class, string expected_class, string last_ans) {
  addToOutput("%i" + to_string(last_var + 1) + " = bitcast %" + actual_class + "* " + last_ans + " to %" + expected_class + "*\n");
  last_var++;
}


LLVM::LLVM(ClassEnv clEnv)
{
  this->env_of_classes = clEnv;
}

LLVM::~LLVM(void)
{
}

string LLVM::run(Visitable *v)
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
  return this->output;
  // std :: cout << this->output;
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
  if(mangle_fn_names)
    addToOutput("define " + type + " @" + mangle_fn_name(p->ident_));
  else 
    addToOutput("define " + type + " @" + p->ident_);

  p->listarg_->accept(this);
  addToOutput(" {\n");

  if(inject != "") {
    addToOutput(inject);
    inject = "";
  }

  for (ListArg::const_iterator i = p->listarg_->begin() ; i != p->listarg_->end() ; ++i)
  {
    if(auto arg = dynamic_cast<ArgDef*>(*i)) {
      auto type_in_string = transform_type_name(*arg->type_);
      addToOutput("%" + getCurrentVarNum(arg->ident_) + " = alloca " + type_in_string + "\n");
      addToOutput("store " + type_in_string + " %" + arg->ident_ + ", " + type_in_string + "* %" + getCurrentVarNum(arg->ident_) + "\n");
    }
  }

  null_ptr_label = genLabel("NullPtrException");
  was_null_ptr_label_needed = false;
  current_expected_return = trim_if_class(type);
  p->block_->accept(this);
  current_expected_return = "";

  skipping_instructions = false;

  if(!doesEndWithReturn()) {
    // Since front-end made sure every computation ends with som return this should not happen 
    if(type == "void") 
      addToOutput("ret void\n");
    addToOutput("unreachable\n");
  }
  if(was_null_ptr_label_needed) {
    addToOutput(null_ptr_label + ":\n");
    addToOutput("call void @fail_null_ptr()\n");
    addToOutput("unreachable\n");
  }
  was_null_ptr_label_needed = false;

  addToOutput("}\n");
}

void LLVM::prefetchClasses(ClassDefInherit *p) {
  addToOutput("%" + p->ident_1 + " = type {\n");
  map <string, pair<string, int> > fields;
  int iter = 0;
  if(p->ident_2 != "") {
    addToOutput("%" + p->ident_2);
    iter++;
  }

  for (ListClassMember::const_iterator i = p->listclassmember_->begin() ; i != p->listclassmember_->end() ; ++i)
  {
    if(auto no_init = dynamic_cast<ClassMem*>(*i)) {
      if(iter != 0) {
        addToOutput(", ");
      }
      auto type_name = transform_type_name(*no_init->type_); 
      addToOutput(type_name);
      type_name = trim_if_class(type_name);
      fields[no_init->ident_] = std :: make_pair(type_name, iter);
      iter++;
    }
  }
  addToOutput("\n}\n");
  struct_data[p->ident_1] = fields;
}

void LLVM::prefetchClasses(ClassDefNoInherit *p) {
  ClassDefInherit* cpy = new ClassDefInherit{p->ident_, "", p->listclassmember_->clone()};
  prefetchClasses(cpy);
}

void LLVM::prefetchClasses(EmptyClassDef *p) {
  auto no_members = new ListClassMember();
  ClassDefInherit* cpy = new ClassDefInherit{p->ident_, "", no_members};
  prefetchClasses(cpy);
}

void LLVM::prefetchClasses(EmptyClassDefInherit *p) {
  auto no_members = new ListClassMember();
  ClassDefInherit* cpy = new ClassDefInherit{p->ident_1, p->ident_2, no_members};
  prefetchClasses(cpy);
}


void LLVM::visitClassDefInherit(ClassDefInherit *p) {
  auto fields = struct_data[p->ident_1];
  addToOutput("define void @" + p->ident_1 + "__reset(%" + p->ident_1 + "* %self) {\n");
  for(auto mem : fields) {
    auto ident = mem.first;
    auto type = mem.second.first;
    auto number = mem.second.second;
    auto cl_type = "%" + p->ident_1;
    addToOutput("%i" + to_string(last_var + 1) + " = getelementptr inbounds " + cl_type + ", " + cl_type + "* %self, i32 0, i32 " + to_string(number) +"\n");
    if(type == LLVM_TYPE_INT) 
      addToOutput("store i32 0, i32* %i" + to_string(last_var + 1) + "\n");
    if(type == LLVM_TYPE_BOOL) 
      addToOutput("store i1 0, i1* %i" + to_string(last_var + 1) + "\n");
    if(type == LLVM_TYPE_STRING) {
      addToOutput("%i" + to_string(last_var + 2) + " = bitcast [1 x i8]* @emptyStr to i8*\n");
      addToOutput("store i8* %i" + to_string(last_var + 2) +  ", i8** %i" + to_string(last_var + 1)+ "\n");
      last_var++;
    }
    if(type != LLVM_TYPE_BOOL && type != LLVM_TYPE_INT && type != LLVM_TYPE_STRING) {
      auto real_type = "%" + type + "*";
      addToOutput("store " + real_type + " null, " + real_type +  "* %i" + to_string(last_var + 1) + "\n");
    } 
    last_var++;
  }
  if(p->ident_2 != "") {

    addToOutput("%i" + to_string(last_var + 1) + " = bitcast %" + p->ident_1 + "* %self to %" + p->ident_2 + "*\n");
    addToOutput("call void @" + p->ident_2 + "__reset" + "(%" + p->ident_2 + "* %i" + to_string(last_var + 1) + ")\n");

    // addToOutput("%father" + to_string(last_var + 1) + " = getelementptr inbounds %" + p->ident_1 + ", %" + p->ident_1 + "* %self, i32 0, i32 0\n");

    // addToOutput("%Size" + to_string(last_var + 1) + " = getelementptr %" + p->ident_2 + ", %" + p->ident_2 + "* null, i32 1\n");
    // addToOutput("%Size_" + to_string(last_var + 1) + " = ptrtoint %" + p->ident_2 + "* %Size" + to_string(last_var + 1) + " to i32" + "\n");
    // auto size = "%Size_" + to_string(last_var + 1);
    // addToOutput("%mem" + to_string(last_var + 1) + " = call i8* @malloc(i32 " + size + ")\n");
    // addToOutput("%casted" + to_string(last_var + 1) + " = bitcast i8* %mem" + to_string(last_var + 1) + " to %" + p->ident_2 + "\n");
    // addToOutput("call void @" + p->ident_2 + "__reset" + "(%" + p->ident_2 + " %casted" + to_string(last_var + 1) + ")\n");
    // addToOutput("store %" + p->ident_2 + "* %casted" + to_string(last_var + 1) + ", %" + p->ident_2 + "* %father" + to_string(last_var + 1) + "\n");

    last_var++;
  }

  addToOutput("ret void\n");
  addToOutput("}\n");

  for (ListClassMember::const_iterator i = p->listclassmember_->begin() ; i != p->listclassmember_->end() ; ++i)
  {
    if(auto fun_member = dynamic_cast<ClassFun*>(*i)) {
      auto args = fun_member->listarg_->clone();
      args->insert(args->begin(), new ArgDef{new Class(p->ident_1), "self"});

      auto block = fun_member->block_->clone();
      auto stmts = dynamic_cast<ListStmt*>(block);

      string current_class = p->ident_1;
      while(current_class != "") {
        for(auto mem : struct_data[current_class]) {
          auto ident = mem.first;
          auto type = mem.second.first;
          auto number = mem.second.second;

          if(current_class == p->ident_1)
            addToInject("%" + getCurrentVarNum(ident) + " = getelementptr inbounds %" + current_class + ", %" + current_class + "* %self" + ", i32 0, i32 " + to_string(number) +"\n");
          else 
            addToInject("%" + getCurrentVarNum(ident) + " = getelementptr inbounds %" + current_class + ", %" + current_class + "* %self" + to_string(last_var) + ", i32 0, i32 " + to_string(number) +"\n");

        }
        auto next_class = env_of_classes[current_class].second;

        if(next_class == "")
          break;

        if(current_class == p->ident_1)
          addToInject("%self" + to_string(last_var + 1) + " = bitcast %" + current_class + "* %self to %" + next_class + "*\n");
        else 
          addToInject("%self" + to_string(last_var + 1) + " = bitcast %" + current_class + "* %self" + to_string(last_var) + " to %" + next_class + "*\n");
      
        last_var++;

        current_class = next_class;
      }
      mangle_fn_names = false; 

      string mangled_name = p->ident_1 + "_" + fun_member->ident_;
      FnDef* tmp_fun = new FnDef{fun_member->type_->clone(), mangled_name, args, fun_member->block_->clone()};

      function_data[mangled_name] = make_pair(fun_member->type_, extract_types_from_args(fun_member->listarg_));

      tmp_fun->accept(this);

      mangle_fn_names = true;
    }
  }
}

void LLVM::visitClassDefNoInherit(ClassDefNoInherit *p) {
  ClassDefInherit* cpy = new ClassDefInherit{p->ident_, "", p->listclassmember_->clone()};
  cpy->accept(this);
}

void LLVM::visitEmptyClassDef(EmptyClassDef *p) {
  auto no_members = new ListClassMember();
  ClassDefInherit* cpy = new ClassDefInherit{p->ident_, "", no_members};
  cpy->accept(this);
}

void LLVM::visitEmptyClassDefInherit(EmptyClassDefInherit *p) {
  auto no_members = new ListClassMember();
  ClassDefInherit* cpy = new ClassDefInherit{p->ident_1, p->ident_2, no_members};
  cpy->accept(this);
}



void LLVM::visitClassMember(ClassMember *p) {

}

void LLVM::visitClassMem(ClassMem *p) {

}

void LLVM::visitClassFun(ClassFun *p) {

}

void LLVM::visitListClassMember(ListClassMember *p) {

}


void LLVM::visitIdentExpan(IdentExpan *p) {} /* abstract class */

IdentExpan* unpackBrackets(IdentExpan* p) {
  IdentExpan* exp_inside = p;
    
  while(auto internal = dynamic_cast<IdentExpBracket*>(exp_inside)) 
    exp_inside = internal->identexpan_; 

  return exp_inside;
}

void LLVM::check_for_nulls() {
  was_null_ptr_label_needed = true;
  addToOutput("%testNull" + to_string(last_var + 1) + " = icmp eq %" + current_exp_type + "*  %i" + to_string(last_var) + ", null\n");
  auto labelNotNull = genLabel("IfNotNull");
  
  addToOutput("br i1 %testNull" + to_string(last_var + 1) + ", label %"  + null_ptr_label + ", label %" + labelNotNull + "\n");
  addToOutput("br label %" + labelNotNull + "\n");
  addToOutput(labelNotNull + ":\n");
}

void LLVM::visitIdentExp(IdentExp *p) {
  p->identexpan_->accept(this);
  check_for_nulls();

  string current_class = current_exp_type;
  while(struct_data[current_class].find(p->ident_) == struct_data[current_class].end()) {
    auto next_class = env_of_classes[current_class].second;

    addToOutput("%i" + to_string(last_var + 1) + " = bitcast %" + current_class + "* %i" + to_string(last_var) + " to %" + next_class + "\n");

    current_class = next_class;
    last_var++;
  }
  current_exp_type = current_class;

  auto next_type = struct_data[current_exp_type][p->ident_].first;

  addToOutput("%i" + to_string(last_var + 1) + " = getelementptr inbounds %" + current_exp_type + ", %" + current_exp_type + "* %i" + to_string(last_var) + ", i32 0, i32 " + to_string(struct_data[current_exp_type][p->ident_].second) +"\n");

  addToOutput("%i" + to_string(last_var + 2) + " = load %" + next_type + "*, %" + next_type + "** %i" + to_string(last_var + 1) + "\n");
  last_var += 2;

  current_exp_type = next_type;
  
}

void LLVM::visitIdentExpFun(IdentExpFun *p) {
  p->identexpan_->accept(this);
  check_for_nulls();

  string current_class = current_exp_type;
  while(env_of_classes[current_class].first.find(p->ident_) == env_of_classes[current_class].first.end()) {
    current_class = env_of_classes[current_class].second;
  }
  if(current_exp_type != current_class) {
    addToOutput("%i" + to_string(last_var + 1) + " = bitcast %" + current_exp_type + "* %i" + to_string(last_var) + " to %" + current_class + "*\n");
    last_var++;
  }

  current_exp_type = current_class;
  auto ans = "%i" + to_string(last_var);
  auto fn_name = current_exp_type + "_" + p->ident_;

  vector <string> computed_args;
  for (ListExpr::const_iterator i = p->listexpr_->begin() ; i != p->listexpr_->end() ; ++i)
  {
    computed_args.push_back(processSingle(*i));
  }

  if(!dynamic_cast<Void*>(function_data[fn_name].first)) {
    addToOutput("%i" + to_string(last_var + 1) + " = ");
    last_var++;
  }

  addToOutput("call " + transform_type_name(*function_data[fn_name].first) + " @" + fn_name + "(%" + current_class + "* " + ans);
  vector<Type*> listarg = function_data[fn_name].second;
  for (int i = 0 ; i < listarg.size() ; ++i)
  {
    addToOutput(", ");
    addToOutput(transform_type_name(*listarg[i]) + " " + computed_args[i]);
  }
  addToOutput(")\n");
}



void LLVM::visitIdentExpSimple(IdentExpSimple *p) {
  current_exp_type = p->my_type_;
  addToOutput("%i" + to_string(last_var + 1) + " = load %" + current_exp_type + "*, %" + current_exp_type + "** %" + getCurrentVarNum(p->ident_) + "\n");
  last_var++;
}

void LLVM::visitIdentExpSimpleFun(IdentExpSimpleFun *p) {
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
  addToOutput("call " + transform_type_name(*function_data[p->ident_].first) + " @" + mangle_fn_name(p->ident_) + "(");
  for (int i = 0 ; i < listarg.size() ; ++i)
  {
    if(i > 0) addToOutput(", ");
    addToOutput(transform_type_name(*listarg[i]) + " " + computed_args[i]);
  }
  addToOutput(")\n");
  current_exp_type = trim_if_class(transform_type_name(*function_data[p->ident_].first));
}

void LLVM::visitIdentExpNew(IdentExpNew *p) {
  auto ident = trim_if_class(transform_type_name(*p->type_));
  auto type = "%" + ident + "*";
  auto type_no_star = "%" + ident;

  // This nifty little snippet will compute how much memory i need to alloc for my structures
  addToOutput("%Size" + to_string(last_var + 1) + " = getelementptr " + type_no_star + ", " + type + " null, i32 1\n");
  addToOutput("%Size_" + to_string(last_var + 1) + " = ptrtoint " + type + " %Size" + to_string(last_var + 1) + " to i32" + "\n");

  auto size = "%Size_" + to_string(last_var + 1);

  addToOutput("%i" + to_string(last_var + 1) + " = call i8* @malloc(i32 " + size + ")\n");
  addToOutput("%i" + to_string(last_var + 2) + " = bitcast i8* %i" + to_string(last_var + 1) + " to " + type + "\n");
  addToOutput("call void @" + ident + "__reset" + "(" + type + " %i" + to_string(last_var + 2) + ")\n");

  current_exp_type = ident;
  last_var += 2;
}

void LLVM::visitIdentExpNull(IdentExpNull *p) {
  current_exp_type = trim_if_class(transform_type_name(*p->type_));
  // TODO
}
void LLVM::visitIdentExpBracket(IdentExpBracket *p) {
  p->identexpan_->accept(this);
}



void LLVM::visitListTopDef(ListTopDef *listtopdef)
{
  addToOutput("@emptyStr = internal constant [1 x i8] c\"\\00\"\n");
  addToOutput("declare void @free(i8*)\n");
  addToOutput("declare i8* @concat(i8*, i8*)\n");
  addToOutput("declare i8* @malloc(i32)\n");
  addToOutput("declare void @fail_null_ptr()\n");
  addToOutput("declare i32 @compare_strings(i8* %s1, i8* %s2)\n");

  addToOutput("declare void @error()\n");
  addToOutput("declare void @printInt(i32 %x)\n");
  addToOutput("declare void @printString(i8* %s)\n");
  addToOutput("declare i32 @readInt()\n");
  addToOutput("declare i8* @readString()\n");

  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i) {
    if(auto fn_def = dynamic_cast<FnDef*>(*i)) {
      function_data[fn_def->ident_] = make_pair(fn_def->type_, extract_types_from_args(fn_def->listarg_));
    }
    if(auto new_class = dynamic_cast<ClassDefNoInherit*>(*i)) 
      prefetchClasses(new_class);
    if(auto new_class = dynamic_cast<ClassDefInherit*>(*i)) 
      prefetchClasses(new_class);
    if(auto new_class = dynamic_cast<EmptyClassDef*>(*i)) 
      prefetchClasses(new_class);
    if(auto new_class = dynamic_cast<EmptyClassDefInherit*>(*i)) 
      prefetchClasses(new_class);
  }

  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i) {
    if(auto new_class = dynamic_cast<ClassDefNoInherit*>(*i)) 
      new_class->accept(this);
    if(auto new_class = dynamic_cast<ClassDefInherit*>(*i)) 
      new_class->accept(this);
    if(auto new_class = dynamic_cast<EmptyClassDef*>(*i)) 
      new_class->accept(this);
    if(auto new_class = dynamic_cast<EmptyClassDefInherit*>(*i)) 
      new_class->accept(this);
  }

  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    if(!dynamic_cast<ClassDefNoInherit*>(*i) && !dynamic_cast<ClassDefInherit*>(*i) && !dynamic_cast<EmptyClassDef*>(*i) && !dynamic_cast<EmptyClassDefInherit*>(*i)) 
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
    run_with_rollback(p->liststmt_);
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
        continue;
      }
      if(dynamic_cast<Bool*>(p->type_)) {
        addToOutput("%" + getCurrentVarNum(no_init->ident_) + " = alloca i1\n");
        addToOutput("store i1 0, i1* %" + getCurrentVarNum(no_init->ident_) + "\n");
        continue;
      }
      if(dynamic_cast<Str*>(p->type_)) {
        addToOutput("%" + getCurrentVarNum(no_init->ident_) + " = alloca i8*\n");
        addToOutput("%i" + to_string(last_var + 1) + " = bitcast [1 x i8]* @emptyStr to i8*\n");
        addToOutput("store i8* %i" + to_string(last_var + 1) +  ", i8** %" + getCurrentVarNum(no_init->ident_) + "\n");
        last_var++;
        continue;
      }
      auto type = transform_type_name(*p->type_);
      addToOutput("%" + getCurrentVarNum(no_init->ident_) + " = alloca " + type + "\n");
      addToOutput("store " + type + " null, " + type +  "* %" + getCurrentVarNum(no_init->ident_) + "\n");
      last_var++;
      
    }
    if(auto init = dynamic_cast<Init*>(*i)) {
      auto ans = processSingle(init->expr_);
      auto type = cpp_to_llvm_types(init->expr_->expr_type_); 

      current_var_number[init->ident_] = last_var_numbers[init->ident_] + 1;
      last_var_numbers[init->ident_] += 1;
      addToOutput("%" + getCurrentVarNum(init->ident_) + " = alloca " + type + "\n");
      addToOutput("store " + type + " " + ans + ", " + type + "* %" + getCurrentVarNum(init->ident_) + "\n");
    }
  }

}

String LLVM::processSingle(Expr* expr) {
  String ans = "";
  if(auto stmt = dynamic_cast<ELitInt*>(expr)) {
    ans = to_string(stmt->integer_);
    return ans;
  } 
  if(dynamic_cast<ELitTrue*>(expr)) {
    ans = "1";
    return ans;
  }
  if(dynamic_cast<ELitFalse*>(expr)) {
    ans = "0";
    return ans;
  } 
  if(auto casted = dynamic_cast<EVar*>(expr)) {
    IdentExpan* exp_inside = unpackBrackets(casted->identexpan_); 

    if(dynamic_cast<IdentExpNull*>(exp_inside)) {
      ans = "null";
      return ans;
    } 
  }
  
  expr->accept(this);
  // if(auto stmt = dynamic_cast<EVar*>(expr)) {
  //   ans = "%i" + to_string(last_var);
  // } 
  // if(ans == "") {
    ans = "%i" + to_string(last_var);
  // }
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

  auto identexpan = unpackBrackets(p->identexpan_);

  if(auto ident = dynamic_cast<IdentExpSimple*>(identexpan)) { 
    if(trim_if_class(type) != ident->my_type_) {
      go_upward_in_inheritance(trim_if_class(type), ident->my_type_, ans);
      ans = "%i" + to_string(last_var);
    }
    addToOutput("store %" + ident->my_type_ + "* " + ans + ", %" + ident->my_type_ + "** %" + getCurrentVarNum(*p->identexpan_) + "\n");
  }
  else {
    identexpan->accept(this);
    // p->identexpan_->accept(this);
    deleteLastLine();
    addToOutput("store " + type + " " + ans + ", " + type + "* %i" + to_string(last_var) + "\n");
  }
}

void LLVM::visitIncr(Incr *p)
{
  auto var_clone = new EVar{p->identexpan_->clone()};
  var_clone->expr_type_ = "int";

  auto add = new EAdd{
    var_clone,
    new Plus{},
    new ELitInt{1}
  };
  add->expr_type_ = "int";

  auto tmp = new Ass{
    p->identexpan_->clone(),
    add 
  };
  tmp->accept(this);

}

void LLVM::visitDecr(Decr *p)
{
  auto var_clone = new EVar{p->identexpan_->clone()};
  var_clone->expr_type_ = "int";

  auto add = new EAdd{
    var_clone,
    new Minus{},
    new ELitInt{1}
  };
  add->expr_type_ = "int";

  auto tmp = new Ass{
    p->identexpan_->clone(),
    add 
  };
  tmp->accept(this);
}

void LLVM::visitRet(Ret *p)
{
  auto ans = processSingle(p->expr_);
  string current_class = trim_if_class(cpp_to_llvm_types(p->expr_->expr_type_));
  if(current_class != current_expected_return) {
    go_upward_in_inheritance(current_class, current_expected_return, ans);
    addToOutput("ret %" + current_expected_return + "* %i" + to_string(last_var) + "\n");
  }
  else {
    addToOutput("ret " + cpp_to_llvm_types(p->expr_->expr_type_) + " " + ans + "\n");
  }

  skipping_instructions = true;
}

void LLVM::visitVRet(VRet *p)
{
  addToOutput("ret void\n");
  skipping_instructions = true;
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

void LLVM::visitClass(Class *p)
{
}

void LLVM::visitFun(Fun *p)
{
}

void LLVM::visitListType(ListType *listtype)
{
}

void LLVM::visitExpr(Expr *p) {} //abstract class

void LLVM::visitEVar(EVar *p)
{
  auto type = cpp_to_llvm_types(p->expr_type_);
  auto identexpan = unpackBrackets(p->identexpan_);

  if(dynamic_cast<IdentExpSimple*>(identexpan)) {
    addToOutput("%i" + to_string(last_var + 1) + " = load " + type + ", " + type + "* %" + getCurrentVarNum(*identexpan) + "\n");
    last_var++;
    return;
  } 
  if(dynamic_cast<IdentExp*>(identexpan)) {
    identexpan->accept(this);
    deleteLastLine();

    addToOutput("%i" + to_string(last_var + 1) + " = load " + type + ", " + type + "* %i" + to_string(last_var) + "\n");
    last_var++; 
    return;
  }
  identexpan->accept(this);
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

void LLVM::visitEString(EString *p)
{
  addConstant(p->string_);
  
  int text_size = p->string_.size();
  string arr_type = "[" + to_string(text_size + 1) + " x i8]";
  
  addToOutput("%i" + to_string(last_var + 1) + " = bitcast " + arr_type + "* @s" + to_string(last_var + 1) + " to i8*\n");
  last_var++;
}


void LLVM::visitNeg(Neg *p)
{
  auto ans = processSingle(p->expr_);
  addToOutput("%i" + to_string(last_var + 1) + " = mul i32 " + ans + ", -1\n");
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
    if(cpp_to_llvm_types(p->expr_1->expr_type_) == LLVM_TYPE_STRING) {
      string new_malloced_thing = "%i" + to_string(last_var + 1);
      addToOutput(new_malloced_thing + " = call i8* @concat(i8* " + s1 + ", i8* " + s2 + ")\n");
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
  auto type1 = cpp_to_llvm_types(p->expr_1->expr_type_), type2 = cpp_to_llvm_types(p->expr_2->expr_type_);

  if(type1 != type2) {
    if(test_ancestership(type1, type2, env_of_classes)) {
      swap(s1, s2);
      swap(type1, type2);
    }
    // Now we have type2 as the son and type1 as the father
    go_upward_in_inheritance(trim_if_class(type1), trim_if_class(type2), s1);
    s1 = "%i" + to_string(last_var);
  }
  
  string prologue = "%i" + to_string(last_var + 1);
  string epilogue = type2 + " " + s1 + ", " + s2 + "\n";
  if(type1 == LLVM_TYPE_STRING) {
    addToOutput("%i_cmp" + to_string(last_var + 1) + " = call i32 @compare_strings(i8* " + s1 + ", i8* " + s2 + ")\n");
    epilogue = "i32 %i_cmp" + to_string(last_var + 1) + ", 0\n"; 
  }
  if(dynamic_cast<LTH*>(p->relop_))
    addToOutput(prologue + " = icmp slt " + epilogue);
  if(dynamic_cast<LE*>(p->relop_))
    addToOutput(prologue + " = icmp sle " + epilogue);
  if(dynamic_cast<GTH*>(p->relop_))
    addToOutput(prologue + " = icmp sgt " + epilogue);
  if(dynamic_cast<GE*>(p->relop_))
    addToOutput(prologue + " = icmp sge " + epilogue);
  if(dynamic_cast<EQU*>(p->relop_))
    addToOutput(prologue + " = icmp eq " + epilogue);
  if(dynamic_cast<NE*>(p->relop_))
    addToOutput(prologue + " = icmp ne " + epilogue);

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