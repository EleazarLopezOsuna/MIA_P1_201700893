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
#line 1 "parser.y" /* yacc.c:339  */

#include "scanner.h"//se importa el header del analisis sintactico
#include <QString>
#include <string>
#include "qdebug.h"
#include <iostream>
#include "MKDISK.h"
#include "RMDISK.h"
//#include "obfdisk.h"
//#include "mount.h"
//#include "unmount.h"
//#include "mkfs.h"
//#include "login.h"
//#include "logout.h"
//#include "mkgrp.h"
//#include "rmgrp.h"
//#include "mkusr.h"
//#include "rmusr.h"
//#include "Chmod.h"
//#include "mkfile.h"
//#include "cat.h"
//#include "rem.h"
//#include "edit.h"
//#include "ren.h"
//#include "Mkdir.h"
//#include "cp.h"
//#include "mv.h"
//#include "ffind.h"
//#include "cchown.h"
//#include "chgrp.h"
//#include "ppause.h"
//#include "reportes.h"

using namespace std;
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON

extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON

extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
MKDISK *disco=new MKDISK();
RMDISK *eliminar=new RMDISK();
//obfdisk *administrado=new obfdisk();
//mount * montaje=new mount(1);
//mount * desmontaje=new mount(2);
//unmount * desmontar=new unmount();
//mkfs * formateo=new mkfs();
//login * entrar=new login();
//logout * salir=new logout();
//mkgrp* grupo=new mkgrp();
//rmgrp *elgrupo=new rmgrp();
//mkusr* usuario=new mkusr();
//rmusr* elusuario=new rmusr();
//Chmod* elusuario1=new Chmod();
//mkfile* file=new mkfile();
//cat * mostrar=new cat();
//rem * elimina=new rem();
//edit * editar=new edit();
//ren * modificar=new ren();
//Mkdir * carpeta=new Mkdir();
//cp * copiar=new cp();
//mv * mover=new mv();
//fFind * buscar=new fFind();
//cchown * cambiar=new cchown();
//chgrp * cambio=new chgrp();
//ppause * pausa=new ppause();
//Estructuras::REP nuevo_reporte;
//reportes * reporte = new reportes();
//particioneslist::lista*lista;
//Estructuras::user_activo * activo;

/*void setSalida(particioneslist::lista * l_general , Estructuras::user_activo * user){
    lista = l_general;
    activo = user;
}*/

int yyerror(const char* mens)
{
    std::cout << mens <<" "<<yytext<< std::endl;
    return 0;
}

#line 148 "parser.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    coment = 258,
    psize = 259,
    pf = 260,
    pu = 261,
    pbf = 262,
    pff = 263,
    pwf = 264,
    pk = 265,
    pm = 266,
    pb = 267,
    ppath = 268,
    pmkdisk = 269,
    prmdisk = 270,
    pfdisk = 271,
    ptype = 272,
    pdelete = 273,
    pname = 274,
    padd = 275,
    pmount = 276,
    punmount = 277,
    pid = 278,
    pmkfs = 279,
    pfs = 280,
    pfast = 281,
    pfull = 282,
    p2fs = 283,
    p3fs = 284,
    plogin = 285,
    pusuario = 286,
    ppassword = 287,
    plogout = 288,
    pmkgrp = 289,
    prmgrp = 290,
    pmkusr = 291,
    pusr = 292,
    pwd = 293,
    pgrp = 294,
    prmusr = 295,
    pchmod = 296,
    pugo = 297,
    pr = 298,
    pmkfile = 299,
    pcont = 300,
    pcat = 301,
    pfilen = 302,
    prem = 303,
    pedit = 304,
    pren = 305,
    pmkdir = 306,
    pp = 307,
    pcp = 308,
    pdest = 309,
    pmv = 310,
    pfind = 311,
    pchown = 312,
    pchgrp = 313,
    ppause = 314,
    pe = 315,
    pl = 316,
    name2 = 317,
    prep = 318,
    pruta = 319,
    pmbr = 320,
    pdisk = 321,
    pinode = 322,
    pjournaling = 323,
    pblock = 324,
    pbm_inode = 325,
    pbm_block = 326,
    ptree = 327,
    psb = 328,
    pexec = 329,
    pls = 330,
    punto = 331,
    bracketabre = 332,
    bracketcierra = 333,
    corcheteabre = 334,
    corchetecierra = 335,
    puntocoma = 336,
    potencia = 337,
    coma = 338,
    parentesisabre = 339,
    parentesiscierra = 340,
    llaveabre = 341,
    llavecierra = 342,
    mas = 343,
    menos = 344,
    multiplicacion = 345,
    igual = 346,
    dolar = 347,
    dospuntos = 348,
    path = 349,
    entero = 350,
    numnegatinamevo = 351,
    cadena = 352,
    identificador = 353,
    caracter = 354,
    ruta = 355,
    ruta_carpeta = 356,
    pass = 357,
    rutacualquiera = 358,
    suma = 359,
    multi = 360,
    division = 361
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 87 "parser.y" /* yacc.c:355  */

//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
//QString TEXT;



