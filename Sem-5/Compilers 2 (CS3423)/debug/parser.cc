/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 3 "parser.yy"

	#include <iostream>
	#include <fstream>
	#include <filesystem>
	#include <string>
	#include "astNodes.h"

	extern int yylex();
	extern void yyrestart(FILE*);
	void yyerror(const char* s);
	extern int yylineno;

	#define YYFPRINTF(f, fmt, ...)  printf(fmt, ##__VA_ARGS__)
	#if YYDEBUG == 1
	#define PARSER_TRACE_DEBUG
	#define SYMBOL_TABLE_DEBUG
	#define AST_DEBUG
	#endif

#line 88 "parser.cc"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_BOOL = 5,                       /* BOOL  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_POINT = 10,                     /* POINT  */
  YYSYMBOL_PATH = 11,                      /* PATH  */
  YYSYMBOL_IMAGE = 12,                     /* IMAGE  */
  YYSYMBOL_RECTANGLE = 13,                 /* RECTANGLE  */
  YYSYMBOL_CIRCLE = 14,                    /* CIRCLE  */
  YYSYMBOL_ELLIPSE = 15,                   /* ELLIPSE  */
  YYSYMBOL_POLYGON = 16,                   /* POLYGON  */
  YYSYMBOL_CURVE = 17,                     /* CURVE  */
  YYSYMBOL_PI = 18,                        /* PI  */
  YYSYMBOL_COLOUR = 19,                    /* COLOUR  */
  YYSYMBOL_INTEGER_LITERAL = 20,           /* INTEGER_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 21,             /* FLOAT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 22,              /* BOOL_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 23,            /* STRING_LITERAL  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_SWITCH = 26,                    /* SWITCH  */
  YYSYMBOL_CASE = 27,                      /* CASE  */
  YYSYMBOL_DEFAULT = 28,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_FOR = 30,                       /* FOR  */
  YYSYMBOL_BREAK = 31,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 32,                  /* CONTINUE  */
  YYSYMBOL_SEND = 33,                      /* SEND  */
  YYSYMBOL_FAMILY = 34,                    /* FAMILY  */
  YYSYMBOL_INHERITS = 35,                  /* INHERITS  */
  YYSYMBOL_PUBLIC = 36,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 37,                   /* PRIVATE  */
  YYSYMBOL_DRIVER = 38,                    /* DRIVER  */
  YYSYMBOL_IDENTIFIER = 39,                /* IDENTIFIER  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_ASSIGN = 41,                    /* ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 42,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 43,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 44,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 45,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 46,                /* MOD_ASSIGN  */
  YYSYMBOL_47_ = 47,                       /* '?'  */
  YYSYMBOL_48_ = 48,                       /* ':'  */
  YYSYMBOL_LOGICAL_OR = 49,                /* LOGICAL_OR  */
  YYSYMBOL_LOGICAL_AND = 50,               /* LOGICAL_AND  */
  YYSYMBOL_EQ = 51,                        /* EQ  */
  YYSYMBOL_NOT_EQ = 52,                    /* NOT_EQ  */
  YYSYMBOL_LS_THAN = 53,                   /* LS_THAN  */
  YYSYMBOL_LS_THAN_EQ = 54,                /* LS_THAN_EQ  */
  YYSYMBOL_GR_THAN = 55,                   /* GR_THAN  */
  YYSYMBOL_GR_THAN_EQ = 56,                /* GR_THAN_EQ  */
  YYSYMBOL_57_ = 57,                       /* '+'  */
  YYSYMBOL_58_ = 58,                       /* '-'  */
  YYSYMBOL_59_ = 59,                       /* '*'  */
  YYSYMBOL_60_ = 60,                       /* '/'  */
  YYSYMBOL_61_ = 61,                       /* '%'  */
  YYSYMBOL_INC = 62,                       /* INC  */
  YYSYMBOL_DEC = 63,                       /* DEC  */
  YYSYMBOL_INC_POST = 64,                  /* INC_POST  */
  YYSYMBOL_DEC_POST = 65,                  /* DEC_POST  */
  YYSYMBOL_UPLUS = 66,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 67,                    /* UMINUS  */
  YYSYMBOL_LOGICAL_NOT = 68,               /* LOGICAL_NOT  */
  YYSYMBOL_69_ = 69,                       /* '('  */
  YYSYMBOL_70_ = 70,                       /* ')'  */
  YYSYMBOL_71_ = 71,                       /* '['  */
  YYSYMBOL_72_ = 72,                       /* ']'  */
  YYSYMBOL_SCOPE_ACCESS = 73,              /* SCOPE_ACCESS  */
  YYSYMBOL_74_ = 74,                       /* ';'  */
  YYSYMBOL_75_ = 75,                       /* '{'  */
  YYSYMBOL_76_ = 76,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_program = 78,                   /* program  */
  YYSYMBOL_translation_unit = 79,          /* translation_unit  */
  YYSYMBOL_external_declaration = 80,      /* external_declaration  */
  YYSYMBOL_driver_definition = 81,         /* driver_definition  */
  YYSYMBOL_82_1 = 82,                      /* $@1  */
  YYSYMBOL_type = 83,                      /* type  */
  YYSYMBOL_literal = 84,                   /* literal  */
  YYSYMBOL_variable_declaration = 85,      /* variable_declaration  */
  YYSYMBOL_86_2 = 86,                      /* $@2  */
  YYSYMBOL_87_3 = 87,                      /* $@3  */
  YYSYMBOL_new_variable_list = 88,         /* new_variable_list  */
  YYSYMBOL_new_variable = 89,              /* new_variable  */
  YYSYMBOL_function_declaration = 90,      /* function_declaration  */
  YYSYMBOL_91_4 = 91,                      /* $@4  */
  YYSYMBOL_92_5 = 92,                      /* $@5  */
  YYSYMBOL_93_6 = 93,                      /* $@6  */
  YYSYMBOL_args_list = 94,                 /* args_list  */
  YYSYMBOL_arg = 95,                       /* arg  */
  YYSYMBOL_family_declaration = 96,        /* family_declaration  */
  YYSYMBOL_97_7 = 97,                      /* $@7  */
  YYSYMBOL_98_8 = 98,                      /* $@8  */
  YYSYMBOL_access_specifier = 99,          /* access_specifier  */
  YYSYMBOL_class_members = 100,            /* class_members  */
  YYSYMBOL_class_member = 101,             /* class_member  */
  YYSYMBOL_constructor_declaration = 102,  /* constructor_declaration  */
  YYSYMBOL_103_9 = 103,                    /* $@9  */
  YYSYMBOL_104_10 = 104,                   /* $@10  */
  YYSYMBOL_primary_expression = 105,       /* primary_expression  */
  YYSYMBOL_variable = 106,                 /* variable  */
  YYSYMBOL_expression = 107,               /* expression  */
  YYSYMBOL_expression_list = 108,          /* expression_list  */
  YYSYMBOL_statement = 109,                /* statement  */
  YYSYMBOL_compound_statement = 110,       /* compound_statement  */
  YYSYMBOL_111_11 = 111,                   /* $@11  */
  YYSYMBOL_statement_list = 112,           /* statement_list  */
  YYSYMBOL_expression_statement = 113,     /* expression_statement  */
  YYSYMBOL_selection_statement = 114,      /* selection_statement  */
  YYSYMBOL_labeled_statement = 115,        /* labeled_statement  */
  YYSYMBOL_iteration_statement = 116,      /* iteration_statement  */
  YYSYMBOL_117_12 = 117,                   /* $@12  */
  YYSYMBOL_118_13 = 118,                   /* $@13  */
  YYSYMBOL_iter_expression = 119,          /* iter_expression  */
  YYSYMBOL_jump_statement = 120            /* jump_statement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 41 "parser.yy"

	#include "symbolTable.h"

	SymbolTable global_symbol_table(NULL, "global");
	SymbolTable* cur_symbol_table = &global_symbol_table;
	Program* root;

#line 254 "parser.cc"

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   540

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  246

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    61,     2,     2,
      69,    70,    59,    57,    40,    58,     2,    60,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    74,
       2,     2,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    71,     2,    72,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,    76,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    41,    42,    43,    44,    45,
      46,    49,    50,    51,    52,    53,    54,    55,    56,    62,
      63,    64,    65,    66,    67,    68,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   137,   137,   138,   142,   143,   147,   148,   149,   150,
     154,   154,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   182,   183,
     184,   185,   189,   189,   191,   191,   196,   197,   201,   206,
     212,   218,   228,   227,   238,   242,   237,   256,   257,   261,
     266,   271,   282,   288,   287,   296,   303,   302,   315,   316,
     320,   321,   325,   326,   327,   332,   336,   331,   352,   353,
     354,   355,   356,   360,   361,   362,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   397,   398,   405,   406,   407,   408,
     409,   410,   411,   412,   416,   417,   417,   423,   424,   428,
     429,   433,   434,   435,   439,   440,   441,   445,   445,   447,
     447,   452,   453,   457,   458,   459
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "CONST", "VAR", "BOOL",
  "FLOAT", "INT", "STRING", "VOID", "POINT", "PATH", "IMAGE", "RECTANGLE",
  "CIRCLE", "ELLIPSE", "POLYGON", "CURVE", "PI", "COLOUR",
  "INTEGER_LITERAL", "FLOAT_LITERAL", "BOOL_LITERAL", "STRING_LITERAL",
  "IF", "ELSE", "SWITCH", "CASE", "DEFAULT", "WHILE", "FOR", "BREAK",
  "CONTINUE", "SEND", "FAMILY", "INHERITS", "PUBLIC", "PRIVATE", "DRIVER",
  "IDENTIFIER", "','", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "'?'", "':'", "LOGICAL_OR", "LOGICAL_AND",
  "EQ", "NOT_EQ", "LS_THAN", "LS_THAN_EQ", "GR_THAN", "GR_THAN_EQ", "'+'",
  "'-'", "'*'", "'/'", "'%'", "INC", "DEC", "INC_POST", "DEC_POST",
  "UPLUS", "UMINUS", "LOGICAL_NOT", "'('", "')'", "'['", "']'",
  "SCOPE_ACCESS", "';'", "'{'", "'}'", "$accept", "program",
  "translation_unit", "external_declaration", "driver_definition", "$@1",
  "type", "literal", "variable_declaration", "$@2", "$@3",
  "new_variable_list", "new_variable", "function_declaration", "$@4",
  "$@5", "$@6", "args_list", "arg", "family_declaration", "$@7", "$@8",
  "access_specifier", "class_members", "class_member",
  "constructor_declaration", "$@9", "$@10", "primary_expression",
  "variable", "expression", "expression_list", "statement",
  "compound_statement", "$@11", "statement_list", "expression_statement",
  "selection_statement", "labeled_statement", "iteration_statement",
  "$@12", "$@13", "iter_expression", "jump_statement", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-147)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     323,   395,   395,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,   -30,  -147,
    -147,    16,   323,  -147,  -147,    -5,  -147,  -147,  -147,  -147,
    -147,   -32,   -27,  -147,  -147,   -24,    -2,    -2,   -14,    -9,
     -13,    34,   -33,   -36,  -147,   -35,  -147,  -147,    27,    28,
      -4,    30,    36,   360,   -10,   103,    -2,  -147,  -147,    33,
    -147,    40,   377,    64,  -147,  -147,    37,  -147,    30,   395,
     395,    78,   -26,  -147,  -147,  -147,  -147,  -147,  -147,   -10,
     -10,    80,    80,   -10,   -10,  -147,  -147,   186,   468,  -147,
     468,   -20,  -147,    44,  -147,  -147,  -147,    47,  -147,  -147,
     241,  -147,    93,    96,  -147,   360,  -147,  -147,  -147,   -17,
     -17,  -147,   232,   -10,   -10,   -10,   -10,   -10,   -10,  -147,
    -147,   255,   -10,    98,   -10,   -10,   -10,   -10,   -10,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,  -147,
      67,    -4,   360,  -147,    69,    77,    83,   -10,   101,    84,
      85,    81,    82,    76,   109,  -147,  -147,   -25,  -147,  -147,
     178,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,    30,
    -147,   468,   468,   468,   468,   468,   468,  -147,   -19,   368,
    -147,   438,   293,   479,   165,   165,    70,    70,    70,    70,
      32,    32,  -147,  -147,  -147,   468,  -147,    75,   -15,  -147,
     -10,   -10,   453,   241,  -147,  -147,  -147,  -147,  -147,   241,
    -147,  -147,  -147,  -147,  -147,  -147,   -10,    88,  -147,   392,
     414,   241,  -147,   -10,   241,  -147,   468,  -147,    30,    30,
     241,  -147,   468,    94,    76,  -147,   133,  -147,    30,   -10,
      30,  -147,    97,  -147,    30,  -147
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,    15,    13,    12,    14,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,     0,    10,
      27,     0,     3,     4,     6,     0,     7,     8,     9,    34,
      32,     0,     0,     1,     5,     0,     0,     0,     0,    53,
       0,    44,    38,     0,    36,     0,    58,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    33,     0,
      52,     0,     0,     0,    60,    64,   115,    11,     0,     0,
       0,     0,     0,    47,    28,    29,    31,    30,    73,     0,
       0,     0,     0,     0,     0,    68,    76,    69,    39,    40,
     104,     0,    37,    56,    65,    62,    63,     0,    61,   114,
       0,    43,     0,     0,    49,     0,    45,    77,    78,    93,
      94,    92,     0,     0,     0,     0,     0,     0,     0,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
       0,     0,     0,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    73,   119,   108,     0,   117,   107,
       0,   109,   110,   106,   111,   112,    51,    50,    48,     0,
      72,    97,   101,   102,    98,    99,   100,    70,     0,     0,
      74,     0,    91,    90,    84,    85,    86,    87,    88,    89,
      82,    83,    79,    80,    81,   105,    55,     0,     0,   113,
       0,     0,     0,     0,   127,   129,   134,   133,   135,     0,
     120,   116,   118,    46,    71,    75,     0,     0,    66,     0,
       0,     0,   126,   131,     0,   124,   103,    57,     0,     0,
       0,   125,   132,     0,     0,    67,   121,   123,     0,   131,
       0,   128,     0,   122,     0,   130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,  -147,  -147,   146,  -147,  -147,    17,  -147,     6,  -147,
    -147,   132,   118,   113,  -147,  -147,  -147,    38,    71,  -147,
    -147,  -147,   145,    43,   -61,  -147,  -147,  -147,  -147,   -41,
     -53,   -31,  -114,   -51,  -147,  -147,  -146,  -147,  -147,  -147,
    -147,  -147,   -54,  -147
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    21,    22,    23,    24,    32,    25,    85,   156,    37,
      36,    43,    44,    27,    52,    53,   169,    72,    73,    28,
      50,   141,    62,    63,    64,    65,   142,   228,    86,    87,
      90,   157,   158,   159,   100,   160,   161,   162,   163,   164,
     223,   224,   233,   165
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,    88,    98,    38,    56,    56,    26,   208,    54,    31,
      74,    75,    76,    77,   105,   138,    33,   101,    29,    30,
     138,   138,    46,    47,    91,   105,   107,   108,    26,    78,
     111,   112,    46,    47,    35,    61,    55,    42,    57,    58,
     109,   110,    40,    39,   106,    41,   212,    79,    80,   210,
     139,   214,    81,    82,   122,   218,   123,    51,    83,    84,
     171,   172,   173,   174,   175,   176,    59,    49,    95,   179,
      71,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   102,   103,   239,   222,
     178,   135,   136,   137,   202,   225,    74,    75,    76,    77,
      46,    47,    60,    61,   -42,    66,    68,   231,    93,    94,
     234,    46,    47,    99,    61,    78,   237,   104,   213,    78,
     140,   143,    71,    74,    75,    76,    77,   133,   134,   135,
     136,   137,   166,    79,    80,   167,    98,   180,    81,    82,
      97,   196,    78,   199,    83,    84,   200,   219,   220,   203,
     155,   217,   201,   204,   205,   206,   207,   209,   240,    71,
      79,    80,   227,   226,   238,    81,    82,   244,    34,    45,
     232,    83,    84,    89,    92,    96,   168,   235,   236,   144,
     198,     1,     2,    48,   197,   242,   232,   241,     0,   243,
       0,     0,     0,   245,     0,     0,     0,     0,    74,    75,
      76,    77,   145,     0,   146,   147,   148,   149,   150,   151,
     152,   153,     0,     0,     0,     0,     0,   154,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   113,   114,   115,
     116,   117,   118,     0,     0,    79,    80,     0,     0,     0,
      81,    82,   144,     0,     1,     2,    83,    84,   119,   120,
       0,     0,   155,    66,   211,   121,     0,   122,     0,   123,
       0,    74,    75,    76,    77,   145,     0,   146,   147,   148,
     149,   150,   151,   152,   153,    74,    75,    76,    77,   124,
     154,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,    78,     0,     0,     0,    79,    80,
       0,     0,   170,    81,    82,     0,     0,     0,     0,    83,
      84,     0,    79,    80,     0,   155,    66,    81,    82,     0,
       0,     0,     0,    83,    84,   177,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,     0,     0,    18,     0,     0,
       0,    19,    20,    69,    70,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,    20,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,   124,    20,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
       0,     0,     0,     0,    20,     0,     0,     0,     0,   124,
     215,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,     0,     0,     0,     0,     0,     0,
       0,   124,   229,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,   230,   124,   216,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     124,   221,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   124,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137
};

static const yytype_int16 yycheck[] =
{
      51,    54,    63,    35,    40,    40,     0,   153,    41,    39,
      20,    21,    22,    23,    40,    40,     0,    68,     1,     2,
      40,    40,    36,    37,    55,    40,    79,    80,    22,    39,
      83,    84,    36,    37,    39,    39,    69,    39,    74,    74,
      81,    82,    69,    75,    70,    69,   160,    57,    58,    74,
      70,    70,    62,    63,    71,    70,    73,    70,    68,    69,
     113,   114,   115,   116,   117,   118,    39,    76,    62,   122,
      53,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,    69,    70,   234,   203,
     121,    59,    60,    61,   147,   209,    20,    21,    22,    23,
      36,    37,    74,    39,    70,    75,    70,   221,    75,    69,
     224,    36,    37,    76,    39,    39,   230,    39,   169,    39,
      76,    74,   105,    20,    21,    22,    23,    57,    58,    59,
      60,    61,    39,    57,    58,    39,   197,    39,    62,    63,
      76,    74,    39,    74,    68,    69,    69,   200,   201,    48,
      74,    76,    69,    69,    69,    74,    74,    48,    25,   142,
      57,    58,    74,   216,    70,    62,    63,    70,    22,    37,
     223,    68,    69,    70,    56,    62,   105,   228,   229,     1,
     142,     3,     4,    38,   141,   239,   239,   238,    -1,   240,
      -1,    -1,    -1,   244,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    39,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    41,    42,    43,
      44,    45,    46,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    63,     1,    -1,     3,     4,    68,    69,    62,    63,
      -1,    -1,    74,    75,    76,    69,    -1,    71,    -1,    73,
      -1,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    33,    20,    21,    22,    23,    47,
      39,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    39,    -1,    -1,    -1,    57,    58,
      -1,    -1,    70,    62,    63,    -1,    -1,    -1,    -1,    68,
      69,    -1,    57,    58,    -1,    74,    75,    62,    63,    -1,
      -1,    -1,    -1,    68,    69,    70,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    34,    -1,    -1,
      -1,    38,    39,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    39,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    47,    39,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    47,
      72,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    70,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    34,    38,
      39,    78,    79,    80,    81,    83,    85,    90,    96,    83,
      83,    39,    82,     0,    80,    39,    87,    86,    35,    75,
      69,    69,    39,    88,    89,    88,    36,    37,    99,    76,
      97,    70,    91,    92,    41,    69,    40,    74,    74,    39,
      74,    39,    99,   100,   101,   102,    75,   110,    70,     3,
       4,    83,    94,    95,    20,    21,    22,    23,    39,    57,
      58,    62,    63,    68,    69,    84,   105,   106,   107,    70,
     107,   108,    89,    75,    69,    85,    90,    76,   101,    76,
     111,   110,    83,    83,    39,    40,    70,   107,   107,   106,
     106,   107,   107,    41,    42,    43,    44,    45,    46,    62,
      63,    69,    71,    73,    47,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    40,    70,
      76,    98,   103,    74,     1,    24,    26,    27,    28,    29,
      30,    31,    32,    33,    39,    74,    85,   108,   109,   110,
     112,   113,   114,   115,   116,   120,    39,    39,    95,    93,
      70,   107,   107,   107,   107,   107,   107,    70,   108,   107,
      39,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,    74,   100,    94,    74,
      69,    69,   107,    48,    69,    69,    74,    74,   113,    48,
      74,    76,   109,   110,    70,    72,    48,    76,    70,   107,
     107,    48,   109,   117,   118,   109,   107,    74,   104,    70,
      70,   109,   107,   119,   109,   110,   110,   109,    70,   113,
      25,   110,   119,   110,    70,   110
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    77,    78,    78,    79,    79,    80,    80,    80,    80,
      82,    81,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      84,    84,    86,    85,    87,    85,    88,    88,    89,    89,
      89,    89,    91,    90,    92,    93,    90,    94,    94,    95,
      95,    95,    96,    97,    96,    96,    98,    96,    99,    99,
     100,   100,   101,   101,   101,   103,   104,   102,   105,   105,
     105,   105,   105,   106,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   111,   110,   112,   112,   113,
     113,   114,   114,   114,   115,   115,   115,   117,   116,   118,
     116,   119,   119,   120,   120,   120
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     1,     1,     1,
       0,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     5,     0,     5,     1,     3,     1,     3,
       3,     4,     0,     6,     0,     0,     8,     1,     3,     2,
       3,     3,     5,     0,     7,     8,     0,    10,     1,     1,
       1,     2,     2,     2,     1,     0,     0,     7,     1,     1,
       3,     4,     3,     1,     3,     4,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     0,     4,     1,     2,     1,
       2,     5,     7,     5,     3,     4,     3,     0,     6,     0,
       8,     0,     1,     2,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 137 "parser.yy"
                                                {(yyval.pgm) = new Program(); root = (yyval.pgm);}
#line 1782 "parser.cc"
    break;

  case 3: /* program: translation_unit  */
