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
#include "FDISK.h"
#include "MOUNT.h"
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
FDISK *administrado=new FDISK();
MOUNT * montaje = new MOUNT(1);
MOUNT * desmontaje = new MOUNT(2);
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
lista::list *listx;
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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   96

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

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
       0,   236,   236,   237,   238,   239,   240,   241,   265,   272,
     281,   286,   291,   296,   298,   302,   306,   311,   315,   320,
     324,   328,   344,   352,   354,   377,   382,   387,   392,   397,
     402,   407,   413,   418,   420,   436,   453,   457,   461,   466,
     470,   474,   479,   483,   487,   492,   496,   501,   511,   516,
     521,   523
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
  "RMDISK", "COMENTS", "FDISK", "COMANDOFDISK", "NAME", "AJUSTE2",
  "UNIDADES2", "TIPO_PARTICION", "TIPO_BORRADO", "MOUNT", "COMANDOMOUNT",
  "UNMOUNT", YY_NULLPTR
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

#define YYPACT_NINF -85

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-85)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       7,   -85,   -84,   -74,   -72,   -57,   -34,    63,   -85,   -85,
     -85,   -85,   -85,   -85,    30,   -85,    51,    20,   -85,    -7,
     -85,    42,   -85,   -25,   -24,   -23,   -22,   -21,   -20,   -19,
     -18,   -17,   -16,   -15,   -14,   -13,   -12,   -10,    -9,    -8,
      -6,    34,   -70,   -70,    -5,    45,    46,   -70,   -11,    21,
     -38,    -4,   -70,    -3,    -2,   -84,   -85,   -85,   -85,   -84,
     -85,   -85,   -84,   -85,   -85,   -85,   -84,   -85,   -72,   -85,
     -85,   -85,   -72,   -85,   -85,   -85,   -72,   -72,   -85,   -85,
     -85,   -72,   -85,   -85,   -72,   -85,   -85,   -72,   -72,   -57,
     -57,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   -85
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    23,    13,     0,    33,    50,     0,     0,     2,     3,
       4,     5,     6,     7,     0,     8,     0,     0,    24,     0,
      47,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,    14,    15,    16,    13,
      17,    18,    13,    21,    19,    20,    13,    22,    33,    36,
      37,    38,    33,    39,    40,    41,    33,    33,    42,    43,
      44,    33,    45,    46,    33,    34,    35,    33,    33,    50,
      50,    51,     9,    10,    11,    12,    25,    26,    27,    28,
      29,    30,    32,    31,    48,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -85,   -85,   -85,   -48,   -85,   -85,    -1,   -85,   -85,   -85,
     -68,   -85,   -85,   -85,   -85,   -85,   -85,   -28,   -85
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,    15,    59,    62,    66,     9,    10,    11,
      18,    87,    72,    76,    81,    84,    12,    20,    13
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      96,    56,    57,    58,    97,    14,    36,    92,    98,    99,
       1,    93,    37,   100,    94,    16,   101,    17,    95,   102,
     103,     2,     3,     4,    28,    29,    30,    63,     5,     6,
      64,    65,    19,    31,    23,    24,    25,    32,    33,    34,
      35,    78,    67,    26,    60,    61,    77,    82,    83,    79,
      80,    89,    69,    70,    71,    21,    73,    74,    75,    85,
      86,   104,   105,    22,    27,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
       0,    53,    54,     0,     0,     0,     0,    55,     0,     0,
      68,    88,     0,     0,     0,    90,    91
};