#line 303 "parser.cpp" /* yacc.c:355  */
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

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 334 "parser.cpp" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
#define YYFINAL  100
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   322

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  163
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  361

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   235,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     264,   271,   280,   285,   290,   295,   297,   301,   305,   310,
     314,   319,   323,   327,   343,   351,   374,   384,   394,   403,
     421,   437,   444,   451,   461,   468,   478,   488,   494,   500,
     506,   511,   521,   531,   541,   549,   559,   569,   617,   633,
     640,   642,   647,   653,   658,   663,   665,   669,   673,   679,
     685,   691,   697,   703,   709,   715,   721,   728,   732,   736,
     738,   743,   747,   751,   753,   758,   763,   768,   770,   775,
     779,   782,   787,   791,   793,   798,   802,   804,   808,   812,
     816,   818,   822,   826,   828,   833,   837,   841,   845,   847,
     851,   855,   859,   861,   866,   871,   876,   878,   883,   888,
     893,   895,   896,   898,   903,   908,   909,   911,   915,   920,
     925,   930,   932,   937,   942,   947,   952,   957,   962,   968,
     973,   975,   991,  1008,  1012,  1016,  1021,  1025,  1029,  1034,
    1038,  1042,  1047,  1051
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "coment", "psize", "pf", "pu", "pbf",
  "pff", "pwf", "pk", "pm", "pb", "ppath", "pmkdisk", "prmdisk", "pfdisk",
  "ptype", "pdelete", "pname", "padd", "pmount", "punmount", "pid",
  "pmkfs", "pfs", "pfast", "pfull", "p2fs", "p3fs", "plogin", "pusuario",
  "ppassword", "plogout", "pmkgrp", "prmgrp", "pmkusr", "pusr", "pwd",
  "pgrp", "prmusr", "pchmod", "pugo", "pr", "pmkfile", "pcont", "pcat",
  "pfilen", "prem", "pedit", "pren", "pmkdir", "pp", "pcp", "pdest", "pmv",
  "pfind", "pchown", "pchgrp", "ppause", "pe", "pl", "name2", "prep",
  "pruta", "pmbr", "pdisk", "pinode", "pjournaling", "pblock", "pbm_inode",
  "pbm_block", "ptree", "psb", "pexec", "pls", "punto", "bracketabre",
  "bracketcierra", "corcheteabre", "corchetecierra", "puntocoma",
  "potencia", "coma", "parentesisabre", "parentesiscierra", "llaveabre",
  "llavecierra", "mas", "menos", "multiplicacion", "igual", "dolar",
  "dospuntos", "path", "entero", "numnegatinamevo", "cadena",
  "identificador", "caracter", "ruta", "ruta_carpeta", "pass",
  "rutacualquiera", "suma", "multi", "division", "$accept", "INICIO",
  "MKDISK", "COMANDOMKDISK", "AJUSTE1", "UNIDADES1", "RUTA_CADENA",
  "RMDISK", "FDISK", "MOUNT", "UNMOUNT", "MKFS", "LOGIN", "LOGOUT",
  "MKGRP", "RMGRP", "MKUSR", "RMUSR", "CHMOD", "MKFILE", "REM", "CAT",
  "EDIT", "REN", "MKDIR", "CP", "MV", "FIND", "CHOWN", "CHGRP", "REPORTES",
  "EXEC", "PAUSE", "COMENTS", "COMANDOREP", "NAME_REPS", "COMANDOCHGRP",
  "COMANDOCHOWN", "COMANDOFIND", "COMANDOMV", "COMANDOCP", "COMANDOMKDIR",
  "COMANDOREN", "COMANDOEDIT", "COMANDOMKFILE", "COMANDOCHMOD",
  "COMANDOMKUSR", "COMANDOLOGIN", "PASS", "COMANDOMKFS",
  "SISTEMA_FORMATEO", "COMANDOMOUNT", "COMANDOFDISK", "NAME", "AJUSTE2",
  "UNIDADES2", "TIPO_PARTICION", "TIPO_BORRADO", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361
};
# endif

