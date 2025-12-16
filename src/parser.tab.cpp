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




/* First part of user prologue.  */
#line 5 "parser.ypp"

#include <iostream>
#include <cstdlib>
#include <vector>
#include "symbol_table.hpp"
#include "codegen.hpp"
#include "ast_print.hpp"
#include "procedure_table.hpp"

ProcedureTable proctab;
std::vector<ProcParam> currentParams;
CodeGen gen(proctab);
SymbolTable symtab;
extern int yylineno;
int yylex(void);
void yyerror(const char *s);
static std::vector<std::string> forIterStack;

static bool isForIterator(const std::string& name) {
    for (auto it = forIterStack.rbegin(); it != forIterStack.rend(); ++it)
        if (*it == name) return true;
    return false;
}
Stmt* programAST = nullptr;
bool verbose = false;
char currentParamMode = 'T';

#line 99 "parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_IS = 4,                         /* IS  */
  YYSYMBOL_IN = 5,                         /* IN  */
  YYSYMBOL_END = 6,                        /* END  */
  YYSYMBOL_PROCEDURE = 7,                  /* PROCEDURE  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_THEN = 9,                       /* THEN  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_ENDIF = 11,                     /* ENDIF  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_DO = 13,                        /* DO  */
  YYSYMBOL_ENDWHILE = 14,                  /* ENDWHILE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_FROM = 16,                      /* FROM  */
  YYSYMBOL_TO = 17,                        /* TO  */
  YYSYMBOL_DOWNTO = 18,                    /* DOWNTO  */
  YYSYMBOL_ENDFOR = 19,                    /* ENDFOR  */
  YYSYMBOL_REPEAT = 20,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 21,                     /* UNTIL  */
  YYSYMBOL_READ = 22,                      /* READ  */
  YYSYMBOL_WRITE = 23,                     /* WRITE  */
  YYSYMBOL_ASSIGN = 24,                    /* ASSIGN  */
  YYSYMBOL_NEQ = 25,                       /* NEQ  */
  YYSYMBOL_LEQ = 26,                       /* LEQ  */
  YYSYMBOL_GEQ = 27,                       /* GEQ  */
  YYSYMBOL_PLUS = 28,                      /* PLUS  */
  YYSYMBOL_MINUS = 29,                     /* MINUS  */
  YYSYMBOL_MUL = 30,                       /* MUL  */
  YYSYMBOL_DIV = 31,                       /* DIV  */
  YYSYMBOL_MOD = 32,                       /* MOD  */
  YYSYMBOL_EQ = 33,                        /* EQ  */
  YYSYMBOL_LT = 34,                        /* LT  */
  YYSYMBOL_GT = 35,                        /* GT  */
  YYSYMBOL_T = 36,                         /* T  */
  YYSYMBOL_I = 37,                         /* I  */
  YYSYMBOL_O = 38,                         /* O  */
  YYSYMBOL_SEM = 39,                       /* SEM  */
  YYSYMBOL_COM = 40,                       /* COM  */
  YYSYMBOL_COL = 41,                       /* COL  */
  YYSYMBOL_LBR = 42,                       /* LBR  */
  YYSYMBOL_RBR = 43,                       /* RBR  */
  YYSYMBOL_LSB = 44,                       /* LSB  */
  YYSYMBOL_RSB = 45,                       /* RSB  */
  YYSYMBOL_NUM = 46,                       /* NUM  */
  YYSYMBOL_PIDENTIFIER = 47,               /* PIDENTIFIER  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program_all = 49,               /* program_all  */
  YYSYMBOL_procedures = 50,                /* procedures  */
  YYSYMBOL_main = 51,                      /* main  */
  YYSYMBOL_commands = 52,                  /* commands  */
  YYSYMBOL_for_dir = 53,                   /* for_dir  */
  YYSYMBOL_command = 54,                   /* command  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_proc_head = 56,                 /* proc_head  */
  YYSYMBOL_57_2 = 57,                      /* $@2  */
  YYSYMBOL_proc_call = 58,                 /* proc_call  */
  YYSYMBOL_declarations = 59,              /* declarations  */
  YYSYMBOL_args_decl = 60,                 /* args_decl  */
  YYSYMBOL_type = 61,                      /* type  */
  YYSYMBOL_args = 62,                      /* args  */
  YYSYMBOL_expression = 63,                /* expression  */
  YYSYMBOL_condition = 64,                 /* condition  */
  YYSYMBOL_value = 65,                     /* value  */
  YYSYMBOL_identifier = 66                 /* identifier  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   279

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    94,   101,   108,   112,   115,   121,   126,
     134,   135,   139,   147,   152,   156,   160,   165,   164,   182,
     185,   188,   194,   194,   207,   224,   229,   234,   239,   247,
     252,   260,   261,   262,   263,   267,   273,   282,   285,   290,
     295,   300,   305,   313,   318,   323,   328,   333,   338,   346,
     349,   355,   360,   374
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "IS", "IN",
  "END", "PROCEDURE", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "ENDWHILE", "FOR", "FROM", "TO", "DOWNTO", "ENDFOR", "REPEAT", "UNTIL",
  "READ", "WRITE", "ASSIGN", "NEQ", "LEQ", "GEQ", "PLUS", "MINUS", "MUL",
  "DIV", "MOD", "EQ", "LT", "GT", "T", "I", "O", "SEM", "COM", "COL",
  "LBR", "RBR", "LSB", "RSB", "NUM", "PIDENTIFIER", "$accept",
  "program_all", "procedures", "main", "commands", "for_dir", "command",
  "$@1", "proc_head", "$@2", "proc_call", "declarations", "args_decl",
  "type", "args", "expression", "condition", "value", "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-38)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -38,    13,    20,   -38,    28,    -3,   -38,    -2,   -38,    31,
     232,    -7,     1,    -4,    -1,     2,     2,     6,   232,    23,
       2,   -37,   113,   -38,    21,    48,    35,   232,    36,   -16,
     232,     3,   -38,    38,    75,    -9,   -38,    72,   -38,   179,
      47,    49,    42,     4,   -38,   -38,   -38,     2,    50,   126,
      55,   -38,   -38,   -38,   -12,    45,   139,   232,   232,     2,
       2,     2,     2,     2,     2,   232,    77,     2,   -38,   -38,
     -38,   -10,    56,    58,    61,    37,    59,   -38,    63,   -16,
     -38,   -38,   -38,   157,   173,   -38,   -38,   -38,   -38,   -38,
     -38,   195,     2,    65,    60,   -38,   -38,   -38,   -38,     2,
       2,     2,     2,     2,    73,    67,    76,   -38,   232,   -38,
     -38,    62,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
      64,   -38,   213,   -38,   -38,     2,    79,   -38,   109,   -38,
     232,   226,   -38
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,     0,     0,     2,     0,    22,     0,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     9,     0,     0,     0,     0,     0,    31,
       0,     0,    49,    51,     0,     0,    50,     0,    17,     0,
       0,     0,     0,     0,     7,     8,    19,     0,     0,     0,
      25,    32,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,    21,
      36,     0,     0,     0,     0,    37,     0,     6,     0,    31,
      23,    30,     4,     0,     0,    44,    48,    47,    43,    46,
      45,     0,     0,     0,     0,    24,    53,    52,    12,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     0,    14,
      15,     0,    16,    35,    38,    39,    40,    41,    42,    28,
       0,    29,     0,    10,    11,     0,     0,    13,     0,    26,
       0,     0,    18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -38,   -38,   -38,   -38,   -18,   -38,   -20,   -38,   -38,   -38,
     -38,   112,   -38,    51,   -38,   -38,   -15,    14,    -5
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,    22,   125,    23,    66,     9,    13,
      24,    12,    54,    55,    71,    74,    34,    35,    25
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      39,    37,    45,    10,    30,    42,    27,    43,    57,    49,
      36,    36,    56,     3,    40,    36,    59,    60,    61,    45,
      51,    52,    53,     4,    62,    63,    64,     5,    79,    45,
      94,    80,     7,    95,    41,    14,    45,    26,    29,    83,
      84,    28,    36,    28,     8,    11,    11,    91,    32,    33,
      72,    73,    93,    38,    36,    36,    36,    36,    36,    36,
      46,    75,    36,    45,    45,    99,   100,   101,   102,   103,
      33,    45,    47,    85,    86,    87,    88,    89,    90,   123,
     124,    48,    43,    50,    58,    65,    68,    36,    69,    70,
     122,    76,    81,    92,    36,    36,    36,    36,    36,    78,
      98,    96,    45,    97,   112,   104,   111,   113,   120,   105,
     126,    45,   131,   114,   115,   116,   117,   118,   119,    44,
      36,    15,   130,   121,   129,    16,    31,     0,    17,     0,
     106,     0,    77,    18,    15,    19,    20,     0,    16,   128,
       0,    17,     0,     0,     0,    82,    18,    15,    19,    20,
       0,    16,     0,     0,    17,     0,     0,     0,     0,    18,
      21,    19,    20,   107,     0,    15,     0,     0,     0,    16,
       0,     0,    17,    21,     0,     0,     0,    18,     0,    19,
      20,    15,     0,   108,   109,    16,    21,    15,    17,     0,
       0,    16,     0,    18,    17,    19,    20,     0,     0,    18,
      67,    19,    20,    15,    21,     0,     0,    16,     0,   110,
      17,     0,     0,     0,     0,    18,     0,    19,    20,     0,
      21,    15,     0,     0,   127,    16,    21,     0,    17,     0,
       0,     0,     0,    18,    15,    19,    20,     0,    16,     0,
      15,    17,    21,     0,    16,   132,    18,    17,    19,    20,
       0,     0,    18,     0,    19,    20,     0,     0,     0,     0,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     0,     0,    21
};

static const yytype_int16 yycheck[] =
{
      18,    16,    22,     5,     5,    42,     5,    44,     5,    27,
      15,    16,    30,     0,    19,    20,    25,    26,    27,    39,
      36,    37,    38,     3,    33,    34,    35,     7,    40,    49,
      40,    43,     4,    43,    20,     4,    56,    44,    42,    57,
      58,    40,    47,    40,    47,    47,    47,    65,    46,    47,
      46,    47,    67,    47,    59,    60,    61,    62,    63,    64,
      39,    47,    67,    83,    84,    28,    29,    30,    31,    32,
      47,    91,    24,    59,    60,    61,    62,    63,    64,    17,
      18,    46,    44,    47,     9,    13,    39,    92,    39,    47,
     108,    41,    47,    16,    99,   100,   101,   102,   103,    44,
      39,    45,   122,    45,    39,    46,    92,    47,    41,    46,
      46,   131,   130,    99,   100,   101,   102,   103,    45,     6,
     125,     8,    13,    47,    45,    12,    14,    -1,    15,    -1,
      79,    -1,     6,    20,     8,    22,    23,    -1,    12,   125,
      -1,    15,    -1,    -1,    -1,     6,    20,     8,    22,    23,
      -1,    12,    -1,    -1,    15,    -1,    -1,    -1,    -1,    20,
      47,    22,    23,     6,    -1,     8,    -1,    -1,    -1,    12,
      -1,    -1,    15,    47,    -1,    -1,    -1,    20,    -1,    22,
      23,     8,    -1,    10,    11,    12,    47,     8,    15,    -1,
      -1,    12,    -1,    20,    15,    22,    23,    -1,    -1,    20,
      21,    22,    23,     8,    47,    -1,    -1,    12,    -1,    14,
      15,    -1,    -1,    -1,    -1,    20,    -1,    22,    23,    -1,
      47,     8,    -1,    -1,    11,    12,    47,    -1,    15,    -1,
      -1,    -1,    -1,    20,     8,    22,    23,    -1,    12,    -1,
       8,    15,    47,    -1,    12,    19,    20,    15,    22,    23,
      -1,    -1,    20,    -1,    22,    23,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    49,    50,     0,     3,     7,    51,     4,    47,    56,
       5,    47,    59,    57,     4,     8,    12,    15,    20,    22,
      23,    47,    52,    54,    58,    66,    44,     5,    40,    42,
       5,    59,    46,    47,    64,    65,    66,    64,    47,    52,
      66,    65,    42,    44,     6,    54,    39,    24,    46,    52,
      47,    36,    37,    38,    60,    61,    52,     5,     9,    25,
      26,    27,    33,    34,    35,    13,    55,    21,    39,    39,
      47,    62,    46,    47,    63,    65,    41,     6,    44,    40,
      43,    47,     6,    52,    52,    65,    65,    65,    65,    65,
      65,    52,    16,    64,    40,    43,    45,    45,    39,    28,
      29,    30,    31,    32,    46,    46,    61,     6,    10,    11,
      14,    65,    39,    47,    65,    65,    65,    65,    65,    45,
      41,    47,    52,    17,    18,    53,    46,    11,    65,    45,
      13,    52,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    51,    51,    52,    52,
      53,    53,    54,    54,    54,    54,    54,    55,    54,    54,
      54,    54,    57,    56,    58,    59,    59,    59,    59,    60,
      60,    61,    61,    61,    61,    62,    62,    63,    63,    63,
      63,    63,    63,    64,    64,    64,    64,    64,    64,    65,
      65,    66,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     8,     7,     0,     6,     5,     2,     1,
       1,     1,     4,     7,     5,     5,     5,     0,    10,     2,
       3,     3,     0,     5,     4,     3,     8,     1,     6,     4,
       2,     0,     1,     1,     1,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     4,     4
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
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
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program_all: procedures main  */
#line 81 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] program_all\n";
                                                                                programAST = (yyvsp[0].stmt);
                                                                                if (verbose) symtab.dump();

                                                                                if (verbose) std::cout << "\n=== AST (last statement) ===\n";
                                                                                gen.genStmt(programAST);
                                                                                gen.finish();
                                                                                gen.flush();
                                                                                //printStmt(lastStmt);
                                                                            }
