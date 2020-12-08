/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "Latte.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "Absyn.H"
typedef struct yy_buffer_state *YY_BUFFER_STATE;
int yyparse(void);
int yylex(void);
YY_BUFFER_STATE yy_scan_string(const char *str);
void yy_delete_buffer(YY_BUFFER_STATE buf);
int yy_mylinenumber;
int initialize_lexer(FILE * inp);
int yywrap(void)
{
  return 1;
}
void yyerror(const char *str)
{
  extern char *yytext;
  fprintf(stderr,"error: line %d: %s at %s\n", 
    yy_mylinenumber, str, yytext);
}



static Program* YY_RESULT_Program_ = 0;
Program* pProgram(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Program_;
  }
}
Program* pProgram(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Program_;
  }
}

static TopDef* YY_RESULT_TopDef_ = 0;
TopDef* pTopDef(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_TopDef_;
  }
}
TopDef* pTopDef(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_TopDef_;
  }
}

static StructMember* YY_RESULT_StructMember_ = 0;
StructMember* pStructMember(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_StructMember_;
  }
}
StructMember* pStructMember(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_StructMember_;
  }
}

static ListStructMember* YY_RESULT_ListStructMember_ = 0;
ListStructMember* pListStructMember(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListStructMember_;
  }
}
ListStructMember* pListStructMember(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListStructMember_;
  }
}

static IdentExpan* YY_RESULT_IdentExpan_ = 0;
IdentExpan* pIdentExpan(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_IdentExpan_;
  }
}
IdentExpan* pIdentExpan(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_IdentExpan_;
  }
}

static ListTopDef* YY_RESULT_ListTopDef_ = 0;
ListTopDef* pListTopDef(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListTopDef_;
  }
}
ListTopDef* pListTopDef(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListTopDef_;
  }
}

static Arg* YY_RESULT_Arg_ = 0;
Arg* pArg(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Arg_;
  }
}
Arg* pArg(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Arg_;
  }
}

static ListArg* YY_RESULT_ListArg_ = 0;
ListArg* pListArg(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListArg_;
  }
}
ListArg* pListArg(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListArg_;
  }
}

static Block* YY_RESULT_Block_ = 0;
Block* pBlock(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Block_;
  }
}
Block* pBlock(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Block_;
  }
}

static ListStmt* YY_RESULT_ListStmt_ = 0;
ListStmt* pListStmt(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListStmt_;
  }
}
ListStmt* pListStmt(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListStmt_;
  }
}

static Stmt* YY_RESULT_Stmt_ = 0;
Stmt* pStmt(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Stmt_;
  }
}
Stmt* pStmt(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Stmt_;
  }
}

static Item* YY_RESULT_Item_ = 0;
Item* pItem(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Item_;
  }
}
Item* pItem(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Item_;
  }
}

static ListItem* YY_RESULT_ListItem_ = 0;
ListItem* pListItem(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListItem_;
  }
}
ListItem* pListItem(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListItem_;
  }
}

static Type* YY_RESULT_Type_ = 0;
Type* pType(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Type_;
  }
}
Type* pType(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Type_;
  }
}

static ListType* YY_RESULT_ListType_ = 0;
ListType* pListType(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListType_;
  }
}
ListType* pListType(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListType_;
  }
}

static Expr* YY_RESULT_Expr_ = 0;
Expr* pExpr(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Expr_;
  }
}
Expr* pExpr(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Expr_;
  }
}

static ListExpr* YY_RESULT_ListExpr_ = 0;
ListExpr* pListExpr(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListExpr_;
  }
}
ListExpr* pListExpr(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListExpr_;
  }
}

static AddOp* YY_RESULT_AddOp_ = 0;
AddOp* pAddOp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_AddOp_;
  }
}
AddOp* pAddOp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_AddOp_;
  }
}

static MulOp* YY_RESULT_MulOp_ = 0;
MulOp* pMulOp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_MulOp_;
  }
}
MulOp* pMulOp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_MulOp_;
  }
}

static RelOp* YY_RESULT_RelOp_ = 0;
RelOp* pRelOp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_RelOp_;
  }
}
RelOp* pRelOp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_RelOp_;
  }
}