#define YYPACT_NINF -210

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-210)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,  -210,   -81,   -52,   -48,    -1,     3,    16,    28,  -210,
      31,    45,    48,    65,    77,    86,    98,   109,   124,   137,
     138,   139,   141,   142,   143,   144,  -210,   145,   146,    11,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,   168,  -210,
       8,   165,  -210,     4,  -210,    62,   163,  -210,   -13,  -210,
     210,   217,   152,  -210,   200,    70,  -210,    61,  -210,   113,
     225,   -10,  -210,    83,  -210,    -9,  -210,    -4,  -210,     5,
    -210,   140,  -210,    71,  -210,   126,  -210,    39,  -210,   226,
    -210,   149,   150,   151,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   164,   166,   167,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,    77,   183,   184,    86,   187,   190,   191,   192,   193,
     194,   195,   196,   138,   197,   198,   199,   201,   202,   203,
     204,   205,   143,   206,   207,   208,   209,   211,   212,   213,
     148,   185,    99,   -71,   -71,   214,   188,   189,   -71,   -45,
     123,   114,   215,   -71,   216,   218,   123,   219,   186,   220,
     114,    41,   114,   114,   114,    41,   114,   114,   -71,   224,
    -210,   227,   -71,  -210,   -71,   -71,   -71,   -71,   -71,   -71,
      18,   -71,  -210,   -71,   -71,   -71,   -71,   -71,   -35,   -71,
     114,  -210,   114,   114,   -71,    60,   222,   -71,   -71,   -81,
    -210,  -210,  -210,   -81,  -210,  -210,   -81,  -210,  -210,  -210,
     -81,  -210,   -48,  -210,  -210,  -210,   -48,  -210,  -210,  -210,
     -48,   -48,  -210,  -210,  -210,   -48,  -210,  -210,   -48,  -210,
    -210,   -48,   -48,    -1,    -1,  -210,    16,    16,  -210,  -210,
      16,    28,    28,  -210,    28,  -210,  -210,  -210,    48,    48,
      48,  -210,    77,    77,    86,    86,    86,  -210,  -210,   124,
     124,   137,   137,   137,   138,   139,   139,   141,   141,   142,
     142,   142,   143,   143,   144,   144,   145,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,   145,   145,
     145,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    70,    35,     0,   150,   141,     0,   136,   130,    50,
       0,     0,   126,     0,   122,   118,     0,     0,   113,   110,
     106,   103,   100,    97,    93,    89,    69,    75,     0,     0,
       2,     3,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     4,     0,    30,
       0,     0,    45,     0,    46,     0,     0,    48,     0,    49,
       0,     0,     0,    53,     0,     0,    55,     0,    56,     0,
       0,     0,    59,     0,    60,     0,    61,     0,    62,     0,
      63,     0,    64,     0,    65,     0,    66,     0,    67,     0,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   122,     0,     0,   118,     0,     0,     0,     0,     0,
       0,     0,     0,   106,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,     0,     0,   115,     0,     0,     0,     0,     0,     0,
       0,     0,   105,     0,     0,     0,     0,     0,     0,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,    38,    35,    39,    40,    35,    43,    41,    42,
      35,    44,   150,   153,   154,   155,   150,   156,   157,   158,
     150,   150,   159,   160,   161,   150,   162,   163,   150,   151,
     152,   150,   150,   141,   141,    47,   136,   136,   137,   138,
     136,   130,   130,   132,   130,   131,    51,    52,   126,   126,
     126,    54,   122,   122,   118,   118,   118,    58,    57,   113,
     113,   110,   110,   110,   106,   103,   103,   100,   100,    97,
      97,    97,    93,    93,    89,    89,    75,    85,    76,    77,
      81,    84,    83,    79,    80,    82,    78,    86,    75,    75,
      75,    68,    31,    32,    33,    34,   142,   143,   144,   145,
     146,   147,   149,   148,   139,   140,   134,   133,   135,   128,
     127,   129,   123,   124,   125,   119,   120,   116,   114,   117,
     111,   112,   107,   109,   108,   104,   101,   102,    98,    99,
      94,    96,    95,    90,    91,    88,    87,    72,    71,    73,
      74
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -210,  -210,  -210,   -68,  -210,  -210,  -128,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -209,  -210,   -78,  -147,   -87,   -69,
     -65,  -137,   -76,   -57,  -134,  -129,   -60,   -85,    69,  -138,
    -210,   -29,   -84,   -89,  -210,  -210,  -210,    80
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    29,    30,    59,   223,   226,   230,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    98,   308,    96,    94,    92,    90,
      88,    86,    84,    82,    78,    76,    73,    69,   264,    67,
     260,    64,    62,   265,   236,   240,   245,   248
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     193,     1,   190,   138,   142,   211,   202,   242,    58,   144,
     120,   100,     2,     3,     4,   243,   244,   114,   146,     5,
       6,   105,     7,   115,   121,   122,   227,   290,     8,   228,
     229,     9,    10,    11,    12,   139,   231,    60,    13,    14,
     241,    61,    15,   143,    16,   253,    17,    18,    19,    20,
     145,    21,   155,    22,    23,    24,    25,    26,   156,   147,
     272,    27,   157,   291,   275,   132,   276,   277,   278,   279,
     280,   281,    28,   284,   133,   285,   286,   287,   288,   289,
     282,   292,   251,   129,   150,   116,   296,   357,    63,   310,
     311,   262,    65,   266,   267,   268,   140,   270,   271,   358,
     359,   360,   141,   158,   134,    66,   135,   297,   151,   224,
     225,   283,   130,   131,   152,   249,   250,    68,   326,   327,
      70,   293,   328,   294,   295,   298,   299,   300,   301,   302,
     303,   304,   305,   306,    71,   307,   263,    72,   249,   250,
     337,   338,   339,   335,   336,   353,   354,   345,   316,   246,
     247,   312,   317,   148,    74,   313,   318,   319,   314,   149,
     136,   320,   315,   153,   321,   154,    75,   322,   323,   106,
     107,   108,   101,   102,   103,    77,   329,   330,   109,   331,
     117,   104,   110,   111,   112,   113,   118,    79,   119,   125,
     126,   127,   220,   221,   222,   233,   234,   235,    80,   237,
     238,   239,   350,   351,   352,   342,   343,   344,   332,   333,
     334,   249,   250,    81,   258,   259,   355,   356,   348,   349,
     346,   347,   340,   341,   324,   325,    83,    85,    87,   123,
      89,    91,    93,    95,    97,    99,   124,   128,   137,   159,
     160,   161,   162,   219,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   269,   173,   256,   174,   175,     0,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   191,   192,     0,     0,   194,     0,
       0,   195,   196,   197,   198,   199,   200,   201,   203,   204,
     205,     0,   206,   207,   208,   209,   210,   212,   213,   214,
     215,     0,   216,   217,   218,     0,     0,     0,     0,   232,
     252,     0,     0,     0,   254,     0,   255,   257,   261,   273,
     309,     0,   274
};

