%option case-insensitive
%option yylineno

%{
#include <iostream>
#include <QString>
#include "parser.h"
#include <string>
#include <QList>

int yylex();
void yyerror(const char *s);
int linea = 0;
int columna = 1;
int anterior = 0;
%}

%option noyywrap
%option nounput

entero [0-9]+
letra [a-zA-ZÑñáéíóúÁÉÍÓÚ]+
identificador ({letra}|{entero})({letra}|{entero}|"_")*
comentarios [#]+.*
caracter "\'"("\\")?({letra}|{entero})"\'"
cadena [\"][^\"\n]*[\"\n]
ru "/"{identificador}
ruta {ru}+"."{identificador}
ruta_carpeta {ru}+
path ^(\/[^\/ ]*)+\/?$
name2 {identificador}"."{identificador}

%x COM

%%
"SIZE" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return psize;}
"MKDISK" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkdisk;}
"F" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pf;}
"U" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pu;}
"PATH" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return ppath;}
"RMDISK" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prmdisk;}
"BF" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pbf;}
"FF" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pff;}
"WF" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pwf;}
"K" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pk;}
"M" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pm;}
"B" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pb;}
"FDISK" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pfdisk;}
"type" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return ptype;}
"delete" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pdelete;}
"name" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pname;}
"add" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return padd;}
"mount" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmount;}
"unmount" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return punmount;}
"id" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pid;}
"MKFS" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkfs;}
"fs" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pfs;}
"fast" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pfast;}
"full" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pfull;}
"2fs" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return p2fs;}
"3fs" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return p3fs;}
"login" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return plogin;}
"logout" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return plogout;}
"mkgrp" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkgrp;}
"rmgrp" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prmgrp;}
"mkusr" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkusr;}
"usr" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pusr;}
"pwd" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pwd;}
"grp" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pgrp;}
"rmusr" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prmusr;}
"chmod" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pchmod;}
"ugo" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pugo;}
"r" {columna=columna+ anterior;  anterior = strlen (yytext);strcpy(yylval.TEXT, yytext);return pr;}
"mkfile" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkfile;}
"cont" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pcont;}
"cat" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pcat;}
"file" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pfilen;}
"rem" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prem;}
"edit" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pedit;}
"ren" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pren;}
"mkdir" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmkdir;}
"p" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pp;}
"cp" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pcp;}
"dest" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pdest;}
"mv" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmv;}
"find" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pfind;}
"chown" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pchown;}
"chgrp" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pchgrp;}
"pause" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return ppause;}
"e" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pe;}
"l" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pl;}
"rep" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return prep;}
"ruta" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pruta;}
"mbr" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pmbr;}
"disk" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pdisk;}
"inode" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pinode;}
"journaling" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pjournaling;}
"block" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pblock;}
"bm_inode" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pbm_inode;}
"bm_block" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pbm_block;}
"tree" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return ptree;}
"sb" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return psb;}
"ls" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pls;}
"exec" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return pexec;}

{entero} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return entero;}
{cadena} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cadena;}
{identificador} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return identificador;}
{caracter} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return caracter;}
{ruta} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ruta;}
{ruta_carpeta} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ruta_carpeta;}
{name2} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return name2;}
{comentarios} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return coment;}

"." {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return punto;}
"<" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return bracketabre;}
">" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return bracketcierra;}
"[" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return corcheteabre;}
"]" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return corchetecierra;}
";" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return puntocoma;}
"^" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return potencia;}
"," {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return coma;}
"(" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return parentesisabre;}
")" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return parentesiscierra;}
"{" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return llaveabre;}
"}" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return llavecierra;}
"+" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return mas;}
"-" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return menos;}
"*" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return multiplicacion;}
"=" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return igual;}
"$" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return dolar;}
":" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return dospuntos;}

"\n" {linea++; columna=0; anterior=0;}
[[:blank:]] { columna++; }

.   {
    std::cout<<"Error Lexico: "<<linea<<"\n";
}
