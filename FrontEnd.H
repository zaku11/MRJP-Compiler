#ifndef FRONTEND_HEADER
#define FRONTEND_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <variant>
#include <map>
#include <set>


// enum TYPE {
//   INT = 0,
//   VOID = 1,
//   BOOLEAN = 2,
//   STRING = 3,
// };

typedef std::string TYPE;
//  "void" VOID;
// typedef "int" INT;
// typedef "bool" BOOLEAN;
// typedef "string" STRING;

struct NOVALUE {
};

// NOVALUE means here that the calculation was impossible
typedef std :: variant <int, bool, std::string, NOVALUE> VALUE;
typedef std :: map<Ident, TYPE> VarEnv;
typedef std :: map<Ident, std :: pair<std :: vector<TYPE>, TYPE>> FunEnv;
typedef std :: map <TYPE, std :: map<Ident, TYPE> > StructEnv;

class StaticAnalyzer : public Visitor
{
 protected:
  int _n_, _i_;
  const NOVALUE DECOY = NOVALUE{};
  const TYPE VOID = "void";
  const TYPE BOOLEAN = "bool";
  const TYPE INT = "int";
  const TYPE STRING = "string";

  // TYPE last_chain_type = "";
  TYPE last_evaluated_expr = "";
  VALUE last_evaluated_expr_value = DECOY;
  TYPE expected_return_type = "";
  TYPE last_return = "";


  std :: set <Ident> defined_in_current_scope; 
  
  StructEnv env_of_structures;
  VarEnv env_of_vars;
  FunEnv env_of_functions;
  // VarEnv new_env_of_vars;
  // FunEnv new_env_of_functions;
  
  void run_with_rollback(Visitable *v);
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
 public:
  StaticAnalyzer(void);
  ~StaticAnalyzer(void);
  void analyze(Visitable *v);

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
  void visitListItem(ListItem *p);
  void visitType(Type *p); /* abstract class */
  void visitInt(Int *p);
  void visitInitStruct(InitStruct *p);
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
};

#endif