static const yytype_int16 yycheck[] =
{
     134,     3,   131,    13,    13,   152,   143,    52,    89,    13,
      23,     0,    14,    15,    16,    60,    61,    13,    13,    21,
      22,    13,    24,    19,    37,    38,    97,    62,    30,   100,
     101,    33,    34,    35,    36,    45,   164,    89,    40,    41,
     168,    89,    44,    52,    46,   173,    48,    49,    50,    51,
      54,    53,    13,    55,    56,    57,    58,    59,    19,    54,
     188,    63,    23,    98,   192,     4,   194,   195,   196,   197,
     198,   199,    74,   201,    13,   203,   204,   205,   206,   207,
      62,   209,   171,    13,    13,    23,   214,   296,    89,   217,
     218,   180,    89,   182,   183,   184,    13,   186,   187,   308,
     309,   310,    19,    64,    43,    89,    45,    47,    37,    10,
      11,   200,    42,    43,    43,    97,    98,    89,   256,   257,
      89,   210,   260,   212,   213,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    89,    75,    95,    89,    97,    98,
     274,   275,   276,   272,   273,   292,   293,   284,   232,    26,
      27,   219,   236,    13,    89,   223,   240,   241,   226,    19,
      47,   245,   230,    37,   248,    39,    89,   251,   252,     4,
       5,     6,     4,     5,     6,    89,   261,   262,    13,   264,
      17,    13,    17,    18,    19,    20,    23,    89,    25,    37,
      38,    39,     7,     8,     9,     7,     8,     9,    89,    10,
      11,    12,   289,   290,   291,   281,   282,   283,   268,   269,
     270,    97,    98,    89,    28,    29,   294,   295,   287,   288,
     285,   286,   279,   280,   253,   254,    89,    89,    89,    19,
      89,    89,    89,    89,    89,    89,    19,    37,    13,    13,
      91,    91,    91,    95,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,   185,    91,   176,    91,    91,    -1,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    -1,    -1,    91,    -1,
      -1,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    -1,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    -1,    91,    91,    91,    -1,    -1,    -1,    -1,    95,
      95,    -1,    -1,    -1,    98,    -1,    98,    98,    98,    95,
      98,    -1,    95
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    14,    15,    16,    21,    22,    24,    30,    33,
      34,    35,    36,    40,    41,    44,    46,    48,    49,    50,
      51,    53,    55,    56,    57,    58,    59,    63,    74,   108,
     109,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,    89,   110,
      89,    89,   159,    89,   158,    89,    89,   156,    89,   154,
      89,    89,    89,   153,    89,    89,   152,    89,   151,    89,
      89,    89,   150,    89,   149,    89,   148,    89,   147,    89,
     146,    89,   145,    89,   144,    89,   143,    89,   141,    89,
       0,     4,     5,     6,    13,    13,     4,     5,     6,    13,
      17,    18,    19,    20,    13,    19,    23,    17,    23,    25,
      23,    37,    38,    19,    19,    37,    38,    39,    37,    13,
      42,    43,     4,    13,    43,    45,    47,    13,    13,    45,
      13,    19,    13,    52,    13,    54,    13,    54,    13,    19,
      13,    37,    43,    37,    39,    13,    19,    23,    64,    13,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
     152,    91,    91,   151,    91,    91,    91,    91,    91,    91,
      91,    91,   148,    91,    91,    91,    91,    91,    91,    91,
      91,   144,    91,    91,    91,    91,    91,    91,    91,    95,
       7,     8,     9,   111,    10,    11,   112,    97,   100,   101,
     113,   113,    95,     7,     8,     9,   161,    10,    11,    12,
     162,   113,    52,    60,    61,   163,    26,    27,   164,    97,
      98,   160,    95,   113,    98,    98,   164,    98,    28,    29,
     157,    98,   160,    95,   155,   160,   160,   160,   160,   155,
     160,   160,   113,    95,    95,   113,   113,   113,   113,   113,
     113,   113,    62,   160,   113,   113,   113,   113,   113,   113,
      62,    98,   113,   160,   160,   160,   113,    47,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    75,   142,    98,
     113,   113,   110,   110,   110,   110,   159,   159,   159,   159,
     159,   159,   159,   159,   158,   158,   156,   156,   156,   154,
     154,   154,   153,   153,   153,   152,   152,   151,   151,   151,
     150,   150,   149,   149,   149,   148,   147,   147,   146,   146,
     145,   145,   145,   144,   144,   143,   143,   141,   141,   141,
     141
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     109,   110,   110,   110,   110,   110,   111,   111,   111,   112,
     112,   113,   113,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   141,   141,   141,   141,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   143,   143,   143,
     144,   144,   144,   144,   145,   145,   145,   145,   146,   146,
     146,   147,   147,   147,   148,   148,   148,   149,   149,   149,
     149,   150,   150,   150,   151,   151,   151,   151,   151,   152,
     152,   152,   152,   153,   153,   153,   153,   154,   154,   154,
     154,   155,   155,   156,   156,   156,   156,   157,   157,   158,
     158,   158,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   160,   160,   161,   161,   161,   162,   162,   162,   163,
     163,   163,   164,   164
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     5,     5,     5,     5,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     2,     2,     5,     2,     2,
       1,     5,     5,     2,     5,     2,     2,     5,     5,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     5,     1,
       1,     5,     5,     5,     5,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     5,     0,
       5,     5,     3,     0,     5,     5,     5,     0,     5,     5,
       0,     5,     5,     0,     5,     3,     0,     5,     5,     5,
       0,     5,     5,     0,     5,     3,     5,     5,     0,     5,
       5,     3,     0,     5,     5,     5,     0,     5,     5,     5,
       0,     1,     1,     5,     5,     5,     0,     1,     1,     5,
       5,     0,     5,     5,     5,     5,     5,     5,     5,     5,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 235 "parser.y" /* yacc.c:1646  */
    { }
#line 1769 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 236 "parser.y" /* yacc.c:1646  */
    {}
#line 1775 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 237 "parser.y" /* yacc.c:1646  */
    {}
#line 1781 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 238 "parser.y" /* yacc.c:1646  */
    {}
#line 1787 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 239 "parser.y" /* yacc.c:1646  */
    {}
#line 1793 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 240 "parser.y" /* yacc.c:1646  */
    {}
#line 1799 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 241 "parser.y" /* yacc.c:1646  */
    {}
#line 1805 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 242 "parser.y" /* yacc.c:1646  */
    {}
#line 1811 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 243 "parser.y" /* yacc.c:1646  */
    {}
#line 1817 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 244 "parser.y" /* yacc.c:1646  */
    {}
#line 1823 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 245 "parser.y" /* yacc.c:1646  */
    {}
#line 1829 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 246 "parser.y" /* yacc.c:1646  */
    {}
#line 1835 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 247 "parser.y" /* yacc.c:1646  */
    {}
#line 1841 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 248 "parser.y" /* yacc.c:1646  */
    {}
#line 1847 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 249 "parser.y" /* yacc.c:1646  */
    {}
#line 1853 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 250 "parser.y" /* yacc.c:1646  */
    {}
#line 1859 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 251 "parser.y" /* yacc.c:1646  */
    {}
#line 1865 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 252 "parser.y" /* yacc.c:1646  */
    {}
#line 1871 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 253 "parser.y" /* yacc.c:1646  */
    {}
#line 1877 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 254 "parser.y" /* yacc.c:1646  */
    {}
#line 1883 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 255 "parser.y" /* yacc.c:1646  */
    {}
#line 1889 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 256 "parser.y" /* yacc.c:1646  */
    {}
#line 1895 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 257 "parser.y" /* yacc.c:1646  */
    {}
#line 1901 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 258 "parser.y" /* yacc.c:1646  */
    {}
#line 1907 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 259 "parser.y" /* yacc.c:1646  */
    {}
#line 1913 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 260 "parser.y" /* yacc.c:1646  */
    {}
#line 1919 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 261 "parser.y" /* yacc.c:1646  */
    {}
#line 1925 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 262 "parser.y" /* yacc.c:1646  */
    {}
#line 1931 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 265 "parser.y" /* yacc.c:1646  */
    {
        disco->ejecutar_mkdisk();
        disco->limpiar();
        disco = new obmkdisk();
    }
#line 1941 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 272 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            if(val>0){
                disco->setSize(val);
            }else{
                std::cout<<"Error, debe ingresar un numero mayor a 0"<<std::endl;
            }
        }
