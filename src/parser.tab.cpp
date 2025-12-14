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
#include "symbol_table.hpp"
#include "codegen.hpp"
#include "ast_print.hpp"

CodeGen gen;
SymbolTable symtab;
extern int yylineno;
int yylex(void);
void yyerror(const char *s);

Stmt* programAST = nullptr;
bool verbose = false;

#line 88 "parser.tab.cpp"

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
  YYSYMBOL_command = 53,                   /* command  */
  YYSYMBOL_proc_head = 54,                 /* proc_head  */
  YYSYMBOL_proc_call = 55,                 /* proc_call  */
  YYSYMBOL_declarations = 56,              /* declarations  */
  YYSYMBOL_args_decl = 57,                 /* args_decl  */
  YYSYMBOL_type = 58,                      /* type  */
  YYSYMBOL_args = 59,                      /* args  */
  YYSYMBOL_expression = 60,                /* expression  */
  YYSYMBOL_condition = 61,                 /* condition  */
  YYSYMBOL_value = 62,                     /* value  */
  YYSYMBOL_identifier = 63                 /* identifier  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   267

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

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
static const yytype_uint8 yyrline[] =
{
       0,    61,    61,    72,    73,    74,    78,    81,    87,    92,
     100,   103,   104,   105,   106,   107,   108,   109,   110,   113,
     119,   123,   127,   132,   137,   142,   150,   151,   155,   156,
     157,   158,   162,   163,   167,   170,   175,   180,   185,   190,
     198,   199,   200,   201,   202,   203,   207,   210,   216,   222,
     233
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
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
  "program_all", "procedures", "main", "commands", "command", "proc_head",
  "proc_call", "declarations", "args_decl", "type", "args", "expression",
  "condition", "value", "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-26)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -26,    11,    45,   -26,     1,   -22,   -26,    -4,    -2,    34,
     220,    18,    -3,    32,    -1,     4,     4,    24,   220,    36,
       4,   -25,     0,   -26,    47,    63,    42,   220,    44,   -26,
     -26,   -26,   -10,    50,   220,     5,   -26,    57,    80,    73,
     -26,    89,    97,     6,    75,    82,    76,    27,   -26,   -26,
     -26,     4,    83,   114,    81,    32,   -26,   -26,   127,   220,
     220,     4,     4,     4,     4,     4,     4,   220,     4,     4,
     -26,   -26,   -26,    23,    85,    86,    93,   218,    92,   -26,
      94,    96,   -26,   140,   156,   -26,   -26,   -26,   -26,   -26,
     -26,   169,    58,   102,    98,   -26,   -26,   -26,   -26,     4,
       4,     4,     4,     4,    99,   110,   -26,   -26,   220,   -26,
     -26,     4,     4,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   107,   182,   141,   143,   112,   -26,   220,   220,   -26,
     198,   211,   -26,   -26
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,     0,     0,     2,     0,     0,     0,
       0,    24,     0,    28,     0,     0,     0,     0,     0,     0,
       0,    48,     0,     9,     0,     0,     0,     0,     0,    29,
      30,    31,     0,     0,     0,     0,    46,    48,     0,     0,
      47,     0,     0,     0,     0,     0,     0,     0,     7,     8,
      17,     0,     0,     0,    22,    28,    20,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    19,    33,     0,     0,     0,     0,    34,     0,     6,
       0,     0,     4,     0,     0,    41,    45,    44,    40,    43,
      42,     0,     0,     0,     0,    21,    50,    49,    10,     0,
       0,     0,     0,     0,     0,     0,    26,     3,     0,    12,
      13,     0,     0,    14,    32,    35,    36,    37,    38,    39,
      25,     0,     0,     0,     0,     0,    11,     0,     0,    23,
       0,     0,    15,    16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -26,   -26,   -26,   -26,   -18,   -19,   -26,   -26,   144,   -26,
     104,   -26,   -26,    -9,    -7,    16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,    22,    23,     9,    24,    12,    32,
      33,    73,    76,    38,    39,    25
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      43,    10,    27,    49,    34,     7,    48,    41,    15,    53,
      59,     3,    16,    45,    15,    17,    58,    46,    16,    47,
      18,    17,    19,    20,    49,     8,    18,    69,    19,    20,
      55,    40,    40,    56,    49,    44,    40,    28,    14,    49,
      13,    83,    84,    11,    77,    28,    11,    21,     4,    91,
      36,    37,     5,    21,    85,    86,    87,    88,    89,    90,
      93,    92,    26,    94,    49,    49,    95,    40,    29,    30,
      31,    42,    49,    74,    75,   111,   112,    40,    40,    40,
      40,    40,    40,    37,    40,    40,    50,    51,    52,    60,
     122,    54,   115,   116,   117,   118,   119,    57,    61,    62,
      63,    47,    67,    49,   123,   124,    64,    65,    66,   130,
     131,    49,    49,    68,    70,    40,    40,    40,    40,    40,
      79,    71,    15,    72,    78,    80,    16,    40,    40,    17,
      96,    97,    98,    82,    18,    15,    19,    20,   104,    16,
     105,   113,    17,   106,   120,   114,   107,    18,    15,    19,
      20,   121,    16,   125,   127,    17,   128,   129,    35,    81,
      18,    21,    19,    20,    15,     0,   108,   109,    16,     0,
       0,    17,     0,     0,    21,     0,    18,    15,    19,    20,
       0,    16,     0,   110,    17,     0,     0,    21,     0,    18,
      15,    19,    20,   126,    16,     0,     0,    17,     0,     0,
       0,     0,    18,    21,    19,    20,    15,     0,     0,     0,
      16,     0,     0,    17,     0,     0,    21,   132,    18,    15,
      19,    20,     0,    16,     0,     0,    17,     0,    15,    21,
     133,    18,    16,    19,    20,    17,     0,     0,     0,     0,
      18,     0,    19,    20,     0,    21,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,     0,     0,    21,     0,
       0,     0,     0,     0,     0,     0,     0,    21
};

static const yytype_int16 yycheck[] =
{
      18,     5,     5,    22,     5,     4,     6,    16,     8,    27,
       5,     0,    12,    20,     8,    15,    34,    42,    12,    44,
      20,    15,    22,    23,    43,    47,    20,    21,    22,    23,
      40,    15,    16,    43,    53,    19,    20,    40,     4,    58,
      42,    59,    60,    47,    51,    40,    47,    47,     3,    67,
      46,    47,     7,    47,    61,    62,    63,    64,    65,    66,
      69,    68,    44,    40,    83,    84,    43,    51,    36,    37,
      38,    47,    91,    46,    47,    17,    18,    61,    62,    63,
      64,    65,    66,    47,    68,    69,    39,    24,    46,     9,
     108,    47,    99,   100,   101,   102,   103,    47,    25,    26,
      27,    44,    13,   122,   111,   112,    33,    34,    35,   127,
     128,   130,   131,    16,    39,    99,   100,   101,   102,   103,
       6,    39,     8,    47,    41,    44,    12,   111,   112,    15,
      45,    45,    39,     6,    20,     8,    22,    23,    46,    12,
      46,    39,    15,    47,    45,    47,     6,    20,     8,    22,
      23,    41,    12,    46,    13,    15,    13,    45,    14,    55,
      20,    47,    22,    23,     8,    -1,    10,    11,    12,    -1,
      -1,    15,    -1,    -1,    47,    -1,    20,     8,    22,    23,
      -1,    12,    -1,    14,    15,    -1,    -1,    47,    -1,    20,
       8,    22,    23,    11,    12,    -1,    -1,    15,    -1,    -1,
      -1,    -1,    20,    47,    22,    23,     8,    -1,    -1,    -1,
      12,    -1,    -1,    15,    -1,    -1,    47,    19,    20,     8,
      22,    23,    -1,    12,    -1,    -1,    15,    -1,     8,    47,
      19,    20,    12,    22,    23,    15,    -1,    -1,    -1,    -1,
      20,    -1,    22,    23,    -1,    47,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    49,    50,     0,     3,     7,    51,     4,    47,    54,
       5,    47,    56,    42,     4,     8,    12,    15,    20,    22,
      23,    47,    52,    53,    55,    63,    44,     5,    40,    36,
      37,    38,    57,    58,     5,    56,    46,    47,    61,    62,
      63,    61,    47,    52,    63,    62,    42,    44,     6,    53,
      39,    24,    46,    52,    47,    40,    43,    47,    52,     5,
       9,    25,    26,    27,    33,    34,    35,    13,    16,    21,
      39,    39,    47,    59,    46,    47,    60,    62,    41,     6,
      44,    58,     6,    52,    52,    62,    62,    62,    62,    62,
      62,    52,    62,    61,    40,    43,    45,    45,    39,    28,
      29,    30,    31,    32,    46,    46,    47,     6,    10,    11,
      14,    17,    18,    39,    47,    62,    62,    62,    62,    62,
      45,    41,    52,    62,    62,    46,    11,    13,    13,    45,
      52,    52,    19,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    51,    51,    52,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    55,    56,    56,    56,    56,    57,    57,    58,    58,
      58,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      61,    61,    61,    61,    61,    61,    62,    62,    63,    63,
      63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     8,     7,     0,     6,     5,     2,     1,
       4,     7,     5,     5,     5,     9,     9,     2,     3,     3,
       4,     4,     3,     8,     1,     6,     4,     2,     0,     1,
       1,     1,     3,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     4,
       4
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
#line 61 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] program_all\n";
                                                                                programAST = (yyvsp[0].stmt);
                                                                                symtab.dump();

                                                                                std::cout << "\n=== AST (last statement) ===\n";
                                                                                gen.genStmt(programAST);
                                                                                //printStmt(lastStmt);
                                                                            }
#line 1251 "parser.tab.cpp"
    break;

  case 3: /* procedures: procedures PROCEDURE proc_head IS declarations IN commands END  */
