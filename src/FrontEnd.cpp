/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include <iostream>
#include <memory>
#include <variant>
#include <map>
#include <set>
#include <algorithm>
#include "FrontEnd.H"

using std :: cerr;
using std :: vector;
using std :: string;
using std :: set;
using std :: map;
using std :: to_string;


TYPE get_type(Type* val) {
  if(dynamic_cast<Int*>(val))
    return "int";
  if(dynamic_cast<Str*>(val))
    return "string";
  if(dynamic_cast<Bool*>(val))
    return "bool";
  if(dynamic_cast<Void*>(val))
    return "void";
  if(auto str = dynamic_cast<Struct*>(val))
    return str->ident_;
  
  return "NULL";
}

bool is_a_valid_type(Type* val, StructEnv &str_env) {
  TYPE type = get_type(val);
  
  if(type == TYPE_VOID || type == TYPE_BOOLEAN || type == TYPE_STRING || type == TYPE_INT || str_env.find(type) != str_env.end()) 
    return true;
  return false;
}

void fail(string msg, Visitable* v) {
  throw front_end_exception(msg, v);
}

void check_for_existence(Ident &ident, VarEnv *env_of_vars, Visitable* v) {
  if(env_of_vars->find(ident) == env_of_vars->end())
    fail("variable " + ident + " is not defined\n", v);
}

void check_for_existence(Ident &ident, FunEnv *env_of_functions, Visitable* v) {
  if(env_of_functions->find(ident) == env_of_functions->end())
    fail("function " + ident + " is not defined\n", v);
}

void check_for_type_matching(TYPE type1, TYPE type2, Visitable *v) {
  if(type1 != type2) 
    fail("got type " + type2 + " but expected " + type1 + "\n", v);
}

void same_scope_redefinition(Ident ident, std:: set<Ident> *defined_in_current_scope, Visitable* v) {
  if(defined_in_current_scope->find(ident) != defined_in_current_scope->end())
    fail("variable " + ident + " got redefined in this same scope\n", v);
}


StaticAnalyzer::StaticAnalyzer(void)
{
}

StaticAnalyzer::~StaticAnalyzer(void)
{
}

void StaticAnalyzer::analyze(Visitable *v)
{
  v->accept(this);
}

void StaticAnalyzer::visitProgram(Program *p) {} //abstract class

void StaticAnalyzer::visitProgramDef(ProgramDef *p)
{
  if(p->listtopdef_) {
    p->listtopdef_->accept(this);
  }
}

void StaticAnalyzer::visitTopDef(TopDef *p) {} //abstract class

void StaticAnalyzer::visitFnDef(FnDef *p)
{
  vector <TYPE> arg_types;
  vector <Ident> arg_names;
  for(int i = 0 ; i < p->listarg_->size(); i++) {
    if(auto arg = dynamic_cast<ArgDef*>((*(p->listarg_))[i])) {
      if(get_type(arg->type_) == TYPE_VOID)
        fail("function can't have void as an argument\n", arg);
      if(std::find(arg_names.begin(), arg_names.end(), arg->ident_) != arg_names.end()) 
        fail("variable " + arg->ident_ + " is duplicated in signature" ,arg);

      arg_types.push_back(get_type(arg->type_));
      arg_names.push_back(arg->ident_);
    }
  }

  auto tmp_env_of_vars = env_of_vars;

  for(int i = 0; i < arg_names.size(); i++) {
    env_of_vars[arg_names[i]] = arg_types[i];
  }  
  expected_return_type = get_type(p->type_);

  p->block_->accept(this);
  if(last_return != get_type(p->type_)) 
    fail("function returned " + last_return + " but should return " + get_type(p->type_) + "\n", p);

  //We need to clear out our env from our vars
  last_return = TYPE_VOID;
  env_of_vars = tmp_env_of_vars;
}