#line 1539 "parser.tab.cpp"
    break;

  case 3: /* procedures: procedures PROCEDURE proc_head IS declarations IN commands END  */
#line 94 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] procedures PROCEDURE IS decl IN\n";
                                                                                auto* body = (yyvsp[-1].block);
                                                                                proctab.defineBody((yyvsp[-5].id), body);
                                                                                
                                                                                symtab.leaveScope();
                                                                                currentParams.clear();
                                                                            }
#line 1551 "parser.tab.cpp"
    break;

  case 4: /* procedures: procedures PROCEDURE proc_head IS IN commands END  */
#line 101 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] procedures PROCEDURE IS IN\n";
                                                                                auto* body = (yyvsp[-1].block);
                                                                                proctab.defineBody((yyvsp[-4].id), body);
                                                                                
                                                                                symtab.leaveScope();
                                                                                currentParams.clear();
                                                                            }
#line 1563 "parser.tab.cpp"
    break;

  case 5: /* procedures: %empty  */
#line 108 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] procedures empty\n";}
#line 1569 "parser.tab.cpp"
    break;

  case 6: /* main: PROGRAM IS declarations IN commands END  */
#line 112 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] main program (with declarations)\n";
                                                                                (yyval.stmt) = (yyvsp[-1].block);
                                                                            }