#line 72 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] procedures PROCEDURE IS decl IN\n";}
#line 1257 "parser.tab.cpp"
    break;

  case 4: /* procedures: procedures PROCEDURE proc_head IS IN commands END  */
#line 73 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] procedures PROCEDURE IS IN\n";}
#line 1263 "parser.tab.cpp"
    break;

  case 5: /* procedures: %empty  */
#line 74 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] procedures empty\n";}
#line 1269 "parser.tab.cpp"
    break;

  case 6: /* main: PROGRAM IS declarations IN commands END  */
#line 78 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] main program (with declarations)\n";
                                                                                (yyval.stmt) = (yyvsp[-1].stmt);
                                                                            }
#line 1277 "parser.tab.cpp"
    break;

  case 7: /* main: PROGRAM IS IN commands END  */
#line 81 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] main program (no declarations)\n";
                                                                                (yyval.stmt) = (yyvsp[-1].stmt); 
                                                                            }
#line 1285 "parser.tab.cpp"
    break;

  case 8: /* commands: commands command  */
#line 87 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] commands with following command\n";
                                                                                auto block = static_cast<BlockStmt*>((yyvsp[-1].stmt));
                                                                                block->stmts.emplace_back((yyvsp[0].stmt));
                                                                                (yyval.stmt) = block;
                                                                            }
