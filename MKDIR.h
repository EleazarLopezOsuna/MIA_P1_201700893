#ifndef MKDIR_H
#define MKDIR_H
#include <QString>
#include "string"
#include <iostream>
#include "objetos.h"
#include "lista.h"
#include <MOUNT.h>
#include <fs.h>
using namespace std;

class MKDIR
{
public:
    MKDIR();
    string path="";
    string p="";
    int crear;
    char ruta_nuevaCarpeta[256];
    int par_path;
    char ruta_carpeta[255];
    int es_carpeta;
    int contador;
    objetos::super_bloque sb_aux;
    objetos::inodo father_aux;
    struct Lista{
        char carpeta[30];
    };
    typedef struct Lista Lista;
    void ejecutar_MKDIR(lista::list * lista , objetos::activeUser * usuario);
    void ejecutar_MKDIR2(lista::list * lista , objetos::activeUser * usuario,char ruta[256]);
    void get_ruta(char * path);
    int ContadorBarras(char *string);
    char *Concatenar(char *param, char letra);
    int BusquedaCarpeta(FILE *fp, objetos::super_bloque super, int posInodo, Lista ruta[], int n, int pos);
    void modificar_bitmap(FILE * archivo, int inicio,objetos::super_bloque super);
    void limpiar();
    int verificarCarpeta(FILE *file_disco, objetos::super_bloque super_bloque, int pos_Inodo, char nombre [10]);
    void EscribirTexto(FILE *fp, char text[]);
};
#endif // MKDIR_H