#line 138 "parser.yy"
                                        {(yyval.pgm) = new Program((yyvsp[0].stmt_list)); root = (yyval.pgm);}
#line 1788 "parser.cc"
    break;

  case 4: /* translation_unit: external_declaration  */
#line 142 "parser.yy"
                                                                {(yyval.stmt_list) = new vector<Statement*>(); (yyval.stmt_list)->push_back((yyvsp[0].stmt));}
#line 1794 "parser.cc"
    break;

  case 5: /* translation_unit: translation_unit external_declaration  */
#line 143 "parser.yy"
                                                {(yyval.stmt_list) = (yyvsp[-1].stmt_list); (yyval.stmt_list)->push_back((yyvsp[0].stmt));}
#line 1800 "parser.cc"
    break;

  case 6: /* external_declaration: driver_definition  */
#line 147 "parser.yy"
                                        {(yyval.stmt) = (yyvsp[0].stmt);}
#line 1806 "parser.cc"
    break;

  case 7: /* external_declaration: variable_declaration  */
#line 148 "parser.yy"
                                {(yyval.stmt) = (yyvsp[0].stmt);}
#line 1812 "parser.cc"
    break;

  case 8: /* external_declaration: function_declaration  */
#line 149 "parser.yy"
                                {(yyval.stmt) = (yyvsp[0].stmt);}