static const yytype_int8 yycheck[] =
{
      68,     7,     8,     9,    72,    89,    13,    55,    76,    77,
       3,    59,    19,    81,    62,    89,    84,    89,    66,    87,
      88,    14,    15,    16,     4,     5,     6,    97,    21,    22,
     100,   101,    89,    13,     4,     5,     6,    17,    18,    19,
      20,    52,    43,    13,    10,    11,    47,    26,    27,    60,
      61,    52,     7,     8,     9,    89,    10,    11,    12,    97,
      98,    89,    90,     0,    13,    23,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      -1,    91,    91,    -1,    -1,    -1,    -1,    95,    -1,    -1,
      95,    95,    -1,    -1,    -1,    98,    98
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    14,    15,    16,    21,    22,   108,   109,   114,
     115,   116,   123,   125,    89,   110,    89,    89,   117,    89,
     124,    89,     0,     4,     5,     6,    13,    13,     4,     5,
       6,    13,    17,    18,    19,    20,    13,    19,    23,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    95,     7,     8,     9,   111,
      10,    11,   112,    97,   100,   101,   113,   113,    95,     7,
       8,     9,   119,    10,    11,    12,   120,   113,    52,    60,
      61,   121,    26,    27,   122,    97,    98,   118,    95,   113,
      98,    98,   110,   110,   110,   110,   117,   117,   117,   117,
     117,   117,   117,   117,   124,   124
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   108,   108,   108,   108,   108,   109,   110,
     110,   110,   110,   110,   111,   111,   111,   112,   112,   113,
     113,   113,   114,   115,   116,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   118,   118,   119,   119,   119,   120,
     120,   120,   121,   121,   121,   122,   122,   123,   124,   124,
     124,   125
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     2,     5,
       5,     5,     5,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     1,     2,     5,     5,     5,     5,     5,
       5,     5,     5,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     5,     5,
       0,     5
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
#line 236 "parser.y" /* yacc.c:1646  */
    { }
#line 1598 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 237 "parser.y" /* yacc.c:1646  */
    {}
#line 1604 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 238 "parser.y" /* yacc.c:1646  */
    {}
#line 1610 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 239 "parser.y" /* yacc.c:1646  */
    {}
#line 1616 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 240 "parser.y" /* yacc.c:1646  */
    {}
#line 1622 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 241 "parser.y" /* yacc.c:1646  */
    {}
#line 1628 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 266 "parser.y" /* yacc.c:1646  */
    {
        disco->ejecutar();
        disco->limpiar();
        disco = new MKDISK();
    }
#line 1638 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 273 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            if(val>0){
                disco->setSize(val);
            }else{
                std::cout<<"Error, debe ingresar un numero mayor a 0"<<std::endl;
            }
        }
#line 1651 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 282 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            disco->f = val;
        }
#line 1660 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 287 "parser.y" /* yacc.c:1646  */
    {
            int tam = atoi((yyvsp[-1].TEXT));
            disco->u = tam;
        }
#line 1669 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 292 "parser.y" /* yacc.c:1646  */
    {
            memset(disco->ruta, 0, 255);
            disco->setRuta((yyvsp[-1].TEXT));
        }
#line 1678 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 296 "parser.y" /* yacc.c:1646  */
    {}
#line 1684 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 299 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 1692 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 303 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 1700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 307 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 1708 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 312 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 1716 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 316 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 1724 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 321 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), (yyvsp[0].TEXT), strlen((yyvsp[0].TEXT)) + 1);
        }
#line 1732 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 325 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), (yyvsp[0].TEXT), strlen((yyvsp[0].TEXT)) + 1);
        }
#line 1740 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 329 "parser.y" /* yacc.c:1646  */
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
#line 1759 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 345 "parser.y" /* yacc.c:1646  */
    {
        RMDISK* eliminar=new RMDISK();
        eliminar->setRuta((yyvsp[0].TEXT));
        eliminar->ejecutar();
        eliminar->limpiar();
    }
#line 1770 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 352 "parser.y" /* yacc.c:1646  */
    {}