#line 1577 "parser.tab.cpp"
    break;

  case 7: /* main: PROGRAM IS IN commands END  */
#line 115 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] main program (no declarations)\n";
                                                                                (yyval.stmt) = (yyvsp[-1].block); 
                                                                            }
#line 1585 "parser.tab.cpp"
    break;

  case 8: /* commands: commands command  */
#line 121 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] commands with following command\n";
                                                                                auto block = (yyvsp[-1].block);
                                                                                block->stmts.emplace_back((yyvsp[0].stmt));
                                                                                (yyval.block) = block;
                                                                            }
#line 1595 "parser.tab.cpp"
    break;

  case 9: /* commands: command  */
#line 126 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] commands with a command\n";
                                                                                auto block = new BlockStmt();
                                                                                block->stmts.emplace_back((yyvsp[0].stmt));
                                                                                (yyval.block) = block;
                                                                            }
#line 1605 "parser.tab.cpp"
    break;

  case 10: /* for_dir: TO  */
#line 134 "parser.ypp"
             { (yyval.num) = 0; }
#line 1611 "parser.tab.cpp"
    break;

  case 11: /* for_dir: DOWNTO  */
#line 135 "parser.ypp"
             { (yyval.num) = 1; }
#line 1617 "parser.tab.cpp"
    break;

  case 12: /* command: identifier ASSIGN expression SEM  */
