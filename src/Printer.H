#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <exception>

/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define _L_PAREN '('
#define _R_PAREN ')'

class end_exception : public std::exception {
public:
  virtual const char* what() const throw()
  {
    return "End Exception";
  }
};

class PrintAbsyn : public Visitor
{
 protected:
  String error_message = "";
  Visitable *erronous_statement;
  int _n_, _i_;
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
  void render(Char c);
  void render(String s);
void render(char *s);
  void indent(void);
  void backup(void);
 public:
  PrintAbsyn(String msg, Visitable *v);
  ~PrintAbsyn(void);
  char *print(Visitable *v);
  void revert_white_chars();
  void try_to_end(Visitable *v, int line_number);

  void visitProgram(Program *p); /* abstract class */
  void visitProgramDef(ProgramDef *p);
  void visitTopDef(TopDef *p); /* abstract class */
  void visitFnDef(FnDef *p);
  void visitStructDef(StructDef *p);
  void visitStructMember(StructMember *p); /* abstract class */
  void visitStructMemNoInit(StructMemNoInit *p);
  void visitStructMemInit(StructMemInit *p);
  void visitListStructMember(ListStructMember *p);
  void visitIdentExpan(IdentExpan *p); /* abstract class */
  void visitIdentExp(IdentExp *p);
  void visitIdentExpSimple(IdentExpSimple *p);
  void visitListTopDef(ListTopDef *p);
  void visitArg(Arg *p); /* abstract class */
  void visitArgDef(ArgDef *p);
  void visitListArg(ListArg *p);
  void visitBlock(Block *p); /* abstract class */
  void visitBlockDef(BlockDef *p);
  void visitListStmt(ListStmt *p);
  void visitStmt(Stmt *p); /* abstract class */
  void visitEmpty(Empty *p);
  void visitBStmt(BStmt *p);
  void visitDecl(Decl *p);
  void visitAss(Ass *p);
  void visitNewStruct(NewStruct *p);
  void visitIncr(Incr *p);
  void visitDecr(Decr *p);
  void visitRet(Ret *p);
  void visitVRet(VRet *p);
  void visitCond(Cond *p);
  void visitCondElse(CondElse *p);
  void visitWhile(While *p);
  void visitSExp(SExp *p);
  void visitItem(Item *p); /* abstract class */
  void visitNoInit(NoInit *p);
  void visitInit(Init *p);
  void visitInitStruct(InitStruct *p);
  void visitListItem(ListItem *p);
  void visitType(Type *p); /* abstract class */
  void visitInt(Int *p);
  void visitStr(Str *p);
  void visitBool(Bool *p);
  void visitVoid(Void *p);
  void visitStruct(Struct *p);
  void visitFun(Fun *p);
  void visitListType(ListType *p);
  void visitExpr(Expr *p); /* abstract class */
  void visitENullCast(ENullCast *p);
  void visitEVar(EVar *p);
  void visitELitInt(ELitInt *p);
  void visitELitTrue(ELitTrue *p);
  void visitELitFalse(ELitFalse *p);
  void visitEApp(EApp *p);
  void visitEString(EString *p);
  void visitNeg(Neg *p);
  void visitNot(Not *p);
  void visitEMul(EMul *p);
  void visitEAdd(EAdd *p);
  void visitERel(ERel *p);
  void visitEAnd(EAnd *p);
  void visitEOr(EOr *p);
  void visitListExpr(ListExpr *p);
  void visitAddOp(AddOp *p); /* abstract class */
  void visitPlus(Plus *p);
  void visitMinus(Minus *p);
  void visitMulOp(MulOp *p); /* abstract class */
  void visitTimes(Times *p);
  void visitDiv(Div *p);
  void visitMod(Mod *p);
  void visitRelOp(RelOp *p); /* abstract class */
  void visitLTH(LTH *p);
  void visitLE(LE *p);
  void visitGTH(GTH *p);
  void visitGE(GE *p);
  void visitEQU(EQU *p);
  void visitNE(NE *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
 protected:
  void inline bufAppend(const char *s)
  {
    int len = strlen(s);
    while (cur_ + len > buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    for(int n = 0; n < len; n++)
    {
      buf_[cur_ + n] = s[n];
    }
    cur_ += len;
    buf_[cur_] = 0;
  }

  void inline bufAppend(const char c)
  {
    if (cur_ == buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    cur_++;
    buf_[cur_] = 0;
  }

  void inline bufAppend(String str)
  {
    const char *s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    cur_ = 0;
    buf_size = BUFFER_INITIAL;
    resizeBuffer();
    memset(buf_, 0, buf_size);
  }

  void inline resizeBuffer(void)
  {
    char *temp = (char *) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
  char *buf_;
  int cur_, buf_size;
};

#endif