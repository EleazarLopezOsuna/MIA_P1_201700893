#ifndef REP_H
#define REP_H
#include <MOUNT.h>
#include <MKDISK.h>
#include "MKFILE.h"
#include <stdio.h>
#include "LOGIN.h"
#include <lista.h>
#include <fstream>;

class REP
{
public:
    REP();
    char ruta_disco[255];
    char ruta_reporte[255];
    char ruta_archivo[255];
    bool par_ra;
    char nombre_Disco[255];
    char extension[10];
    char nombre_disco[255];
    void limpiar();
    void ejecutar_REP(lista::list *, objetos::REP);
    double obtenerPorcentaje(double , double , double );
    void graficar_MBR(char path[], objetos::REP);
    void graficar_Disk(char path[], objetos::REP rep);
    void getRuta(char * path);
    objetos::MBR crear_mbr_(int size);
    //reportes fase 2
    void rep_sb(char path[255], lista::nodoP*particion);
    void rep_bm_inodes(char path[255], lista::nodoP*particion);
    void rep_bm_blockes(char path[255], lista::nodoP*particion);
    void rep_inodos( char path[255],lista::nodoP * particion );
    void CuerpoInodos(objetos::superBloque super, int noInodo, int pos_inode, FILE *archivo, FILE * fp);
    void rep_arbol( char path[255],lista::nodoP * particion );
    void CuerpoArbol(objetos::superBloque super, int noInodo, int pos_inode, FILE *archivo, FILE * fp);
    void ApuntadoresArbol(objetos::superBloque super, int noInodo, int pos_inode, FILE *archivo, FILE * fp);
    void rep_bloques( char path[255],lista::nodoP * particion );
    void CuerpoBloques(objetos::superBloque super, int pos_inode, FILE *archivo, FILE * fp);
    void rep_journal( char path[255],lista::nodoP * particion );
    void CuerpoJournaling(int inicioParticion, int inicioBitmapInodo, FILE *archivo, FILE * fp,char particion[]);
    void rep_file(char path[255],lista::nodoP * particion) ;
    void rep_ls(char path[255],lista::nodoP * particion);
    void permisos(int permisos, FILE * doc);
    void obtener_Nuser(objetos::superBloque super_bloque, int n_usuario, FILE * archivo_disco, FILE* doc);
    void obtener_Ngrupo(objetos::superBloque super_bloque, int n_grupo, FILE * archivo_disco,FILE* doc);
    void flechas_journal(int inicioParticion, int inicioBitmapInodo, FILE *archivo, FILE * fp, char particion[]);
    void flechas_inodos(objetos::superBloque super, FILE * fp);
    char *get_Fecha(time_t time);
};

#endif // REPORTES_H