void StaticAnalyzer::visitStructDef(StructDef *p) {
  if(p->ident_ == TYPE_INT || p->ident_ == TYPE_VOID || p->ident_ == TYPE_BOOLEAN || p->ident_ == TYPE_STRING) {
    fail("you can't have " + p->ident_ + " as a struct name\n", p);
  }
  set <Ident> present_args;

  for(int i = 0; i < p->liststructmember_->size(); i++) {
    auto member = ((*(p->liststructmember_))[i]);
    if(auto no_init_member = dynamic_cast<StructMemNoInit*>(member)) {
      if(get_type(no_init_member->type_) == TYPE_VOID)
        fail("struct can't have TYPE_VOID as an attribute\n",no_init_member);
      if(!is_a_valid_type(no_init_member->type_, env_of_structures)) 
        fail(get_type(no_init_member->type_) + " does not name a valid type\n", no_init_member);

      if(present_args.find(no_init_member->ident_) != present_args.end()) 
        fail("member" + no_init_member->ident_ + " was already present\n", no_init_member);
      present_args.insert(no_init_member->ident_);
    }
    
    if(auto init_member = dynamic_cast<StructMemInit*>(member)) {
      if(get_type(init_member->type_) == TYPE_VOID)
        fail("struct can't have TYPE_VOID as an attribute\n", init_member);
      if(!is_a_valid_type(init_member->type_, env_of_structures)) 
        fail(get_type(init_member->type_) + " does not name a valid type\n", init_member);

      init_member->expr_->accept(this);
      check_for_type_matching(get_type(init_member->type_), last_evaluated_expr, init_member);

      if(present_args.find(init_member->ident_) != present_args.end()) 
        fail("member" + init_member->ident_ + " was already present\n", init_member);
      present_args.insert(init_member->ident_);
    }
  }
}

void StaticAnalyzer::visitStructMember(StructMember *p) {} //abstract class

void StaticAnalyzer::visitStructMemNoInit(StructMemNoInit *p)
{
}

void StaticAnalyzer::visitStructMemInit(StructMemInit *p)
{
}

void StaticAnalyzer::visitListStructMember(ListStructMember *liststructmember)
{
}

void StaticAnalyzer::visitIdentExpan(IdentExpan *p) {} /* abstract class */

void StaticAnalyzer::visitIdentExp(IdentExp *p) {
  if(p->identexpan_)
    p->identexpan_->accept(this);
  
  if(env_of_structures[last_evaluated_expr].find(p->ident_) == env_of_structures[last_evaluated_expr].end()) 
    fail(last_evaluated_expr + " does not have " + p->ident_ + " as a member\n", p);
  
  last_evaluated_expr = env_of_structures[last_evaluated_expr][p->ident_];
}

void StaticAnalyzer::visitIdentExpSimple(IdentExpSimple *p) {
  check_for_existence(p->ident_, &env_of_vars, p);
  last_evaluated_expr = env_of_vars[p->ident_];
  last_evaluated_expr_value = DECOY;
}



