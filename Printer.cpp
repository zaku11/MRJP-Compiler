/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include <iostream>
#include <memory>
#include "Printer.H"
#define INDENT_WIDTH 2

using std :: cerr;
using std :: vector;

inline std::ostream& operator<<(std::ostream& out, const TYPE value) {
  switch(value) {
    case INT:
      return out << " INT ";
    case VOID:
      return out << " VOID ";
    case BOOLEAN:
      return out << " BOOLEAN ";
    case STRING:
      return out << " STRING ";
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
    cerr << "ERROR at " << line_number << " : " << ident << " is not defined\n";
    exit(-1);
  }
}

void check_for_existence(Ident &ident, FunEnv *env_of_functions, int &line_number) {
  if(env_of_functions->find(ident) == env_of_functions->end()) {
    cerr << "ERROR at " << line_number << " : " << ident << " is not defined\n";
    exit(-1);
  }
}

void check_for_type_matching(TYPE type1, TYPE type2, int &line_number) {
  if(type1 != type2) {
    cerr << "ERROR at " << line_number << " : trying to assign " << type2 << " to " << type1 << "\n";
    exit(-1); 
  }
}


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(' ');
     bufAppend(c);
     bufAppend(' ');
  }
}

void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::render(char *s)
{
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}

void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}

void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}

PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char *PrintAbsyn::print(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}

void PrintAbsyn::visitProgram(Program *p) {} //abstract class

void PrintAbsyn::visitProgramDef(ProgramDef *p)
{
  if(p->listtopdef_) {
    p->listtopdef_->accept(this);
  }
}

void PrintAbsyn::visitTopDef(TopDef *p) {} //abstract class

void PrintAbsyn::visitFnDef(FnDef *p)
{
  // p->type_->accept(this);
  // visitIdent(p->ident_);
  vector <TYPE> arg_types;
  vector <Ident> arg_names;
  if(p->listarg_) {
    for(int i = 0 ; i < p->listarg_->size(); i++) {
      if(auto arg = dynamic_cast<ArgDef*>((*(p->listarg_))[i])) {
        arg_types.push_back(type_translator(arg->type_));
        arg_names.push_back(arg->ident_);
      }
    }
    // p->listarg_->accept(this);
  }
  env_of_functions[p->ident_] = make_pair(arg_types, type_translator(p->type_));
  // expected_return_type = type_translator(p->type_);

  auto tmp_env_of_vars = env_of_vars;

  for(int i = 0; i < arg_names.size(); i++) {
    env_of_vars[arg_names[i]] = arg_types[i];
  }  
  auto ret_before = last_return;
  last_return = VOID;
  
  // run_with_rollback(p->block_);
  expected_return_type = type_translator(p->type_);

  p->block_->accept(this);
  if(last_return != type_translator(p->type_)) {
    cerr << "ERROR at : " << p->line_number << " : function returned " << last_return << " but should return " << type_translator(p->type_) << "\n";
    exit(-1); 
  }

  //We need to clear out our env from our vars
  last_return = ret_before;
  env_of_vars = tmp_env_of_vars;
}

void PrintAbsyn::visitListTopDef(ListTopDef *listtopdef)
{
  bool was_there_main = false;
  vector <TYPE> single_int(1, INT);
  env_of_functions["printInt"] = make_pair(single_int, VOID);
  vector <TYPE> single_bool(1, BOOLEAN);
  env_of_functions["printBool"] = make_pair(single_bool, VOID);
  vector <TYPE> single_string(1, STRING);
  env_of_functions["printString"] = make_pair(single_string, VOID);
  vector <TYPE> empty_vec;
  env_of_functions["readInt"] = make_pair(empty_vec, INT);
  env_of_functions["readString"] = make_pair(empty_vec, STRING);
  env_of_functions["readBool"] = make_pair(empty_vec, BOOLEAN);

  //We need to gather all signatures BEFORE
  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    if(auto fn_def = dynamic_cast<FnDef*>(*i)) {
      if(fn_def->ident_ == "main" && type_translator(fn_def->type_) == INT) {
        was_there_main = true;
      }
      vector <TYPE> arg_types;
      for(int j = 0 ; j < fn_def->listarg_->size(); j++) {
        if(auto arg = dynamic_cast<ArgDef*>((*(fn_def->listarg_))[j])) {
          if(type_translator(arg->type_) == VOID) {
            cerr << "ERROR at " << fn_def->line_number << " : function can't have VOID as an argument\n";
            exit(-1);
          }
          arg_types.push_back(type_translator(arg->type_));
        }
      }
      env_of_functions[fn_def->ident_] = make_pair(arg_types, type_translator(fn_def->type_));
    }
  }
  
  if(!was_there_main) {
    cerr << "ERROR : no function main present\n";
    exit(-1);
  }



  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
  }
  cerr << "OK\n";
}

