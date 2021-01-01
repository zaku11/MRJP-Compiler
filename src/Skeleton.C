/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"



void Skeleton::visitProgram(Program *t) {} //abstract class
void Skeleton::visitTopDef(TopDef *t) {} //abstract class
void Skeleton::visitClassMember(ClassMember *t) {} //abstract class
void Skeleton::visitIdentExpan(IdentExpan *t) {} //abstract class
void Skeleton::visitArg(Arg *t) {} //abstract class
void Skeleton::visitBlock(Block *t) {} //abstract class
void Skeleton::visitStmt(Stmt *t) {} //abstract class
void Skeleton::visitItem(Item *t) {} //abstract class
void Skeleton::visitType(Type *t) {} //abstract class
void Skeleton::visitExpr(Expr *t) {} //abstract class
void Skeleton::visitAddOp(AddOp *t) {} //abstract class
void Skeleton::visitMulOp(MulOp *t) {} //abstract class
void Skeleton::visitRelOp(RelOp *t) {} //abstract class

void Skeleton::visitProgramDef(ProgramDef *program_def)
{
  /* Code For ProgramDef Goes Here */

  program_def->listtopdef_->accept(this);

}

void Skeleton::visitFnDef(FnDef *fn_def)
{
  /* Code For FnDef Goes Here */

  fn_def->type_->accept(this);
  visitIdent(fn_def->ident_);
  fn_def->listarg_->accept(this);
  fn_def->block_->accept(this);

}

void Skeleton::visitClassDefNoInherit(ClassDefNoInherit *class_def_no_inherit)
{
  /* Code For ClassDefNoInherit Goes Here */

  visitIdent(class_def_no_inherit->ident_);
  class_def_no_inherit->listclassmember_->accept(this);

}

void Skeleton::visitClassDefInherit(ClassDefInherit *class_def_inherit)
{
  /* Code For ClassDefInherit Goes Here */

  visitIdent(class_def_inherit->ident_1);
  visitIdent(class_def_inherit->ident_2);
  class_def_inherit->listclassmember_->accept(this);

}

void Skeleton::visitEmptyClassDef(EmptyClassDef *empty_class_def)
{
  /* Code For EmptyClassDef Goes Here */

  visitIdent(empty_class_def->ident_);

}

void Skeleton::visitClassMem(ClassMem *class_mem)
{
  /* Code For ClassMem Goes Here */

  class_mem->type_->accept(this);
  visitIdent(class_mem->ident_);

}

void Skeleton::visitClassFun(ClassFun *class_fun)
{
  /* Code For ClassFun Goes Here */

  class_fun->type_->accept(this);
  visitIdent(class_fun->ident_);
  class_fun->listarg_->accept(this);
  class_fun->block_->accept(this);

}

void Skeleton::visitIdentExp(IdentExp *ident_exp)
{
  /* Code For IdentExp Goes Here */

  ident_exp->identexpan_->accept(this);
  visitIdent(ident_exp->ident_);

}

void Skeleton::visitIdentExpFun(IdentExpFun *ident_exp_fun)
{
  /* Code For IdentExpFun Goes Here */

  ident_exp_fun->identexpan_->accept(this);
  visitIdent(ident_exp_fun->ident_);
  ident_exp_fun->listexpr_->accept(this);

}

void Skeleton::visitIdentExpSimple(IdentExpSimple *ident_exp_simple)
{
  /* Code For IdentExpSimple Goes Here */

  visitIdent(ident_exp_simple->ident_);

}

void Skeleton::visitIdentExpSimpleFun(IdentExpSimpleFun *ident_exp_simple_fun)
{
  /* Code For IdentExpSimpleFun Goes Here */

  visitIdent(ident_exp_simple_fun->ident_);
  ident_exp_simple_fun->listexpr_->accept(this);

}

void Skeleton::visitArgDef(ArgDef *arg_def)
{
  /* Code For ArgDef Goes Here */

  arg_def->type_->accept(this);
  visitIdent(arg_def->ident_);

}

void Skeleton::visitBlockDef(BlockDef *block_def)
{
  /* Code For BlockDef Goes Here */

  block_def->liststmt_->accept(this);

}

void Skeleton::visitEmpty(Empty *empty)
{
  /* Code For Empty Goes Here */


}

void Skeleton::visitBStmt(BStmt *b_stmt)
{
  /* Code For BStmt Goes Here */

  b_stmt->block_->accept(this);

}

void Skeleton::visitDecl(Decl *decl)
{
  /* Code For Decl Goes Here */

  decl->type_->accept(this);
  decl->listitem_->accept(this);

}

void Skeleton::visitAss(Ass *ass)
{
  /* Code For Ass Goes Here */

  ass->identexpan_->accept(this);
  ass->expr_->accept(this);

}

void Skeleton::visitIncr(Incr *incr)
{
  /* Code For Incr Goes Here */

  incr->identexpan_->accept(this);

}

void Skeleton::visitDecr(Decr *decr)
{
  /* Code For Decr Goes Here */

  decr->identexpan_->accept(this);

}

void Skeleton::visitRet(Ret *ret)
{
  /* Code For Ret Goes Here */

  ret->expr_->accept(this);

}

void Skeleton::visitVRet(VRet *v_ret)
{
  /* Code For VRet Goes Here */


}

void Skeleton::visitCond(Cond *cond)
{
  /* Code For Cond Goes Here */

  cond->expr_->accept(this);
  cond->stmt_->accept(this);

}

void Skeleton::visitCondElse(CondElse *cond_else)
{
  /* Code For CondElse Goes Here */

  cond_else->expr_->accept(this);
  cond_else->stmt_1->accept(this);
  cond_else->stmt_2->accept(this);

}