#line 1295 "parser.tab.cpp"
    break;

  case 9: /* commands: command  */
#line 92 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] commands with a command\n";
                                                                                auto block = new BlockStmt();
                                                                                block->stmts.emplace_back((yyvsp[0].stmt));
                                                                                (yyval.stmt) = block;
                                                                            }
#line 1305 "parser.tab.cpp"
    break;

  case 10: /* command: identifier ASSIGN expression SEM  */
#line 100 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command ASSIGN\n";
                                                                                (yyval.stmt) = new AssignStmt((yyvsp[-3].id), std::unique_ptr<Expr>((yyvsp[-1].expr)));
                                                                            }
#line 1313 "parser.tab.cpp"
    break;

  case 11: /* command: IF condition THEN commands ELSE commands ENDIF  */
#line 103 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command IF THEN ELSE\n";}
#line 1319 "parser.tab.cpp"
    break;

  case 12: /* command: IF condition THEN commands ENDIF  */
#line 104 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command IF THEN\n";}
#line 1325 "parser.tab.cpp"
    break;

  case 13: /* command: WHILE condition DO commands ENDWHILE  */
#line 105 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command WHILE DO\n";}
#line 1331 "parser.tab.cpp"
    break;

  case 14: /* command: REPEAT commands UNTIL condition SEM  */
#line 106 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command REPEAT UNTIL\n";}
#line 1337 "parser.tab.cpp"
    break;

  case 15: /* command: FOR PIDENTIFIER FROM value TO value DO commands ENDFOR  */
#line 107 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command FOR FROM TO DO\n";}
#line 1343 "parser.tab.cpp"
    break;

  case 16: /* command: FOR PIDENTIFIER FROM value DOWNTO value DO commands ENDFOR  */
#line 108 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command FOR FROM DOWNTO DO\n";}
#line 1349 "parser.tab.cpp"
    break;

  case 17: /* command: proc_call SEM  */