void StaticAnalyzer::visitListTopDef(ListTopDef *listtopdef)
{
  bool was_there_main = false;
  vector <TYPE> single_int(1, TYPE_INT);
  env_of_functions["printInt"] = make_pair(single_int, TYPE_VOID);
  vector <TYPE> single_string(1, TYPE_STRING);
  env_of_functions["printString"] = make_pair(single_string, TYPE_VOID);
  vector <TYPE> empty_vec;
  env_of_functions["readInt"] = make_pair(empty_vec, TYPE_INT);
  env_of_functions["readString"] = make_pair(empty_vec, TYPE_STRING);
  env_of_functions["error"] = make_pair(empty_vec, TYPE_VOID);

  //We need to gather all signatures BEFORE checking for correctness
  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    if(auto fn_def = dynamic_cast<FnDef*>(*i)) {
      if(fn_def->ident_ == "main" && get_type(fn_def->type_) == TYPE_INT && fn_def->listarg_->size() == 0) {
        was_there_main = true;
      }
      vector <TYPE> arg_types;
      for(int j = 0 ; j < fn_def->listarg_->size(); j++)
        if(auto arg = dynamic_cast<ArgDef*>((*(fn_def->listarg_))[j]))
          arg_types.push_back(get_type(arg->type_));

      if(env_of_functions.find(fn_def->ident_) != env_of_functions.end())
        fail("function with name " + fn_def->ident_ + " already exists\n", fn_def);

      env_of_functions[fn_def->ident_] = make_pair(arg_types, get_type(fn_def->type_));
    }
    if(auto struct_def = dynamic_cast<StructDef*>(*i)) {
      std :: map <Ident, TYPE> members;
      auto items = struct_def->liststructmember_;
      for(auto item : *items) {
        if(auto member = dynamic_cast<StructMemNoInit*>(item))
          members[member->ident_] = get_type(member->type_);
        if(auto member = dynamic_cast<StructMemInit*>(item))
          members[member->ident_] = get_type(member->type_);
      }

      if(env_of_structures.find(struct_def->ident_) != env_of_structures.end())
        fail("struct was defined before\n", struct_def);
      env_of_structures[struct_def->ident_] = members;
    }
  }
  
  if(!was_there_main) {
    cerr << "ERROR\nNo function main present\n";
    exit(-1);
  }

  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void StaticAnalyzer::visitArg(Arg *p) {} //abstract class

void StaticAnalyzer::visitArgDef(ArgDef *p)
{
}

void StaticAnalyzer::visitListArg(ListArg *listarg)
{
}

void StaticAnalyzer::visitBlock(Block *p) {} //abstract class

void StaticAnalyzer::visitBlockDef(BlockDef *p)
{
  if(p->liststmt_) {
    run_with_rollback(p->liststmt_);
  }
}

void StaticAnalyzer::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void StaticAnalyzer::visitStmt(Stmt *p) {} //abstract class

