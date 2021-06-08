#include "RMDISK.h"
using namespace std;
RMDISK::RMDISK(){
    memset(ruta, 0, 255);
	f_ruta = false;
}
void RMDISK::setRuta(char *path){
	strcpy(ruta, path);
	f_ruta = true;
}
void RMDISK::limpiar(){
    memset(ruta, 0, 255);
	f_ruta = false;
}
void RMDISK::ejecutar(){
	FILE *file = fopen(ruta, "rb");
    char respuesta[1];
	while(true){
		if(file != NULL){
			cout << "Desea eliminar el disco: " << ruta << "?" << endl;
			cout << "Y/N" << endl;
			scanf("%s", &respuesta);
			if(strcmp(respuesta, "Y") == 0 || strcmp(respuesta, "y") == 0){
				if(remove(ruta) == 0){
					cout << "Disco eliminado" << endl;
				}else{
					cout << "Error: no se pudo eliminar el disco" << endl;
				}
				break;
			}else if(strcmp(respuesta, "N") == 0 || strcmp(respuesta, "n") == 0){
				break;
			}
		}
	}
}