#line 139 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command ASSIGN\n";
                                                                                auto v = static_cast<VarExpr*>((yyvsp[-3].expr));

                                                                                if (isForIterator(v->name))
                                                                                    yyerror("Modification of FOR iterator");

                                                                                (yyval.stmt) = new AssignStmt(v, std::unique_ptr<Expr>((yyvsp[-1].expr)));
                                                                            }
#line 1630 "parser.tab.cpp"
    break;

  case 13: /* command: IF condition THEN commands ELSE commands ENDIF  */
#line 147 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command IF THEN ELSE\n";
                                                                                (yyval.stmt) = new IfStmt(std::unique_ptr<CondExpr>((yyvsp[-5].cond)),
                                                                                                std::unique_ptr<Stmt>((yyvsp[-3].block)),
                                                                                                std::unique_ptr<Stmt>((yyvsp[-1].block)));
                                                                            }
#line 1640 "parser.tab.cpp"
    break;

  case 14: /* command: IF condition THEN commands ENDIF  */
#line 152 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command IF THEN\n";
                                                                                (yyval.stmt) = new IfStmt(std::unique_ptr<CondExpr>((yyvsp[-3].cond)),
                                                                                                std::unique_ptr<Stmt>((yyvsp[-1].block)));
                                                                            }
#line 1649 "parser.tab.cpp"
    break;

  case 15: /* command: WHILE condition DO commands ENDWHILE  */