#line 1818 "parser.cc"
    break;

  case 9: /* external_declaration: family_declaration  */
#line 150 "parser.yy"
                                {(yyval.stmt) = (yyvsp[0].stmt);}
#line 1824 "parser.cc"
    break;

  case 10: /* $@1: %empty  */
#line 154 "parser.yy"
                                                                        {cur_symbol_table = cur_symbol_table->addSymbol("driver", "void->()", &(yylsp[0]), KIND::FUNCTION);}
#line 1830 "parser.cc"
    break;

  case 11: /* driver_definition: DRIVER $@1 '(' ')' compound_statement  */
#line 155 "parser.yy"
                                                        {(yyval.stmt) = new DriverDefinition((yyvsp[0].stmt)); cur_symbol_table = cur_symbol_table->returnFromFunction();}
#line 1836 "parser.cc"
    break;

  case 12: /* type: INT  */
#line 163 "parser.yy"
                                {(yyval.t) = new Identifier("int");}
#line 1842 "parser.cc"
    break;

  case 13: /* type: FLOAT  */
#line 164 "parser.yy"
                                {(yyval.t) = new Identifier("float");}
#line 1848 "parser.cc"
    break;

  case 14: /* type: STRING  */
#line 165 "parser.yy"
                                {(yyval.t) = new Identifier("string");}
