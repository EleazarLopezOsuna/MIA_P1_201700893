#ifndef MKFS_H
#define MKFS_H
#include <objetos.h>
#include <lista.h>
#include <MOUNT.h>
#include <fs.h>
using namespace std;

class MKFS
{
public:
    MKFS();
	char id[10] ;// id que se le dio en el mount vda1 ...
	int type; // si es 1= fast, 2=full
	bool par_id;
	bool ext2;
	bool ext3;
	void ejecutar_MKFS(lista::list * lista);
	void formatear_sistema(char *name, char *path, int tfs);
	int PosBitmap(int inicio, int max, int tamanio);
	void escribirBitmapInodos(objetos::superBloque s_bloque, int n, FILE* archivo_disco);
	void escribirBitmapBloques(objetos::superBloque s_bloque, FILE* archivo_disco);
    void crearArchivoUsuarios(objetos::bloqueCarpeta Bloque, FILE *archivo_disco, objetos::superBloque s_bloque, fs *sistema);
};

#endif // MKFS_H