void PrintAbsyn::visitArg(Arg *p) {} //abstract class

void PrintAbsyn::visitArgDef(ArgDef *p)
{
  // p->type_->accept(this);
  // visitIdent(p->ident_);

}

void PrintAbsyn::visitListArg(ListArg *listarg)
{
  // for (ListArg::const_iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  // {
  //   (*i)->accept(this);
  // }
}

void PrintAbsyn::visitBlock(Block *p) {} //abstract class

void PrintAbsyn::visitBlockDef(BlockDef *p)
{
  if(p->liststmt_) {
    run_with_rollback(p->liststmt_);
  }
}

void PrintAbsyn::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
    // env_of_vars = new_env_of_vars;
    // env_of_functions = new_env_of_functions;
  }
}

void PrintAbsyn::visitStmt(Stmt *p) {} //abstract class

void PrintAbsyn::visitEmpty(Empty *p)
{
  last_evaluated_expr = VOID;
}

void PrintAbsyn::run_with_rollback(Visitable* v) {
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
  defined_in_current_scope = curr_defined_in_current_scope;
  // last_return = curr_last_return;
}

//Some rollbacks happening
void PrintAbsyn::visitBStmt(BStmt *p)
{
  p->block_->accept(this);
}

void PrintAbsyn::visitDecl(Decl *p)
{
  // p->type_->accept(this);
  // p->listitem_->accept(this);
  if(p->listitem_) 
  {
    for (ListItem::const_iterator i = p->listitem_->begin() ; i != p->listitem_->end() ; ++i)
    {
      if(auto init = dynamic_cast<NoInit*>(*i)) 
      {
        if(defined_in_current_scope.find(init->ident_) != defined_in_current_scope.end()) 
        {
          cerr << "ERROR at " << init->line_number << " : variable " << init->ident_ << " got redefined in this same scope\n";
          exit(-1);
        }
        defined_in_current_scope.insert(init->ident_);
        env_of_vars[init->ident_] = type_translator(p->type_);
      }
      if(auto init = dynamic_cast<Init*>(*i)) 
      {
        if(defined_in_current_scope.find(init->ident_) != defined_in_current_scope.end()) 
        {
          cerr << "ERROR at " << init->line_number << " : variable " << init->ident_ << " got redefined in this same scope\n";
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

void PrintAbsyn::visitAss(Ass *p)
{
  check_for_existence(p->ident_, &env_of_vars, p->line_number);
  p->expr_->accept(this);
  check_for_type_matching(env_of_vars[p->ident_], last_evaluated_expr, p->line_number);
}

void PrintAbsyn::visitIncr(Incr *p)
{
  check_for_existence(p->ident_, &env_of_vars, p->line_number);
  check_for_type_matching(env_of_vars[p->ident_], INT, p->line_number);
}

void PrintAbsyn::visitDecr(Decr *p)
{
  check_for_existence(p->ident_, &env_of_vars, p->line_number);
  check_for_type_matching(env_of_vars[p->ident_], INT, p->line_number);
}

void PrintAbsyn::visitRet(Ret *p)
{
  p->expr_->accept(this);
  // if(last_evaluated_expr == VOID) {
  //   cerr << "ERROR at " << p->line_number << " : you can't return VOID that way\n";
  //   exit(-1);
  // }
  // if(last_return != last_evaluated_expr && last_return != VOID) {
  //   cerr << "ERROR at : " << p->line_number << " : function has returns both of " << last_return << " and " << last_evaluated_expr << " type\n";
  //   exit(-1);
  // }
  if(expected_return_type != last_evaluated_expr) {
    cerr << "ERROR at " << p->line_number << " : wanted to return " << last_evaluated_expr << " but expected " << expected_return_type << "\n";
    exit(-1); 
  }
  last_return = last_evaluated_expr;
}

void PrintAbsyn::visitVRet(VRet *p)
{
  last_return = VOID;
  if(last_return != expected_return_type) {
    cerr << "ERROR at : " << p->line_number << " : function returns " << last_return << " but it expects " << expected_return_type << " type\n";
    exit(-1);
  }
}

void PrintAbsyn::visitCond(Cond *p)
{
  p->expr_->accept(this);
  if(last_evaluated_expr != BOOLEAN) {
    cerr << "ERROR at " << p->line_number << " : IF must have condition of type BOOLEAN\n";
    exit(-1);
  }
  auto ret_tmp = last_return;
  p->stmt_->accept(this);
  last_return = ret_tmp;
}


void PrintAbsyn::visitCondElse(CondElse *p)
{
  p->expr_->accept(this);
  if(last_evaluated_expr != BOOLEAN) {
    cerr << "ERROR at " << p->line_number << " : IF must have condition of type BOOLEAN\n";
    exit(-1);
  }
  p->stmt_1->accept(this);
  TYPE ret1 = last_return;
  last_return = VOID;
  p->stmt_2->accept(this);
  TYPE ret2 = last_return;

  if(ret1 != ret2) last_return = VOID;
}

void PrintAbsyn::visitWhile(While *p)
{
  p->expr_->accept(this);
  if(last_evaluated_expr != BOOLEAN) {
    cerr << "ERROR at " << p->line_number << " : WHILE must have condition of type BOOLEAN\n";
    exit(-1);
  }
  // run_with_rollback(p->stmt_);
  p->stmt_->accept(this);
}

void PrintAbsyn::visitSExp(SExp *p)
{
  p->expr_->accept(this);
}

void PrintAbsyn::visitItem(Item *p) {} //abstract class

void PrintAbsyn::visitNoInit(NoInit *p)
{  
  // In a perfect world this will not be used
  // visitIdent(p->ident_);
}

void PrintAbsyn::visitInit(Init *p)
{
  // In a perfect world this will not be used
  // visitIdent(p->ident_);
  // p->expr_->accept(this);
}

void PrintAbsyn::visitListItem(ListItem *listitem)
{
  // In a perfect world this will not be used
  // for (ListItem::const_iterator i = listitem->begin() ; i != listitem->end() ; ++i)
  // {
  //   (*i)->accept(this);
  // }
}

void PrintAbsyn::visitType(Type *p) {} //abstract class

void PrintAbsyn::visitInt(Int *p)
{
}

void PrintAbsyn::visitStr(Str *p)
{
}

void PrintAbsyn::visitBool(Bool *p)
{
}

void PrintAbsyn::visitVoid(Void *p)
{
}


void PrintAbsyn::visitFun(Fun *p)
{
  p->type_->accept(this);
  if(p->listtype_) {p->listtype_->accept(this);}
}

void PrintAbsyn::visitListType(ListType *listtype)
{
  for (ListType::const_iterator i = listtype->begin() ; i != listtype->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void PrintAbsyn::visitExpr(Expr *p) {} //abstract class

void PrintAbsyn::visitEVar(EVar *p)
{
  check_for_existence(p->ident_, &env_of_vars, p->line_number);
  last_evaluated_expr = env_of_vars[p->ident_];
  // visitIdent(p->ident_);
}

void PrintAbsyn::visitELitInt(ELitInt *p)
{
  last_evaluated_expr = INT;
  last_evaluated_expr_value = p->integer_;
}

void PrintAbsyn::visitELitTrue(ELitTrue *p)
{
  last_evaluated_expr = BOOLEAN;
  last_evaluated_expr_value = true;
}

void PrintAbsyn::visitELitFalse(ELitFalse *p)
{
  last_evaluated_expr = BOOLEAN;
  last_evaluated_expr_value = false;
}

void PrintAbsyn::visitEApp(EApp *p)
{
  // visitIdent(p->ident_);
  check_for_existence(p->ident_, &env_of_functions, p->line_number);
  auto expected_arg_types = env_of_functions[p->ident_].first;
  if(p->listexpr_->size() != expected_arg_types.size()) {
    cerr << "ERROR at " << p->line_number << " : function " << p->ident_ << " was supplied " << p->listexpr_->size() << " arguments but needed " << expected_arg_types.size() << "\n";
    exit(-1);  
  }
  for(int i = 0; i < p->listexpr_->size(); i++) {
    (*(p->listexpr_))[i]->accept(this);
    check_for_type_matching(expected_arg_types[i], last_evaluated_expr, p->line_number);
  }
  last_evaluated_expr = env_of_functions[p->ident_].second;
  // if(p->listexpr_) {p->listexpr_->accept(this);}
}

void PrintAbsyn::visitEString(EString *p)
{
  last_evaluated_expr = STRING;
  last_evaluated_expr_value = p->string_;
}

void PrintAbsyn::visitNeg(Neg *p)
{
  p->expr_->accept(this);
  check_for_type_matching(last_evaluated_expr, INT, p->line_number);
  if(auto val = std::get_if<int>(last_evaluated_expr_value))
    last_evaluated_expr_value = -val;
  }
  catch(std::bad_variant_access&) {
    last_evaluated_expr_value = void;
  }
}

void PrintAbsyn::visitNot(Not *p)
{
  p->expr_->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  last_evaluated_expr_value = !(std::get<bool>(last_evaluated_expr_value));
}

void PrintAbsyn::visitEMul(EMul *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(last_evaluated_expr, INT, p->line_number);
  int i1 = std::get<int>(last_evaluated_expr_value);
  p->expr_2->accept(this);
  check_for_type_matching(last_evaluated_expr, INT, p->line_number);
  int i2 = std::get<int>(last_evaluated_expr_value);
  last_evaluated_expr_value = i1 * i2;
}

void PrintAbsyn::visitEAdd(EAdd *p)
{
  p->expr_1->accept(this);
  std::variant<int, string> v1 = last_evaluated_expr_value;
  if(last_evaluated_expr != INT && last_evaluated_expr != STRING) {
    cerr << "ERROR at " << p->line_number << " : you can only add STRINGs and INTs\n";
    exit(-1);
  }
  p->expr_2->accept(this);
  if(last_evaluated_expr != INT && last_evaluated_expr != STRING) {
    cerr << "ERROR at " << p->line_number << " : you can only add STRINGs and INTs\n";
    exit(-1);
  }
}

void PrintAbsyn::visitERel(ERel *p)
{
  p->expr_1->accept(this);
  TYPE type1 = last_evaluated_expr;
  // p->relop_->accept(this);
  p->expr_2->accept(this);
  TYPE type2 = last_evaluated_expr;
  if(type1 != type2 || type1 == VOID || type2 == VOID || type1 == STRING || type2 == STRING) {
    cerr << "ERROR at " << p->line_number << " : cannot compare " << type1 << " and " << type2 <<"\n";
    exit(-1);
  }
  if(type1 == BOOLEAN) {
    if(dynamic_cast<EQU*>(p->relop_) || dynamic_cast<NE*>(p->relop_)) {}
    else {
      cerr << "ERROR at " << p->line_number << " : this operation is not allowed for BOOLEANS\n";
      exit(-1);
    }
  }

  last_evaluated_expr = BOOLEAN;
}

void PrintAbsyn::visitEAnd(EAnd *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  p->expr_2->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  last_evaluated_expr = BOOLEAN;
}

void PrintAbsyn::visitEOr(EOr *p)
{
  p->expr_1->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  p->expr_2->accept(this);
  check_for_type_matching(last_evaluated_expr, BOOLEAN, p->line_number);
  last_evaluated_expr = BOOLEAN;
}

void PrintAbsyn::visitListExpr(ListExpr *listexpr)
{
  // for (ListExpr::const_iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  // {
  //   (*i)->accept(this);
  // }
}
void PrintAbsyn::visitAddOp(AddOp *p) {} //abstract class

void PrintAbsyn::visitPlus(Plus *p) {}

void PrintAbsyn::visitMinus(Minus *p) {}

void PrintAbsyn::visitMulOp(MulOp *p) {} //abstract class

void PrintAbsyn::visitTimes(Times *p) {}

void PrintAbsyn::visitDiv(Div *p) {}

void PrintAbsyn::visitMod(Mod *p) {}

void PrintAbsyn::visitRelOp(RelOp *p) {} //abstract class

void PrintAbsyn::visitLTH(LTH *p) {}

void PrintAbsyn::visitLE(LE *p) {}

void PrintAbsyn::visitGTH(GTH *p) {}

void PrintAbsyn::visitGE(GE *p) {}

void PrintAbsyn::visitEQU(EQU *p) {}

void PrintAbsyn::visitNE(NE *p) {}

void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}

void PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}

void PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}

void PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

void PrintAbsyn::visitIdent(String s)
{
  render(s);
}