#line 109 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command proc_call\n";}
#line 1355 "parser.tab.cpp"
    break;

  case 18: /* command: READ identifier SEM  */
#line 110 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command READ\n";
                                                                                (yyval.stmt) = new ReadStmt((yyvsp[-1].id));
                                                                            }
#line 1363 "parser.tab.cpp"
    break;

  case 19: /* command: WRITE value SEM  */
#line 113 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] command WRITE\n";
                                                                                (yyval.stmt) = new WriteStmt(std::unique_ptr<Expr>((yyvsp[-1].expr)));
                                                                            }
#line 1371 "parser.tab.cpp"
    break;

  case 20: /* proc_head: PIDENTIFIER LBR args_decl RBR  */
#line 119 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] proc_head PIDENTIFIER(args_decl)\n";}
#line 1377 "parser.tab.cpp"
    break;

  case 21: /* proc_call: PIDENTIFIER LBR args RBR  */
#line 123 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] proc_call PIDENTIFIER(args)\n";}
#line 1383 "parser.tab.cpp"
    break;

  case 22: /* declarations: declarations COM PIDENTIFIER  */
#line 127 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] declarations with more PID\n";
                                                                                if (!symtab.declareVariable((yyvsp[0].id))) {
                                                                                    yyerror("Variable redeclared");
                                                                                }
                                                                            }
#line 1393 "parser.tab.cpp"
    break;

  case 23: /* declarations: declarations COM PIDENTIFIER LSB NUM COL NUM RSB  */
#line 132 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] declarations with more PID[]\n";
                                                                                if (!symtab.declareArray((yyvsp[-5].id), (yyvsp[-3].num), (yyvsp[-1].num))) {
                                                                                    yyerror("Array redeclared or invalid range");
                                                                                }
                                                                            }
#line 1403 "parser.tab.cpp"
    break;

  case 24: /* declarations: PIDENTIFIER  */
#line 137 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] declarations with last PID\n";
                                                                                if (!symtab.declareVariable((yyvsp[0].id))) {
                                                                                    yyerror("Variable redeclared");
                                                                                }
                                                                            }
#line 1413 "parser.tab.cpp"
    break;

  case 25: /* declarations: PIDENTIFIER LSB NUM COL NUM RSB  */
#line 142 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] declarations with last PID[]\n";
                                                                                if (!symtab.declareArray((yyvsp[-5].id), (yyvsp[-3].num), (yyvsp[-1].num))) {
                                                                                    yyerror("Array redeclared or invalid range");
                                                                                }
                                                                            }
#line 1423 "parser.tab.cpp"
    break;

  case 26: /* args_decl: args_decl COM type PIDENTIFIER  */
#line 150 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] args_decl with more PID\n";}
#line 1429 "parser.tab.cpp"
    break;

  case 27: /* args_decl: type PIDENTIFIER  */
#line 151 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] args_decl with last PID\n";}
#line 1435 "parser.tab.cpp"
    break;

  case 28: /* type: %empty  */
#line 155 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] type empty\n";}
#line 1441 "parser.tab.cpp"
    break;

  case 29: /* type: T  */
#line 156 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] type T\n";}
#line 1447 "parser.tab.cpp"
    break;

  case 30: /* type: I  */
#line 157 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] type I\n";}
#line 1453 "parser.tab.cpp"
    break;

  case 31: /* type: O  */
#line 158 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] type O\n";}
#line 1459 "parser.tab.cpp"
    break;

  case 32: /* args: args COM PIDENTIFIER  */
#line 162 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] args with more PID\n";}
#line 1465 "parser.tab.cpp"
    break;

  case 33: /* args: PIDENTIFIER  */
#line 163 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] args with last PID\n";}
#line 1471 "parser.tab.cpp"
    break;

  case 34: /* expression: value  */
#line 167 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression value\n";
                                                                                (yyval.expr) = (yyvsp[0].expr);
                                                                            }
#line 1479 "parser.tab.cpp"
    break;

  case 35: /* expression: value PLUS value  */