#line 156 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command WHILE DO\n";
                                                                                (yyval.stmt) = new WhileStmt(std::unique_ptr<CondExpr>((yyvsp[-3].cond)),
                                                                                                    std::unique_ptr<Stmt>((yyvsp[-1].block)));
                                                                            }
#line 1658 "parser.tab.cpp"
    break;

  case 16: /* command: REPEAT commands UNTIL condition SEM  */
#line 160 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command REPEAT UNTIL\n";
                                                                                (yyval.stmt) = new RepeatStmt(std::unique_ptr<Stmt>((yyvsp[-3].block)),
                                                                                                    std::unique_ptr<CondExpr>((yyvsp[-1].cond)));
                                                                            }
#line 1667 "parser.tab.cpp"
    break;

  case 17: /* $@1: %empty  */
#line 165 "parser.ypp"
    {
        symtab.enterScope();
        symtab.declareVariable((yyvsp[0].id));
        forIterStack.push_back((yyvsp[0].id));
    }
#line 1677 "parser.tab.cpp"
    break;

  case 18: /* command: FOR PIDENTIFIER $@1 FROM value for_dir value DO commands ENDFOR  */
#line 171 "parser.ypp"
    {
        const Symbol* itSym = symtab.lookup((yyvsp[-8].id));
if (!itSym) yyerror("INTERNAL: missing FOR iterator");

(yyval.stmt) = new ForStmt(itSym->uid,
                std::unique_ptr<Expr>((yyvsp[-5].expr)),
                std::unique_ptr<Expr>((yyvsp[-3].expr)),
                std::unique_ptr<Stmt>((yyvsp[-1].block)),
                (yyvsp[-4].num) == 1);

    }