#line 757 "Parser.C" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    _ERROR_ = 258,
    _SYMB_0 = 259,
    _SYMB_1 = 260,
    _SYMB_2 = 261,
    _SYMB_3 = 262,
    _SYMB_4 = 263,
    _SYMB_5 = 264,
    _SYMB_6 = 265,
    _SYMB_7 = 266,
    _SYMB_8 = 267,
    _SYMB_9 = 268,
    _SYMB_10 = 269,
    _SYMB_11 = 270,
    _SYMB_12 = 271,
    _SYMB_13 = 272,
    _SYMB_14 = 273,
    _SYMB_15 = 274,
    _SYMB_16 = 275,
    _SYMB_17 = 276,
    _SYMB_18 = 277,
    _SYMB_19 = 278,
    _SYMB_20 = 279,
    _SYMB_21 = 280,
    _SYMB_22 = 281,
    _SYMB_23 = 282,
    _SYMB_24 = 283,
    _SYMB_25 = 284,
    _SYMB_26 = 285,
    _SYMB_27 = 286,
    _SYMB_28 = 287,
    _SYMB_29 = 288,
    _SYMB_30 = 289,
    _SYMB_31 = 290,
    _SYMB_32 = 291,
    _SYMB_33 = 292,
    _SYMB_34 = 293,
    _SYMB_35 = 294,
    _SYMB_36 = 295,
    _STRING_ = 296,
    _INTEGER_ = 297,
    _IDENT_ = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 694 "Latte.y" /* yacc.c:355  */

  int int_;
  char char_;
  double double_;
  char* string_;
  Program* program_;
  TopDef* topdef_;
  StructMember* structmember_;
  ListStructMember* liststructmember_;
  IdentExpan* identexpan_;
  ListTopDef* listtopdef_;
  Arg* arg_;
  ListArg* listarg_;
  Block* block_;
  ListStmt* liststmt_;
  Stmt* stmt_;
  Item* item_;
  ListItem* listitem_;
  Type* type_;
  ListType* listtype_;
  Expr* expr_;
  ListExpr* listexpr_;
  AddOp* addop_;
  MulOp* mulop_;
  RelOp* relop_;

#line 865 "Parser.C" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 882 "Parser.C" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  137

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   793,   793,   795,   796,   797,   799,   800,   802,   803,
     805,   806,   808,   809,   811,   813,   814,   815,   817,   819,
     820,   822,   823,   824,   825,   826,   827,   828,   829,   830,
     831,   832,   833,   834,   836,   837,   838,   840,   841,   843,
     844,   845,   846,   847,   853,   854,   855,   856,   857,   858,
     859,   860,   861,   863,   864,   865,   867,   868,   870,   871,
     873,   874,   876,   877,   879,   880,   882,   883,   884,   886,
     887,   889,   890,   891,   893,   894,   895,   896,   897,   898
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_ERROR_", "_SYMB_0", "_SYMB_1",
  "_SYMB_2", "_SYMB_3", "_SYMB_4", "_SYMB_5", "_SYMB_6", "_SYMB_7",
  "_SYMB_8", "_SYMB_9", "_SYMB_10", "_SYMB_11", "_SYMB_12", "_SYMB_13",
  "_SYMB_14", "_SYMB_15", "_SYMB_16", "_SYMB_17", "_SYMB_18", "_SYMB_19",
  "_SYMB_20", "_SYMB_21", "_SYMB_22", "_SYMB_23", "_SYMB_24", "_SYMB_25",
  "_SYMB_26", "_SYMB_27", "_SYMB_28", "_SYMB_29", "_SYMB_30", "_SYMB_31",
  "_SYMB_32", "_SYMB_33", "_SYMB_34", "_SYMB_35", "_SYMB_36", "_STRING_",
  "_INTEGER_", "_IDENT_", "$accept", "Program", "TopDef", "StructMember",
  "ListStructMember", "IdentExpan", "ListTopDef", "Arg", "ListArg",
  "Block", "ListStmt", "Stmt", "Item", "ListItem", "Type", "Expr6",
  "Expr5", "Expr4", "Expr3", "Expr2", "Expr1", "Expr", "ListExpr", "AddOp",
  "MulOp", "RelOp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

#define YYPACT_NINF -108

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-108)))

