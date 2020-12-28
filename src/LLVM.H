#ifndef LLVM_HEADER
#define LLVM_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <variant>
#include <map>
#include <set>
#include <vector>
#include <exception>

using std :: string;
using std :: set;
using std :: map;
using std :: pair;
using std :: vector;

class LLVM : public Visitor
{
protected:
  int last_var = 1;
  int last_label_num = 0;

  // Type* current_return_type;
  
  // map<Ident, Type*> var_types;
  // string last_evaluated_expr_type;
  bool skipping_instructions = false;
  map<Ident, int> current_var_number;
  map<Ident, int> last_var_numbers;
  map<Ident, pair<Type*, vector<Type*> > > function_data;

  // string label_true;
  // string label_false;

public:
  string output;

  LLVM(void);
  ~LLVM(void);
  // void allocAndStore(Ident id);
  void addToOutput(string text);
  void addConstant(string text);
  void addReference(string id);
  void deleteReference(string id);
  bool doesEndWithReturn();
  map <string, int> reference_map;
  vector <string> new_things_added;
  // bool isLabelLast();
  // bool isFnEmpty();

  void run(Visitable *v);
  void run_with_rollback(Visitable* v);
  string getCurrentVarNum(Ident id);
  string getCurrentVarNum(IdentExpan &id);
  string genLabel(string text);
  string genTmpVar(string text);

  void visitProgram(Program *p); /* abstract class */
  void visitProgramDef(ProgramDef *p);
  void visitTopDef(TopDef *p); /* abstract class */
  void visitFnDef(FnDef *p);

  void visitStructDef(StructDef *p);
  void visitEmptyStructDef(EmptyStructDef *p);

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

  String processSingle(Expr* e1); 
  std :: pair<String, String> process(Expr* e1, Expr* e2);

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