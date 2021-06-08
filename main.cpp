#include <QCoreApplication>
#include <iostream>
#include <scanner.h>
#include <parser.h>
//#include <particioneslist.h>
//#include <mount.h>
//#include "Estructuras.h"
using namespace std;


int main()
{

    //extern void setSalida(particioneslist::lista * l_general, Estructuras::user_activo * usr);


    //lista_particiones::nodo_particion * nuevo = (lista_particiones::nodo_particion*)malloc(sizeof (lista_particiones::nodo_particion));
    //particioneslist::lista * lista_particionesMontadas =(particioneslist::lista*)malloc(sizeof (lista_particionesMontadas));
    //lista_particionesMontadas->primero = NULL;
    //lista_particionesMontadas->ultimo = NULL;

    //Estructuras::user_activo * usr_activo = (Estructuras::user_activo*)malloc(sizeof(Estructuras::user_activo));
    //usr_activo->estado=-1;


    // while para mantener escuchando comandos
    int activa=0;
    char contenidoLinea[1024];
    while(activa==0){
        cout<<"\n $-";
      // leer las lineas de laconsola
            int i = 0;
            while(contenidoLinea[i] != '\0'){ // lipiar la entrada
                contenidoLinea[i]='\0';
                i++;
            }

            int caracterAscii;
            i=0;
            while ((caracterAscii = getchar()) != '\n' && caracterAscii != NULL){
                contenidoLinea[i]=caracterAscii;
                i++;
            };
            int caratecres=i;
            if(caratecres ==0){
                cout<<"ingrese un comando "<<endl;
                continue;
            }
        //-------------------------

            //cout<<"\n la entrada es: "<<contenidoLinea<<endl;

        yy_scan_string(contenidoLinea);
        //setSalida(lista_particionesMontadas, usr_activo);
        yyparse();

/*if(lista_particionesMontadas->primero!= NULL){
               cout<<"***********************************************"<<endl;
             cout<<lista_particionesMontadas->primero->path<<endl;

        }*/

    }

    return 0;
}