#line 1954 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 281 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            disco->f = val;
        }
#line 1963 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 286 "parser.y" /* yacc.c:1646  */
    {
            int tam = atoi((yyvsp[-1].TEXT));
            disco->u = tam;
        }
#line 1972 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 291 "parser.y" /* yacc.c:1646  */
    {
            memset(disco->ruta, 0, 255);
            disco->setRuta((yyvsp[-1].TEXT));
        }
#line 1981 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 295 "parser.y" /* yacc.c:1646  */
    {}
#line 1987 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 298 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 1995 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 302 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 2003 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 306 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 2011 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 311 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 2019 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 315 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 2027 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 320 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), (yyvsp[0].TEXT), strlen((yyvsp[0].TEXT)) + 1);
        }
#line 2035 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 324 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), (yyvsp[0].TEXT), strlen((yyvsp[0].TEXT)) + 1);
        }
#line 2043 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 328 "parser.y" /* yacc.c:1646  */
    {
            char ruta [255];
            int s=strlen((yyvsp[0].TEXT));
            int j=0;
            for(int i=0;i<255;i++){
                if((yyvsp[0].TEXT)[i]=='\"'){

                }else{
                    ruta[j] = (yyvsp[0].TEXT)[i];
                    j++;
                }
            }
            memcpy((yyval.TEXT), ruta, strlen(ruta)+1);
        }
#line 2062 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 344 "parser.y" /* yacc.c:1646  */
    {
        obrmdisk* eliminar=new obrmdisk();
        eliminar->setRuta((yyvsp[0].TEXT));
        eliminar->eliminar_mrdisk();
        eliminar->limpiar();
    }
#line 2073 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 352 "parser.y" /* yacc.c:1646  */
    {
        if(administrado->par_nombre == true && administrado->par_path){
            //hay que verificar que tipo de operacion de fdisk es
            if(administrado->borrar !=0 && administrado->add == 0 && administrado->size ==NULL){
                administrado->operacion=1;
                administrado->ejecutar_fdisk(lista);
                administrado->limpiar();
            }else if(administrado->add == 1 && administrado->borrar== 0 && administrado->size == NULL){
                administrado->operacion=2;
                administrado->ejecutar_fdisk(lista);
                administrado->limpiar();
            }else if(administrado->size != NULL && administrado->add == 0 && administrado->borrar==0){
                administrado->operacion=0;
                administrado->ejecutar_fdisk(lista);
                administrado->limpiar();
            }
            administrado->limpiar();
        }else{
            std::cout<<"Error, no se cumplen con los parametros -> FDISK"<<endl;
        }
    }
#line 2099 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 375 "parser.y" /* yacc.c:1646  */
    {
        if(montaje->p_name == true && montaje->p_path == true){
            montaje->ejecutar_MOUNT(montaje->st_mount, lista);
            montaje->limpiar_mount();
        }else{
            std::cout<<"Error, no se cumplen con los parametros -> MOUNT"<<std::endl;
        }
    }
#line 2112 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 385 "parser.y" /* yacc.c:1646  */
    {
        if(lista->primero== NULL){
            std::cout<<"La lista esta vacia"<<std::endl;
        }
        strcpy(desmontaje->st_unmount.id, (yyvsp[0].TEXT));
        desmontaje->ejecutar_UNMOUNT(lista, desmontaje->st_unmount);
        desmontaje->limpiar_Unmount();
    }
#line 2125 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 395 "parser.y" /* yacc.c:1646  */
    {
        if(formateo->par_id == true){
            formateo->ejecutar_MKFS(lista);
        }else{
            std::cout<<"Error, no se cumple con el parametro ID -> MKFS"<<std::endl;
        }
    }
#line 2137 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 404 "parser.y" /* yacc.c:1646  */
    {
        if(activo->estado !='1'){
            if(entrar->par_id == true && entrar->par_pass == true && entrar->par_user == true ){
                entrar->ejecutar_login(lista , activo);
                if(activo->estado==-1){

                }else{
                   activo = entrar->usuario;
                }
            }else{
                std::cout<<"Error, no se cumplen con los parametros -> LOGIN"<<std::endl;
            }
        }else{
            std::cout<<"Error, ya hay iniciada una sesion"<<std::endl;
        }
    }
#line 2158 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 422 "parser.y" /* yacc.c:1646  */
    {
        if(activo->estado==-1){
            std::cout<<"Error, no hay ninguna sesion iniciada"<<std::endl;
        }else{
            std::cout<<"Sesion terminada"<<std::endl;
            memset(activo->user, 0, 15);
            activo->grupo=-1;
            activo->estado=-1;
            entrar->limpiar();
            memset(activo->user, 0, 15);
            memset(activo->ruta_disco, 0, 50);
            memset(activo->particion, 0, 50);
        }
    }
#line 2177 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 438 "parser.y" /* yacc.c:1646  */
    {
        grupo->tipo = 1;
        strcpy(grupo->nombre, (yyvsp[0].TEXT));
        grupo->ejecutar(activo, lista);
    }
#line 2187 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 445 "parser.y" /* yacc.c:1646  */
    {
        strcpy(elgrupo->nombre, (yyvsp[0].TEXT));
        elgrupo->ejecutar_rmgrp(activo, lista);
        elgrupo->limpar();
    }
#line 2197 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 452 "parser.y" /* yacc.c:1646  */
    {
        if(grupo->par_usr == true && grupo->par_pwd == true && grupo->par_grp == true){
            grupo->tipo=2;
            grupo->ejecutar(activo, lista);
        }else{
            std::cout<<"Error, no se cumplen con los parametros -> MKUSR"<<std::endl;
        }
    }
