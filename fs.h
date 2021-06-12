#ifndef FS_H
#define FS_H
#include <objetos.h>
#include <lista.h>
#include <stdio.h>
#include <iostream>
#include <QString>
#include "string"
#include <MKDIR.h>
#include <MKFILE.h>
#include <CP.h>
using namespace std;

class fs
{
public:
    int size;
    int crear;
    int contador=0;

    fs();
    void ActualizarBitmap(FILE * archivo, int posicion, char estado);

    int ObtenerNumeroInodo(objetos::superBloque  super);
    int ObtenerNumeroBloque(objetos::superBloque super);

    objetos::BloqueArchivo CrearBloqueArchivo();
    objetos::Inodo Crear_Inodo();
    objetos::superBloque newSuperBloque();
    void EscribirTexto(FILE *fp, objetos::superBloque super, objetos::Inodo *node, char text[]);
    char *Concatenar(char *param, char letra);
    objetos::Journal * CrearJornal(char name[12], char operation[256]);
    char* ObtenerTexto(FILE *fp, objetos::superBloque super, objetos::Inodo node);
    char ObtenerTexto2(FILE *fp, objetos::superBloque super, objetos::Inodo node);
    void CambiarPermisos(FILE *fp, objetos::superBloque super, objetos::Inodo *node, char text[]);

        //*** para buscar el inodo
    int ExisteInodo(objetos::superBloque superBloque, int pos_Inodo, char nombre[],FILE *file_disco);
    int RecursivisdadCHMOD(objetos::superBloque superBloque, int pos_Inodo, char nombre[],FILE *file_disco,int ugo,lista::list * lista , objetos::activeUser * usuario);
    int RecursivisdadCHOWN(objetos::superBloque superBloque, int pos_Inodo, char nombre[],FILE *file_disco,int ugo,lista::list * lista , objetos::activeUser * usuario);
    int EliminarReferencia(objetos::superBloque superBloque, int pos_Inodo, char nombre[],FILE *file_disco);
    int EliminarReferencia2(objetos::superBloque superBloque, int pos_Inodo, char nombre[],FILE *file_disco,lista::list * lista , objetos::activeUser * usuario);
    int CambiarNombre(objetos::superBloque superBloque, int pos_Inodo, char nombre[],char nombrenuevo[],FILE *file_disco);
    int ExisteInodo2(objetos::superBloque superBloque, int pos_Inodo, char nombre[],FILE *file_disco,char rutaNueva[256],char rutaVieja[256],lista::list * lista , objetos::activeUser * usuario);
    int calcularPermisos(char buffer[]);
};

#endif // FSYSTEM_H