#line 1693 "parser.tab.cpp"
    break;

  case 19: /* command: proc_call SEM  */
#line 182 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command proc_call\n";
                                                                                (yyval.stmt) = (yyvsp[-1].stmt);
                                                                            }
#line 1701 "parser.tab.cpp"
    break;

  case 20: /* command: READ identifier SEM  */
#line 185 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command READ\n";
                                                                                (yyval.stmt) = new ReadStmt(static_cast<VarExpr*>((yyvsp[-1].expr)));
                                                                            }
#line 1709 "parser.tab.cpp"
    break;

  case 21: /* command: WRITE value SEM  */
#line 188 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command WRITE\n";
                                                                                (yyval.stmt) = new WriteStmt(std::unique_ptr<Expr>((yyvsp[-1].expr)));
                                                                            }
#line 1717 "parser.tab.cpp"
    break;

  case 22: /* $@2: %empty  */
#line 194 "parser.ypp"
                                                                            {
                                                                                symtab.enterScope();
                                                                                currentParams.clear();
                                                                            }
#line 1726 "parser.tab.cpp"
    break;

  case 23: /* proc_head: PIDENTIFIER $@2 LBR args_decl RBR  */
#line 198 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] proc_head PIDENTIFIER(args_decl)\n";
                                                                                if (!proctab.declareProcedure((yyvsp[-4].id), currentParams)) {
                                                                                    yyerror("Procedure redeclared");
                                                                                }
                                                                                (yyval.id) = (yyvsp[-4].id);
                                                                            }
#line 1737 "parser.tab.cpp"
    break;

  case 24: /* proc_call: PIDENTIFIER LBR args RBR  */
#line 207 "parser.ypp"
                                                                            {
          const auto* proc = proctab.lookup((yyvsp[-3].id));
          if (!proc) yyerror("Call to undeclared procedure");
          if (proc->params.size() != (yyvsp[-1].idlist)->size())
              yyerror("Wrong number of procedure arguments");

          std::vector<std::string> callArgs;
          callArgs.reserve((yyvsp[-1].idlist)->size());
          for (char* s : *(yyvsp[-1].idlist)) callArgs.emplace_back(s);

          (yyval.stmt) = new CallStmt(std::string((yyvsp[-3].id)), std::move(callArgs));

          delete (yyvsp[-1].idlist);
      }
#line 1756 "parser.tab.cpp"
    break;

  case 25: /* declarations: declarations COM PIDENTIFIER  */
#line 224 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] declarations with more PID\n";
                                                                                if (!symtab.declareVariable((yyvsp[0].id))) {
                                                                                    yyerror("Variable redeclared");
                                                                                }
                                                                            }
#line 1766 "parser.tab.cpp"
    break;

  case 26: /* declarations: declarations COM PIDENTIFIER LSB NUM COL NUM RSB  */
#line 229 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] declarations with more PID[]\n";
                                                                                if (!symtab.declareArray((yyvsp[-5].id), (yyvsp[-3].num), (yyvsp[-1].num))) {
                                                                                    yyerror("Array redeclared or invalid range");
                                                                                }
                                                                            }
#line 1776 "parser.tab.cpp"
    break;

  case 27: /* declarations: PIDENTIFIER  */
#line 234 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] declarations with last PID\n";
                                                                                if (!symtab.declareVariable((yyvsp[0].id))) {
                                                                                    yyerror("Variable redeclared");
                                                                                }
                                                                            }
#line 1786 "parser.tab.cpp"
    break;

  case 28: /* declarations: PIDENTIFIER LSB NUM COL NUM RSB  */
#line 239 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] declarations with last PID[]\n";
                                                                                if (!symtab.declareArray((yyvsp[-5].id), (yyvsp[-3].num), (yyvsp[-1].num))) {
                                                                                    yyerror("Array redeclared or invalid range");
                                                                                }
                                                                            }
#line 1796 "parser.tab.cpp"
    break;

  case 29: /* args_decl: args_decl COM type PIDENTIFIER  */