void StaticAnalyzer::visitEmpty(Empty *p)
{
  last_evaluated_expr = TYPE_VOID;
  last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::run_with_rollback(Visitable* v) {
  auto curr_env_of_vars = env_of_vars;
  auto curr_env_of_functions = env_of_functions;
  auto curr_defined_in_current_scope = defined_in_current_scope;
  auto curr_last_evaluated_expr = last_evaluated_expr;
  auto curr_expected_return_type = expected_return_type;
  defined_in_current_scope.clear();

  v->accept(this);

  env_of_vars = curr_env_of_vars;
  env_of_functions = curr_env_of_functions;
  defined_in_current_scope = curr_defined_in_current_scope;
  last_evaluated_expr = curr_last_evaluated_expr;
  expected_return_type = curr_expected_return_type;
}

void StaticAnalyzer::visitBStmt(BStmt *p)
{
  p->block_->accept(this);
}

void StaticAnalyzer::visitDecl(Decl *p)
{
  if(get_type(p->type_) == TYPE_VOID) 
    fail("can't have void as a variable type\n", p);

  if(!is_a_valid_type(p->type_, env_of_structures))
    fail(get_type(p->type_) + " was not recognized as a valid type\n", p);


  if(p->listitem_) {
    for (ListItem::const_iterator i = p->listitem_->begin() ; i != p->listitem_->end() ; ++i) {
      if(auto init = dynamic_cast<NoInit*>(*i)) {
        same_scope_redefinition(init->ident_, &defined_in_current_scope, init);
        defined_in_current_scope.insert(init->ident_);
        env_of_vars[init->ident_] = get_type(p->type_);
      }
      if(auto init = dynamic_cast<Init*>(*i)) {
        same_scope_redefinition(init->ident_, &defined_in_current_scope, init);
        
        init->expr_->accept(this);
        check_for_type_matching(get_type(p->type_), last_evaluated_expr, init);
        defined_in_current_scope.insert(init->ident_);
        env_of_vars[init->ident_] = get_type(p->type_);
      }
      if(auto init = dynamic_cast<InitStruct*>(*i)) {
        same_scope_redefinition(init->ident_1, &defined_in_current_scope, init);
        
        if(get_type(p->type_) != init->ident_2) 
          fail("LINE " + to_string(init->line_number) + " : " + init->ident_1 + " was declared as a " + get_type(p->type_) + " but was assigned a new " + init->ident_2 + "\n", init);
        
        defined_in_current_scope.insert(init->ident_1);
        env_of_vars[init->ident_1] = get_type(p->type_);
      }
    }
  }
}

void StaticAnalyzer::visitNewStruct(NewStruct *p) {
  // Here identexpan_ is a id of a variable
  // And indent_ is a name of the struct
  p->identexpan_->accept(this);
  check_for_type_matching(p->ident_, last_evaluated_expr, p);
}


void StaticAnalyzer::visitAss(Ass *p)
{
  p->identexpan_->accept(this);
  auto var_type = last_evaluated_expr;
  p->expr_->accept(this);
  check_for_type_matching(var_type, last_evaluated_expr, p);
}

void StaticAnalyzer::visitIncr(Incr *p)
{
  p->identexpan_->accept(this);
  check_for_type_matching(TYPE_INT, last_evaluated_expr, p);
}

void StaticAnalyzer::visitDecr(Decr *p)
{
  p->identexpan_->accept(this);
  check_for_type_matching(TYPE_INT, last_evaluated_expr, p);
}

void StaticAnalyzer::visitRet(Ret *p)
{
  p->expr_->accept(this);
  
  check_for_type_matching(expected_return_type, last_evaluated_expr, p);

  last_return = last_evaluated_expr;

  if(last_return == TYPE_VOID)
    fail("you can't return void that way\n", p);
}

void StaticAnalyzer::visitVRet(VRet *p)
{
  last_return = TYPE_VOID;
  if(last_return != expected_return_type) 
    fail("function returns " + last_return + " but it expects " + expected_return_type + " type\n", p);
}

void StaticAnalyzer::visitCond(Cond *p)
{
  p->expr_->accept(this);

  if(last_evaluated_expr != TYPE_BOOLEAN) 
    fail("if must have condition of type bool\n", p);

  auto cond_value = last_evaluated_expr_value;
  auto ret_tmp = last_return;
  p->stmt_->accept(this);

  if(auto val = std::get_if<bool>(&cond_value)) { {
    if((*val) == true) {
      // This means that we are statically sure we're entering the IF branch
      // So if there was a return(in the IF) and there was no return before then this is a valid code 
    }
    else {
      last_return = ret_tmp;
    }
  }
  } else {
    last_return = ret_tmp;
  }
  
}


void StaticAnalyzer::visitCondElse(CondElse *p)
{
  p->expr_->accept(this);
  if(last_evaluated_expr != TYPE_BOOLEAN)
    fail("if else must have condition of type TYPE_BOOLEAN\n", p);

  auto cond_value = last_evaluated_expr_value;
  auto ret_before_all_operations = last_return;

  last_return = TYPE_VOID;
  p->stmt_1->accept(this);
  TYPE ret1 = last_return;
  last_return = TYPE_VOID;
  p->stmt_2->accept(this);
  TYPE ret2 = last_return;

  if(ret1 != ret2) {
    last_return = ret_before_all_operations;
  }
  if(auto val = std::get_if<bool>(&cond_value)) {
    if((*val) == true) {
      last_return = ret1;
    }
    else {
      last_return = ret2;
    }
  }
}

void StaticAnalyzer::visitWhile(While *p)
{
  p->expr_->accept(this);
  if(last_evaluated_expr != TYPE_BOOLEAN) 
    fail("while must have condition of type TYPE_BOOLEAN\n", p);

  auto cond_value = last_evaluated_expr_value;
  auto ret_tmp = last_return;
  p->stmt_->accept(this);

  if(auto val = std::get_if<bool>(&cond_value)) {
    if((*val) == true) {
      // This means that we are statically sure we're entering the WHILE loop
      // So if there was a return and there was no return before then this is a
      // valid code 
    }
    else {
      last_return = ret_tmp;
    }
  } else {
    last_return = ret_tmp;
  }

}

void StaticAnalyzer::visitSExp(SExp *p)
{
  p->expr_->accept(this);
}

void StaticAnalyzer::visitItem(Item *p) {} //abstract class

void StaticAnalyzer::visitNoInit(NoInit *p)
{  
}

void StaticAnalyzer::visitInitStruct(InitStruct *p) {

}

void StaticAnalyzer::visitInit(Init *p)
{
}

void StaticAnalyzer::visitListItem(ListItem *listitem)
{
}

void StaticAnalyzer::visitType(Type *p) {} //abstract class

void StaticAnalyzer::visitInt(Int *p)
{
}

void StaticAnalyzer::visitStr(Str *p)
{
}

void StaticAnalyzer::visitBool(Bool *p)
{
}

void StaticAnalyzer::visitVoid(Void *p)
{
}

void StaticAnalyzer::visitStruct(Struct *p)
{
}

void StaticAnalyzer::visitFun(Fun *p)
{
}

void StaticAnalyzer::visitListType(ListType *listtype)
{
}

void StaticAnalyzer::visitExpr(Expr *p) {} //abstract class

void StaticAnalyzer::visitENullCast(ENullCast *p) {
  last_evaluated_expr = get_type(p->type_);
  last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitEVar(EVar *p)
{
  p->identexpan_->accept(this);
  last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitELitInt(ELitInt *p)
{
  last_evaluated_expr = TYPE_INT;
  last_evaluated_expr_value = p->integer_;
}

void StaticAnalyzer::visitELitTrue(ELitTrue *p)
{
  last_evaluated_expr = TYPE_BOOLEAN;
  last_evaluated_expr_value = true;
}

void StaticAnalyzer::visitELitFalse(ELitFalse *p)
{
  last_evaluated_expr = TYPE_BOOLEAN;
  last_evaluated_expr_value = false;
}

void StaticAnalyzer::visitEApp(EApp *p)
{
  check_for_existence(p->ident_, &env_of_functions, p);
  auto expected_arg_types = env_of_functions[p->ident_].first;
  if(p->listexpr_->size() != expected_arg_types.size()) 
    fail("function " + p->ident_ + " was supplied " + to_string(p->listexpr_->size()) + " arguments but needed " + to_string(expected_arg_types.size()) + "\n", p);

  for(int i = 0; i < p->listexpr_->size(); i++) {
    (*(p->listexpr_))[i]->accept(this);
    check_for_type_matching(expected_arg_types[i], last_evaluated_expr, p);
  }
  last_evaluated_expr = env_of_functions[p->ident_].second;
  last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitEString(EString *p)
{
  last_evaluated_expr = TYPE_STRING;
  last_evaluated_expr_value = p->string_;
}

void StaticAnalyzer::visitNeg(Neg *p)
{
  p->expr_->accept(this);
  check_for_type_matching(TYPE_INT, last_evaluated_expr, p);
  if(auto val = std::get_if<int>(&last_evaluated_expr_value))
    last_evaluated_expr_value = -(*val);
  else 
    last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitNot(Not *p)
{
  p->expr_->accept(this);
  check_for_type_matching(TYPE_BOOLEAN, last_evaluated_expr, p);
  if(auto val = std::get_if<bool>(&last_evaluated_expr_value))
    last_evaluated_expr_value = !(*val);
  else 
    last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitEMul(EMul *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(TYPE_INT, last_evaluated_expr, p);
  auto i1 = last_evaluated_expr_value;
  p->expr_2->accept(this);
  check_for_type_matching(TYPE_INT, last_evaluated_expr, p);
  auto i2 = last_evaluated_expr_value;

  last_evaluated_expr_value = DECOY;
  if(auto val1 = std::get_if<int>(&i1)) 
    if(auto val2 = std::get_if<int>(&i2)) { 
      if(dynamic_cast<Times*>(p->mulop_))
        last_evaluated_expr_value = (*val1) * (*val2);
      if(dynamic_cast<Mod*>(p->mulop_)) {
        if(*val2 == 0)
          fail("you can't mod by 0\n", p);
        last_evaluated_expr_value = (*val1) % (*val2);
      }
      if(dynamic_cast<Div*>(p->mulop_)) {
        if(*val2 == 0)
          fail("you can't divide by 0\n", p);
        last_evaluated_expr_value = (*val1) / (*val2);
      }
    }
}

void StaticAnalyzer::visitEAdd(EAdd *p)
{
  p->expr_1->accept(this);
  auto v1 = last_evaluated_expr_value;
  auto exp1 = last_evaluated_expr;

  p->expr_2->accept(this);
  auto v2 = last_evaluated_expr_value;
  auto exp2 = last_evaluated_expr;

  if(exp1 != exp2) 
    fail("you can only add/substract expressions of the same type.\n", p);

  if(exp1 != TYPE_INT && exp1 != TYPE_STRING) {
    fail("this operation is not allowed for " + exp1 + " and " + exp2 + "\n", p);
  }

  last_evaluated_expr_value = DECOY;
  if(auto val1 = std::get_if<int>(&v1)) 
    if(auto val2 = std::get_if<int>(&v2)) { 
      if(dynamic_cast<Plus*>(p->addop_))
        last_evaluated_expr_value = (*val1) + (*val2);
      else 
        last_evaluated_expr_value = (*val1) - (*val2);
    }

  if(auto val1 = std::get_if<string>(&v1)) 
    if(auto val2 = std::get_if<string>(&v2)) {
      if(dynamic_cast<Plus*>(p->addop_)) 
        last_evaluated_expr_value = (*val1) + (*val2);
      else 
        fail("you can't substract strings.\n", p); 
    }
  
  
}

void StaticAnalyzer::visitERel(ERel *p)
{
  p->expr_1->accept(this);
  TYPE type1 = last_evaluated_expr;
  auto v1 = last_evaluated_expr_value;

  p->expr_2->accept(this);
  TYPE type2 = last_evaluated_expr;
  auto v2 = last_evaluated_expr_value;

  last_evaluated_expr = TYPE_BOOLEAN;
  last_evaluated_expr_value = DECOY;

  if(type1 != type2 || type1 == TYPE_VOID) 
    fail("cannot compare " + type1 + " and " + type2 + "\n", p);

  if(type1 == TYPE_BOOLEAN) {
    if(!(dynamic_cast<EQU*>(p->relop_) || dynamic_cast<NE*>(p->relop_)))
      fail("this operation is not allowed for " + type1 + "\n", p);
      
    if(auto b1 = std::get_if<bool>(&v1)) 
      if(auto b2 = std::get_if<bool>(&v2)) {
        if(dynamic_cast<EQU*>(p->relop_)) 
          last_evaluated_expr_value = ((*b1) == (*b2));
        if(dynamic_cast<NE*>(p->relop_)) 
          last_evaluated_expr_value = ((*b1) != (*b2));
    }
    return;
  }
  if(type1 == TYPE_INT) {
    if(auto i1 = std::get_if<int>(&v1)) 
      if(auto i2 = std::get_if<int>(&v2)) {
        if(dynamic_cast<LTH*>(p->relop_))
          last_evaluated_expr_value = (*i1 < *i2);    
        if(dynamic_cast<LE*>(p->relop_))
          last_evaluated_expr_value = (*i1 <= *i2);    
        if(dynamic_cast<GTH*>(p->relop_))
          last_evaluated_expr_value = (*i1 > *i2);    
        if(dynamic_cast<GE*>(p->relop_))
          last_evaluated_expr_value = (*i1 >= *i2);    
        if(dynamic_cast<EQU*>(p->relop_))
          last_evaluated_expr_value = (*i1 == *i2);
        if(dynamic_cast<NE*>(p->relop_))
          last_evaluated_expr_value = (*i1 != *i2);    
    }
    return;
  }
  if(type1 == TYPE_STRING) {
    if(auto s1 = std::get_if<string>(&v1)) 
      if(auto s2 = std::get_if<string>(&v2)) {
        if(dynamic_cast<LTH*>(p->relop_))
          last_evaluated_expr_value = (*s1 < *s2);    
        if(dynamic_cast<LE*>(p->relop_))
          last_evaluated_expr_value = (*s1 <= *s2);    
        if(dynamic_cast<GTH*>(p->relop_))
          last_evaluated_expr_value = (*s1 > *s2);    
        if(dynamic_cast<GE*>(p->relop_))
          last_evaluated_expr_value = (*s1 >= *s2);    
        if(dynamic_cast<EQU*>(p->relop_))
          last_evaluated_expr_value = (*s1 == *s2);
        if(dynamic_cast<NE*>(p->relop_))
          last_evaluated_expr_value = (*s1 != *s2);    
    }
    return;
  }
  // If we are here that means that have a custom struct
  if(!(dynamic_cast<EQU*>(p->relop_) || dynamic_cast<NE*>(p->relop_))) 
    fail("you can only == and != for type " + type1 + "\n", p);
}

void StaticAnalyzer::visitEAnd(EAnd *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(TYPE_BOOLEAN, last_evaluated_expr, p);
  auto v1 = last_evaluated_expr_value;
  p->expr_2->accept(this);
  check_for_type_matching(TYPE_BOOLEAN, last_evaluated_expr, p);
  auto v2 = last_evaluated_expr_value;
  last_evaluated_expr = TYPE_BOOLEAN;

  last_evaluated_expr_value = DECOY;
  if(auto val1 = std::get_if<bool>(&v1)) 
    if(auto val2 = std::get_if<bool>(&v2)) 
      last_evaluated_expr_value = *val1 && *val2;

}

void StaticAnalyzer::visitEOr(EOr *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(TYPE_BOOLEAN, last_evaluated_expr, p);
  auto v1 = last_evaluated_expr_value;
  p->expr_2->accept(this);
  check_for_type_matching(TYPE_BOOLEAN, last_evaluated_expr, p);
  auto v2 = last_evaluated_expr_value;
  last_evaluated_expr = TYPE_BOOLEAN;


  last_evaluated_expr_value = DECOY;
  if(auto val1 = std::get_if<bool>(&v1)) 
    if(auto val2 = std::get_if<bool>(&v2)) 
      last_evaluated_expr_value = *val1 || *val2;

}

void StaticAnalyzer::visitListExpr(ListExpr *listexpr)
{
}

void StaticAnalyzer::visitAddOp(AddOp *p) {} //abstract class

void StaticAnalyzer::visitPlus(Plus *p) {}

void StaticAnalyzer::visitMinus(Minus *p) {}

void StaticAnalyzer::visitMulOp(MulOp *p) {} //abstract class

void StaticAnalyzer::visitTimes(Times *p) {}

void StaticAnalyzer::visitDiv(Div *p) {}

void StaticAnalyzer::visitMod(Mod *p) {}

void StaticAnalyzer::visitRelOp(RelOp *p) {} //abstract class

void StaticAnalyzer::visitLTH(LTH *p) {}

void StaticAnalyzer::visitLE(LE *p) {}

void StaticAnalyzer::visitGTH(GTH *p) {}

void StaticAnalyzer::visitGE(GE *p) {}

void StaticAnalyzer::visitEQU(EQU *p) {}

void StaticAnalyzer::visitNE(NE *p) {}

void StaticAnalyzer::visitInteger(Integer i)
{
}

void StaticAnalyzer::visitDouble(Double d)
{
}

void StaticAnalyzer::visitChar(Char c)
{
}

void StaticAnalyzer::visitString(String s)
{
}

void StaticAnalyzer::visitIdent(String s)
{
}