#line 1854 "parser.cc"
    break;

  case 15: /* type: BOOL  */
#line 166 "parser.yy"
                                {(yyval.t) = new Identifier("bool");}
#line 1860 "parser.cc"
    break;

  case 16: /* type: VOID  */
#line 167 "parser.yy"
                                {(yyval.t) = new Identifier("void");}
#line 1866 "parser.cc"
    break;

  case 17: /* type: POINT  */
#line 168 "parser.yy"
                                {(yyval.t) = new Identifier("Point");}
#line 1872 "parser.cc"
    break;

  case 18: /* type: PATH  */
#line 169 "parser.yy"
                                {(yyval.t) = new Identifier("Path");}
#line 1878 "parser.cc"
    break;

  case 19: /* type: IMAGE  */
#line 170 "parser.yy"
                                {(yyval.t) = new Identifier("Image");}
#line 1884 "parser.cc"
    break;

  case 20: /* type: RECTANGLE  */
#line 171 "parser.yy"
                        {(yyval.t) = new Identifier("Rectangle");}
#line 1890 "parser.cc"
    break;

  case 21: /* type: CIRCLE  */
#line 172 "parser.yy"
                                {(yyval.t) = new Identifier("Circle");}
#line 1896 "parser.cc"
    break;

  case 22: /* type: ELLIPSE  */
#line 173 "parser.yy"
                                {(yyval.t) = new Identifier("Ellipse");}
#line 1902 "parser.cc"
    break;

  case 23: /* type: POLYGON  */
#line 174 "parser.yy"
                                {(yyval.t) = new Identifier("Polygon");}
#line 1908 "parser.cc"
    break;

  case 24: /* type: CURVE  */
#line 175 "parser.yy"
                                {(yyval.t) = new Identifier("Curve");}
#line 1914 "parser.cc"
    break;

  case 25: /* type: PI  */
#line 176 "parser.yy"
                                {(yyval.t) = new Identifier("Pi");}
#line 1920 "parser.cc"
    break;

  case 26: /* type: COLOUR  */
#line 177 "parser.yy"
                                {(yyval.t) = new Identifier("Colour");}
#line 1926 "parser.cc"
    break;

  case 27: /* type: IDENTIFIER  */
#line 178 "parser.yy"
                        {(yyval.t) = new Identifier(*((yyvsp[0].id)));}
#line 1932 "parser.cc"
    break;

  case 28: /* literal: INTEGER_LITERAL  */
#line 182 "parser.yy"
                                {(yyval.exp) = new IntegerLiteral((yyvsp[0].valuei));}
#line 1938 "parser.cc"
    break;

  case 29: /* literal: FLOAT_LITERAL  */