#line 247 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] args_decl with more PID\n";
                                                                                symtab.declareVariable((yyvsp[0].id));
                                                                                const Symbol* s = symtab.lookup((yyvsp[0].id));
                                                                                currentParams.push_back({currentParamMode, (yyvsp[0].id), s->uid});
                                                                            }
#line 1806 "parser.tab.cpp"
    break;

  case 30: /* args_decl: type PIDENTIFIER  */
#line 252 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] args_decl with last PID\n";
                                                                                symtab.declareVariable((yyvsp[0].id));
                                                                                const Symbol* s = symtab.lookup((yyvsp[0].id));
                                                                                currentParams.push_back({currentParamMode, (yyvsp[0].id), s->uid});
                                                                            }
#line 1816 "parser.tab.cpp"
    break;

  case 31: /* type: %empty  */
#line 260 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] type empty\n";}
#line 1822 "parser.tab.cpp"
    break;

  case 32: /* type: T  */
#line 261 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] type T\n"; currentParamMode = 'T';}
#line 1828 "parser.tab.cpp"
    break;

  case 33: /* type: I  */
#line 262 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] type I\n"; currentParamMode = 'I';}
#line 1834 "parser.tab.cpp"
    break;

  case 34: /* type: O  */
#line 263 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] type O\n"; currentParamMode = 'O';}
#line 1840 "parser.tab.cpp"
    break;

  case 35: /* args: args COM PIDENTIFIER  */
#line 267 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] args with more PID\n";
                                                                                if (symtab.lookup((yyvsp[0].id))->kind == SymbolKind::ARRAY)
                                                                                yyerror("Array passed as procedure argument");
                                                                                (yyvsp[-2].idlist)->push_back((yyvsp[0].id));
                                                                                (yyval.idlist) = (yyvsp[-2].idlist);
                                                                            }
#line 1851 "parser.tab.cpp"
    break;

  case 36: /* args: PIDENTIFIER  */
#line 273 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] args with last PID\n";
                                                                                if (symtab.lookup((yyvsp[0].id))->kind == SymbolKind::ARRAY)
                                                                                yyerror("Array passed as procedure argument");
                                                                                (yyval.idlist) = new std::vector<char*>();
                                                                                (yyval.idlist)->push_back((yyvsp[0].id));
                                                                            }
#line 1862 "parser.tab.cpp"
    break;

  case 37: /* expression: value  */
#line 282 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression value\n";
                                                                                (yyval.expr) = (yyvsp[0].expr);
                                                                            }
#line 1870 "parser.tab.cpp"
    break;

  case 38: /* expression: value PLUS value  */