#line 170 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression PLUS\n";
                                                                                (yyval.expr) = new BinExpr(BinOp::ADD,
                                                                                                    std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                    std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1489 "parser.tab.cpp"
    break;

  case 36: /* expression: value MINUS value  */
#line 175 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression MINUS\n";
                                                                                (yyval.expr) = new BinExpr(BinOp::SUB,
                                                                                                    std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                    std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1499 "parser.tab.cpp"
    break;

  case 37: /* expression: value MUL value  */
#line 180 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression MUL\n";
                                                                            (yyval.expr) = new BinExpr(BinOp::MUL,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1509 "parser.tab.cpp"
    break;

  case 38: /* expression: value DIV value  */
#line 185 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expressiion DIV\n";
                                                                            (yyval.expr) = new BinExpr(BinOp::DIV,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1519 "parser.tab.cpp"
    break;

  case 39: /* expression: value MOD value  */
#line 190 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] expression MOD\n";
                                                                            (yyval.expr) = new BinExpr(BinOp::MOD,
                                                                                                std::unique_ptr<Expr>((yyvsp[-2].expr)),
                                                                                                std::unique_ptr<Expr>((yyvsp[0].expr)));
                                                                            }
#line 1529 "parser.tab.cpp"
    break;

  case 40: /* condition: value EQ value  */
#line 198 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condition EQ\n";}
#line 1535 "parser.tab.cpp"
    break;

  case 41: /* condition: value NEQ value  */
#line 199 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condiition NEQ\n";}
#line 1541 "parser.tab.cpp"
    break;

  case 42: /* condition: value GT value  */
#line 200 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condition GT\n";}
#line 1547 "parser.tab.cpp"
    break;

  case 43: /* condition: value LT value  */
#line 201 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condiition LT\n";}
#line 1553 "parser.tab.cpp"
    break;

  case 44: /* condition: value GEQ value  */
#line 202 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condiition GEQ\n";}
#line 1559 "parser.tab.cpp"
    break;

  case 45: /* condition: value LEQ value  */
#line 203 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] condition LEQ\n";}
#line 1565 "parser.tab.cpp"
    break;

  case 46: /* value: NUM  */
#line 207 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] value NUM\n";
                                                                                (yyval.expr) = new ConstExpr((yyvsp[0].num));
                                                                            }
#line 1573 "parser.tab.cpp"
    break;

  case 47: /* value: identifier  */
#line 210 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] value identifier\n";
                                                                                (yyval.expr) = new VarExpr((yyvsp[0].id));
                                                                            }
#line 1581 "parser.tab.cpp"
    break;

  case 48: /* identifier: PIDENTIFIER  */
#line 216 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] identifier PID\n";
                                                                                (yyval.id) = (yyvsp[0].id);
                                                                                if (!symtab.lookup((yyvsp[0].id))) {
                                                                                    yyerror("Use of undeclared variable");
                                                                                }
                                                                            }
#line 1592 "parser.tab.cpp"
    break;

  case 49: /* identifier: PIDENTIFIER LSB PIDENTIFIER RSB  */
#line 222 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] identifier [PID]\n";
                                                                                (yyval.id) = (yyvsp[-3].id);
                                                                                auto sym = symtab.lookup((yyvsp[-3].id));
                                                                                if (!sym) yyerror("Use of undeclared array");
                                                                                if (sym->kind != SymbolKind::ARRAY) yyerror("Indexing non-array");

                                                                                // indeks jest zmienną → NIE sprawdzamy zakresu
                                                                                if (!symtab.lookup((yyvsp[-1].id))) {
                                                                                    yyerror("Use of undeclared variable as array index");
                                                                                }
                                                                            }
#line 1608 "parser.tab.cpp"
    break;

  case 50: /* identifier: PIDENTIFIER LSB NUM RSB  */
#line 233 "parser.ypp"
                                                                            {if (verbose) std::cout << "[PARSE] identifier [NUM]\n";
                                                                                (yyval.id) = (yyvsp[-3].id);
                                                                                auto sym = symtab.lookup((yyvsp[-3].id));
                                                                                if (!sym) {
                                                                                    yyerror("Use of undeclared array");
                                                                                }
                                                                                if (sym->kind != SymbolKind::ARRAY) {
                                                                                    yyerror("Indexing non-array");
                                                                                }
                                                                                if ((yyvsp[-1].num) < sym->start || (yyvsp[-1].num) > sym->end)
                                                                                    yyerror("Array index out of bounds");
                                                                            }
#line 1625 "parser.tab.cpp"
    break;


#line 1629 "parser.tab.cpp"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 247 "parser.ypp"


void yyerror(const char *s) {
    std::cerr << "SYNTAX ERROR line "
              << yylineno << ": " << s << std::endl;
    exit(1);
}