#line 183 "parser.yy"
                                {(yyval.exp) = new FloatLiteral((yyvsp[0].valuef));}
#line 1944 "parser.cc"
    break;

  case 30: /* literal: STRING_LITERAL  */
#line 184 "parser.yy"
                                {(yyval.exp) = new StringLiteral(*((yyvsp[0].values)));}
#line 1950 "parser.cc"
    break;

  case 31: /* literal: BOOL_LITERAL  */
#line 185 "parser.yy"
                                {(yyval.exp) = new BooleanLiteral((yyvsp[0].valueb));}
#line 1956 "parser.cc"
    break;

  case 32: /* $@2: %empty  */
#line 189 "parser.yy"
                   { SymbolTable::currentVariableType = (yyvsp[0].t)->ret_id(); }
#line 1962 "parser.cc"
    break;

  case 33: /* variable_declaration: VAR type $@2 new_variable_list ';'  */
#line 190 "parser.yy"
                                              { (yyval.stmt) = new VariableDeclaration(*((yyvsp[-3].t)), *((yyvsp[-1].exp_list))); }
#line 1968 "parser.cc"
    break;

  case 34: /* $@3: %empty  */
#line 191 "parser.yy"
                     { SymbolTable::currentVariableType = (yyvsp[0].t)->ret_id(); }
#line 1974 "parser.cc"
    break;

  case 35: /* variable_declaration: CONST type $@3 new_variable_list ';'  */
#line 192 "parser.yy"
                                              { (yyval.stmt) = new VariableDeclaration(*((yyvsp[-3].t)), *((yyvsp[-1].exp_list))); }
#line 1980 "parser.cc"
    break;

  case 36: /* new_variable_list: new_variable  */
#line 196 "parser.yy"
                                                                 {(yyval.exp_list) = new vector<Expression*>(); (yyval.exp_list)->push_back((yyvsp[0].exp));}
#line 1986 "parser.cc"
    break;

  case 37: /* new_variable_list: new_variable_list ',' new_variable  */
#line 197 "parser.yy"
                                             {(yyval.exp_list) = (yyvsp[-2].exp_list); (yyval.exp_list)->push_back((yyvsp[0].exp));}
#line 1992 "parser.cc"
    break;

  case 38: /* new_variable: IDENTIFIER  */
#line 202 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[0].id), SymbolTable::currentVariableType, &(yylsp[0])); 
				(yyval.exp) = new Identifier(*((yyvsp[0].id)));
			}
#line 2001 "parser.cc"
    break;

  case 39: /* new_variable: IDENTIFIER ASSIGN expression  */
#line 207 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-2].id), SymbolTable::currentVariableType, &(yylsp[-2])); 
				Variable* temp = new Identifier(*((yyvsp[-2].id))); 
				(yyval.exp) = new AssignmentExp(temp, (yyvsp[0].exp));
			}
#line 2011 "parser.cc"
    break;

  case 40: /* new_variable: IDENTIFIER '(' ')'  */
#line 213 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-2].id), SymbolTable::currentVariableType, &(yylsp[-2])); 
				Variable* temp = new Identifier(*((yyvsp[-2].id))); 
				(yyval.exp) = new FunctionCall(temp);
			}
#line 2021 "parser.cc"
    break;

  case 41: /* new_variable: IDENTIFIER '(' expression_list ')'  */
#line 219 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-3].id), SymbolTable::currentVariableType, &(yylsp[-3])); 
				Variable* temp = new Identifier(*((yyvsp[-3].id))); 
				(yyval.exp) = new FunctionCall(temp, *((yyvsp[-1].exp_list)));
			}
#line 2031 "parser.cc"
    break;

  case 42: /* $@4: %empty  */
#line 228 "parser.yy"
                        { 
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-1].id), (yyvsp[-2].t)->ret_id()+"->()", &(yylsp[-2]), KIND::FUNCTION); 
			}
#line 2039 "parser.cc"
    break;

  case 43: /* function_declaration: type IDENTIFIER '(' $@4 ')' compound_statement  */
#line 232 "parser.yy"
                        { 
				cur_symbol_table = cur_symbol_table->returnFromFunction(); 
				auto temp = new Identifier(*((yyvsp[-4].id))); 
				(yyval.stmt) = new FunctionDeclaration(temp, *((yyvsp[-5].t)), (yyvsp[0].stmt)); 
			}
#line 2049 "parser.cc"
    break;

  case 44: /* $@5: %empty  */
#line 238 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-1].id), (yyvsp[-2].t)->ret_id()+"->", &(yylsp[-2]), KIND::FUNCTION);
			}
#line 2057 "parser.cc"
    break;

  case 45: /* $@6: %empty  */
#line 242 "parser.yy"
                        {
				std::string arg_types = "";
				for(auto arg: *((yyvsp[-1].arg_list))) arg_types += arg->getType() + ",";
				cur_symbol_table->lookUp(*(yyvsp[-4].id))->addArgTypeNames(arg_types.substr(0, arg_types.size()-1));
			}
#line 2067 "parser.cc"
    break;

  case 46: /* function_declaration: type IDENTIFIER '(' $@5 args_list ')' $@6 compound_statement  */
#line 248 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->returnFromFunction();
				auto temp = new Identifier(*((yyvsp[-6].id))); 
				(yyval.stmt) = new FunctionDeclaration(temp, *((yyvsp[-7].t)), (yyvsp[0].stmt), *((yyvsp[-3].arg_list)));
			}
#line 2077 "parser.cc"
    break;

  case 47: /* args_list: arg  */
#line 256 "parser.yy"
                                        {(yyval.arg_list) = new vector<Arg*>(); (yyval.arg_list)->push_back((yyvsp[0].argument));}
#line 2083 "parser.cc"
    break;

  case 48: /* args_list: args_list ',' arg  */
#line 257 "parser.yy"
                                {(yyval.arg_list) = (yyvsp[-2].arg_list); (yyval.arg_list)->push_back((yyvsp[0].argument));}
#line 2089 "parser.cc"
    break;

  case 49: /* arg: type IDENTIFIER  */
#line 262 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[0].id), (yyvsp[-1].t)->ret_id(), &(yylsp[-1])); 
				(yyval.argument) = new Arg(*((yyvsp[-1].t)), Identifier(*((yyvsp[0].id))));
			}
#line 2098 "parser.cc"
    break;

  case 50: /* arg: VAR type IDENTIFIER  */
#line 267 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[0].id), (yyvsp[-1].t)->ret_id(), &(yylsp[-2])); 
				(yyval.argument) = new Arg(*((yyvsp[-1].t)), Identifier(*((yyvsp[0].id))));
			}
#line 2107 "parser.cc"
    break;

  case 51: /* arg: CONST type IDENTIFIER  */
#line 272 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[0].id), (yyvsp[-1].t)->ret_id(), &(yylsp[-2])); 
				(yyval.argument) = new Arg(*((yyvsp[-1].t)), Identifier(*((yyvsp[0].id))));
			}
