#include "FDISK.h"
#include "MKDISK.h"
using namespace std;

FDISK::FDISK(){
	limpiar();
}
void FDISK::limpiar(){
	size = NULL;
	memset(path, 0, 255);
	memset(nombre, 0, 255);
	f_path = false;
	f_nombre = false;
	operacion = NULL;
	type = 0; //P
	fit = 2; //WF
	unit = 1;
	borrar = 0;
	add = 0;
	size_add = 0;
}
void FDISK::setName(char *name){
	strcpy(nombre, name);
}
void FDISK::setRuta(char *ruta){
	strcpy(path, ruta);
}
void FDISK::ejecutar(lista::list *listx){
	objetos::MBR mbr;
	int size_p;
	FILE *file = fopen(path, "rb+");
	if(file != NULL){
		fseek(file, 0, SEEK_SET);
		fread(&mbr, sizeof(objetos::MBR), 1, file);
		fclose(file);
		if(operacion == 0){
			if(size > 0){
				if(unit == 2){
					size_p = size * 1024 * 1024;
				}else if(unit == 1){
					size_p = size * 1024;
				}else{
					size_p = size;
				}
				nuevaParticion(mbr, size_p);
			}else{
				cout << "Error, el size de la particion debe de ser mayor a 0" << endl;
			}
		}else if(operacion == 1){
            eliminarParticion(mbr, listx);
		}
	}else{
		cout << "Error, no se pudo abrir el disco" << endl;
	}
}
void FDISK::nuevaParticion(objetos::MBR mbr, int size_p){
	int f_disponible = -1;
	int f_primaria = 0;
	int f_extendida = -1;
	int f_nombre = 0;
	int actual = -1;
	for(int i = 0; i < 4; i++){
        if(mbr.mbr_partitions[i].part_status == '0'){
			f_disponible++;
			if(actual == -1){
				actual = i;
			}
		}else{
            if(mbr.mbr_partitions[i].part_type == 'P'){
				f_primaria++;
            }else if(mbr.mbr_partitions[i].part_type == 'E'){
                f_extendida = i;
            }
            if(strcmp(mbr.mbr_partitions[i].part_name, nombre) == 0){
                f_nombre++;
            }
        }
    }
	if(type == 1 && f_extendida != -1){
		cout << "Error, ya existe una particion extendida" << endl;
		return;
    }else if(type == 2 && f_extendida == -1){
		cout << "Error, no existe una particion extendida" << endl;
		return;
    }else if(type == 2){
		crearLogica(mbr, size_p, f_extendida);
	}else{
		int start = sizeof(objetos::MBR);
		int newStart = -1;
		if(f_disponible < 4 && f_disponible != -1){
			if(f_nombre != 0){
				cout << "Error, ya existe una particion con ese nombre" << endl;
				return;
			}else{
				//newStart = calculoInicio(mbr, size_p, f_disponible, start);
                if((mbr.mbr_tamano - sizeof(objetos::MBR)) < size_p){
                    newStart = -1;
                    cout << mbr.mbr_tamano <<endl;
                    cout << size_p << endl;
                }else{
                    if(mbr.mbr_disk_fit == 1){ //primer
                        newStart = calculoFit(mbr, size_p, f_disponible, start);
                    }else if(mbr.mbr_disk_fit == 2){ //peor
                        newStart = calculoFit(mbr, size_p, f_disponible, start);
                    }else if(mbr.mbr_disk_fit ==0 ){ // mejor
                        newStart = calculoFit(mbr, size_p, f_disponible, start);
                    }
                }
                if(newStart != -1){
                    if(type == 0 || type == 1 && size_p > sizeof(objetos::EBR)){
                        mbr.mbr_partitions[actual].part_status = '1';
                        if(type == 0){
                            mbr.mbr_partitions[actual].part_type = 'P';
                        }else if(type == 1){
                            mbr.mbr_partitions[actual].part_type = 'E';
                        }
                        mbr.mbr_partitions[actual].part_start = newStart;
                        mbr.mbr_partitions[actual].part_size = size_p;
                        strcpy(mbr.mbr_partitions[actual].part_name, nombre);
                        if(fit == 1){
                            mbr.mbr_partitions[actual].part_fit = 'F';
                        }else if(fit == 2){
                            mbr.mbr_partitions[actual].part_fit = 'W';
                        }else{
                            mbr.mbr_partitions[actual].part_fit = 'B';
                        }
                        ordenamiento(mbr);
                        FILE *file = fopen(path, "rb+");
                        fseek(file, 0, SEEK_SET);
                        fwrite(&mbr, sizeof(objetos::MBR), 1, file);
                        fclose(file);
                        if(type == 0){
                            printf("Se creo una nueva particion %i de tipo primaria\n", actual);
                            printf("--> Nombre: %s . \n", nombre);
                            printf("--> Size: %i . \n", size_p);
                            printf("************************************************************* \n");
                        }else if(type == 1){
                            objetos::EBR newEBR = crearEBR(size_p, start, -1);
                            if(particionE(mbr, newEBR, actual) == 1){
                                printf("Se creo una nueva particion %i de tipo extendida:\n", actual, nombre);
                                printf("--> Nombre: %s . \n", nombre);
                                printf("--> Tamanio: %i . \n", size_p);
                                printf("--> next: %i . \n ", newEBR.part_next);
                                printf("Fit: %c .\n", newEBR.part_fit);
                                printf("************************************************************* \n");
                            }else{
                                cout << "Error, no se pudo crear la particion" << endl;
                            }
                        }
                    }else{
                        cout << "Error, la particion logica debe de ser menor a la particion extendida" << endl;
                    }
                }else{
                    cout << "Error, no hay espacio suficiente para crear la particion" << endl;
                }
			}
		}else{
			cout << "Error, no se pueden crear mas de 4 particiones" << endl;
		}
	}
}
void FDISK::ordenamiento(objetos::MBR mbr){
	objetos::part temp;
	for(int i=1; i < 4; i++){
	    for(int j=0; j<3; j++){
            if((mbr.mbr_partitions[j].part_start > mbr.mbr_partitions[j+1].part_start) || (mbr.mbr_partitions[j].part_start == 0)){
                temp = mbr.mbr_partitions[j];
                mbr.mbr_partitions[j] = mbr.mbr_partitions[j+1];
                mbr.mbr_partitions[j+1] = temp;
	        }
	    }
	}
}
int FDISK::calculoFit(objetos::MBR mbr, int size_p, int free_p, int start_p){
	int pos_ini = -1;
	int size_part = 0;
	int pos_minima = -1;
	int diff = 0;
	int min_diferencia = -1;
	int uso = 0;
	for(int i = 0; i < 4; i++){
        if(mbr.mbr_partitions[i].part_start > -1){
			uso++;
		}
	}
	if(mbr.mbr_disk_fit == 1){
		//Calculo FF
		for(int i = 0; i < uso; i++){
            pos_ini = mbr.mbr_partitions[i].part_start;
            size_part = mbr.mbr_partitions[i].part_size;
			//Verificamos si hay espacio disponible entre la particion
			if((pos_ini - start_p) >= size_p)
				break;
			start_p = pos_ini + size_part;
		}
        if(start_p <= (mbr.mbr_tamano - size_p))
			return start_p;
		return -1;
	}else if(mbr.mbr_disk_fit == 2){
		//Calculo BF
		for(int i = 0; i < uso; i++){
			//Tomamos los datos de la particion
            pos_ini = mbr.mbr_partitions[i].part_start;
            size_part = mbr.mbr_partitions[i].part_size;
			//start - size (comprobamos si la particion ya esta usada)
			diff = pos_ini - start_p;
			//Cabe en el espacio i
			if(diff >= size_p){
				if(i == 0){
					//La posicion 0 tiene espacio
					pos_minima = start_p;
					min_diferencia = diff;
				}else{
					if(min_diferencia == -1 || diff <= min_diferencia){
						//La posicion i tiene mejor capacidad para manejar el BF, se cambian las posiciones
						pos_minima = start_p;
						min_diferencia = diff;
					}
				}
			}
			start_p = pos_ini + size_part;
		}
		//calculamos la diferencia
        diff = mbr.mbr_tamano - start_p;
		if((min_diferencia == -1 && diff >= size_p) || (diff >= size_p && diff <= min_diferencia)){
			//Comprobamos si la particion cabe en el espacio sugerido
			pos_minima = start_p;
            min_diferencia = diff;
		}
		if(min_diferencia > -1)
			return pos_minima;
		return -1;
	}else if(mbr.mbr_disk_fit == 0){
		//Calculo WF
		for(int i = 0; i < uso; i++){
			//Tomamos los datos de la particion
            pos_ini = mbr.mbr_partitions[i].part_start;
            size_part = mbr.mbr_partitions[i].part_size;
			//start - size (comprobamos si la particion ya esta usada)
			diff = pos_ini - start_p;
			//Cabe en el espacio i
			if(diff >= size_p){
				if(i == 0){
					//La posicion 0 tiene espacio
					pos_minima = start_p;
					min_diferencia = diff;
				}else{
					if(min_diferencia == -1 || diff > min_diferencia){
						//La posicion i tiene mejor capacidad para manejar el WF, se cambian las posiciones
						pos_minima = start_p;
						min_diferencia = diff;
					}
				}
			}
			start_p = pos_ini + size_part;
		}
		//calculamos la diferencia
        diff = mbr.mbr_tamano - start_p;
		if((min_diferencia == -1 && diff >= size_p) || (diff >= size_p && diff >= min_diferencia)){
			//Comprobamos si la particion cabe en el espacio sugerido
			pos_minima = start_p;
            min_diferencia = diff;
		}
		if(min_diferencia > -1)
			return pos_minima;
		return -1;
	}
}
objetos::EBR FDISK::crearEBR(int size_p, int inicio_p, int next){
	objetos::EBR newEBR;
	newEBR.part_status = '0';
	if(fit == 0){
		newEBR.part_fit = 'B';
	}else if(fit == 1){
		newEBR.part_fit = 'F';
	}else{
		newEBR.part_fit = 'W';
	}
	newEBR.part_start = inicio_p;
	newEBR.part_size = size_p;
	newEBR.part_next = -1;
	strcpy(newEBR.part_name, nombre);
	return newEBR;
}
int FDISK::particionE(objetos::MBR mbr, objetos::EBR ebr, int actual){
	int f_creado = 0;
    int part_start = mbr.mbr_partitions[actual].part_start;
    int part_size = mbr.mbr_partitions[actual].part_size;
	int part_end = part_start + part_size - 1;
	if(part_end < mbr.mbr_tamano){
		if(part_start > part_end){
			cout << "Error, no hay espacio suficiente" << endl;
		}else{
			FILE *file = fopen(path, "rb+");
			if(file != NULL){
				fseek(file, part_start, SEEK_SET);
				fwrite(&ebr, sizeof(objetos::EBR), 1, file);
				fclose(file);
				return 1;
			}
			cout << "Error, no se pudo abrir el disco" << endl;
			return 0;
		}
	}
	cout << "Error, no hay espacio suficiente" << endl;
	return 0;
}
void FDISK::crearLogica(objetos::MBR mbr, int size_p, int pos){
	objetos::EBR ebr;
    int inicio_part = mbr.mbr_partitions[pos].part_start;
    int total = mbr.mbr_partitions[pos].part_size;
	int extendida = inicio_part + total;
	int disponible = total - sizeof(objetos::EBR);
	int necesario = disponible - size_p;
    int logica = 0;
	FILE *file = fopen(path, "rb+");
	fseek(file, inicio_part, SEEK_SET);
    fread(&ebr, sizeof(objetos::EBR), 1, file);
    if(total > size_p){
		if(sizeof(objetos::EBR) > size_p){
            cout << "Error, no hay espacio suficiente" << endl;
		}else{
			objetos::EBR tmp = ebr;
            objetos::EBR next;
			if(no_existe_logica(ebr, mbr) == 0){
                logica = 0;
                while(logica != 1){
					fseek(file, inicio_part, SEEK_SET);
					fread(&tmp, sizeof(objetos::EBR), 1, file);
					if(tmp.part_status == '0' && tmp.part_next == -1){
						int final = inicio_part + total - 1;
						if((inicio_part + size_p) < extendida){
							strcpy(tmp.part_name, nombre);
							if(fit == 0)
								tmp.part_fit = 'B';
							else if(fit == 1)
								tmp.part_fit = 'F';
							else
								tmp.part_fit = 'W';
							tmp.part_start = inicio_part;
							tmp.part_size = size_p;
							tmp.part_next = inicio_part + tmp.part_size;
							tmp.part_status = '1';
							fseek(file, inicio_part, SEEK_SET);
							fwrite(&tmp, sizeof(objetos::EBR), 1, file);
							strcpy(next.part_name, "\0");
							next.part_fit = 'W';
							next.part_start = inicio_part + size_p;
							next.part_size = 0;
							next.part_next = -1;
							next.part_status = '0';
							fseek(file, next.part_start, SEEK_SET);
							fwrite(&next, sizeof(objetos::EBR), 1, file);
							logica = 1;
						}else{
                            cout << "Error, no hay espacio suficiente para crear la particion" << endl;
						}
					}
					inicio_part = tmp.part_next;
				}
            }else{
                cout << "Error, no se pudo crear la particion logica, ya existe una particion con ese nombre" << endl;
            }
		}
    }
	fclose(file);
}
int FDISK::no_existe_logica(objetos::EBR ebr, objetos::MBR mbr){
	int flag = 0;
	for(int i = 0; i < 4; i++){
        if(strcmp(nombre, mbr.mbr_partitions[i].part_name) == 0){
			flag = 1;
			break;
		}
	}
    objetos::EBR tmp = ebr;
	objetos::EBR next;
	FILE *file = fopen(path, "rb+");
    while(tmp.part_next != -1){
		if(strcmp(nombre, tmp.part_name) == 0){
			flag = 1;
			break;
		}
		fseek(file, tmp.part_next, SEEK_SET);
		fread(&tmp, sizeof(objetos::EBR), 1, file);
	}
	fclose(file);
	return flag;
}
void FDISK::eliminarParticion(objetos::MBR mbr, lista::list *listx){
	int particion = -1;
	int posicion = -1;
	int f_eliminada = 0;
    MOUNT *newMount;
	for(int i = 0; i < 4; i++){
        if(mbr.mbr_partitions[i].part_status == '1'){
            if(strcmp(mbr.mbr_partitions[i].part_name, nombre) == 0){
				f_eliminada = i; //Obtengo la particion a eliminar
			}
            if(mbr.mbr_partitions[i].part_type = 'E'){
                posicion = i; //Obtengo la posicion de la extendida
			}
		}
	}
	if(particion != -1){
		lista::nodoC *tmp = newMount->buscar(path, listx->first);
		if(tmp != NULL){
			//Si existe
			lista::nodoP *particion = newMount->buscarP(path, listx->first);
			if(particion != NULL){
                newMount->eliminarName(&(tmp->particiones), nombre, tmp);
			}
		}
		FILE *file = fopen(path, "rb+");
        if(mbr.mbr_partitions[particion].part_type == 'P' || mbr.mbr_partitions[particion].part_type == 'E'){
			if(borrar == 2){
				//Full
				if(file != NULL){
                    int inicio = mbr.mbr_partitions[particion].part_start;
                    int tam = mbr.mbr_partitions[particion].part_size;
					fseek(file, inicio, SEEK_SET);
					for(int i = 0; i < tam; i ++){
						fputc(0, file);
					}
				}
			}
            mbr.mbr_partitions[particion].part_status = '0';
            mbr.mbr_partitions[particion].part_fit = '\0';
            strcpy(mbr.mbr_partitions[particion].part_name, "\0");
            mbr.mbr_partitions[particion].part_size = 0;
            mbr.mbr_partitions[particion].part_start = 0;
            mbr.mbr_partitions[particion].part_type = 'N';
			ordenamiento(mbr);
			fseek(file, 0, SEEK_SET);
			fwrite(&mbr, sizeof(objetos::MBR), 1, file);
			fclose(file);
            f_eliminada++;
		}
    }else if(particion == -1 && posicion != -1){
		//Logica
		lista::nodoC *tmp = newMount->buscar(path, listx->first);
		if(tmp != NULL){
            lista::nodoP *particion = newMount->buscarP(nombre, listx->first);
			if(particion != NULL){
				newMount->eliminarName(&(tmp->particiones), nombre, tmp);
			}
		}
		FILE *file = fopen(path, "rb+");
		if(file != NULL){
			objetos::EBR ebr;
			objetos::EBR primero;
			objetos::EBR temp;
            int inicio_part = mbr.mbr_partitions[posicion].part_start;
			int inicio = 0;
			int size = 0;
			fseek(file, inicio_part, SEEK_SET);
			fread(&ebr, sizeof(objetos::EBR), 1, file);
			primero = ebr;
			temp = existe_logica(ebr, nombre, path, mbr);
			if(temp.part_status != '0' && temp.part_next != 0){
				if(temp.part_start == primero.part_start){
					objetos::EBR newEBR;
					newEBR.part_status = '0';
					newEBR.part_fit = 'W';
					newEBR.part_start = temp.part_start;
					newEBR.part_size = temp.part_size;
					newEBR.part_next = temp.part_next;
					strcpy(newEBR.part_name, "\0");
					if(newEBR.part_start < inicio_part){
						//no se pudo eliminar por que el inicio queda antes que el ebr
						return;
					}
					fseek(file, newEBR.part_start, SEEK_SET);
					fwrite(&newEBR, sizeof(objetos::EBR), 1, file);
					inicio = temp.part_start + sizeof(objetos::EBR);
					size = temp.part_size - sizeof(objetos::EBR);
				}else if(temp.part_next == -1){
					//Es en la ultima posicion
					objetos::EBR prev;
					objetos::EBR next;
					prev = primero;
					if(prev.part_next != -1){
						fseek(file, prev.part_next, SEEK_SET);
						fread(&next, sizeof(objetos::EBR), 1, file);
						if(next.part_start < temp.part_start){
							prev = next;
						}
					}
					prev.part_next = -1;
					if(prev.part_start < inicio_part){
						//no se pudo eliminar por que el inicio queda antes que el ebr
						return;
					}
					prev.part_status = '0';
					fseek(file, prev.part_start, SEEK_SET);
					fwrite(&prev, sizeof(objetos::EBR), 1, file);
					inicio = temp.part_start;
					size = temp.part_size;
				}else{
					objetos::EBR next;
					fseek(file, temp.part_next, SEEK_SET);
					fwrite(&next, sizeof(objetos::EBR), 1, file);
					objetos::EBR prev;
					prev = primero;
					objetos::EBR temporal;
					if(prev.part_next != -1){
						fseek(file, prev.part_next, SEEK_SET);
						fread(&temporal, sizeof(objetos::EBR), 1, file);
						if(temporal.part_start < temp.part_start){
							prev = temporal;
						}
					}
					if(prev.part_start < inicio_part){
						//no se pudo eliminar por que el inicio queda antes que el ebr
                        return;
					}
					prev.part_status = '0';
					prev.part_fit = 'W';
					strcpy(prev.part_name, "\0");
					prev.part_start = temp.part_start;
					prev.part_size = temp.part_size;
					prev.part_next = temp.part_next;
					fseek(file, prev.part_start, SEEK_SET);
					fwrite(&prev, sizeof(objetos::EBR), 1, file);
					inicio = temp.part_start;
					size = temp.part_size;
				}
				if(borrar = 2){
					//Full
					int final = inicio + size - 1;
					fseek(file, inicio, SEEK_SET);
                    for(int i = 0; i < temp.part_size; i++){
						fputc(0, file);
					}
				}
			}
			fclose(file);
		}
	}
}
objetos::EBR FDISK::existe_logica(objetos::EBR ebr, char nom[], char ruta[], objetos::MBR mbr){
	objetos::EBR newEBR;
	newEBR.part_next = 0;
	newEBR.part_status = '0';
	objetos::EBR temp = ebr;
	FILE *file = fopen(ruta, "rb+");
	while(temp.part_next != -1){
        if(strcmp(nombre, temp.part_name) == 0){
			newEBR = temp;
			break;
		}
		fseek(file, temp.part_next, SEEK_SET);
		fread(&temp, sizeof(objetos::EBR), 1, file);
	}
	fclose(file);
	return newEBR;
}