void Skeleton::visitWhile(While *while_)
{
  /* Code For While Goes Here */

  while_->expr_->accept(this);
  while_->stmt_->accept(this);

}

void Skeleton::visitSExp(SExp *s_exp)
{
  /* Code For SExp Goes Here */

  s_exp->expr_->accept(this);

}

void Skeleton::visitNoInit(NoInit *no_init)
{
  /* Code For NoInit Goes Here */

  visitIdent(no_init->ident_);

}

void Skeleton::visitInit(Init *init)
{
  /* Code For Init Goes Here */

  visitIdent(init->ident_);
  init->expr_->accept(this);

}

void Skeleton::visitInt(Int *int_)
{
  /* Code For Int Goes Here */


}

void Skeleton::visitStr(Str *str)
{
  /* Code For Str Goes Here */


}

void Skeleton::visitBool(Bool *bool_)
{
  /* Code For Bool Goes Here */


}

void Skeleton::visitVoid(Void *void_)
{
  /* Code For Void Goes Here */


}

void Skeleton::visitClass(Class *class_)
{
  /* Code For Class Goes Here */

  visitIdent(class_->ident_);

}

void Skeleton::visitFun(Fun *fun)
{
  /* Code For Fun Goes Here */

  fun->type_->accept(this);
  fun->listtype_->accept(this);

}

void Skeleton::visitENullCast(ENullCast *e_null_cast)
{
  /* Code For ENullCast Goes Here */

  e_null_cast->type_->accept(this);

}

void Skeleton::visitENewClass(ENewClass *e_new_struct)
{
  /* Code For ENewClass Goes Here */

  e_new_struct->type_->accept(this);

}

void Skeleton::visitEVar(EVar *e_var)
{
  /* Code For EVar Goes Here */

  e_var->identexpan_->accept(this);

}

void Skeleton::visitELitInt(ELitInt *e_lit_int)
{
  /* Code For ELitInt Goes Here */

  visitInteger(e_lit_int->integer_);

}

void Skeleton::visitELitTrue(ELitTrue *e_lit_true)
{
  /* Code For ELitTrue Goes Here */


}

void Skeleton::visitELitFalse(ELitFalse *e_lit_false)
{
  /* Code For ELitFalse Goes Here */


}

void Skeleton::visitEString(EString *e_string)
{
  /* Code For EString Goes Here */

  visitString(e_string->string_);

}

void Skeleton::visitNeg(Neg *neg)
{
  /* Code For Neg Goes Here */

  neg->expr_->accept(this);

}

void Skeleton::visitNot(Not *not_)
{
  /* Code For Not Goes Here */

  not_->expr_->accept(this);

}

void Skeleton::visitEMul(EMul *e_mul)
{
  /* Code For EMul Goes Here */

  e_mul->expr_1->accept(this);
  e_mul->mulop_->accept(this);
  e_mul->expr_2->accept(this);

}

void Skeleton::visitEAdd(EAdd *e_add)
{
  /* Code For EAdd Goes Here */

  e_add->expr_1->accept(this);
  e_add->addop_->accept(this);
  e_add->expr_2->accept(this);

}

void Skeleton::visitERel(ERel *e_rel)
{
  /* Code For ERel Goes Here */

  e_rel->expr_1->accept(this);
  e_rel->relop_->accept(this);
  e_rel->expr_2->accept(this);

}

void Skeleton::visitEAnd(EAnd *e_and)
{
  /* Code For EAnd Goes Here */

  e_and->expr_1->accept(this);
  e_and->expr_2->accept(this);

}

void Skeleton::visitEOr(EOr *e_or)
{
  /* Code For EOr Goes Here */

  e_or->expr_1->accept(this);
  e_or->expr_2->accept(this);

}

void Skeleton::visitPlus(Plus *plus)
{
  /* Code For Plus Goes Here */


}

void Skeleton::visitMinus(Minus *minus)
{
  /* Code For Minus Goes Here */


}

void Skeleton::visitTimes(Times *times)
{
  /* Code For Times Goes Here */


}

void Skeleton::visitDiv(Div *div)
{
  /* Code For Div Goes Here */


}

void Skeleton::visitMod(Mod *mod)
{
  /* Code For Mod Goes Here */


}

void Skeleton::visitLTH(LTH *lth)
{
  /* Code For LTH Goes Here */


}

void Skeleton::visitLE(LE *le)
{
  /* Code For LE Goes Here */


}

void Skeleton::visitGTH(GTH *gth)
{
  /* Code For GTH Goes Here */


}

void Skeleton::visitGE(GE *ge)
{
  /* Code For GE Goes Here */


}

void Skeleton::visitEQU(EQU *equ)
{
  /* Code For EQU Goes Here */


}

void Skeleton::visitNE(NE *ne)
{
  /* Code For NE Goes Here */


}


void Skeleton::visitListClassMember(ListClassMember *list_class_member)
{
  for (ListClassMember::iterator i = list_class_member->begin() ; i != list_class_member->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListTopDef(ListTopDef *list_top_def)
{
  for (ListTopDef::iterator i = list_top_def->begin() ; i != list_top_def->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListArg(ListArg *list_arg)
{
  for (ListArg::iterator i = list_arg->begin() ; i != list_arg->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListStmt(ListStmt *list_stmt)
{
  for (ListStmt::iterator i = list_stmt->begin() ; i != list_stmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListItem(ListItem *list_item)
{
  for (ListItem::iterator i = list_item->begin() ; i != list_item->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListType(ListType *list_type)
{
  for (ListType::iterator i = list_type->begin() ; i != list_type->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListExpr(ListExpr *list_expr)
{
  for (ListExpr::iterator i = list_expr->begin() ; i != list_expr->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void Skeleton::visitInteger(Integer x)
{
  /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void Skeleton::visitString(String x)
{
  /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}



