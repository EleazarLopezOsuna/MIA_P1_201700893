%{
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
%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output "parser.cpp"
%define parse.error verbose
%locations
%union{
//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
//QString TEXT;


}

//TERMINALES DE TIPO TEXT, SON STRINGS
%token<TEXT> coment;
%token<TEXT> psize;
%token<TEXT> pf;
%token<TEXT> pu;
%token<TEXT> pbf;
%token<TEXT> pff;
%token<TEXT> pwf;
%token<TEXT> pk;
%token<TEXT> pm;
%token<TEXT> pb;
%token<TEXT> ppath;
%token<TEXT> pmkdisk;
%token<TEXT> prmdisk;
%token<TEXT> pfdisk;
%token<TEXT> ptype;
%token<TEXT> pdelete;
%token<TEXT> pname;
%token<TEXT> padd;
%token<TEXT> pmount;
%token<TEXT> punmount;
%token<TEXT> pid;
%token<TEXT> pmkfs;
%token<TEXT> pfs;
%token<TEXT> pfast;
%token<TEXT> pfull;
%token<TEXT> p2fs;
%token<TEXT> p3fs;
%token<TEXT> plogin;
%token<TEXT> pusuario;
%token<TEXT> ppassword;
%token<TEXT> plogout;
%token<TEXT> pmkgrp;
%token<TEXT> prmgrp;
%token<TEXT> pmkusr;
%token<TEXT> pusr;
%token<TEXT> pwd;
%token<TEXT> pgrp;
%token<TEXT> prmusr;
%token<TEXT> pchmod;
%token<TEXT> pugo;
%token<TEXT> pr;
%token<TEXT> pmkfile;
%token<TEXT> pcont;
%token<TEXT> pcat;
%token<TEXT> pfilen;
%token<TEXT> prem;
%token<TEXT> pedit;
%token<TEXT> pren;
%token<TEXT> pmkdir;
%token<TEXT> pp;
%token<TEXT> pcp;
%token<TEXT> pdest;
%token<TEXT> pmv;
%token<TEXT> pfind;
%token<TEXT> pchown;
%token<TEXT> pchgrp;
%token<TEXT> ppause;
%token<TEXT> pe;
%token<TEXT> pl;
%token<TEXT> name2;
%token<TEXT> prep;
%token<TEXT> pruta;
%token<TEXT> pmbr;
%token<TEXT> pdisk;
%token<TEXT> pinode;
%token<TEXT> pjournaling;
%token<TEXT> pblock;
%token<TEXT> pbm_inode;
%token<TEXT> pbm_block;
%token<TEXT> ptree;
%token<TEXT> psb;
%token<TEXT> pexec;
%token<TEXT> pls;
%token<TEXT> punto;
%token<TEXT> bracketabre;
%token<TEXT> bracketcierra;
%token<TEXT> corcheteabre;
%token<TEXT> corchetecierra;
%token<TEXT> puntocoma;
%token<TEXT> potencia;
%token<TEXT> coma;
%token<TEXT> parentesisabre;
%token<TEXT> parentesiscierra;
%token<TEXT> llaveabre;
%token<TEXT> llavecierra;
%token<TEXT> mas;
%token<TEXT> menos;
%token<TEXT> multiplicacion;
%token<TEXT> igual;
%token<TEXT> dolar;
%token<TEXT> dospuntos;
%token<TEXT> path;
%token<TEXT> entero;
%token<TEXT> numnegatinamevo;
%token<TEXT> cadena;
%token<TEXT> identificador;
%token<TEXT> caracter;
%token<TEXT> ruta;
%token<TEXT> ruta_carpeta;
%token<TEXT> pass;
%token<TEXT> rutacualquiera;
//%type<TEXT> PAUSE;
//%type<TEXT> COMANDOCHGRP;
//%type<TEXT> COMANDOREP;
//%type<TEXT> REPORTES;
//%type<TEXT> COMANDOCHMOD;
//%type<TEXT> RMUSR;
//%type<TEXT> RMGRP;
//%type<TEXT> COMANDOMKUSR;
//%type<TEXT> MKGRP;
//%type<TEXT> COMANDOLOGIN;
//%type<TEXT> COMANDOMKFS;
//%type<TEXT> SISTEMA_FORMATEO;
%type<TEXT> COMANDOMKDISK; // lista de instrucciones
//%type<TEXT>COMANDOCHOWN;
//%type<TEXT>COMANDOMV;
//%type<busca>COMANDOFIND;
//%type<TEXT>COMANDOCP;
//%type<TEXT>COMANDOMKDIR;
//%type<TEXT>COMANDOREN;
//%type<TEXT>COMANDOEDIT;
//%type<TEXT>PASS;
//%type<TEXT>COMANDOMKFILE;
%type<TEXT>COMANDOFDISK;
%type<TEXT>COMANDOMOUNT;
%type<TEXT>RUTA_CADENA;
%type<TEXT>AJUSTE1;
%type<TEXT>AJUSTE2;
%type<TEXT>TIPO_PARTICION;
%type<TEXT>TIPO_BORRADO;
%type<TEXT>NAME;
%type<TEXT>UNIDADES1;
%type<TEXT>UNIDADES2;
//%type<TEXT>NAME_REPS;
%type<TEXT>COMENTS;
%left suma menos
%left multi division
%left potencia
%start INICIO
%%
INICIO : MKDISK { }
    | RMDISK{}
    | COMENTS{}
    | FDISK{}
    | MOUNT{}
    | UNMOUNT{}
    /*| MKFS{}
    | LOGIN{}
    | LOGOUT{}
    | MKGRP{}
    | RMGRP{}
    | MKUSR{}
    | RMUSR{}
    | CHMOD{}
    | MKFILE{}
    | REM{}
    | CAT{}
    | EDIT{}
    | REN{}
    | MKDIR{}
    | CP{}
    | MV{}
    | FIND{}
    | CHOWN{}
    | CHGRP{}
    | REPORTES{}
    | EXEC{}
    | PAUSE{}*/
;
MKDISK:  pmkdisk COMANDOMKDISK
    {
        disco->ejecutar();
        disco->limpiar();
        disco = new MKDISK();
    }
;
COMANDOMKDISK: menos psize igual entero COMANDOMKDISK
        {
            int val = atoi($4);
            if(val>0){
                disco->setSize(val);
            }else{
                std::cout<<"Error, debe ingresar un numero mayor a 0"<<std::endl;
            }
        }
    | menos pf igual AJUSTE1 COMANDOMKDISK
        {
            int val = atoi($4);
            disco->f = val;
        }
    | menos pu igual UNIDADES1 COMANDOMKDISK
        {
            int tam = atoi($4);
            disco->u = tam;
        }
    | menos ppath igual RUTA_CADENA COMANDOMKDISK
        {
            memset(disco->ruta, 0, 255);
            disco->setRuta($4);
        }
    | {}
;
AJUSTE1: pbf
        {
            memcpy($$, "0", 1);
        }
    | pff
        {
            memcpy($$, "1", 1);
        }
    | pwf
        {
            memcpy($$, "2", 1);
        }
;
UNIDADES1: pk
        {
            memcpy($$, "0", 1);
        }
    | pm
        {
            memcpy($$, "1", 1);
        }
;
RUTA_CADENA: ruta
        {
            memcpy($$, $1, strlen($1) + 1);
        }
    | ruta_carpeta
        {
            memcpy($$, $1, strlen($1) + 1);
        }
    | cadena
        {
            char ruta [255];
            int s=strlen($1);
            int j=0;
            for(int i=0;i<255;i++){
                if($1[i]=='\"'){

                }else{
                    ruta[j] = $1[i];
                    j++;
                }
            }
            memcpy($$, ruta, strlen(ruta)+1);
        }
;
RMDISK:  prmdisk menos ppath igual RUTA_CADENA
    {
        RMDISK* eliminar=new RMDISK();
        eliminar->setRuta($5);
        eliminar->ejecutar();
        eliminar->limpiar();
    }
;
COMENTS: coment{}
;
FDISK:  pfdisk COMANDOFDISK
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
;
COMANDOFDISK: menos psize igual entero COMANDOFDISK
        {
            int tam=atoi($4);
            administrado->size=tam;
        }
    | menos pf igual AJUSTE2 COMANDOFDISK
        {
            int valor = atoi($4);
            administrado->fit =valor;
        }
    | menos pu igual UNIDADES2 COMANDOFDISK
        {
            int unidad=atoi($4);
            administrado->unit=unidad;
        }
    | menos ppath igual RUTA_CADENA COMANDOFDISK
        {
            administrado->setRuta($4);
            administrado->f_path=true;
        }
    | menos ptype igual TIPO_PARTICION COMANDOFDISK
        {
            int valor=atoi($4);
            administrado->type=valor;
        }
    | menos pdelete igual TIPO_BORRADO COMANDOFDISK
        {
            int val = atoi($4);
            administrado->borrar=val;
        }
    | menos padd igual entero COMANDOFDISK
        {
            int val = atoi($4);
            administrado->add=1;
            administrado->size_add=val;
        }
    | menos pname igual NAME COMANDOFDISK
        {
            administrado->setName($4);
            administrado->f_nombre = true;
        }
    | {}
;
NAME : cadena
        {
            int s = strlen($1);
            char nombre [s];
            int j=0;
            memset(nombre,'\0',s+1);
            for(int i=0;i<s;i++){
                if($1[i]=='\"'){

                }else{
                    nombre[j] = $1[i];
                    j++;
                }
            }
            memcpy($$, nombre, strlen(nombre)+1);
        }
    | identificador
        {
            int s = strlen($1);
            char nombre [s];
            int j=0;
            memset(nombre,'\0',s+1);
            for(int i=0;i<s;i++){
                if($1[i]=='\"'){

                }else{
                    nombre[j] = $1[i];
                    j++;
                }
            }
            memcpy($$, nombre, strlen(nombre)+1);
        }
;
AJUSTE2: pbf
        {
            memcpy($$, "0", 1);
        }
    |   pff
        {
            memcpy($$, "1", 1);
        }
    |   pwf
        {
            memcpy($$, "2", 1);
        }
;
UNIDADES2: pk
        {
            memcpy($$, "1", 1);
        }
    | pm
        {
            memcpy($$, "2", 1);
        }
    | pb
        {
            memcpy($$, "0", 1);
        }
;
TIPO_PARTICION: pp
        {
            memcpy($$, "0", 1);
        }
    | pe
        {
            memcpy($$, "1", 1);
        }
    | pl
        {
            memcpy($$, "2", 1);
        }
;
TIPO_BORRADO: pfast
        {
            memcpy($$, "1", 1);
        }
    | pfull
        {
            memcpy($$, "2", 1);
        }
;
MOUNT: pmount COMANDOMOUNT
    {
        if(montaje->f_name == true && montaje->f_path == true){
            montaje->ejecutarM(montaje->obj_mount, listx);
            montaje->limpiar_m();
        }else{
            std::cout<<"Error, no se cumplen con los parametros -> MOUNT"<<std::endl;
        }
    }
;
COMANDOMOUNT: menos ppath igual RUTA_CADENA COMANDOMOUNT
        {
            strcpy(montaje->obj_mount.path, $4);
            montaje->f_path = true;
        }
    | menos pname igual identificador COMANDOMOUNT
        {
            strcpy(montaje->obj_mount.name, $4);
            montaje->f_name = true;
        }
    | {}
;
UNMOUNT: punmount menos pid igual identificador
    {
        if(listx == NULL){
            std::cout<<"La lista esta vacia"<<std::endl;
        }
        strcpy(desmontaje->obj_unmount.id, $5);
        desmontaje->ejecutarU(listx, desmontaje->obj_unmount);
        desmontaje->limpiar_u();
    }
;
/*MKFS: pmkfs COMANDOMKFS
    {
        if(formateo->par_id == true){
            formateo->ejecutar_MKFS(lista);
        }else{
            std::cout<<"Error, no se cumple con el parametro ID -> MKFS"<<std::endl;
        }
    }
;
LOGIN:  plogin COMANDOLOGIN
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
;
LOGOUT: plogout
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
;
MKGRP: pmkgrp menos pname igual NAME
    {
        grupo->tipo = 1;
        strcpy(grupo->nombre, $5);
        grupo->ejecutar(activo, lista);
    }
;
RMGRP: prmgrp menos pname igual NAME
    {
        strcpy(elgrupo->nombre, $5);
        elgrupo->ejecutar_rmgrp(activo, lista);
        elgrupo->limpar();
    }
;
MKUSR: pmkusr COMANDOMKUSR
    {
        if(grupo->par_usr == true && grupo->par_pwd == true && grupo->par_grp == true){
            grupo->tipo=2;
            grupo->ejecutar(activo, lista);
        }else{
            std::cout<<"Error, no se cumplen con los parametros -> MKUSR"<<std::endl;
        }
    }
;
RMUSR: prmusr menos pusr igual NAME
    {
        strcpy(elusuario->nombre, $5);
        elusuario->ejecutar_rmusr(activo, lista);
        elusuario->limpar();
    }
;
CHMOD: pchmod COMANDOCHMOD
    {
        if(elusuario1->ruta !="" ){
            elusuario1->ejecutar_CHMOD(lista, activo);
            elusuario1->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> MKFILE"<<std::endl;
        }
    }
;
MKFILE: pmkfile COMANDOMKFILE
    {
        if(file->par_ruta == true){
            file->ejecutar_MKFILE(lista, activo);
            file->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> MKFILE"<<std::endl;
        }
    }
;
REM: prem menos ppath igual RUTA_CADENA
    {
        strcpy(elimina->ruta, $5);
        elimina->ejecutar_REM(lista, activo);
    }
;
CAT: pcat menos pfilen igual RUTA_CADENA
    {
        strcpy(mostrar->ruta, $5);
        mostrar->ejecutar_cat(lista, activo);
    }
;
EDIT: pedit COMANDOEDIT
    {
        editar->ejecutar_edit(lista, activo);
        editar->limpiar();
    }
;
REN: pren COMANDOREN
    {
        modificar->REN(lista, activo);
    }
;
MKDIR: pmkdir COMANDOMKDIR
    {
        if(carpeta->par_path ==1){
            carpeta->ejecutar_mkdir(lista, activo);
            carpeta->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> MKDIR"<<std::endl;
        }
    }
;
CP: pcp COMANDOCP
    {
        if(copiar->par_ruta == true){
            copiar->CP(lista, activo);
            copiar->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> CP"<<std::endl;
        }
    }
;
MV: pmv COMANDOMV
    {
        if(mover->par_ruta == true){
            mover->MV(lista, activo);
            mover->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> MV"<<std::endl;
        }
    }
;
FIND: pfind COMANDOFIND
    {
        if(buscar->par_ruta == true && buscar->par_nombre == true){
            buscar->ejecutar_find(lista, activo);
            buscar->limpiar();
        }
    }
;
CHOWN: pchown COMANDOCHOWN
    {
        if(cambiar->par_ruta == true){
            cambiar->CHOWN(lista, activo);
            cambiar->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro PATH -> CHOWN"<<std::endl;
        }
    }
;
CHGRP: pchgrp COMANDOCHGRP
    {
        if(cambio->user != ""){
            cambio->CHGRP(lista,activo);
            cambio->limpiar();
        }else{
            std::cout<<"Error, no se cumple con el parametro USR -> CHGRP"<<std::endl;
        }
    }
;
REPORTES:   prep COMANDOREP
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
;
EXEC: pexec menos ppath igual RUTA_CADENA
    {
        ifstream archivo;
        archivo.open($5,ios::in);
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
;
PAUSE: ppause
    {
        std::cout<<"Presione cualquier tecla para continuar con la ejecucion del programa"<<std::endl;
        char l;
        cin>>l;
    }
;
COMANDOREP: menos pname igual NAME_REPS COMANDOREP
        {
            strcpy(nuevo_reporte.path, $4);
            nuevo_reporte.f_nombre = 1;
        }
    | menos ppath igual RUTA_CADENA COMANDOREP
        {
            strcpy(nuevo_reporte.path, $4);
            nuevo_reporte.f_path = 1;
            strcpy(reporte->ruta_reporte, $4);
        }
    | menos pid igual identificador COMANDOREP
        {
            strcpy(nuevo_reporte.id, $4);
            nuevo_reporte.f_id = 1;
        }
    | menos pruta igual RUTA_CADENA COMANDOREP
        {
            strcpy(reporte->ruta_archivo, $4);
            reporte->par_ra = true;
        }
    | {}
;
NAME_REPS : pmbr
        {
            nuevo_reporte.isMbr = 1;
        }
    | pdisk
        {
            nuevo_reporte.isDisk = 1;
        }
    | psb
        {
            nuevo_reporte.rep2 = 1;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
    | pbm_inode
        {
            nuevo_reporte.rep2 = 3;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
    | pbm_block
        {
            nuevo_reporte.rep2 = 4;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
    | pinode
        {
            nuevo_reporte.rep2 =5;
            nuevo_reporte.isDisk =0;
            nuevo_reporte.isMbr =0;
         }
    | ptree
        {
            nuevo_reporte.rep2 = 6;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
    | pblock
        {
            nuevo_reporte.rep2 = 7;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
    | pjournaling
        {
            nuevo_reporte.rep2 = 8;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
    | pfilen
        {
            nuevo_reporte.rep2 = 2;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
    | pls
        {
            nuevo_reporte.rep2 = 9;
            nuevo_reporte.isDisk = 0;
            nuevo_reporte.isMbr = 0;
        }
;
COMANDOCHGRP: menos pgrp igual NAME COMANDOCHGRP
        {
            cambio->grupo = $4;
        }
    | menos pusr igual NAME COMANDOCHGRP
        {
            cambio->user = $4;
        }
    | {}
;
COMANDOCHOWN: menos ppath igual RUTA_CADENA COMANDOCHOWN
        {
            strcpy(cambiar->ruta, $4);
            cambiar->par_ruta = true;
        }
    | menos pusr igual NAME COMANDOCHOWN
        {
            cambiar->user = $4;
        }
    | menos pr COMANDOCHOWN
        {
            cambiar->r=true;
        }
    | {}
;
COMANDOFIND: menos ppath igual RUTA_CADENA COMANDOFIND
        {
            strcpy(buscar->ruta, $4);
            buscar->par_ruta = true;
        }
    | menos pname igual identificador COMANDOFIND
        {
            strcpy(buscar->nombre, $4);
            buscar->par_nombre = true;
        }
    | menos pname igual name2 COMANDOFIND
        {
            strcpy(buscar->nombre, $4);
            buscar->par_nombre = true;
        }
    | {}
;
COMANDOMV: menos ppath igual RUTA_CADENA COMANDOMV
        {
            strcpy(mover->ruta, $4);
            mover->par_ruta = true;
        }
    | menos pdest igual RUTA_CADENA COMANDOMV
        {
            mover->dest2 = $4;
        }
    | {}
;

COMANDOCP: menos ppath igual RUTA_CADENA COMANDOCP
        {
            strcpy(copiar->ruta, $4);
            copiar->par_ruta = true;
        }
    | menos pdest igual RUTA_CADENA COMANDOCP
        {
            copiar->dest2 = $4;
        }
    | {}
;
COMANDOMKDIR: menos ppath igual RUTA_CADENA COMANDOMKDIR
        {
            strcpy(carpeta->ruta_nuevaCarpeta, $4);
            carpeta->par_path = 1;
        }
    | menos pp COMANDOMKDIR
        {
            carpeta->crear =1;
        }
    | {}
;
COMANDOREN: menos ppath igual RUTA_CADENA COMANDOREN
        {
            strcpy(modificar->ruta, $4);
        }
    | menos pname igual NAME COMANDOREN
        {
            strcpy(modificar->nombre, $4);
        }
    | menos pname igual name2 COMANDOREN
        {
            strcpy(modificar->nombre, $4);
        }
    | {}
;
COMANDOEDIT: menos ppath igual  RUTA_CADENA COMANDOEDIT
        {
            strcpy(editar->ruta, $4);
        }
    | menos pcont igual  RUTA_CADENA COMANDOEDIT
        {
            strcpy(editar->cont, $4);
        }
    | {}
;
COMANDOMKFILE: menos ppath igual RUTA_CADENA COMANDOMKFILE
        {
            strcpy(file->ruta_nArchivo, $4);
            file->par_ruta = true;
        }
    | menos pr COMANDOMKFILE
        {
            file->crear = 1;
        }
    | menos psize igual entero COMANDOMKFILE
        {
            file->size =  atoi($4);
        }
    | menos pcont igual RUTA_CADENA COMANDOMKFILE
        {
            strcpy(file->cont_ruta,$4);
        }
    | {}
;
COMANDOCHMOD: menos ppath igual RUTA_CADENA COMANDOCHMOD
        {
            strcpy(elusuario1->ruta, $4);
        }
    | menos pugo igual entero COMANDOCHMOD
        {
            elusuario1->ugo = atoi($4);
        }
    | menos pr COMANDOCHMOD
        {
            elusuario1->r = true;
        }
    | {}
;
COMANDOMKUSR: menos pusr igual NAME COMANDOMKUSR
        {
            strcpy(grupo->nombre, $4);
            grupo->par_usr = true;
        }
    | menos pwd igual PASS COMANDOMKUSR
        {
            strcpy(grupo->password, $4);
            grupo->par_pwd = true;
        }
    | menos pgrp igual NAME COMANDOMKUSR
        {
            strcpy(grupo->grupo,$4);
            grupo->par_grp = true;
        }
    | {}
;
COMANDOLOGIN: menos pusr igual NAME COMANDOLOGIN
        {
            strcpy(entrar->user, $4);
            entrar->par_user = true;
        }
    | menos pid igual identificador COMANDOLOGIN
        {
            strcpy(entrar->id, $4);
            entrar->par_id = true;
        }
    | menos pwd igual PASS COMANDOLOGIN
        {
            strcpy(entrar->pwd, $4);
            entrar->par_pass = true;
        }
    | {}
;
PASS: NAME
    | entero
;
COMANDOMKFS: menos pid igual identificador COMANDOMKFS
        {
            strcpy(formateo->id, $4);
            formateo->par_id = true;
        }
    | menos ptype igual TIPO_BORRADO COMANDOMKFS
        {
            int val = atoi($4);
            formateo->type=val;
        }
    | menos pfs igual SISTEMA_FORMATEO COMANDOMKFS {}
    | {}
;
SISTEMA_FORMATEO: p2fs
        {
            formateo->ext2 = true;
        }
    | p3fs
        {
            formateo->ext3 = true;
        }
;
*/
