/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_HH_INCLUDED
# define YY_YY_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 27 "parser.yy"

	#define YYLTYPE YYLTYPE
	typedef struct YYLTYPE
	{
		int first_line;
		int first_column;
		int last_line;
		int last_column;
		std::string filename;
	} YYLTYPE;
	#define YYLTYPE_IS_DECLARED 1
	#define YYLTYPE_IS_TRIVIAL 1

#line 63 "parser.hh"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONST = 258,                   /* CONST  */
    VAR = 259,                     /* VAR  */
    BOOL = 260,                    /* BOOL  */
    FLOAT = 261,                   /* FLOAT  */
    INT = 262,                     /* INT  */
    STRING = 263,                  /* STRING  */
    VOID = 264,                    /* VOID  */
    POINT = 265,                   /* POINT  */
    PATH = 266,                    /* PATH  */
    IMAGE = 267,                   /* IMAGE  */
    RECTANGLE = 268,               /* RECTANGLE  */
    CIRCLE = 269,                  /* CIRCLE  */
    ELLIPSE = 270,                 /* ELLIPSE  */
    POLYGON = 271,                 /* POLYGON  */
    CURVE = 272,                   /* CURVE  */
    PI = 273,                      /* PI  */
    COLOUR = 274,                  /* COLOUR  */
    INTEGER_LITERAL = 275,         /* INTEGER_LITERAL  */
    FLOAT_LITERAL = 276,           /* FLOAT_LITERAL  */
    BOOL_LITERAL = 277,            /* BOOL_LITERAL  */
    STRING_LITERAL = 278,          /* STRING_LITERAL  */
    IF = 279,                      /* IF  */
    ELSE = 280,                    /* ELSE  */
    SWITCH = 281,                  /* SWITCH  */
    CASE = 282,                    /* CASE  */
    DEFAULT = 283,                 /* DEFAULT  */
    WHILE = 284,                   /* WHILE  */
    FOR = 285,                     /* FOR  */
    BREAK = 286,                   /* BREAK  */
    CONTINUE = 287,                /* CONTINUE  */
    SEND = 288,                    /* SEND  */
    FAMILY = 289,                  /* FAMILY  */
    INHERITS = 290,                /* INHERITS  */
    PUBLIC = 291,                  /* PUBLIC  */
    PRIVATE = 292,                 /* PRIVATE  */
    DRIVER = 293,                  /* DRIVER  */
    IDENTIFIER = 294,              /* IDENTIFIER  */
    ASSIGN = 295,                  /* ASSIGN  */
    ADD_ASSIGN = 296,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 297,              /* SUB_ASSIGN  */
    MUL_ASSIGN = 298,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 299,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 300,              /* MOD_ASSIGN  */
    LOGICAL_OR = 301,              /* LOGICAL_OR  */
    LOGICAL_AND = 302,             /* LOGICAL_AND  */
    EQ = 303,                      /* EQ  */
    NOT_EQ = 304,                  /* NOT_EQ  */
    LS_THAN = 305,                 /* LS_THAN  */
    LS_THAN_EQ = 306,              /* LS_THAN_EQ  */
    GR_THAN = 307,                 /* GR_THAN  */
    GR_THAN_EQ = 308,              /* GR_THAN_EQ  */
    INC = 309,                     /* INC  */
    DEC = 310,                     /* DEC  */
    INC_POST = 311,                /* INC_POST  */
    DEC_POST = 312,                /* DEC_POST  */
    UPLUS = 313,                   /* UPLUS  */
    UMINUS = 314,                  /* UMINUS  */
    LOGICAL_NOT = 315,             /* LOGICAL_NOT  */
    SCOPE_ACCESS = 316             /* SCOPE_ACCESS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 51 "parser.yy"

	Program *pgm;
	vector<Statement*> *stmt_list;
	vector<Expression*> *exp_list;
	Expression *exp;
	Statement* stmt;
	Identifier *t;
	string *id;
	int valuei;
	float valuef;
	bool valueb;
	string *values;
	ACCESS_SPEC *access_spec;
	FamilyMembers *class_member;
	vector<FamilyMembers*> *class_members;
	Arg* argument;
	vector<Arg*>* arg_list;

#line 160 "parser.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_PARSER_HH_INCLUDED  */
