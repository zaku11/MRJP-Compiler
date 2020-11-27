/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include <iostream>
#include <memory>
#include <variant>
#include "FrontEnd.H"
#define INDENT_WIDTH 2

using std :: cerr;
using std :: vector;

inline std::ostream& operator<<(std::ostream& out, const TYPE value) {
  switch(value) {
    case INT:
      return out << "INT";
    case VOID:
      return out << "VOID";
    case BOOLEAN:
      return out << "BOOLEAN";
    case STRING:
      return out << "STRING";
  }
  return out;
}

TYPE type_translator(Type* val) {
  if(dynamic_cast<Int*>(val)) return INT;
  if(dynamic_cast<Str*>(val)) return STRING;
  if(dynamic_cast<Bool*>(val)) return BOOLEAN;
  if(dynamic_cast<Void*>(val)) return VOID;
  return VOID;
}

void check_for_existence(Ident &ident, VarEnv *env_of_vars, int &line_number) {
  if(env_of_vars->find(ident) == env_of_vars->end()) {
    cerr << "ERROR\nLine " << line_number << " : " << ident << " is not defined\n";
    exit(-1);
  }
}

void check_for_existence(Ident &ident, FunEnv *env_of_functions, int &line_number) {
  if(env_of_functions->find(ident) == env_of_functions->end()) {
    cerr << "ERROR\nLine " << line_number << " : " << ident << " is not defined\n";
    exit(-1);
  }
}

void check_for_type_matching(TYPE type1, TYPE type2, int &line_number) {
  if(type1 != type2) {
    cerr << "ERROR\nLine " << line_number << " : trying to assign " << type2 << " to " << type1 << "\n";
    exit(-1); 
  }
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
      arg_types.push_back(type_translator(arg->type_));
      arg_names.push_back(arg->ident_);
    }
  }
  

  auto tmp_env_of_vars = env_of_vars;

  for(int i = 0; i < arg_names.size(); i++) {
    env_of_vars[arg_names[i]] = arg_types[i];
  }  
  auto ret_before = last_return;
  last_return = VOID;
  
  expected_return_type = type_translator(p->type_);

  p->block_->accept(this);
  if(last_return != type_translator(p->type_)) {
    cerr << "ERROR\nLine " << p->line_number << " : function returned " << last_return << " but should return " << type_translator(p->type_) << "\n";
    exit(-1); 
  }

  //We need to clear out our env from our vars
  last_return = ret_before;
  env_of_vars = tmp_env_of_vars;
}

void StaticAnalyzer::visitListTopDef(ListTopDef *listtopdef)
{
  bool was_there_main = false;
  vector <TYPE> single_int(1, INT);
  env_of_functions["printInt"] = make_pair(single_int, VOID);
  vector <TYPE> single_string(1, STRING);
  env_of_functions["printString"] = make_pair(single_string, VOID);
  vector <TYPE> empty_vec;
  env_of_functions["readInt"] = make_pair(empty_vec, INT);
  env_of_functions["readString"] = make_pair(empty_vec, STRING);
  env_of_functions["error"] = make_pair(empty_vec, VOID);

  //We need to gather all signatures BEFORE
  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    if(auto fn_def = dynamic_cast<FnDef*>(*i)) {
      if(fn_def->ident_ == "main" && type_translator(fn_def->type_) == INT && fn_def->listarg_->size() == 0) {
        was_there_main = true;
      }
      vector <TYPE> arg_types;
      for(int j = 0 ; j < fn_def->listarg_->size(); j++) {
        if(auto arg = dynamic_cast<ArgDef*>((*(fn_def->listarg_))[j])) {
          if(type_translator(arg->type_) == VOID) {
            cerr << "ERROR\nLine " << fn_def->line_number << " : function can't have VOID as an argument\n";
            exit(-1);
          }
          arg_types.push_back(type_translator(arg->type_));
        }
      }
      if(env_of_functions.find(fn_def->ident_) != env_of_functions.end()) {
        cerr << "ERROR\nLine " << fn_def->line_number << " : function with name " << fn_def->ident_ << " already exists.\n";
        exit(-1); 
      }

      env_of_functions[fn_def->ident_] = make_pair(arg_types, type_translator(fn_def->type_));
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
  cerr << "OK\n";
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
    // env_of_vars = new_env_of_vars;
    // env_of_functions = new_env_of_functions;
  }
}

