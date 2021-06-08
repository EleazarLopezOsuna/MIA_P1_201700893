/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 87 "parser.y" /* yacc.c:1909  */

//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
//QString TEXT;



#line 169 "parser.h" /* yacc.c:1909  */
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
