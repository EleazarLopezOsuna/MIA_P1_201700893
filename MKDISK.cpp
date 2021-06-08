#include "MKDISK.h";
using namespace std;

MKDISK::MKDISK(){
	f = 1;
	u = 1;
	size = NULL;
	fruta = false;
	memset(ruta_raid, 0, 500);
	memset(ruta, 0 , 255);
	memset(ruta_disco, 0 , 255);
	memset(nombre_disco, 0 , 63);
	memset(extension, 0 , 10);
}

void MKDISK::setSize(int givenSize){
	size = givenSize;
}
void MKDISK::setRuta(char *givenPath){
	fruta = true;
	strcpy(ruta, givenPath);
}
void MKDISK::limpiar(){
	f = 1;
	u = 1;
	size = NULL;
	fruta = false;
	memset(ruta_raid, 0, 500);
	memset(ruta, 0 , 255);
	memset(ruta_disco, 0 , 255);
	memset(nombre_disco, 0 , 63);
	memset(extension, 0 , 10);
}
void MKDISK::ejecutar(){
	FILE *file = fopen(ruta, "r");
	if(file != NULL){
		printf("Error: el disco ya existe \n");
		fclose(archivo);
	}else{
		getRuta(ruta);
		strcpy(ruta_raid, getRutaRaid(ruta));
		if(strcmp(extension, "dk") == 0){
			DIR* nuevoDirectorio = opendir(ruta_disco);
			if(nuevoDirectorio){
				closedir(nuevoDirectorio);
				crearDisco(ruta, 1);
				crearDisco(ruta_raid, 2);
			}else{
				int status = system("mkdir -p /home/archivos");
				if(status == -1){
					cerr << "Error: " << strerror(errno) << endl;
				}else{
					cout << "Directorio /home/archivos creado" << endl;
				}
			}
		}else{
			cout << "Error: la extension del disco no es soportada, se esperaba MK" << endl;

		}
	}
}
void MKDISK::getRuta(char *path){
	int i = 0;
	char character;
	char temp_path[500] = {0};
	memset(temp_path, 0, 500);
	while(path[i] != 0){
		character = path[i];
		if(strcmp(character, "/") == 0){
			strcat(temp_path, "/");
			strcat(ruta_disco, temp_path);
			memset(temp_path, 0, 500);
			mkdir(ruta_disco, 0777);
		}else if(strcmp(character, ".") == 0){
			strcat(nombre_disco, temp_path);
			memset(temp_path, 0, 500);
		}else{
			strcat(temp_path, character);
		}
		i++;
	}
	strcpy(extension, temp_path);
}
char* MKDISK::getRutaRaid(char *path){
	char *ruta = (char*) malloc(sizeof (char)*500);
    memset(ruta, 0, 500);
    int i=0;
    char character;
    char temp_path[500] = {0};
    memset(temp_path, 0, 500);
    while(path[i] != 0)
    {
        caracter = path[i];
        if(strcmp(caracter,"/") == 0)
        {
            strcat(ruta, temp_path);
             strcat(ruta, "/");
            memset(temp_path, 0, 500);
        }else if(strcmp(caracter,".") == 0){
            strcat(temp_path, "_raid");
            strcat(ruta, temp_path);
            memset(temp_path, 0, 500);
        }else{
            strcat(temp_path,caracter);
        }
        i++;
    }
    strcat(ruta,".");
    strcat(ruta, temp_path);
    return ruta;
}
void MKDISK::crearDisco(char *path, int tipo){
	objetos::MBR mbr;
	FIle *file = fopen(path, "wb+");
	if(file == NULL){
		cout << "Error: el disco no pudo ser creado" << endl;
	}else{
		fseek(file, 0, SEEK_SET);
		objetos::content llenado;
		int sizeI = size;
		if(u != 0){
			sizeI *= 1024;
		}
		for(int i = 0; i < sizeI; i++){
			for(int j = 0; j < 1024; j++){
				llenado.contenido[j] = '\0';
			}
			fwrite(&llenado, sizeof(objetos::content), 1, file)
		}
		fseek(file, 0, SEEK_SET);
		mbr = crearMBR(obtenerSize());
		fwrite(&mbr, sizeof(objetos::MBR), 1, file);
	}
	fclose(file);
}
void MKDISK::obtenerSize(){
	int retorno = 0;
	if(u == 1){
		retorno = size * size * 1024;
	}else if(u == 0){
		retorno = size * 1024;
	}else{
		retorno = size * size * 1024;
	}
}
objetos::MBR MKDISK::crearMBR(int mbrSize){
	objetos::MBR newMBR;
	newMBR.mbr_tamano = mbrSize;
	time(NULL);
	newMBR.mbr_disk_signature = rand()%999;
	newMBR.mbr_disk_fit = f;
	newMBR.mbr_fecha_creacion = time(0);
	for(int i = 0; i < 4; i++){
		objetos::part particion;
		particion.part_status = '0';
		particion.part_type = 'N';
		particion.part_fit = 'F';
		particion.part_start = -1;
		particion.part_size = -1;
		newMBR.mbr_partitions = particion;
	}
	return newMBR;
}

void MKDISK::mostrarDatos(MKDISK *disco){
	cout << "---------Informacion del Disco----------" << endl;
	cout << "Size: " << disco->size << endl;
	cout << "Fit: " << disco->f << endl;
	cout << "U: " << disco->u << endl;
	cout << "Path: " << disco->path << endl;
	disco->ejecutar();
	disco->limpiar();
	disco = new obmkdisk();
}