#line 2210 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 462 "parser.y" /* yacc.c:1646  */
    {
        strcpy(elusuario->nombre, (yyvsp[0].TEXT));
        elusuario->ejecutar_rmusr(activo, lista);
        elusuario->limpar();
    }
#line 2220 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 469 "parser.y" /* yacc.c:1646  */
    {
        if(elusuario1->ruta !="" ){
            elusuario1->ejecutar_CHMOD(lista, activo);
            elusuario1->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> MKFILE"<<std::endl;
        }
    }
#line 2233 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 479 "parser.y" /* yacc.c:1646  */
    {
        if(file->par_ruta == true){
            file->ejecutar_MKFILE(lista, activo);
            file->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> MKFILE"<<std::endl;
        }
    }
#line 2246 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 489 "parser.y" /* yacc.c:1646  */
    {
        strcpy(elimina->ruta, (yyvsp[0].TEXT));
        elimina->ejecutar_REM(lista, activo);
    }
#line 2255 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 495 "parser.y" /* yacc.c:1646  */
    {
        strcpy(mostrar->ruta, (yyvsp[0].TEXT));
        mostrar->ejecutar_cat(lista, activo);
    }
#line 2264 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 501 "parser.y" /* yacc.c:1646  */
    {
        editar->ejecutar_edit(lista, activo);
        editar->limpiar();
    }
#line 2273 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 507 "parser.y" /* yacc.c:1646  */
    {
        modificar->REN(lista, activo);
    }
#line 2281 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 512 "parser.y" /* yacc.c:1646  */
    {
        if(carpeta->par_path ==1){
            carpeta->ejecutar_mkdir(lista, activo);
            carpeta->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> MKDIR"<<std::endl;
        }
    }
#line 2294 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 522 "parser.y" /* yacc.c:1646  */
    {
        if(copiar->par_ruta == true){
            copiar->CP(lista, activo);
            copiar->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> CP"<<std::endl;
        }
    }
#line 2307 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 532 "parser.y" /* yacc.c:1646  */
    {
        if(mover->par_ruta == true){
            mover->MV(lista, activo);
            mover->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> MV"<<std::endl;
        }
    }
#line 2320 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 542 "parser.y" /* yacc.c:1646  */
    {
        if(buscar->par_ruta == true && buscar->par_nombre == true){
            buscar->ejecutar_find(lista, activo);
            buscar->limpiar();
        }
    }
#line 2331 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 550 "parser.y" /* yacc.c:1646  */
    {
        if(cambiar->par_ruta == true){
            cambiar->CHOWN(lista, activo);
            cambiar->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> CHOWN"<<std::endl;
        }
    }
#line 2344 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 560 "parser.y" /* yacc.c:1646  */
    {
        if(cambio->user != ""){
            cambio->CHGRP(lista,activo);
            cambio->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro USR -> CHGRP"<<std::endl;
        }
    }
#line 2357 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 570 "parser.y" /* yacc.c:1646  */
    {
        //Verifica que los parametros obligatorios fueron ingresados
        if(nuevo_reporte.f_nombre ==1 && nuevo_reporte.f_path ==1 && nuevo_reporte.f_id==1){
            // revisar parametro RUTA para los repores file y ls
            if(nuevo_reporte.rep2 == 2 || nuevo_reporte.rep2 == 9){
                if(reporte->z == false){
                    std::cout<<"Error, no se cumple con el parametro RUTA -> REP"<<std::endl;
                }else{
                    reporte->ejecutar_REP(lista,  nuevo_reporte);
                    memset(reporte->ruta_disco, 0, 255);
                    memset(reporte->ruta_reporte, 0, 255);
                    nuevo_reporte.isDisk =0;
                    nuevo_reporte.isMbr =0;
                    nuevo_reporte.f_nombre=0;
                    nuevo_reporte.f_path=0;
                    nuevo_reporte.f_id=0;
                }
            }else{
                reporte->ejecutar_REP(lista,  nuevo_reporte);
                memset(reporte->ruta_disco, 0, 255);
                memset(reporte->ruta_reporte, 0, 255);
                nuevo_reporte.isDisk =0;
                nuevo_reporte.isMbr =0;
                nuevo_reporte.f_nombre=0;
                nuevo_reporte.f_path=0;
                nuevo_reporte.f_id=0;
            }
            reporte->limpiar();
            memset(reporte->ruta_disco, '\0', 255);
            memset(reporte->ruta_reporte, '\0', 255);

            memset(nuevo_reporte.path, '\0', 255);
            memset(nuevo_reporte.ruta, '\0', 255);
            memset(nuevo_reporte.name, '\0', 255);
            memset(nuevo_reporte.id, '\0', 10);

            nuevo_reporte.isDisk =0;
            nuevo_reporte.isMbr =0;
            nuevo_reporte.f_nombre=0;
            nuevo_reporte.f_path=0;
            nuevo_reporte.f_id=0;
            nuevo_reporte.rep2 =0;
        }else{
            std::cout<<"Error, los parametros obligatorios no fueron ingresados -> REP"<<std::endl;
        }
    }
#line 2408 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 618 "parser.y" /* yacc.c:1646  */
    {
        ifstream archivo;
        archivo.open((yyvsp[0].TEXT),ios::in);
        string contenidoLinea;
        while(!archivo.eof()){
            getline(archivo,contenidoLinea);
            char content[1024];
            strcpy(content, contenidoLinea.c_str());
            yy_scan_string(content);
            setSalida(lista, activo);
            yyparse();
        }
        archivo.close();
    }
#line 2427 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 634 "parser.y" /* yacc.c:1646  */
    {
        std::cout<<"Presione cualquier tecla para continuar con la ejecucion del programa"<<std::endl;
        char l;
        cin>>l;
    }
#line 2437 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 640 "parser.y" /* yacc.c:1646  */
    {}