#line 2116 "parser.cc"
    break;

  case 52: /* family_declaration: FAMILY IDENTIFIER '{' '}' ';'  */
#line 283 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-3].id), "Family", &(yylsp[-4]), KIND::FAMILY);
				(yyval.stmt) = new FamilyDecl(Identifier(*(yyvsp[-3].id)));
			}
#line 2125 "parser.cc"
    break;

  case 53: /* $@7: %empty  */
#line 288 "parser.yy"
                        { 
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-1].id), "Family", &(yylsp[-2]), KIND::FAMILY); 
			}
#line 2133 "parser.cc"
    break;

  case 54: /* family_declaration: FAMILY IDENTIFIER '{' $@7 class_members '}' ';'  */
#line 292 "parser.yy"
                        {
				(yyval.stmt) = new FamilyDecl(Identifier(*(yyvsp[-5].id)), *((yyvsp[-2].class_members))); 
				cur_symbol_table = cur_symbol_table->endScope();
			}
#line 2142 "parser.cc"
    break;

  case 55: /* family_declaration: FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' '}' ';'  */
#line 297 "parser.yy"
                        {
				cur_symbol_table->addSymbol(*(yyvsp[-6].id), "Family", &(yylsp[-7]), KIND::FAMILY);
				// TODO: Copy public members from parent class
				(yyval.stmt) = new FamilyDecl(Identifier(*((yyvsp[-6].id))),optional<pair<Identifier, ACCESS_SPEC>>(make_pair(Identifier(*(yyvsp[-3].id)), *((yyvsp[-4].access_spec)))));
			}
#line 2152 "parser.cc"
    break;

  case 56: /* $@8: %empty  */
#line 303 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-4].id), "Family", &(yylsp[-5]), KIND::FAMILY);
				// TODO: Copy public members from parent class
			}
#line 2161 "parser.cc"
    break;

  case 57: /* family_declaration: FAMILY IDENTIFIER INHERITS access_specifier IDENTIFIER '{' $@8 class_members '}' ';'  */
#line 308 "parser.yy"
                        {
				(yyval.stmt) = new FamilyDecl(Identifier(*((yyvsp[-8].id))),*((yyvsp[-2].class_members)), optional<pair<Identifier, ACCESS_SPEC>>(make_pair(Identifier(*(yyvsp[-5].id)), *((yyvsp[-6].access_spec)))));
				cur_symbol_table = cur_symbol_table->endScope();
			}
#line 2170 "parser.cc"
    break;

  case 58: /* access_specifier: PUBLIC  */
#line 315 "parser.yy"
                        {(yyval.access_spec) = new ACCESS_SPEC(ACCESS_SPEC::PUBLIC);}
#line 2176 "parser.cc"
    break;

  case 59: /* access_specifier: PRIVATE  */
#line 316 "parser.yy"
                        {(yyval.access_spec) = new ACCESS_SPEC(ACCESS_SPEC::PRIVATE);}
#line 2182 "parser.cc"
    break;

  case 60: /* class_members: class_member  */
#line 320 "parser.yy"
                                                        {(yyval.class_members) = new vector<FamilyMembers*>(); (yyval.class_members)->push_back((yyvsp[0].class_member));}
#line 2188 "parser.cc"
    break;

  case 61: /* class_members: class_members class_member  */
#line 321 "parser.yy"
                                        {(yyval.class_members) =(yyvsp[-1].class_members); (yyval.class_members)->push_back((yyvsp[0].class_member));}
#line 2194 "parser.cc"
    break;

  case 62: /* class_member: access_specifier variable_declaration  */
#line 325 "parser.yy"
                                                {(yyval.class_member) = new FamilyMembers(*((yyvsp[-1].access_spec)), (yyvsp[0].stmt));}
#line 2200 "parser.cc"
    break;

  case 63: /* class_member: access_specifier function_declaration  */
#line 326 "parser.yy"
                                                {(yyval.class_member) = new FamilyMembers(*((yyvsp[-1].access_spec)), (yyvsp[0].stmt));}
#line 2206 "parser.cc"
    break;

  case 64: /* class_member: constructor_declaration  */
#line 327 "parser.yy"
                                                                {(yyval.class_member) = new FamilyMembers(ACCESS_SPEC::PUBLIC, (yyvsp[0].stmt));}
#line 2212 "parser.cc"
    break;

  case 65: /* $@9: %empty  */
#line 332 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->addSymbol(*(yyvsp[-1].id), "void->", &(yylsp[-1]), KIND::FUNCTION);
			}
#line 2220 "parser.cc"
    break;

  case 66: /* $@10: %empty  */
#line 336 "parser.yy"
                        {
				std::string arg_types = "";
				for(auto arg: *((yyvsp[-1].arg_list))) arg_types += arg->getType() + ",";
				cur_symbol_table->lookUp(*(yyvsp[-4].id))->addArgTypeNames(arg_types.substr(0, arg_types.size()-1));
			}
#line 2230 "parser.cc"
    break;

  case 67: /* constructor_declaration: IDENTIFIER '(' $@9 args_list ')' $@10 compound_statement  */
#line 342 "parser.yy"
                        {
				cur_symbol_table = cur_symbol_table->returnFromFunction();
				(yyval.stmt) = new ConstructorDeclaration(Identifier(*((yyvsp[-6].id))), (yyvsp[0].stmt), *((yyvsp[-3].arg_list)));
			}
#line 2239 "parser.cc"
    break;

  case 68: /* primary_expression: literal  */
#line 352 "parser.yy"
                                                                        {(yyval.exp) = (Expression*)(yyvsp[0].exp);}
#line 2245 "parser.cc"
    break;

  case 69: /* primary_expression: variable  */
#line 353 "parser.yy"
                                                                        {(yyval.exp) = (Expression*)(yyvsp[0].exp);}
#line 2251 "parser.cc"
    break;

  case 70: /* primary_expression: variable '(' ')'  */
#line 354 "parser.yy"
                                                                {(yyval.exp) = new FunctionCall((yyvsp[-2].exp));}
#line 2257 "parser.cc"
    break;

  case 71: /* primary_expression: variable '(' expression_list ')'  */
#line 355 "parser.yy"
                                                {(yyval.exp) = new FunctionCall((yyvsp[-3].exp), *((yyvsp[-1].exp_list)));}
#line 2263 "parser.cc"
    break;

  case 72: /* primary_expression: '(' expression ')'  */
#line 356 "parser.yy"
                                                        {(yyval.exp) = (yyvsp[-1].exp);}
#line 2269 "parser.cc"
    break;

  case 73: /* variable: IDENTIFIER  */
#line 360 "parser.yy"
                                                                {(yyval.exp) = new Identifier(*((yyvsp[0].id)));}
#line 2275 "parser.cc"
    break;

  case 74: /* variable: variable SCOPE_ACCESS IDENTIFIER  */
#line 361 "parser.yy"
                                                {(yyval.exp) = new MemberAccess((Variable*)(yyvsp[-2].exp), *((yyvsp[0].id)));}