#define YYTABLE_NINF -44

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -18,  -108,   -41,  -108,  -108,  -108,  -108,     9,   -18,  -108,
     -23,    14,  -108,  -108,    20,   114,   149,  -108,   149,    35,
     -14,    38,    41,     8,  -108,  -108,    58,   149,    70,  -108,
    -108,   124,  -108,  -108,  -108,    19,    55,    55,  -108,  -108,
    -108,  -108,    72,    74,  -108,  -108,    34,    -2,   177,    78,
      84,    -1,    68,    86,    94,  -108,  -108,   124,    57,  -108,
    -108,  -108,   124,  -108,  -108,   124,   124,  -108,  -108,  -108,
    -108,  -108,  -108,   124,   124,  -108,  -108,  -108,   104,    88,
     116,     2,    56,  -108,  -108,    81,   115,    90,    92,  -108,
     125,   130,  -108,  -108,    34,  -108,    -2,  -108,   124,  -108,
     134,   124,   103,   137,   142,   143,   147,   148,  -108,  -108,
    -108,   124,  -108,   159,  -108,   164,   127,   162,  -108,  -108,
     118,    81,  -108,  -108,    73,    73,   166,  -108,   131,  -108,
    -108,   145,  -108,  -108,  -108,    73,  -108
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    41,     0,    39,    40,    42,    43,     0,    12,     2,
       0,     0,     1,    13,     0,     0,    15,     5,     8,     0,
       0,    16,     0,     0,     9,     4,     0,    15,     0,    14,
       6,     0,    17,    19,     3,     0,     0,     0,    49,    48,
      51,    47,    11,    46,    55,    57,    59,    61,    63,    65,
       0,     0,    11,     0,     0,    53,    54,    66,     0,    71,
      72,    73,     0,    70,    69,     0,     0,    74,    75,    76,
      77,    78,    79,     0,     0,     7,    21,    18,     0,     0,
       0,    11,    46,    22,    20,     0,     0,     0,     0,    52,
      67,     0,    10,    56,    58,    62,    60,    64,     0,    29,
       0,     0,     0,     0,     0,    34,    37,     0,    33,    45,
      44,    66,    50,     0,    28,     0,     0,     0,    26,    27,
       0,     0,    23,    68,     0,     0,     0,    24,     0,    35,
      38,    30,    32,    25,    36,     0,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,  -108,  -108,   155,   -50,   168,  -108,   153,   156,
    -108,  -107,  -108,    62,   163,    46,   123,   122,   121,  -108,
     129,   -31,    80,  -108,  -108,  -108
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,    18,    19,    43,     9,    21,    22,    83,
      51,    84,   106,   107,    85,    44,    45,    46,    47,    48,
      49,    86,    91,    65,    62,    73
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    82,    11,    35,    54,    76,    57,    33,    77,    12,
       1,     2,    63,    36,    37,     3,    64,   131,   132,     4,
      14,     5,    15,    35,    16,     6,    90,     1,   136,    26,
      38,    78,     3,    36,    37,    79,     4,    39,     5,    80,
      40,    41,    81,    97,    25,   -43,    28,     1,   100,    27,
      38,    29,     3,    59,    60,    61,     4,    39,     5,    35,
      40,    41,    52,   102,    30,    31,    58,   113,   103,   104,
     115,   117,    57,    87,    82,    82,    57,    35,    33,    76,
      90,    33,    55,    56,    58,    82,    38,    36,    37,   129,
      75,    88,    35,    39,    99,    74,    40,    41,    42,    89,
      92,     1,    36,    37,    38,    78,     3,    35,    98,    79,
       4,    39,     5,    80,    40,    41,    81,    36,    37,    38,
     101,   108,    35,    17,   105,   109,    39,   110,    35,    40,
      41,    42,    36,    37,    38,   112,   111,   116,    36,    37,
     114,    39,     1,   118,    40,    41,    42,     3,   119,    38,
     120,     4,   128,     5,   122,    38,    39,     6,   121,    40,
      41,    42,    39,    10,   124,    40,    41,    42,   127,   125,
     126,    10,   133,    24,   134,   135,    13,     1,    20,    23,
      32,    20,     3,   130,    34,    93,     4,    94,     5,     0,
      23,   123,     6,    66,    96,    95,     0,     0,    53,    67,
      68,    69,    70,    71,    72
};

