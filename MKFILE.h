#ifndef MKFILE_H
#define MKFILE_H
#include <QString>
#include "string"
#include <iostream>
#include "objetos.h"
#include "lista.h"
#include <MOUNT.h>
#include <fs.h>
#include "MKDIR.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libgen.h>
#include <ctype.h>
using namespace std;
class MKFILE
{
public:
  MKFILE();
  string path="";
  string r="";
  string cont="";
  void CrearArchivo(MKFILE *file);
  char ruta_nArchivo[256];
  int crear;
  int size;
  char cont_ruta[256];
  bool par_ruta;
  void limpiar();
  void ejecutar_MKFILE(lista::list * lista , objetos::activeUser * usuario);
  void ejecutar_MKFILE2(lista::list * lista , objetos::activeUser * usuario,char txt[14000]);
  int VerificarPath(char path[]);
  int ContadorTipoPunto(char *string);
  int PosBitmap(int inicio, int max, int tamanio);
};

#endif // MKFILE_H
