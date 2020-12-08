#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"


class Skeleton : public Visitor
{
public:
  void visitProgram(Program *p);
  void visitTopDef(TopDef *p);
  void visitStructMember(StructMember *p);
  void visitIdentExpan(IdentExpan *p);
  void visitArg(Arg *p);
  void visitBlock(Block *p);
  void visitStmt(Stmt *p);
  void visitItem(Item *p);
  void visitType(Type *p);
  void visitExpr(Expr *p);
  void visitAddOp(AddOp *p);
  void visitMulOp(MulOp *p);
  void visitRelOp(RelOp *p);
  void visitProgramDef(ProgramDef *p);
  void visitFnDef(FnDef *p);
  void visitStructMemNoInit(StructMemNoInit *p);
  void visitStructMemInit(StructMemInit *p);
  void visitStructDef(StructDef *p);
  void visitEmptyStructDef(EmptyStructDef *p);
  void visitIdentExp(IdentExp *p);
  void visitIdentExpSimple(IdentExpSimple *p);
  void visitArgDef(ArgDef *p);
  void visitBlockDef(BlockDef *p);
  void visitEmpty(Empty *p);
  void visitBStmt(BStmt *p);
  void visitDecl(Decl *p);
  void visitNoInit(NoInit *p);
  void visitInit(Init *p);
  void visitInitStruct(InitStruct *p);
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
  void visitInt(Int *p);
  void visitStr(Str *p);
  void visitBool(Bool *p);
  void visitVoid(Void *p);
  void visitStruct(Struct *p);
  void visitFun(Fun *p);
  void visitENullCastType(ENullCastType *p);
  void visitENullCastIdent(ENullCastIdent *p);
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
  void visitPlus(Plus *p);
  void visitMinus(Minus *p);
  void visitTimes(Times *p);
  void visitDiv(Div *p);
  void visitMod(Mod *p);
  void visitLTH(LTH *p);
  void visitLE(LE *p);
  void visitGTH(GTH *p);
  void visitGE(GE *p);
  void visitEQU(EQU *p);
  void visitNE(NE *p);
  void visitListStructMember(ListStructMember *p);
  void visitListTopDef(ListTopDef *p);
  void visitListArg(ListArg *p);
  void visitListStmt(ListStmt *p);
  void visitListItem(ListItem *p);
  void visitListType(ListType *p);
  void visitListExpr(ListExpr *p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

};


#endif