#line 2281 "parser.cc"
    break;

  case 75: /* variable: variable '[' expression ']'  */
#line 362 "parser.yy"
                                                {(yyval.exp) = new ArrayAccess((yyvsp[-3].exp), (yyvsp[-1].exp));}
#line 2287 "parser.cc"
    break;

  case 77: /* expression: '+' expression  */
#line 367 "parser.yy"
                                                                {(yyval.exp) = new UnaryPlus((yyvsp[0].exp));}
#line 2293 "parser.cc"
    break;

  case 78: /* expression: '-' expression  */
#line 368 "parser.yy"
                                                                {(yyval.exp) = new UnaryMinus((yyvsp[0].exp));}
#line 2299 "parser.cc"
    break;

  case 79: /* expression: expression '*' expression  */
#line 369 "parser.yy"
                                                                        {(yyval.exp) = new Multiplication((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2305 "parser.cc"
    break;

  case 80: /* expression: expression '/' expression  */
#line 370 "parser.yy"
                                                                        {(yyval.exp) = new Division((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2311 "parser.cc"
    break;

  case 81: /* expression: expression '%' expression  */
#line 371 "parser.yy"
                                                                        {(yyval.exp) = new ModularDiv((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2317 "parser.cc"
    break;

  case 82: /* expression: expression '+' expression  */
#line 372 "parser.yy"
                                                                        {(yyval.exp) = new Addition((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2323 "parser.cc"
    break;

  case 83: /* expression: expression '-' expression  */
#line 373 "parser.yy"
                                                                        {(yyval.exp) = new Subtraction((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2329 "parser.cc"
    break;

  case 84: /* expression: expression EQ expression  */
#line 374 "parser.yy"
                                                                        {(yyval.exp) = new CompEQ((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2335 "parser.cc"
    break;

  case 85: /* expression: expression NOT_EQ expression  */
#line 375 "parser.yy"
                                                                {(yyval.exp) = new CompNEQ((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2341 "parser.cc"
    break;

  case 86: /* expression: expression LS_THAN expression  */
#line 376 "parser.yy"
                                                                {(yyval.exp) = new CompLT((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2347 "parser.cc"
    break;

  case 87: /* expression: expression LS_THAN_EQ expression  */
#line 377 "parser.yy"
                                                                {(yyval.exp) = new CompLE((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2353 "parser.cc"
    break;

  case 88: /* expression: expression GR_THAN expression  */
#line 378 "parser.yy"
                                                                {(yyval.exp) = new CompGT((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2359 "parser.cc"
    break;

  case 89: /* expression: expression GR_THAN_EQ expression  */
#line 379 "parser.yy"
                                                                {(yyval.exp) = new CompGE((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2365 "parser.cc"
    break;

  case 90: /* expression: expression LOGICAL_AND expression  */
#line 380 "parser.yy"
                                                                {(yyval.exp) = new LogicalAND((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2371 "parser.cc"
    break;

  case 91: /* expression: expression LOGICAL_OR expression  */
#line 381 "parser.yy"
                                                                {(yyval.exp) = new LogicalOR((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2377 "parser.cc"
    break;

  case 92: /* expression: LOGICAL_NOT expression  */
#line 382 "parser.yy"
                                                                        {(yyval.exp) = new LogicalNOT((yyvsp[0].exp));}
#line 2383 "parser.cc"
    break;

  case 93: /* expression: INC variable  */
#line 383 "parser.yy"
                                                                                {(yyval.exp) = new PrefixInc((Variable*)(yyvsp[0].exp));}
#line 2389 "parser.cc"
    break;

  case 94: /* expression: DEC variable  */
#line 384 "parser.yy"
                                                                                {(yyval.exp) = new PostfixDec((Variable*)(yyvsp[0].exp));}
#line 2395 "parser.cc"
    break;

  case 95: /* expression: variable INC  */
#line 385 "parser.yy"
                                                                {(yyval.exp) = new PostfixInc((Variable*)(yyvsp[-1].exp));}
#line 2401 "parser.cc"
    break;

  case 96: /* expression: variable DEC  */
#line 386 "parser.yy"
                                                                {(yyval.exp) = new PostfixDec((Variable*)(yyvsp[-1].exp));}
#line 2407 "parser.cc"
    break;

  case 97: /* expression: variable ASSIGN expression  */
#line 387 "parser.yy"
                                                                {(yyval.exp) = new AssignmentExp((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2413 "parser.cc"
    break;

  case 98: /* expression: variable MUL_ASSIGN expression  */
#line 388 "parser.yy"
                                                                {(yyval.exp) = new MulAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2419 "parser.cc"
    break;

  case 99: /* expression: variable DIV_ASSIGN expression  */
#line 389 "parser.yy"
                                                                {(yyval.exp) = new DivAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2425 "parser.cc"
    break;

  case 100: /* expression: variable MOD_ASSIGN expression  */
#line 390 "parser.yy"
                                                                {(yyval.exp) = new ModAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2431 "parser.cc"
    break;

  case 101: /* expression: variable ADD_ASSIGN expression  */
#line 391 "parser.yy"
                                                                {(yyval.exp) = new AddAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2437 "parser.cc"
    break;

  case 102: /* expression: variable SUB_ASSIGN expression  */
#line 392 "parser.yy"
                                                                {(yyval.exp) = new SubAssign((Variable*)(yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2443 "parser.cc"
    break;

  case 103: /* expression: expression '?' expression ':' expression  */
#line 393 "parser.yy"
                                                        {(yyval.exp) = new TernaryOperator((yyvsp[-4].exp), (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 2449 "parser.cc"
    break;

  case 104: /* expression_list: expression  */
#line 397 "parser.yy"
                                                                {(yyval.exp_list) = new vector<Expression*>(); ((yyval.exp_list))->push_back((yyvsp[0].exp));}
#line 2455 "parser.cc"
    break;

  case 105: /* expression_list: expression_list ',' expression  */
#line 398 "parser.yy"
                                                {(yyval.exp_list) = (yyvsp[-2].exp_list); ((yyval.exp_list))->push_back((yyvsp[0].exp));}
#line 2461 "parser.cc"
    break;

  case 114: /* compound_statement: '{' '}'  */
#line 416 "parser.yy"
                                                        {(yyval.stmt) = new CompoundStatement(vector<Statement*>());}
#line 2467 "parser.cc"
    break;

  case 115: /* $@11: %empty  */
#line 417 "parser.yy"
              {cur_symbol_table = cur_symbol_table->startNewScope();}
#line 2473 "parser.cc"
    break;

  case 116: /* compound_statement: '{' $@11 statement_list '}'  */
#line 419 "parser.yy"
              {cur_symbol_table = cur_symbol_table->endScope(); (yyval.stmt) = new CompoundStatement(*((yyvsp[-1].stmt_list)));}
#line 2479 "parser.cc"
    break;

  case 117: /* statement_list: statement  */
#line 423 "parser.yy"
                                                        {(yyval.stmt_list) = new vector<Statement*>(); ((yyval.stmt_list))->push_back((yyvsp[0].stmt));}
#line 2485 "parser.cc"
    break;

  case 118: /* statement_list: statement_list statement  */
#line 424 "parser.yy"
                                        {(yyval.stmt_list) = (yyvsp[-1].stmt_list); ((yyval.stmt_list))->push_back((yyvsp[0].stmt));}
#line 2491 "parser.cc"
    break;

  case 119: /* expression_statement: ';'  */
#line 428 "parser.yy"
                                          {(yyval.stmt) = new ExpressionStatement();}
#line 2497 "parser.cc"
    break;

  case 120: /* expression_statement: expression_list ';'  */
#line 429 "parser.yy"
                              {(yyval.stmt) = new ExpressionStatement((yyvsp[-1].exp_list));}
#line 2503 "parser.cc"
    break;

  case 121: /* selection_statement: IF '(' expression ')' compound_statement  */
#line 433 "parser.yy"
                                                                                                        {(yyval.stmt) = new IfStatement((yyvsp[-2].exp), (CompoundStatement*)(yyvsp[0].stmt));}
#line 2509 "parser.cc"
    break;

  case 122: /* selection_statement: IF '(' expression ')' compound_statement ELSE compound_statement  */
#line 434 "parser.yy"
                                                                                {(yyval.stmt) = new IfElseStatement((yyvsp[-4].exp), (CompoundStatement*)(yyvsp[-2].stmt), (CompoundStatement*)(yyvsp[0].stmt));}
#line 2515 "parser.cc"
    break;

  case 123: /* selection_statement: SWITCH '(' expression ')' statement  */
#line 435 "parser.yy"
                                                                                                        {(yyval.stmt) = new SwitchStatement((yyvsp[-2].exp), (CompoundStatement*)(yyvsp[0].stmt));}
#line 2521 "parser.cc"
    break;

  case 124: /* labeled_statement: IDENTIFIER ':' statement  */
#line 439 "parser.yy"
                                                {Expression* temp = new Identifier(*((yyvsp[-2].id)));(yyval.stmt) = new LabeledStatement(temp, (yyvsp[0].stmt));}
#line 2527 "parser.cc"
    break;

  case 125: /* labeled_statement: CASE expression ':' statement  */
#line 440 "parser.yy"
                                        {(yyval.stmt) = new CaseLabel((yyvsp[-2].exp), (yyvsp[0].stmt));}
#line 2533 "parser.cc"
    break;

  case 126: /* labeled_statement: DEFAULT ':' statement  */
#line 441 "parser.yy"
                                                {(yyval.stmt) = new DefaultLabel((yyvsp[0].stmt));}
#line 2539 "parser.cc"
    break;

  case 127: /* $@12: %empty  */
#line 445 "parser.yy"
                    {cur_symbol_table = cur_symbol_table->startNewScope("while", true);}
#line 2545 "parser.cc"
    break;

  case 128: /* iteration_statement: WHILE '(' $@12 iter_expression ')' compound_statement  */
#line 446 "parser.yy"
                                                                                                                                        {(yyval.stmt) = new WhileLoop((CompoundStatement*)(yyvsp[0].stmt), (yyvsp[-2].exp)); cur_symbol_table = cur_symbol_table->endScope();}
#line 2551 "parser.cc"
    break;

  case 129: /* $@13: %empty  */
#line 447 "parser.yy"
                  {cur_symbol_table = cur_symbol_table->startNewScope("for", true);}
#line 2557 "parser.cc"
    break;

  case 130: /* iteration_statement: FOR '(' $@13 statement expression_statement iter_expression ')' compound_statement  */
#line 448 "parser.yy"
                                                                                        {(yyval.stmt) = new ForLoop((CompoundStatement*)(yyvsp[0].stmt), (ExpressionStatement*)(yyvsp[-4].stmt), (ExpressionStatement*)(yyvsp[-3].stmt), (yyvsp[-2].exp)); cur_symbol_table = cur_symbol_table->endScope();}
#line 2563 "parser.cc"
    break;

  case 131: /* iter_expression: %empty  */
#line 452 "parser.yy"
                  {(yyval.exp) = NULL;}
#line 2569 "parser.cc"
    break;

  case 133: /* jump_statement: CONTINUE ';'  */
#line 457 "parser.yy"
                                                {(yyval.stmt) = new ContinueStatement();}
#line 2575 "parser.cc"
    break;

  case 134: /* jump_statement: BREAK ';'  */
#line 458 "parser.yy"
                                                        {(yyval.stmt) = new BreakStatement();}
#line 2581 "parser.cc"
    break;

  case 135: /* jump_statement: SEND expression_statement  */
#line 459 "parser.yy"
                                        {(yyval.stmt) = new ReturnStatement((((ExpressionStatement*)(yyvsp[0].stmt))->getValue()).back());}
#line 2587 "parser.cc"
    break;


#line 2591 "parser.cc"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 462 "parser.yy"


void init_yylloc(const char* filename){
	yylloc.first_line = yylloc.last_line = yylineno = 1;
	yylloc.first_column = yylloc.last_column = 0;
	yylloc.filename = filename;
}

int main(int argc, char **argv){
	// The parser trace is generated only if yydebug is set to 1
	#ifdef PARSER_TRACE_DEBUG
		yydebug = 1;
	#endif
	
	if(argc < 2){
		string filename = "test10.tngt";
		init_yylloc(filename.c_str());
		yyrestart(fopen(filename.c_str(), "r"));
		yyparse();
		#ifdef SYMBOL_TABLE_DEBUG
			global_symbol_table.printSymbolTable(std::cout);
		#endif
	}
    else{
        for(int i = 1; i < argc; i++){
            init_yylloc(argv[i]);
            FILE *file = fopen(argv[i], "r");
            if(file == NULL){ perror(argv[i]); return -1; }
            yyrestart(file);

			yyparse();

			#ifdef SYMBOL_TABLE_DEBUG
			int file_dir_path_size = (string(argv[i]).find_last_of('/') == string::npos) ? 0 : string(argv[i]).find_last_of('/') + 1;
			string dirname = string(argv[i]).substr(0, file_dir_path_size);
			string filename = string(argv[i]).substr(file_dir_path_size, string(argv[i]).size() - file_dir_path_size - 5);
			filesystem::create_directory(dirname + "output/");
			string symbol_table_filename = dirname + "output/" + filename + ".sym";
			ofstream symbol_table_output_file(symbol_table_filename);
			global_symbol_table.printSymbolTable(symbol_table_output_file);
			#endif

            fclose(file);
        }
    }
}

void yyerror(const char*s){
	fprintf(stdout, "%s: Line %d-(%d..%d):\n\t%s\n", yylloc.filename.c_str(), yylloc.first_line, yylloc.first_column, yylloc.last_column, s);
	fprintf(stderr, "%s: Line %d-(%d..%d):\n\t%s\n", yylloc.filename.c_str(), yylloc.first_line, yylloc.first_column, yylloc.last_column, s);
}
