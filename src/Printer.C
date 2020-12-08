/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2


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

void PrintAbsyn::revert_white_chars() {
  while (cur_ > 0 && (buf_[cur_ - 1] == '\n' || buf_[cur_ - 1] == ' '))
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}

PrintAbsyn::PrintAbsyn(String msg, Visitable *v)
{
  this->error_message = msg;
  this->erronous_statement = v;
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char *PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  try {
    v->accept(this);
    return buf_;
  }
  catch(end_exception &e) {
    int ptr = this->cur_;
    int how_many_enters = 3;
    while(how_many_enters > 0 && ptr > 0) {
      if(buf_[ptr] == '\n')
        how_many_enters--;
      ptr--;
    }
    if(ptr != 0) ptr += 2;
    return buf_ + ptr;
  }
}

void PrintAbsyn::try_to_end(Visitable *v, int line_number) {
  if(this->erronous_statement == v) {
    revert_white_chars();
    bufAppend(" <- LINE " + std::to_string(line_number) + " : " + this->error_message);
    throw end_exception();
  }
}

void PrintAbsyn::visitProgram(Program *p) {} //abstract class

void PrintAbsyn::visitProgramDef(ProgramDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  if(p->listtopdef_) {_i_ = 0; p->listtopdef_->accept(this);}

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitTopDef(TopDef *p) {} //abstract class

void PrintAbsyn::visitFnDef(FnDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render('(');
  if(p->listarg_) {_i_ = 0; p->listarg_->accept(this);}
  render(')');
  _i_ = 0; p->block_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEmptyStructDef(EmptyStructDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"class");
  visitIdent(p->ident_);
  render('{');
  render('}');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}


void PrintAbsyn::visitStructDef(StructDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"class");
  visitIdent(p->ident_);
  render('{');
  if(p->liststructmember_) {_i_ = 0; p->liststructmember_->accept(this);}
  render('}');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitStructMember(StructMember *p) {} //abstract class

void PrintAbsyn::visitStructMemNoInit(StructMemNoInit *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitStructMemInit(StructMemInit *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);
  render('=');
  _i_ = 0; p->expr_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitListStructMember(ListStructMember *liststructmember)
{
  for (ListStructMember::const_iterator i = liststructmember->begin() ; i != liststructmember->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != liststructmember->end() - 1) render((char*)"");
  }

}

void PrintAbsyn::visitIdentExpan(IdentExpan *p) {} //abstract class

void PrintAbsyn::visitIdentExp(IdentExp *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->identexpan_->accept(this);
  render('.');
  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitIdentExpSimple(IdentExpSimple *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitListTopDef(ListTopDef *listtopdef)
{
  for (ListTopDef::const_iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listtopdef->end() - 1) render((char*)"");
  }
}

void PrintAbsyn::visitArg(Arg *p) {} //abstract class

void PrintAbsyn::visitArgDef(ArgDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitListArg(ListArg *listarg)
{
  for (ListArg::const_iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listarg->end() - 1) render(',');
  }
}

void PrintAbsyn::visitBlock(Block *p) {} //abstract class

void PrintAbsyn::visitBlockDef(BlockDef *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('{');
  if(p->liststmt_) {_i_ = 0; p->liststmt_->accept(this);}
  render('}');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
    render((char*)"");
  }
}

void PrintAbsyn::visitStmt(Stmt *p) {} //abstract class

void PrintAbsyn::visitEmpty(Empty *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitBStmt(BStmt *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->block_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitDecl(Decl *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->type_->accept(this);
  if(p->listitem_) {_i_ = 0; p->listitem_->accept(this);}
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitAss(Ass *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->identexpan_->accept(this);
  render('=');
  _i_ = 0; p->expr_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitNewStruct(NewStruct *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->identexpan_->accept(this);
  render('=');
  render((char*)"new");
  visitIdent(p->ident_);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitIncr(Incr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->identexpan_->accept(this);
  render((char*)"++");
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitDecr(Decr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->identexpan_->accept(this);
  render((char*)"--");
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitRet(Ret *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"return");
  _i_ = 0; p->expr_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitVRet(VRet *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"return");
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitCond(Cond *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"if");
  render('(');
  _i_ = 0; p->expr_->accept(this);
  render(')');
  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitCondElse(CondElse *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"if");
  render('(');
  _i_ = 0; p->expr_->accept(this);
  render(')');
  _i_ = 0; p->stmt_1->accept(this);
  render((char*)"else");
  _i_ = 0; p->stmt_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitWhile(While *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"while");
  render('(');
  _i_ = 0; p->expr_->accept(this);
  render(')');
  _i_ = 0; p->stmt_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitSExp(SExp *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->expr_->accept(this);
  render(';');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitItem(Item *p) {} //abstract class

void PrintAbsyn::visitNoInit(NoInit *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitInit(Init *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);
  render('=');
  _i_ = 0; p->expr_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitInitStruct(InitStruct *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_1);
  render('=');
  render((char*)"new");
  visitIdent(p->ident_2);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitListItem(ListItem *listitem)
{
  for (ListItem::const_iterator i = listitem->begin() ; i != listitem->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listitem->end() - 1) render(',');
  }
}

void PrintAbsyn::visitType(Type *p) {} //abstract class

void PrintAbsyn::visitInt(Int *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"int");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitStr(Str *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"string");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitBool(Bool *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"boolean");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitVoid(Void *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"void");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitStruct(Struct *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitFun(Fun *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  /* Internal Category */

  _i_ = 0; p->type_->accept(this);
  render('(');
  if(p->listtype_) {_i_ = 0; p->listtype_->accept(this);}
  render(')');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitListType(ListType *listtype)
{
  for (ListType::const_iterator i = listtype->begin() ; i != listtype->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listtype->end() - 1) render(',');
  }
}

void PrintAbsyn::visitExpr(Expr *p) {} //abstract class

void PrintAbsyn::visitENullCastType(ENullCastType *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  render('(');
  _i_ = 0; p->type_->accept(this);
  render(')');
  render((char*)"null");

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENullCastIdent(ENullCastIdent *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  render('(');
  visitIdent(p->ident_);
  render(')');
  render((char*)"null");

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEVar(EVar *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  _i_ = 0; p->identexpan_->accept(this);

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitELitInt(ELitInt *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitELitTrue(ELitTrue *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  render((char*)"true");

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitELitFalse(ELitFalse *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  render((char*)"false");

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEApp(EApp *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  visitIdent(p->ident_);
  render('(');
  if(p->listexpr_) {_i_ = 0; p->listexpr_->accept(this);}
  render(')');

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEString(EString *p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitNeg(Neg *p)
{
  int oldi = _i_;
  if (oldi > 5) render(_L_PAREN);

  render('-');
  _i_ = 6; p->expr_->accept(this);

  if (oldi > 5) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitNot(Not *p)
{
  int oldi = _i_;
  if (oldi > 5) render(_L_PAREN);

  render('!');
  _i_ = 6; p->expr_->accept(this);

  if (oldi > 5) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEMul(EMul *p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  _i_ = 4; p->expr_1->accept(this);
  _i_ = 0; p->mulop_->accept(this);
  _i_ = 5; p->expr_2->accept(this);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEAdd(EAdd *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 3; p->expr_1->accept(this);
  _i_ = 0; p->addop_->accept(this);
  _i_ = 4; p->expr_2->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitERel(ERel *p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->expr_1->accept(this);
  _i_ = 0; p->relop_->accept(this);
  _i_ = 3; p->expr_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEAnd(EAnd *p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 2; p->expr_1->accept(this);
  render((char*)"&&");
  _i_ = 1; p->expr_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEOr(EOr *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 1; p->expr_1->accept(this);
  render((char*)"||");
  _i_ = 0; p->expr_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitListExpr(ListExpr *listexpr)
{
  for (ListExpr::const_iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexpr->end() - 1) render(',');
  }
}

void PrintAbsyn::visitAddOp(AddOp *p) {} //abstract class

void PrintAbsyn::visitPlus(Plus *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('+');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitMinus(Minus *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('-');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitMulOp(MulOp *p) {} //abstract class

void PrintAbsyn::visitTimes(Times *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('*');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitDiv(Div *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('/');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitMod(Mod *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('%');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitRelOp(RelOp *p) {} //abstract class

void PrintAbsyn::visitLTH(LTH *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('<');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitLE(LE *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"<=");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitGTH(GTH *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('>');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitGE(GE *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)">=");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitEQU(EQU *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"==");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

void PrintAbsyn::visitNE(NE *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render((char*)"!=");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
  try_to_end(p, p->line_number);
}

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