#line 285 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression PLUS\n";
                                                                                (yyval.expr) = new BinExpr(BinOp::ADD,
                                                                                                    std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                    std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1880 "parser.tab.cpp"
    break;

  case 39: /* expression: value MINUS value  */
#line 290 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression MINUS\n";
                                                                                (yyval.expr) = new BinExpr(BinOp::SUB,
                                                                                                    std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                    std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1890 "parser.tab.cpp"
    break;

  case 40: /* expression: value MUL value  */
#line 295 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression MUL\n";
                                                                            (yyval.expr) = new BinExpr(BinOp::MUL,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1900 "parser.tab.cpp"
    break;

  case 41: /* expression: value DIV value  */
#line 300 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expressiion DIV\n";
                                                                            (yyval.expr) = new BinExpr(BinOp::DIV,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1910 "parser.tab.cpp"
    break;

  case 42: /* expression: value MOD value  */
#line 305 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression MOD\n";
                                                                            (yyval.expr) = new BinExpr(BinOp::MOD,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1920 "parser.tab.cpp"
    break;

  case 43: /* condition: value EQ value  */
#line 313 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condition EQ\n";
                                                                                (yyval.cond) = new CondExpr(CondOp::EQ,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1930 "parser.tab.cpp"
    break;

  case 44: /* condition: value NEQ value  */
#line 318 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condiition NEQ\n";
                                                                                (yyval.cond) = new CondExpr(CondOp::NEQ,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1940 "parser.tab.cpp"
    break;

  case 45: /* condition: value GT value  */
#line 323 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condition GT\n";
                                                                                (yyval.cond) = new CondExpr(CondOp::GT,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1950 "parser.tab.cpp"
    break;

  case 46: /* condition: value LT value  */
#line 328 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condiition LT\n";
                                                                                (yyval.cond) = new CondExpr(CondOp::LT,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1960 "parser.tab.cpp"
    break;

  case 47: /* condition: value GEQ value  */
#line 333 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condiition GEQ\n";
                                                                                (yyval.cond) = new CondExpr(CondOp::GEQ,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1970 "parser.tab.cpp"
    break;

  case 48: /* condition: value LEQ value  */
#line 338 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condition LEQ\n";
                                                                                (yyval.cond) = new CondExpr(CondOp::LEQ,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1980 "parser.tab.cpp"
    break;

  case 49: /* value: NUM  */
#line 346 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] value NUM\n";
                                                                                (yyval.expr) = new ConstExpr((yyvsp[0].num));
                                                                            }
#line 1988 "parser.tab.cpp"
    break;

  case 50: /* value: identifier  */
#line 349 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] value identifier\n";
                                                                                (yyval.expr) = (yyvsp[0].expr);
                                                                            }
#line 1996 "parser.tab.cpp"
    break;

  case 51: /* identifier: PIDENTIFIER  */
#line 355 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] identifier PID\n";
                                                                                const Symbol* sym = symtab.lookup((yyvsp[0].id));
                                                                                if (!sym) yyerror("Use of undeclared variable");
                                                                                (yyval.expr) = new VarExpr((yyvsp[0].id), sym->uid);
                                                                            }
#line 2006 "parser.tab.cpp"
    break;

  case 52: /* identifier: PIDENTIFIER LSB PIDENTIFIER RSB  */
#line 360 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] identifier [PID]\n";
                                                                                const Symbol* symArr = symtab.lookup((yyvsp[-3].id));
                                                                                const Symbol* symIdx = symtab.lookup((yyvsp[-1].id));
                                                                                if (!symArr) yyerror("Use of undeclared array");
                                                                                if (symArr->kind != SymbolKind::ARRAY) yyerror("Indexing non-array");
                                                                                if (!symIdx) yyerror("Use of undeclared variable");

                                                                                auto idx = std::make_unique<VarExpr>((yyvsp[-1].id), symIdx->uid);
                                                                                auto* v  = new VarExpr((yyvsp[-3].id), symArr->uid, std::move(idx));
                                                                                v->arrStart = symArr->start;
                                                                                v->arrEnd   = symArr->end;

                                                                                (yyval.expr) = v;
                                                                            }
#line 2025 "parser.tab.cpp"
    break;

  case 53: /* identifier: PIDENTIFIER LSB NUM RSB  */
#line 374 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] identifier [NUM]\n";
                                                                                const Symbol* symArr = symtab.lookup((yyvsp[-3].id));
                                                                                if (!symArr) yyerror("Use of undeclared array");
                                                                                if (symArr->kind != SymbolKind::ARRAY) yyerror("Indexing non-array");

                                                                                auto idx = std::make_unique<ConstExpr>((yyvsp[-1].num));
                                                                                auto* v  = new VarExpr((yyvsp[-3].id), symArr->uid, std::move(idx));
                                                                                v->arrStart = symArr->start;
                                                                                v->arrEnd   = symArr->end;
                                                                                (yyval.expr) = v;
                                                                            }
#line 2041 "parser.tab.cpp"
    break;


#line 2045 "parser.tab.cpp"

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
          = {yyssp, yytoken};
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
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

#line 387 "parser.ypp"


void yyerror(const char *s) {
    std::cerr << "SYNTAX ERROR line "
              << yylineno << ": " << s << std::endl;
    exit(1);
}