#line 2443 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 643 "parser.y" /* yacc.c:1646  */
    {
            strcpy(nuevo_reporte.path, (yyvsp[-1].TEXT));
            nuevo_reporte.f_nombre = 1;
        }
#line 2452 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 648 "parser.y" /* yacc.c:1646  */
    {
            strcpy(nuevo_reporte.path, (yyvsp[-1].TEXT));
            nuevo_reporte.f_path = 1;
            strcpy(reporte->ruta_reporte, (yyvsp[-1].TEXT));
        }
#line 2462 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 654 "parser.y" /* yacc.c:1646  */
    {
            strcpy(nuevo_reporte.id, (yyvsp[-1].TEXT));
            nuevo_reporte.f_id = 1;
        }
#line 2471 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 659 "parser.y" /* yacc.c:1646  */
    {
            strcpy(reporte->ruta_archivo, (yyvsp[-1].TEXT));
            reporte->par_ra = true;
        }
#line 2480 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 663 "parser.y" /* yacc.c:1646  */
    {}
#line 2486 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 666 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.isMbr = 1;
        }
#line 2494 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 670 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.isDisk = 1;
        }
#line 2502 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 674 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 = 1;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
#line 2512 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 680 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 = 3;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
#line 2522 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 686 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 = 4;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
#line 2532 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 692 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 =5;
            nuevo_reporte.isDisk =0;
            nuevo_reporte.isMbr =0;
         }
#line 2542 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 698 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 = 6;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
#line 2552 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 704 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 = 7;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
#line 2562 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 710 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 = 8;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
#line 2572 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 716 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 = 2;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
#line 2582 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 722 "parser.y" /* yacc.c:1646  */
    {
            nuevo_reporte.rep2 = 9;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
#line 2592 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 729 "parser.y" /* yacc.c:1646  */
    {
            cambio->grupo = (yyvsp[-1].TEXT);
        }
#line 2600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 733 "parser.y" /* yacc.c:1646  */
    {
            cambio->user = (yyvsp[-1].TEXT);
        }
#line 2608 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 736 "parser.y" /* yacc.c:1646  */
    {}
#line 2614 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 739 "parser.y" /* yacc.c:1646  */
    {
            strcpy(cambiar->ruta, (yyvsp[-1].TEXT));
            cambiar->par_ruta = true;
        }
#line 2623 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 744 "parser.y" /* yacc.c:1646  */
    {
            cambiar->user = (yyvsp[-1].TEXT);
        }
#line 2631 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 748 "parser.y" /* yacc.c:1646  */
    {
            cambiar->r=true;
        }
#line 2639 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 751 "parser.y" /* yacc.c:1646  */
    {}
#line 2645 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 754 "parser.y" /* yacc.c:1646  */
    {
            strcpy(buscar->ruta, (yyvsp[-1].TEXT));
            buscar->par_ruta = true;
        }
#line 2654 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 759 "parser.y" /* yacc.c:1646  */
    {
            strcpy(buscar->nombre, (yyvsp[-1].TEXT));
            buscar->par_nombre = true;
        }
#line 2663 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 764 "parser.y" /* yacc.c:1646  */
    {
            strcpy(buscar->nombre, (yyvsp[-1].TEXT));
            buscar->par_nombre = true;
        }
#line 2672 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 768 "parser.y" /* yacc.c:1646  */
    {}
#line 2678 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 771 "parser.y" /* yacc.c:1646  */
    {
            strcpy(mover->ruta, (yyvsp[-1].TEXT));
            mover->par_ruta = true;
        }
#line 2687 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 776 "parser.y" /* yacc.c:1646  */
    {
            mover->dest2 = (yyvsp[-1].TEXT);
        }
#line 2695 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 779 "parser.y" /* yacc.c:1646  */
    {}
#line 2701 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 783 "parser.y" /* yacc.c:1646  */
    {
            strcpy(copiar->ruta, (yyvsp[-1].TEXT));
            copiar->par_ruta = true;
        }
#line 2710 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 788 "parser.y" /* yacc.c:1646  */
    {
            copiar->dest2 = (yyvsp[-1].TEXT);
        }
#line 2718 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 791 "parser.y" /* yacc.c:1646  */
    {}
#line 2724 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 794 "parser.y" /* yacc.c:1646  */
    {
            strcpy(carpeta->ruta_nuevaCarpeta, (yyvsp[-1].TEXT));
            carpeta->par_path = 1;
        }
#line 2733 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 799 "parser.y" /* yacc.c:1646  */
    {
            carpeta->crear =1;
        }
#line 2741 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 802 "parser.y" /* yacc.c:1646  */
    {}
#line 2747 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 805 "parser.y" /* yacc.c:1646  */
    {
            strcpy(modificar->ruta, (yyvsp[-1].TEXT));
        }
#line 2755 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 809 "parser.y" /* yacc.c:1646  */
    {
            strcpy(modificar->nombre, (yyvsp[-1].TEXT));
        }
#line 2763 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 813 "parser.y" /* yacc.c:1646  */
    {
            strcpy(modificar->nombre, (yyvsp[-1].TEXT));
        }
#line 2771 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 816 "parser.y" /* yacc.c:1646  */
    {}
#line 2777 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 819 "parser.y" /* yacc.c:1646  */
    {
            strcpy(editar->ruta, (yyvsp[-1].TEXT));
        }
#line 2785 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 823 "parser.y" /* yacc.c:1646  */
    {
            strcpy(editar->cont, (yyvsp[-1].TEXT));
        }
#line 2793 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 826 "parser.y" /* yacc.c:1646  */
    {}
#line 2799 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 829 "parser.y" /* yacc.c:1646  */
    {
            strcpy(file->ruta_nArchivo, (yyvsp[-1].TEXT));
            file->par_ruta = true;
        }
#line 2808 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 834 "parser.y" /* yacc.c:1646  */
    {
            file->crear = 1;
        }
#line 2816 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 838 "parser.y" /* yacc.c:1646  */
    {
            file->size =  atoi((yyvsp[-1].TEXT));
        }
#line 2824 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 842 "parser.y" /* yacc.c:1646  */
    {
            strcpy(file->cont_ruta,(yyvsp[-1].TEXT));
        }
#line 2832 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 845 "parser.y" /* yacc.c:1646  */
    {}
#line 2838 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 848 "parser.y" /* yacc.c:1646  */
    {
            strcpy(elusuario1->ruta, (yyvsp[-1].TEXT));
        }
#line 2846 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 852 "parser.y" /* yacc.c:1646  */
    {
            elusuario1->ugo = atoi((yyvsp[-1].TEXT));
        }
#line 2854 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 856 "parser.y" /* yacc.c:1646  */
    {
            elusuario1->r = true;
        }
#line 2862 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 859 "parser.y" /* yacc.c:1646  */
    {}
#line 2868 "parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 862 "parser.y" /* yacc.c:1646  */
    {
            strcpy(grupo->nombre, (yyvsp[-1].TEXT));
            grupo->par_usr = true;
        }
#line 2877 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 867 "parser.y" /* yacc.c:1646  */
    {
            strcpy(grupo->password, (yyvsp[-1].TEXT));
            grupo->par_pwd = true;
        }
#line 2886 "parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 872 "parser.y" /* yacc.c:1646  */
    {
            strcpy(grupo->grupo,(yyvsp[-1].TEXT));
            grupo->par_grp = true;
        }
#line 2895 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 876 "parser.y" /* yacc.c:1646  */
    {}
#line 2901 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 879 "parser.y" /* yacc.c:1646  */
    {
            strcpy(entrar->user, (yyvsp[-1].TEXT));
            entrar->par_user = true;
        }
#line 2910 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 884 "parser.y" /* yacc.c:1646  */
    {
            strcpy(entrar->id, (yyvsp[-1].TEXT));
            entrar->par_id = true;
        }
#line 2919 "parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 889 "parser.y" /* yacc.c:1646  */
    {
            strcpy(entrar->pwd, (yyvsp[-1].TEXT));
            entrar->par_pass = true;
        }
#line 2928 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 893 "parser.y" /* yacc.c:1646  */
    {}
#line 2934 "parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 899 "parser.y" /* yacc.c:1646  */
    {
            strcpy(formateo->id, (yyvsp[-1].TEXT));
            formateo->par_id = true;
        }
#line 2943 "parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 904 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            formateo->type=val;
        }