static const yytype_int16 yycheck[] =
{
      31,    51,    43,     4,    35,     6,     4,     8,     9,     0,
      28,    29,    14,    14,    15,    33,    18,   124,   125,    37,
      43,    39,     8,     4,     4,    43,    57,    28,   135,    43,
      31,    32,    33,    14,    15,    36,    37,    38,    39,    40,
      41,    42,    43,    74,     9,    43,     5,    28,    79,    11,
      31,    43,    33,    19,    20,    21,    37,    38,    39,     4,
      41,    42,    43,     7,     6,     7,    10,    98,    12,    13,
     101,   102,     4,     5,   124,   125,     4,     4,     8,     6,
     111,     8,    36,    37,    10,   135,    31,    14,    15,   120,
       6,     5,     4,    38,     6,    17,    41,    42,    43,     5,
      43,    28,    14,    15,    31,    32,    33,     4,     4,    36,
      37,    38,    39,    40,    41,    42,    43,    14,    15,    31,
       4,     6,     4,     9,    43,    35,    38,    35,     4,    41,
      42,    43,    14,    15,    31,     5,    11,    34,    14,    15,
       6,    38,    28,     6,    41,    42,    43,    33,     6,    31,
       7,    37,    34,    39,     6,    31,    38,    43,    11,    41,
      42,    43,    38,     0,     5,    41,    42,    43,     6,     5,
      43,     8,     6,    18,    43,    30,     8,    28,    15,    16,
      27,    18,    33,   121,    28,    62,    37,    65,    39,    -1,
      27,   111,    43,    16,    73,    66,    -1,    -1,    35,    22,
      23,    24,    25,    26,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    33,    37,    39,    43,    45,    46,    50,
      58,    43,     0,    50,    43,     8,     4,     9,    47,    48,
      58,    51,    52,    58,    48,     9,    43,    11,     5,    43,
       6,     7,    52,     8,    53,     4,    14,    15,    31,    38,
      41,    42,    43,    49,    59,    60,    61,    62,    63,    64,
      65,    54,    43,    58,    65,    59,    59,     4,    10,    19,
      20,    21,    68,    14,    18,    67,    16,    22,    23,    24,
      25,    26,    27,    69,    17,     6,     6,     9,    32,    36,
      40,    43,    49,    53,    55,    58,    65,     5,     5,     5,
      65,    66,    43,    60,    61,    64,    62,    65,     4,     6,
      65,     4,     7,    12,    13,    43,    56,    57,     6,    35,
      35,    11,     5,    65,     6,    65,    34,    65,     6,     6,
       7,    11,     6,    66,     5,     5,    43,     6,    34,    65,
      57,    55,    55,     6,    43,    30,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    46,    46,    47,    47,    48,    48,
      49,    49,    50,    50,    51,    52,    52,    52,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    56,    56,    56,    57,    57,    58,
      58,    58,    58,    58,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    66,    66,    66,    67,
      67,    68,    68,    68,    69,    69,    69,    69,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     6,     5,     4,     3,     5,     1,     2,
       3,     1,     1,     2,     2,     0,     1,     3,     3,     0,
       2,     1,     1,     3,     4,     5,     3,     3,     3,     2,
       5,     7,     5,     2,     1,     3,     4,     1,     3,     1,
       1,     1,     1,     1,     4,     4,     1,     1,     1,     1,
       4,     1,     3,     2,     2,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     0,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 793 "Latte.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[0].listtopdef_)->begin(),(yyvsp[0].listtopdef_)->end()) ;(yyval.program_) = new ProgramDef((yyvsp[0].listtopdef_)); (yyval.program_)->line_number = yy_mylinenumber; YY_RESULT_Program_= (yyval.program_); }
#line 2069 "Parser.C" /* yacc.c:1646  */
    break;

  case 3:
#line 795 "Latte.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[-2].listarg_)->begin(),(yyvsp[-2].listarg_)->end()) ;(yyval.topdef_) = new FnDef((yyvsp[-5].type_), (yyvsp[-4].string_), (yyvsp[-2].listarg_), (yyvsp[0].block_)); (yyval.topdef_)->line_number = yy_mylinenumber;  }
#line 2075 "Parser.C" /* yacc.c:1646  */
    break;

  case 4:
#line 796 "Latte.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[-1].liststructmember_)->begin(),(yyvsp[-1].liststructmember_)->end()) ;(yyval.topdef_) = new StructDef((yyvsp[-3].string_), (yyvsp[-1].liststructmember_)); (yyval.topdef_)->line_number = yy_mylinenumber;  }
#line 2081 "Parser.C" /* yacc.c:1646  */
    break;

  case 5:
#line 797 "Latte.y" /* yacc.c:1646  */
    {  (yyval.topdef_) = new EmptyStructDef((yyvsp[-2].string_)); (yyval.topdef_)->line_number = yy_mylinenumber;  }
#line 2087 "Parser.C" /* yacc.c:1646  */
    break;

  case 6:
#line 799 "Latte.y" /* yacc.c:1646  */
    {  (yyval.structmember_) = new StructMemNoInit((yyvsp[-2].type_), (yyvsp[-1].string_)); (yyval.structmember_)->line_number = yy_mylinenumber;  }
#line 2093 "Parser.C" /* yacc.c:1646  */
    break;

  case 7:
#line 800 "Latte.y" /* yacc.c:1646  */
    {  (yyval.structmember_) = new StructMemInit((yyvsp[-4].type_), (yyvsp[-3].string_), (yyvsp[-1].expr_)); (yyval.structmember_)->line_number = yy_mylinenumber;  }
#line 2099 "Parser.C" /* yacc.c:1646  */
    break;

  case 8:
#line 802 "Latte.y" /* yacc.c:1646  */
    {  (yyval.liststructmember_) = new ListStructMember() ; (yyval.liststructmember_)->push_back((yyvsp[0].structmember_));  }
#line 2105 "Parser.C" /* yacc.c:1646  */
    break;

  case 9:
#line 803 "Latte.y" /* yacc.c:1646  */
    {  (yyvsp[0].liststructmember_)->push_back((yyvsp[-1].structmember_)) ; (yyval.liststructmember_) = (yyvsp[0].liststructmember_) ;  }
#line 2111 "Parser.C" /* yacc.c:1646  */
    break;

  case 10:
#line 805 "Latte.y" /* yacc.c:1646  */
    {  (yyval.identexpan_) = new IdentExp((yyvsp[-2].identexpan_), (yyvsp[0].string_)); (yyval.identexpan_)->line_number = yy_mylinenumber;  }
#line 2117 "Parser.C" /* yacc.c:1646  */
    break;

  case 11:
#line 806 "Latte.y" /* yacc.c:1646  */
    {  (yyval.identexpan_) = new IdentExpSimple((yyvsp[0].string_)); (yyval.identexpan_)->line_number = yy_mylinenumber;  }
#line 2123 "Parser.C" /* yacc.c:1646  */
    break;

  case 12:
#line 808 "Latte.y" /* yacc.c:1646  */
    {  (yyval.listtopdef_) = new ListTopDef() ; (yyval.listtopdef_)->push_back((yyvsp[0].topdef_));  }
#line 2129 "Parser.C" /* yacc.c:1646  */
    break;

  case 13:
#line 809 "Latte.y" /* yacc.c:1646  */
    {  (yyvsp[0].listtopdef_)->push_back((yyvsp[-1].topdef_)) ; (yyval.listtopdef_) = (yyvsp[0].listtopdef_) ;  }
#line 2135 "Parser.C" /* yacc.c:1646  */
    break;

  case 14:
#line 811 "Latte.y" /* yacc.c:1646  */
    {  (yyval.arg_) = new ArgDef((yyvsp[-1].type_), (yyvsp[0].string_)); (yyval.arg_)->line_number = yy_mylinenumber;  }
#line 2141 "Parser.C" /* yacc.c:1646  */
    break;

  case 15:
#line 813 "Latte.y" /* yacc.c:1646  */
    {  (yyval.listarg_) = new ListArg();  }
#line 2147 "Parser.C" /* yacc.c:1646  */
    break;

  case 16:
#line 814 "Latte.y" /* yacc.c:1646  */
    {  (yyval.listarg_) = new ListArg() ; (yyval.listarg_)->push_back((yyvsp[0].arg_));  }
#line 2153 "Parser.C" /* yacc.c:1646  */
    break;

  case 17:
#line 815 "Latte.y" /* yacc.c:1646  */
    {  (yyvsp[0].listarg_)->push_back((yyvsp[-2].arg_)) ; (yyval.listarg_) = (yyvsp[0].listarg_) ;  }
#line 2159 "Parser.C" /* yacc.c:1646  */
    break;

  case 18:
#line 817 "Latte.y" /* yacc.c:1646  */
    {  (yyval.block_) = new BlockDef((yyvsp[-1].liststmt_)); (yyval.block_)->line_number = yy_mylinenumber;  }
#line 2165 "Parser.C" /* yacc.c:1646  */
    break;

  case 19:
#line 819 "Latte.y" /* yacc.c:1646  */
    {  (yyval.liststmt_) = new ListStmt();  }
#line 2171 "Parser.C" /* yacc.c:1646  */
    break;

  case 20:
#line 820 "Latte.y" /* yacc.c:1646  */
    {  (yyvsp[-1].liststmt_)->push_back((yyvsp[0].stmt_)) ; (yyval.liststmt_) = (yyvsp[-1].liststmt_) ;  }
#line 2177 "Parser.C" /* yacc.c:1646  */
    break;

  case 21:
#line 822 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new Empty(); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2183 "Parser.C" /* yacc.c:1646  */
    break;

  case 22:
#line 823 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new BStmt((yyvsp[0].block_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2189 "Parser.C" /* yacc.c:1646  */
    break;

  case 23:
#line 824 "Latte.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[-1].listitem_)->begin(),(yyvsp[-1].listitem_)->end()) ;(yyval.stmt_) = new Decl((yyvsp[-2].type_), (yyvsp[-1].listitem_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2195 "Parser.C" /* yacc.c:1646  */
    break;

  case 24:
#line 825 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new Ass((yyvsp[-3].identexpan_), (yyvsp[-1].expr_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2201 "Parser.C" /* yacc.c:1646  */
    break;

  case 25:
#line 826 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new NewStruct((yyvsp[-4].identexpan_), (yyvsp[-1].string_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2207 "Parser.C" /* yacc.c:1646  */
    break;

  case 26:
#line 827 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new Incr((yyvsp[-2].identexpan_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2213 "Parser.C" /* yacc.c:1646  */
    break;

  case 27:
#line 828 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new Decr((yyvsp[-2].identexpan_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2219 "Parser.C" /* yacc.c:1646  */
    break;

  case 28:
#line 829 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new Ret((yyvsp[-1].expr_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2225 "Parser.C" /* yacc.c:1646  */
    break;

  case 29:
#line 830 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new VRet(); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2231 "Parser.C" /* yacc.c:1646  */
    break;

  case 30:
#line 831 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new Cond((yyvsp[-2].expr_), (yyvsp[0].stmt_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2237 "Parser.C" /* yacc.c:1646  */
    break;

  case 31:
#line 832 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new CondElse((yyvsp[-4].expr_), (yyvsp[-2].stmt_), (yyvsp[0].stmt_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2243 "Parser.C" /* yacc.c:1646  */
    break;

  case 32:
#line 833 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new While((yyvsp[-2].expr_), (yyvsp[0].stmt_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2249 "Parser.C" /* yacc.c:1646  */
    break;

  case 33:
#line 834 "Latte.y" /* yacc.c:1646  */
    {  (yyval.stmt_) = new SExp((yyvsp[-1].expr_)); (yyval.stmt_)->line_number = yy_mylinenumber;  }
#line 2255 "Parser.C" /* yacc.c:1646  */
    break;

  case 34:
#line 836 "Latte.y" /* yacc.c:1646  */
    {  (yyval.item_) = new NoInit((yyvsp[0].string_)); (yyval.item_)->line_number = yy_mylinenumber;  }
#line 2261 "Parser.C" /* yacc.c:1646  */
    break;

  case 35:
#line 837 "Latte.y" /* yacc.c:1646  */
    {  (yyval.item_) = new Init((yyvsp[-2].string_), (yyvsp[0].expr_)); (yyval.item_)->line_number = yy_mylinenumber;  }
#line 2267 "Parser.C" /* yacc.c:1646  */
    break;

  case 36:
#line 838 "Latte.y" /* yacc.c:1646  */
    {  (yyval.item_) = new InitStruct((yyvsp[-3].string_), (yyvsp[0].string_)); (yyval.item_)->line_number = yy_mylinenumber;  }
#line 2273 "Parser.C" /* yacc.c:1646  */
    break;

  case 37:
#line 840 "Latte.y" /* yacc.c:1646  */
    {  (yyval.listitem_) = new ListItem() ; (yyval.listitem_)->push_back((yyvsp[0].item_));  }
#line 2279 "Parser.C" /* yacc.c:1646  */
    break;

  case 38:
#line 841 "Latte.y" /* yacc.c:1646  */
    {  (yyvsp[0].listitem_)->push_back((yyvsp[-2].item_)) ; (yyval.listitem_) = (yyvsp[0].listitem_) ;  }
#line 2285 "Parser.C" /* yacc.c:1646  */
    break;

  case 39:
#line 843 "Latte.y" /* yacc.c:1646  */
    {  (yyval.type_) = new Int(); (yyval.type_)->line_number = yy_mylinenumber;  }
#line 2291 "Parser.C" /* yacc.c:1646  */
    break;

  case 40:
#line 844 "Latte.y" /* yacc.c:1646  */
    {  (yyval.type_) = new Str(); (yyval.type_)->line_number = yy_mylinenumber;  }
#line 2297 "Parser.C" /* yacc.c:1646  */
    break;

  case 41:
#line 845 "Latte.y" /* yacc.c:1646  */
    {  (yyval.type_) = new Bool(); (yyval.type_)->line_number = yy_mylinenumber;  }
#line 2303 "Parser.C" /* yacc.c:1646  */
    break;

  case 42:
#line 846 "Latte.y" /* yacc.c:1646  */
    {  (yyval.type_) = new Void(); (yyval.type_)->line_number = yy_mylinenumber;  }
#line 2309 "Parser.C" /* yacc.c:1646  */
    break;

  case 43:
#line 847 "Latte.y" /* yacc.c:1646  */
    {  (yyval.type_) = new Struct((yyvsp[0].string_)); (yyval.type_)->line_number = yy_mylinenumber;  }
#line 2315 "Parser.C" /* yacc.c:1646  */
    break;

  case 44:
#line 853 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new ENullCastType((yyvsp[-2].type_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2321 "Parser.C" /* yacc.c:1646  */
    break;

  case 45:
#line 854 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new ENullCastIdent((yyvsp[-2].string_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2327 "Parser.C" /* yacc.c:1646  */
    break;

  case 46:
#line 855 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new EVar((yyvsp[0].identexpan_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2333 "Parser.C" /* yacc.c:1646  */
    break;

  case 47:
#line 856 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new ELitInt((yyvsp[0].int_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2339 "Parser.C" /* yacc.c:1646  */
    break;

  case 48:
#line 857 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new ELitTrue(); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2345 "Parser.C" /* yacc.c:1646  */
    break;

  case 49:
#line 858 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new ELitFalse(); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2351 "Parser.C" /* yacc.c:1646  */
    break;

  case 50:
#line 859 "Latte.y" /* yacc.c:1646  */
    {  std::reverse((yyvsp[-1].listexpr_)->begin(),(yyvsp[-1].listexpr_)->end()) ;(yyval.expr_) = new EApp((yyvsp[-3].string_), (yyvsp[-1].listexpr_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2357 "Parser.C" /* yacc.c:1646  */
    break;

  case 51:
#line 860 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new EString((yyvsp[0].string_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2363 "Parser.C" /* yacc.c:1646  */
    break;

  case 52:
#line 861 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = (yyvsp[-1].expr_);  }
#line 2369 "Parser.C" /* yacc.c:1646  */
    break;

  case 53:
#line 863 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new Neg((yyvsp[0].expr_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2375 "Parser.C" /* yacc.c:1646  */
    break;

  case 54:
#line 864 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new Not((yyvsp[0].expr_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2381 "Parser.C" /* yacc.c:1646  */
    break;

  case 55:
#line 865 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = (yyvsp[0].expr_);  }
#line 2387 "Parser.C" /* yacc.c:1646  */
    break;

  case 56:
#line 867 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new EMul((yyvsp[-2].expr_), (yyvsp[-1].mulop_), (yyvsp[0].expr_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2393 "Parser.C" /* yacc.c:1646  */
    break;

  case 57:
#line 868 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = (yyvsp[0].expr_);  }
#line 2399 "Parser.C" /* yacc.c:1646  */
    break;

  case 58:
#line 870 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new EAdd((yyvsp[-2].expr_), (yyvsp[-1].addop_), (yyvsp[0].expr_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2405 "Parser.C" /* yacc.c:1646  */
    break;

  case 59:
#line 871 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = (yyvsp[0].expr_);  }
#line 2411 "Parser.C" /* yacc.c:1646  */
    break;

  case 60:
#line 873 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new ERel((yyvsp[-2].expr_), (yyvsp[-1].relop_), (yyvsp[0].expr_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2417 "Parser.C" /* yacc.c:1646  */
    break;

  case 61:
#line 874 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = (yyvsp[0].expr_);  }
#line 2423 "Parser.C" /* yacc.c:1646  */
    break;

  case 62:
#line 876 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new EAnd((yyvsp[-2].expr_), (yyvsp[0].expr_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2429 "Parser.C" /* yacc.c:1646  */
    break;

  case 63:
#line 877 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = (yyvsp[0].expr_);  }
#line 2435 "Parser.C" /* yacc.c:1646  */
    break;

  case 64:
#line 879 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = new EOr((yyvsp[-2].expr_), (yyvsp[0].expr_)); (yyval.expr_)->line_number = yy_mylinenumber;  }
#line 2441 "Parser.C" /* yacc.c:1646  */
    break;

  case 65:
#line 880 "Latte.y" /* yacc.c:1646  */
    {  (yyval.expr_) = (yyvsp[0].expr_);  }
#line 2447 "Parser.C" /* yacc.c:1646  */
    break;

  case 66:
#line 882 "Latte.y" /* yacc.c:1646  */
    {  (yyval.listexpr_) = new ListExpr();  }
#line 2453 "Parser.C" /* yacc.c:1646  */
    break;

  case 67:
#line 883 "Latte.y" /* yacc.c:1646  */
    {  (yyval.listexpr_) = new ListExpr() ; (yyval.listexpr_)->push_back((yyvsp[0].expr_));  }
#line 2459 "Parser.C" /* yacc.c:1646  */
    break;

  case 68:
#line 884 "Latte.y" /* yacc.c:1646  */
    {  (yyvsp[0].listexpr_)->push_back((yyvsp[-2].expr_)) ; (yyval.listexpr_) = (yyvsp[0].listexpr_) ;  }
#line 2465 "Parser.C" /* yacc.c:1646  */
    break;

  case 69:
#line 886 "Latte.y" /* yacc.c:1646  */
    {  (yyval.addop_) = new Plus(); (yyval.addop_)->line_number = yy_mylinenumber;  }
#line 2471 "Parser.C" /* yacc.c:1646  */
    break;

  case 70:
#line 887 "Latte.y" /* yacc.c:1646  */
    {  (yyval.addop_) = new Minus(); (yyval.addop_)->line_number = yy_mylinenumber;  }
#line 2477 "Parser.C" /* yacc.c:1646  */
    break;

  case 71:
#line 889 "Latte.y" /* yacc.c:1646  */
    {  (yyval.mulop_) = new Times(); (yyval.mulop_)->line_number = yy_mylinenumber;  }
#line 2483 "Parser.C" /* yacc.c:1646  */
    break;

  case 72:
#line 890 "Latte.y" /* yacc.c:1646  */
    {  (yyval.mulop_) = new Div(); (yyval.mulop_)->line_number = yy_mylinenumber;  }
#line 2489 "Parser.C" /* yacc.c:1646  */
    break;

  case 73:
#line 891 "Latte.y" /* yacc.c:1646  */
    {  (yyval.mulop_) = new Mod(); (yyval.mulop_)->line_number = yy_mylinenumber;  }
#line 2495 "Parser.C" /* yacc.c:1646  */
    break;

  case 74:
#line 893 "Latte.y" /* yacc.c:1646  */
    {  (yyval.relop_) = new LTH(); (yyval.relop_)->line_number = yy_mylinenumber;  }
#line 2501 "Parser.C" /* yacc.c:1646  */
    break;

  case 75:
#line 894 "Latte.y" /* yacc.c:1646  */
    {  (yyval.relop_) = new LE(); (yyval.relop_)->line_number = yy_mylinenumber;  }
#line 2507 "Parser.C" /* yacc.c:1646  */
    break;

  case 76:
#line 895 "Latte.y" /* yacc.c:1646  */
    {  (yyval.relop_) = new GTH(); (yyval.relop_)->line_number = yy_mylinenumber;  }
#line 2513 "Parser.C" /* yacc.c:1646  */
    break;

  case 77:
#line 896 "Latte.y" /* yacc.c:1646  */
    {  (yyval.relop_) = new GE(); (yyval.relop_)->line_number = yy_mylinenumber;  }
#line 2519 "Parser.C" /* yacc.c:1646  */
    break;

  case 78:
#line 897 "Latte.y" /* yacc.c:1646  */
    {  (yyval.relop_) = new EQU(); (yyval.relop_)->line_number = yy_mylinenumber;  }
#line 2525 "Parser.C" /* yacc.c:1646  */
    break;

  case 79:
#line 898 "Latte.y" /* yacc.c:1646  */
    {  (yyval.relop_) = new NE(); (yyval.relop_)->line_number = yy_mylinenumber;  }
#line 2531 "Parser.C" /* yacc.c:1646  */
    break;


#line 2535 "Parser.C" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
