#include "MOUNT.h"

MOUNT::MOUNT(int type){
    if(type == 1){
        obj_mount.f_name = 0;
        obj_mount.f_path = 0;
		obj_mount.error = 0;
		f_name = false;
		f_path = false;
	}else{
        obj_unmount.f_id = 0;
		obj_unmount.error = 0;
		f_id = false;
	}
}
void MOUNT::limpiar_m(){
	obj_mount.f_name = 0;
	obj_mount.f_path = 0;
	obj_mount.error = 0;
	f_name = false;
	f_path = false;
	memset(obj_mount.id, 0, 10);
	memset(obj_mount.path, 0, 255);
	memset(obj_mount.name, 0, 16);
}
void MOUNT::limpiar_u(){
	obj_unmount.f_id = 0;
	obj_unmount.error = 0;
	f_id = false;
	memset(obj_unmount.id, 0, 10);
}
lista::nodoC *MOUNT::insertar(lista::list ** lista, int character, objetos::MOUNT mount, lista::nodoC *pivote){
	lista::nodoC * newNodo = (lista::nodoC *)malloc(sizeof(lista::nodoC));
    strcpy(newNodo->path, mount.path);
    newNodo->next = newNodo->prev = NULL;
    newNodo->particiones = (lista::listaParticiones *)malloc(sizeof(lista::listaParticiones));
    newNodo->particiones->first = NULL;
	//Es el primer dato en la lista
	if((*lista)->first == NULL){
		(*lista)->first = newNodo;
		(*lista)->last = newNodo;
		(*lista)->size++;
		newNodo->character = character;
	}else if((*lista)->first == (*lista)->last){
		//Es el segundo dato en la lista
		(*lista)->size++;
		pivote->next = newNodo;
		(*lista)->last = newNodo;
		newNodo->prev = (*lista)->first;
		newNodo->character = newNodo->prev->character + 1;
	}else{
		(*lista)->size++;
		pivote = (*lista)->last;
		pivote->next = newNodo;
		newNodo->next = NULL;
        newNodo->prev = (*lista)->last;
        (*lista)->last = newNodo;
		newNodo->character = newNodo->prev->character + 1;
	}
	return newNodo;
}
lista::nodoC *MOUNT::buscar(char path[], lista::nodoC *pivote){
	if(pivote == NULL)
		return NULL;
	else
        while(pivote != NULL){
			if(strcmp(pivote->path, path) == 0)
				return pivote;
            pivote = pivote->next;
		}
	return NULL;
}
void MOUNT::eliminar(lista::list **lista, int character, lista::nodoC *pivote){
	if(pivote == NULL)
		cout << "Error, no hay discos montados" << endl;
	else
		while(pivote != NULL){
			if(pivote->character == character){
				if(pivote == (*lista)->first){
					pivote->next->prev == NULL;
					(*lista)->first = pivote->next;
				}else if(pivote == (*lista)->last){
					pivote->prev->next = NULL;
					(*lista)->last = pivote->prev;
				}else{
					pivote->next->prev = pivote->prev;
					pivote->prev->next = pivote->next;
				}
			}
		}
	free(pivote);
}
void MOUNT::mostrar(lista::nodoC *pivote){
	lista::nodoP *tmp;
	char character;	do{
		if(pivote != NULL){
			character = pivote->character;
            tmp = pivote->particiones->first;
            if(tmp != NULL){
				cout << "Disco montado " << pivote->path <<endl;
				do{
					cout << "Particion: " << tmp->name;
                    tmp = tmp->next;
				}while(tmp != NULL);
			}
			pivote = pivote->next;
		}
	}while(pivote != NULL);
}
void MOUNT::ejecutarM(objetos::MOUNT mount, lista::list *listaP){
	objetos::MBR mbr;
	FILE *file = fopen(mount.path, "rb+");
	if(file != NULL){
		fseek(file, 0, SEEK_SET);
		fread(&mbr, sizeof(objetos::MBR), 1, file);
		int f_existe = 0;
		int f_existe_logica = 0;
		int index_extendida = 0;
		int pos_particion = 0;
		for(int i = 0; i < 4; i++){
			if(strcmp(mbr.mbr_partitions[i].part_name, mount.name) == 0){
				f_existe++;
			}
			if(mbr.mbr_partitions[i].part_type == 'E'){
				index_extendida = i;
			}
		}
		if(index_extendida != 0){
			//Existe una particion extendida
			objetos::EBR ebr;
			objetos::EBR next;
			int start = mbr.mbr_partitions[index_extendida].part_start;
			fseek(file, start, SEEK_SET);
			fread(&ebr, sizeof(objetos::EBR), 1, file);
			if(no_existe_logica(ebr, mount, mbr) != 0){
				f_existe_logica++;
			}
		}
		if(f_existe == 0 || f_existe_logica == 0){
			cout << "Error, la particion no existe" << endl;
		}else{
            lista::nodoC *nodo = buscar(mount.path, listaP->first);
			if(nodo != NULL){
				if((buscarP(mount.name, nodo)) == NULL){
					cout << "Error, la particion ya esta montada" << endl;
				}else{
					insertarP(&(nodo->particiones), nodo, mount, nodo->particiones->first);
				}
			}else{
				int letra = 'a';
                lista::nodoC *disco = insertar(&(listaP), letra, mount, listaP->first);
				insertarP(&(disco->particiones), disco, mount, disco->particiones->first);
			}
			mostrar(listaP->first);
		}
		fclose(file);
	}else{
		cout << "El disco " << mount.path << " no existe" << endl;
	}
}
lista::nodoP *MOUNT::crearP(objetos::MOUNT mount){
    return (lista::nodoP *)malloc(sizeof(lista::nodoP));
}
int MOUNT::no_existe_logica(objetos::EBR ebr, objetos::MOUNT mount, objetos::MBR mbr){
	int f_existe = 0;
	for(int i = 0; i < 4; i++){
        if(strcmp(mount.name, mbr.mbr_partitions[i].part_name) == 0){
			f_existe = 1;
			break;
		}
	}
	objetos::EBR tmp = ebr;
	objetos::EBR next;
	FILE *file = fopen(mount.path, "rb+");
    while(tmp.part_next != -1){
        if(strcmp(mount.name, tmp.part_name) == 0){
			f_existe = 1;
			break;
		}
		fseek(file, tmp.part_next, SEEK_SET);
		fread(&tmp, sizeof(objetos::EBR), 1, file);
	}
	fclose(file);
	return f_existe;
}
void MOUNT::insertarP(lista::listaParticiones **lista, lista::nodoC *nodo, objetos::MOUNT mount, lista::nodoP *pivote){
    lista::nodoP *newNodo = (lista::nodoP *)malloc(sizeof(lista::nodoP));
	int valor = 0;
	strcpy(newNodo->name, mount.name);
	newNodo->id[0] = '9';
	newNodo->id[1] = '3';
	newNodo->id[3] = nodo->character;
	newNodo->next = NULL;
	newNodo->prev = NULL;
	if((*lista)->first == NULL){
        nodo->particiones->first = (*lista)->first = newNodo;
		(*lista)->last = newNodo;
		newNodo->id[2] = '1';
		(*lista)->size = 1;
    }else if((*lista)->first == (*lista)->last){
		(*lista)->size++;
		pivote->next = newNodo;
		(*lista)->last = newNodo;
		newNodo->prev = (*lista)->first;
		newNodo->id[2] = newNodo->prev->id[2] + 1;
	}else{
		(*lista)->size++;
		pivote = (*lista)->last;
		pivote->next = newNodo;
        newNodo->next = NULL;
        newNodo->prev = (*lista)->last;
        (*lista)->last = newNodo;
		newNodo->id[2] = newNodo->prev->id[2] + 1;
		char charact[1] = {0};
		charact[0] = newNodo->id[2];
		if(charact[0] == ':'){
            newNodo->id[2] = '1';
            newNodo->id[3] = '0';
        }else if(charact[0]  == '3' || charact[0]  == '4' ||charact[0] == '5' || charact[0] == '6' || charact[0] == '7' ||charact[0] == '8' || charact[0] == '9'  ){
            if(newNodo->prev->id[3] == '0' || newNodo->prev->id[3] == '1' || newNodo->prev->id[3] == '2' || newNodo->prev->id[3] == '3' || newNodo->prev->id[3] == '4'){
                newNodo->id[2] = '1';
                newNodo->id[3] = newNodo->prev->id[3] + 1;
            }
        }else if(charact[0] == '2'){
            if(newNodo->prev->id[3] == '0' || newNodo->prev->id[3] == '1' || newNodo->prev->id[3] == '2' || newNodo->prev->id[3] == '3' || newNodo->prev->id[3] == '4'){
                newNodo->id[2] = '1';
                newNodo->id[3] = newNodo->prev->id[3] + 1;
            }
        }else{
            newNodo->id[2] = '1';
            newNodo->id[3] = newNodo->prev->id[3] + 1;
        }
	}
}
lista::nodoP *MOUNT::buscarP(char name[], lista::nodoC *pivote){
    lista::nodoP *tmp;
	if(pivote != NULL){
		do{
            tmp = pivote->particiones->first;
			if(tmp != NULL){
				do{
					if(strcmp(tmp->name, name) == 0)
						return tmp;
					else
						tmp = tmp->next;
				}while(tmp != NULL);
			}
			pivote = pivote->next;
		}while(pivote != NULL);
	}
	return NULL;
}
void MOUNT::eliminarP(lista::listaParticiones **lista, objetos::UNMOUNT unmount, lista::nodoC *pivote){
	lista::nodoP *tmp = pivote->particiones->first;
	if(tmp == NULL){
		cout << "Error, no existen particiones en el disco" << endl;
	}else{
		if((*lista)->size == 1){
			(*lista)->first = NULL;
			(*lista)->last = NULL;
			pivote->particiones->first = NULL;
		}else{
			while(tmp != NULL){
				if(strcmp(tmp->id, unmount.id) == 0){
					if(tmp == (*lista)->first){
						tmp->next->prev = NULL;
						(*lista)->first = tmp->next;
					}else if(tmp == (*lista)->last){
						tmp->prev->next = NULL;
						(*lista)->last = tmp->prev;
					}else{
						tmp->next->prev = tmp->prev;
						tmp->prev->next = tmp->next;
					}
				}else{
                    tmp = tmp->next;
				}
			}
		}
	}
	free(tmp);
}
lista::nodoP *MOUNT::buscar_id(objetos::UNMOUNT unmount, lista::nodoC *pivote){
	lista::nodoP *tmp;
	if(pivote != NULL){
		do{
			tmp = pivote->particiones->first;
			if(tmp != NULL){
				do{
                    if(strcmp(tmp->id, unmount.id) == 0){
                        return tmp;
                    }
                    else{
						tmp = tmp->next;
                    }
				}while(tmp != NULL);
				pivote = pivote->next;
			}
		}while(pivote != NULL);
	}
	return NULL;
}
void MOUNT::ejecutarU(lista::list *listx, objetos::UNMOUNT unmount){
	char ans[2] = {0};
	char character = unmount.id[3];
	int valor = character;
	char id[10] = {0};
	strcpy(id, unmount.id);
	lista::nodoC *tmp = buscarLetra(valor, listx->first);
	if(tmp != NULL){
		lista::nodoP *particion = buscar_id(unmount, listx->first);
		if(particion != NULL){
			eliminarP(&(tmp->particiones), unmount, tmp);
			mostrar(listx->first);
		}
	}
}
lista::nodoC *MOUNT::buscarLetra(int letra, lista::nodoC *pivote){
	if(pivote == NULL){
		return NULL;
	}
	while(pivote != NULL){
		if(pivote->character == letra)
			return pivote;
		pivote = pivote->next;
	}
	return NULL;
}
lista::nodoP *MOUNT::buscar_id(objetos::REP rep, lista::nodoC *pivote){
	lista::nodoP *tmp;
	if(pivote != NULL){
		do{
			tmp = pivote->particiones->first;
			if(tmp != NULL){
				do{
					if(strcmp(tmp->id, rep.id) == 0)
						return tmp;
					tmp = tmp->next;
				}while(tmp != NULL);
				pivote = pivote->next;
			}
		}while(pivote != NULL);
	}
	return NULL;
}
lista::nodoP *MOUNT::buscarExistente(char *id, lista::nodoC *pivote){
	lista::nodoP *tmp;
	if(pivote != NULL){
		do{
			tmp = pivote->particiones->first;
			if(tmp != NULL){
				do{
					if(strcmp(tmp->id, id) == 0)
						return tmp;
					tmp = tmp->next;
				}while(tmp != NULL);
				pivote = pivote->next;
			}
		}while(pivote != NULL);
	}
	return NULL;
}
void MOUNT::eliminarName(lista::listaParticiones **lista, char nombre[], lista::nodoC *pivote){
	lista::nodoP *tmp = pivote->particiones->first;
	if(tmp == NULL){
		cout << "Error, no existen particiones en el disco" << endl;
	}else{
        if((*lista)->size == 1){
			(*lista)->first = NULL;
			(*lista)->last = NULL;
			pivote->particiones->first = NULL;
			free(tmp);
			return;
		}else{
			while(tmp != NULL){
				if(strcmp(tmp->name, nombre) == 0){
					if(tmp == (*lista)->first){
						tmp->next->prev = NULL;
						(*lista)->first = tmp->next;
						free(tmp);
						return;
					}else if(tmp == (*lista)->last){
						tmp->prev->next = NULL;
						(*lista)->last = tmp->prev;
						free(tmp);
						return;
					}else{
						tmp->next->prev = tmp->prev;
						tmp->prev->next = tmp->next;
						free(tmp);
						return;
					}
				}else{
					tmp = tmp->next;
				}
			}
		}
	}
}