#line 2952 "parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 908 "parser.y" /* yacc.c:1646  */
    {}
#line 2958 "parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 909 "parser.y" /* yacc.c:1646  */
    {}
#line 2964 "parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 912 "parser.y" /* yacc.c:1646  */
    {
            formateo->ext2 = true;
        }
#line 2972 "parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 916 "parser.y" /* yacc.c:1646  */
    {
            formateo->ext3 = true;
        }
#line 2980 "parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 921 "parser.y" /* yacc.c:1646  */
    {
            strcpy(montaje->st_mount.path, (yyvsp[-1].TEXT));
            montaje->p_path = true;
        }
#line 2989 "parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 926 "parser.y" /* yacc.c:1646  */
    {
            strcpy(montaje->st_mount.name, (yyvsp[-1].TEXT));
            montaje->p_name = true;
        }
#line 2998 "parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 930 "parser.y" /* yacc.c:1646  */
    {}
#line 3004 "parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 933 "parser.y" /* yacc.c:1646  */
    {
            int tam=atoi((yyvsp[-1].TEXT));
            administrado->size=tam;
        }
#line 3013 "parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 938 "parser.y" /* yacc.c:1646  */
    {
            int valor = atoi((yyvsp[-1].TEXT));
            administrado->fit =valor;
        }
#line 3022 "parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 943 "parser.y" /* yacc.c:1646  */
    {
            int unidad=atoi((yyvsp[-1].TEXT));
            administrado->unit=unidad;
        }
#line 3031 "parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 948 "parser.y" /* yacc.c:1646  */
    {
            administrado->setRuta((yyvsp[-1].TEXT));
            administrado->par_path=true;
        }
#line 3040 "parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 953 "parser.y" /* yacc.c:1646  */
    {
            int valor=atoi((yyvsp[-1].TEXT));
            administrado->type=valor;
        }
#line 3049 "parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 958 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            administrado->borrar=val;
        }
#line 3058 "parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 963 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            administrado->add=1;
            administrado->size_add=val;
        }
#line 3068 "parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 969 "parser.y" /* yacc.c:1646  */
    {
            administrado->setName((yyvsp[-1].TEXT));
            administrado->par_nombre = true;
        }
#line 3077 "parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 973 "parser.y" /* yacc.c:1646  */
    {}
#line 3083 "parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 976 "parser.y" /* yacc.c:1646  */
    {
            int s = strlen((yyvsp[0].TEXT));
            char nombre [s];
            int j=0;
            memset(nombre,'\0',s+1);
            for(int i=0;i<s;i++){
                if((yyvsp[0].TEXT)[i]=='\"'){

                }else{
                    nombre[j] = (yyvsp[0].TEXT)[i];
                    j++;
                }
            }
            memcpy((yyval.TEXT), nombre, strlen(nombre)+1);
        }
#line 3103 "parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 992 "parser.y" /* yacc.c:1646  */
    {
            int s = strlen((yyvsp[0].TEXT));
            char nombre [s];
            int j=0;
            memset(nombre,'\0',s+1);
            for(int i=0;i<s;i++){
                if((yyvsp[0].TEXT)[i]=='\"'){

                }else{
                    nombre[j] = (yyvsp[0].TEXT)[i];
                    j++;
                }
            }
            memcpy((yyval.TEXT), nombre, strlen(nombre)+1);
        }
#line 3123 "parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 1009 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 3131 "parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 1013 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 3139 "parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 1017 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 3147 "parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 1022 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 3155 "parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 1026 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 3163 "parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 1030 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 3171 "parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 1035 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 3179 "parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 1039 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 3187 "parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 1043 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 3195 "parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 1048 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 3203 "parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 1052 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 3211 "parser.cpp" /* yacc.c:1646  */
    break;


#line 3215 "parser.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