void StaticAnalyzer::visitStmt(Stmt *p) {} //abstract class

void StaticAnalyzer::visitEmpty(Empty *p)
{
  last_evaluated_expr = VOID;
  last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::run_with_rollback(Visitable* v) {
  auto curr_env_of_vars = env_of_vars;
  auto curr_env_of_functions = env_of_functions;
  auto curr_defined_in_current_scope = defined_in_current_scope;
  auto curr_last_evaluated_expr = last_evaluated_expr;
  auto curr_expected_return_type = expected_return_type;
  // auto curr_last_return = last_return;
  defined_in_current_scope.clear();

  v->accept(this);

  env_of_vars = curr_env_of_vars;
  env_of_functions = curr_env_of_functions;
  defined_in_current_scope = curr_defined_in_current_scope;
  last_evaluated_expr = curr_last_evaluated_expr;
  expected_return_type = curr_expected_return_type;
  // last_return = curr_last_return;
}

void StaticAnalyzer::visitBStmt(BStmt *p)
{
  p->block_->accept(this);
}

void StaticAnalyzer::visitDecl(Decl *p)
{
  if(type_translator(p->type_) == VOID) {
    cerr << "ERROR\nLine " << p->line_number << " : can't have VOID as a variable type\n";
    exit(-1);
  }
  if(p->listitem_) {
    for (ListItem::const_iterator i = p->listitem_->begin() ; i != p->listitem_->end() ; ++i) {
      if(auto init = dynamic_cast<NoInit*>(*i)) {
        if(defined_in_current_scope.find(init->ident_) != defined_in_current_scope.end()) {
          cerr << "ERROR\nLine " << init->line_number << " : variable " << init->ident_ << " got redefined in this same scope\n";
          exit(-1);
        }
        defined_in_current_scope.insert(init->ident_);
        env_of_vars[init->ident_] = type_translator(p->type_);
      }
      if(auto init = dynamic_cast<Init*>(*i)) {
        if(defined_in_current_scope.find(init->ident_) != defined_in_current_scope.end()){
          cerr << "ERROR\nLine " << init->line_number << " : variable " << init->ident_ << " got redefined in this same scope\n";
          exit(-1);
        }
        init->expr_->accept(this);
        check_for_type_matching(type_translator(p->type_), last_evaluated_expr, init->line_number);
        defined_in_current_scope.insert(init->ident_);
        env_of_vars[init->ident_] = type_translator(p->type_);
      }
    }

  }

}

void StaticAnalyzer::visitAss(Ass *p)
{
  check_for_existence(p->ident_, &env_of_vars, p->line_number);
  p->expr_->accept(this);
  check_for_type_matching(env_of_vars[p->ident_], last_evaluated_expr, p->line_number);
}

void StaticAnalyzer::visitIncr(Incr *p)
{
  check_for_existence(p->ident_, &env_of_vars, p->line_number);
  check_for_type_matching(env_of_vars[p->ident_], INT, p->line_number);
}

void StaticAnalyzer::visitDecr(Decr *p)
{
  check_for_existence(p->ident_, &env_of_vars, p->line_number);
  check_for_type_matching(env_of_vars[p->ident_], INT, p->line_number);
}

void StaticAnalyzer::visitRet(Ret *p)
{
  p->expr_->accept(this);
  
  if(expected_return_type != last_evaluated_expr) {
    cerr << "ERROR\nLine " << p->line_number << " : wanted to return " << last_evaluated_expr << " but expected " << expected_return_type << "\n";
    exit(-1); 
  }
  if(last_evaluated_expr == VOID) {
    cerr << "ERROR\nLine " << p->line_number << " : you can't return VOID that way\n";
    exit(-1);
  }  
  last_return = last_evaluated_expr;
}

void StaticAnalyzer::visitVRet(VRet *p)
{
  last_return = VOID;
  if(last_return != expected_return_type) {
    cerr << "ERROR\nLine " << p->line_number << " : function returns " << last_return << " but it expects " << expected_return_type << " type\n";
    exit(-1);
  }
}

void StaticAnalyzer::visitCond(Cond *p)
{
  p->expr_->accept(this);

  if(last_evaluated_expr != BOOLEAN) {
    cerr << "ERROR\nLine " << p->line_number << " : IF must have condition of type BOOLEAN\n";
    exit(-1);
  }
  auto cond_value = last_evaluated_expr_value;
  auto ret_tmp = last_return;
  p->stmt_->accept(this);

  if(auto val = std::get_if<bool>(&cond_value)) { {
    if((*val) == true) {
      // This means that we are statically sure we're entering the IF branch
      // So if there was a return and there was no return before then this is a
      // valid code 
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
  if(last_evaluated_expr != BOOLEAN) {
    cerr << "ERROR\nLine " << p->line_number << " : IF must have condition of type BOOLEAN\n";
    exit(-1);
  }
  auto cond_value = last_evaluated_expr_value;
  auto ret_before_all_operations = last_return;


  p->stmt_1->accept(this);
  TYPE ret1 = last_return;
  last_return = VOID;
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
  if(last_evaluated_expr != BOOLEAN) {
    cerr << "ERROR\nLine " << p->line_number << " : WHILE must have condition of type BOOLEAN\n";
    exit(-1);
  }

  auto cond_value = last_evaluated_expr_value;
  auto ret_tmp = last_return;
  p->stmt_->accept(this);

  if(auto val = std::get_if<bool>(&cond_value)) { {
    if((*val) == true) {
      // This means that we are statically sure we're entering the WHILE loop
      // So if there was a return and there was no return before then this is a
      // valid code 
    }
    else {
      last_return = ret_tmp;
    }
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


void StaticAnalyzer::visitFun(Fun *p)
{
}

void StaticAnalyzer::visitListType(ListType *listtype)
{
}

void StaticAnalyzer::visitExpr(Expr *p) {} //abstract class

void StaticAnalyzer::visitEVar(EVar *p)
{
  check_for_existence(p->ident_, &env_of_vars, p->line_number);
  last_evaluated_expr = env_of_vars[p->ident_];
  last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitELitInt(ELitInt *p)
{
  last_evaluated_expr = INT;
  last_evaluated_expr_value = p->integer_;
}

void StaticAnalyzer::visitELitTrue(ELitTrue *p)
{
  last_evaluated_expr = BOOLEAN;
  last_evaluated_expr_value = true;
}

void StaticAnalyzer::visitELitFalse(ELitFalse *p)
{
  last_evaluated_expr = BOOLEAN;
  last_evaluated_expr_value = false;
}

void StaticAnalyzer::visitEApp(EApp *p)
{
  check_for_existence(p->ident_, &env_of_functions, p->line_number);
  auto expected_arg_types = env_of_functions[p->ident_].first;
  if(p->listexpr_->size() != expected_arg_types.size()) {
    cerr << "ERROR\nLine " << p->line_number << " : function " << p->ident_ << " was supplied " << p->listexpr_->size() << " arguments but needed " << expected_arg_types.size() << "\n";
    exit(-1);  
  }
  for(int i = 0; i < p->listexpr_->size(); i++) {
    (*(p->listexpr_))[i]->accept(this);
    check_for_type_matching(expected_arg_types[i], last_evaluated_expr, p->line_number);
  }
  last_evaluated_expr = env_of_functions[p->ident_].second;
  last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitEString(EString *p)
{
  last_evaluated_expr = STRING;
  last_evaluated_expr_value = p->string_;
}

void StaticAnalyzer::visitNeg(Neg *p)
{
  p->expr_->accept(this);
  check_for_type_matching(last_evaluated_expr, INT, p->line_number);
  if(auto val = std::get_if<int>(&last_evaluated_expr_value))
    last_evaluated_expr_value = -(*val);
  else 
    last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitNot(Not *p)
{
  p->expr_->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  if(auto val = std::get_if<bool>(&last_evaluated_expr_value))
    last_evaluated_expr_value = !(*val);
  else 
    last_evaluated_expr_value = DECOY;
}

void StaticAnalyzer::visitEMul(EMul *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(last_evaluated_expr, INT, p->line_number);
  auto i1 = last_evaluated_expr_value;
  p->expr_2->accept(this);
  check_for_type_matching(last_evaluated_expr, INT, p->line_number);
  auto i2 = last_evaluated_expr_value;

  last_evaluated_expr_value = DECOY;
  if(auto val1 = std::get_if<int>(&i1)) 
    if(auto val2 = std::get_if<int>(&i2)) 
      last_evaluated_expr_value = (*val1) * (*val2);

}

void StaticAnalyzer::visitEAdd(EAdd *p)
{
  p->expr_1->accept(this);
  auto v1 = last_evaluated_expr_value;
  auto exp1 = last_evaluated_expr;

  p->expr_2->accept(this);
  auto v2 = last_evaluated_expr_value;
  auto exp2 = last_evaluated_expr;

  if(exp1 != exp2) {
    cerr << "ERROR\nLine " << p->line_number << " : you can only add/substract expressions of the same type.\n";
    exit(-1);
  }


  last_evaluated_expr_value = DECOY;
  if(auto val1 = std::get_if<int>(&v1)) 
    if(auto val2 = std::get_if<int>(&v2)) { 
      if(dynamic_cast<Plus*>(p->addop_))
        last_evaluated_expr_value = (*val1) + (*val2);
      else 
        last_evaluated_expr_value = (*val1) - (*val2);
    }

  if(auto val1 = std::get_if<std::string>(&v1)) 
    if(auto val2 = std::get_if<std::string>(&v2)) {
      if(dynamic_cast<Plus*>(p->addop_))
        last_evaluated_expr_value = (*val1) + (*val2);
      else {
        cerr << "ERROR\nLine " << p->line_number << " : you can't substract STRINGs.\n";
        exit(-1);
      } 
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

  if(type1 != type2 || type1 == VOID || type2 == VOID) {
    cerr << "ERROR\nLine " << p->line_number << " : cannot compare " << type1 << " and " << type2 <<"\n";
    exit(-1);
  }
  last_evaluated_expr_value = DECOY;
  if(type1 == STRING || type1 == BOOLEAN) {
    if(!(dynamic_cast<EQU*>(p->relop_) || dynamic_cast<NE*>(p->relop_))) {
      cerr << "ERROR\nLine " << p->line_number << " : this operation is not allowed for " << type1 << "\n";
      exit(-1);
    }
    if(auto s1 = std::get_if<std::string>(&v1)) 
      if(auto s2 = std::get_if<std::string>(&v2)) {
        if(dynamic_cast<EQU*>(p->relop_)) 
          last_evaluated_expr_value = ((*s1) == (*s2));
        if(dynamic_cast<NE*>(p->relop_)) 
          last_evaluated_expr_value = ((*s1) != (*s2));
      }
    if(auto b1 = std::get_if<bool>(&v1)) 
      if(auto b2 = std::get_if<bool>(&v2)) {
        if(dynamic_cast<EQU*>(p->relop_)) 
          last_evaluated_expr_value = ((*b1) == (*b2));
        if(dynamic_cast<NE*>(p->relop_)) 
          last_evaluated_expr_value = ((*b1) != (*b2));
    }
  }
  if(type1 == INT) {
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
  }

  last_evaluated_expr = BOOLEAN;
}

void StaticAnalyzer::visitEAnd(EAnd *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  auto v1 = last_evaluated_expr_value;
  p->expr_2->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  auto v2 = last_evaluated_expr_value;
  last_evaluated_expr = BOOLEAN;

  last_evaluated_expr_value = DECOY;
  if(auto val1 = std::get_if<bool>(&v1)) 
    if(auto val2 = std::get_if<bool>(&v2)) 
      last_evaluated_expr_value = *val1 && *val2;

}

void StaticAnalyzer::visitEOr(EOr *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  auto v1 = last_evaluated_expr_value;
  p->expr_2->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  auto v2 = last_evaluated_expr_value;
  last_evaluated_expr = BOOLEAN;


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