#include "RMGRP.h"

RMGRP::RMGRP()
{
    memset(nombre, 0, 10);
}
void RMGRP::limpar(){
    memset(nombre, 0, 10);
}
void RMGRP::ejecutar_RMGRP(objetos::activeUser * usuario, lista::list * lista){
    if(strcmp(usuario->user, "root") != 0){
        cout << "Error, no se tienen los permisos para eliminar grupos" << endl;
        return;
    }
    int letra = usuario->particion[3];
    MOUNT * nuevo;
    //busca la lista del particiones del disco
    lista::nodoC * disco_montado = nuevo->buscar_porLetra(letra, lista->primero);
    lista::nodoP * particion= nuevo->buscar_id_existente(usuario->particion, lista->primero);
    if(disco_montado !=NULL){
        FILE * archivo_disco = fopen(disco_montado->path, "rb+");
        if(archivo_disco != NULL){
            //obtener el mbr del disco
            objetos::MBR  mbr ;
            fseek(archivo_disco, 0, SEEK_SET);
            fread(&mbr, sizeof (objetos::MBR), 1, archivo_disco);
            //buscar particion en el mbr
            int num_particion=-1;
            for(int i=0;i<4;i++){
                if(strcmp(mbr.mbr_particion[i].part_name,particion->name)==0){
                   num_particion=i;
                   break;
                }
            }
            //obtener super bloque
            objetos::superBloque super_bloque;
            fseek(archivo_disco, mbr.mbr_particion[num_particion].part_start, SEEK_SET);
            fread(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            //OBTENIENDO inodo DE ARCHIVO USERS
            objetos::inodo *users = (objetos::inodo*) malloc(sizeof (objetos::inodo));
            int posUser = super_bloque.s_inode_start + sizeof (objetos::inodo); //Posición del inodo de users (siempre será el segundo)
            fseek(archivo_disco, posUser, SEEK_SET);
            fread(users, sizeof (objetos::inodo), 1, archivo_disco);
            //PARA USAR METODOS DEL FILE_SYSTEM
            fs * sis = new fs();
            LOGIN * n_log = new LOGIN();
            //OBTENIENDO TExTO DEL ARCHIVO y ANALIZANDO
            char Texto[14000];
            memset(Texto, 0, sizeof (Texto));
            strcpy(Texto, n_log->ObtenerTexto(archivo_disco, super_bloque, users));
            //Auxiliar en donde se irá concatenando el nuevo texto
            char Text[14000];
            memset(Text, 0, sizeof (Text));
            //Variables
            int id = 0;
            char tipo = 'A';
            char nameGroup[11];
            char nameUser[11];
            int existe = 0;
            char lineGroup[20];
            char lineUser[40];
            //SPLIT
            char *end_str;
            char *line = strtok_r(Texto, "\n", &end_str);
            while (line != NULL) {
                if (existe == 1) { //Si ya se encontro que vaya concatenando el resto de líneas
                    strcat(Text, line);
                    strcat(Text, "\n");
                } else {
                    char *end_token;
                    char *token = strtok_r(line, ",", &end_token);
                    while (token != NULL) {
                        id = 0;
                        tipo = 'A';
                        memset(nameGroup, 0, sizeof (nameGroup));
                        memset(nameUser, 0, sizeof (nameUser));
                        memset(lineGroup, 0, sizeof (lineGroup));
                        memset(lineUser, 0, sizeof (lineUser));
                        //Almacenando
                        id = atoi(token);
                        token = strtok_r(NULL, ",", &end_token);
                        tipo = token[0];
                        token = strtok_r(NULL, ",", &end_token);
                        strcpy(nameGroup, token);
                        token = strtok_r(NULL, ",", &end_token);
                        if (tipo == 'U') {
                            //Solo nos interesan los grupos
                            sprintf(lineUser, "%d", id);
                            strcat(lineUser, ",U,");
                            strcat(lineUser, nameGroup);
                            strcat(lineUser, ",");
                            strcat(lineUser, token);
                            strcat(lineUser, ",");
                            token = strtok_r(NULL, ",", &end_token);
                            strcat(lineUser, token);
                            strcat(lineUser, "\n");
                            strcat(Text, lineUser);
                            token = strtok_r(NULL, ",", &end_token);
                        } else if (tipo == 'G') {
                            if (strcmp(nameGroup, nombre) == 0) {
                                if (id == 0) {
                                    existe = -1;
                                } else {
                                    id = 0;
                                    existe = 1;
                                }
                            }
                            //Concatenar de nuevo la línea para no perderla
                            sprintf(lineGroup, "%d", id);
                            strcat(lineGroup, ",G,");
                            strcat(lineGroup, nameGroup);
                            strcat(lineGroup, "\n");
                            strcat(Text, lineGroup);
                        }
                    }
                }
                line = strtok_r(NULL, "\n", &end_str);
            }
            //ESCRIBIR
            sis->EscribirTexto(archivo_disco, super_bloque, users, Text);
            //ACTUALIZAR inodo
            fseek(archivo_disco, posUser, SEEK_SET);
            fwrite(users, sizeof (objetos::inodo), 1, archivo_disco);
            //Actualizar Super Bloque
            fseek(archivo_disco, mbr.mbr_particion[num_particion].part_start, SEEK_SET);
            fwrite(&super_bloque, sizeof (super_bloque), 1, archivo_disco);
            //Verificar si operación fue existosa
            if (existe == 1) {
                //*** crear journalin
                //--------------------------------- obtengo la posicion del journal
                int posjournal =-1;
                int posicion = mbr.mbr_particion[num_particion].part_start + sizeof (super_bloque);
                int a=0;
                for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::journal)) {
                    objetos::journal j;
                    fseek(archivo_disco, i, SEEK_SET);
                    fread(&j, sizeof (objetos::journal), 1, archivo_disco);
                    a++;
                    if (j.estado =='0') {
                        posjournal =i ;
                        break;
                    }
                }
                //--------------------------------
                if(posjournal == -1){
                    cout << "Error, no se pudo escribir el journal" << endl;
                }else{
                    char comando[256];
                    strcpy(comando,"RMGRP -name=");
                    strcat(comando,nombre);
                    objetos::journal * journal = (objetos::journal*)malloc(sizeof (objetos::journal));
                    journal = sis->CrearJornal(usuario->user,comando);
                    journal->estado ='1';
                    fseek(archivo_disco, posjournal, SEEK_SET);
                    fwrite(journal, sizeof (objetos::journal), 1, archivo_disco);
                }
            } else if (existe == -1) {
               cout << "Error, el usuario ya fue eliminado" << endl;
            } else if (existe == 0) {
               cout << "Error, el usuario no existe" << endl
            }
            fclose(archivo_disco);
        }else{
            cout << "Error, no se pudo leer el disco" << endl;
        }
    }else {
        cout << "Error, la particion no esta montada" << endl;
        return;
    }
}