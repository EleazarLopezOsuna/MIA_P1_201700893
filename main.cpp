#include <QCoreApplication>
#include <iostream>
#include <scanner.h>
#include <parser.h>
#include <lista.h>
#include <MOUNT.h>
#include "objetos.h"
using namespace std;


int main()
{

    extern void setSalida(lista::list * l_general, objetos::activeUser * usr);


    lista::nodoP * nuevo = (lista::nodoP *)malloc(sizeof (lista::nodoP));
    lista::list * listapartMontadas =(lista::list*)malloc(sizeof (listapartMontadas));
    listapartMontadas->first = NULL;
    listapartMontadas->last = NULL;

    objetos::activeUser * usr_activo = (objetos::activeUser*)malloc(sizeof(objetos::activeUser));
    usr_activo->estado=-1;


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
        setSalida(listapartMontadas, usr_activo);
        yyparse();

        if(listapartMontadas->first!= NULL){
            cout << "***********************************************" << endl;
            cout << listapartMontadas->first->path << endl;
        }

    }

    return 0;
}