#line 1776 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 355 "parser.y" /* yacc.c:1646  */
    {
        if(administrado->f_nombre == true && administrado->f_path){
            //hay que verificar que tipo de operacion de fdisk es
            if(administrado->borrar !=0 && administrado->add == 0 && administrado->size ==NULL){
                administrado->operacion=1;
                administrado->ejecutar(listx);
                administrado->limpiar();
            }else if(administrado->add == 1 && administrado->borrar== 0 && administrado->size == NULL){
                administrado->operacion=2;
                administrado->ejecutar(listx);
                administrado->limpiar();
            }else if(administrado->size != NULL && administrado->add == 0 && administrado->borrar==0){
                administrado->operacion=0;
                administrado->ejecutar(listx);
                administrado->limpiar();
            }
            administrado->limpiar();
        }else{
            std::cout<<"Error, no se cumplen con los parametros -> FDISK"<<endl;
        }
    }
#line 1802 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 378 "parser.y" /* yacc.c:1646  */
    {
            int tam=atoi((yyvsp[-1].TEXT));
            administrado->size=tam;
        }
#line 1811 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 383 "parser.y" /* yacc.c:1646  */
    {
            int valor = atoi((yyvsp[-1].TEXT));
            administrado->fit =valor;
        }
#line 1820 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 388 "parser.y" /* yacc.c:1646  */
    {
            int unidad=atoi((yyvsp[-1].TEXT));
            administrado->unit=unidad;
        }
#line 1829 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 393 "parser.y" /* yacc.c:1646  */
    {
            administrado->setRuta((yyvsp[-1].TEXT));
            administrado->f_path=true;
        }
#line 1838 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 398 "parser.y" /* yacc.c:1646  */
    {
            int valor=atoi((yyvsp[-1].TEXT));
            administrado->type=valor;
        }
#line 1847 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 403 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            administrado->borrar=val;
        }
#line 1856 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 408 "parser.y" /* yacc.c:1646  */
    {
            int val = atoi((yyvsp[-1].TEXT));
            administrado->add=1;
            administrado->size_add=val;
        }
#line 1866 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 414 "parser.y" /* yacc.c:1646  */
    {
            administrado->setName((yyvsp[-1].TEXT));
            administrado->f_nombre = true;
        }
#line 1875 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 418 "parser.y" /* yacc.c:1646  */
    {}
#line 1881 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 421 "parser.y" /* yacc.c:1646  */
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
#line 1901 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 437 "parser.y" /* yacc.c:1646  */
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
#line 1921 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 454 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 1929 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 458 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 1937 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 462 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 1945 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 467 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 1953 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 471 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 1961 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 475 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 1969 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 480 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "0", 1);
        }
#line 1977 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 484 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 1985 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 488 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 1993 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 493 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "1", 1);
        }
#line 2001 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 497 "parser.y" /* yacc.c:1646  */
    {
            memcpy((yyval.TEXT), "2", 1);
        }
#line 2009 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 502 "parser.y" /* yacc.c:1646  */
    {
        if(montaje->f_name == true && montaje->f_path == true){
            montaje->ejecutarM(montaje->obj_mount, listx);
            montaje->limpiar_m();
        }else{
            std::cout<<"Error, no se cumplen con los parametros -> MOUNT"<<std::endl;
        }
    }
#line 2022 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 512 "parser.y" /* yacc.c:1646  */
    {
            strcpy(montaje->obj_mount.path, (yyvsp[-1].TEXT));
            montaje->f_path = true;
        }
#line 2031 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 517 "parser.y" /* yacc.c:1646  */
    {
            strcpy(montaje->obj_mount.name, (yyvsp[-1].TEXT));
            montaje->f_name = true;
        }
#line 2040 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 521 "parser.y" /* yacc.c:1646  */
    {}
#line 2046 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 524 "parser.y" /* yacc.c:1646  */
    {
        if(listx == NULL){
            std::cout<<"La lista esta vacia"<<std::endl;
        }
        strcpy(desmontaje->obj_unmount.id, (yyvsp[0].TEXT));
        desmontaje->ejecutarU(listx, desmontaje->obj_unmount);
        desmontaje->limpiar_u();
    }
#line 2059 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2063 "parser.cpp" /* yacc.c:1646  */
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
