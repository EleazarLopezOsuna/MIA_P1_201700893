#include "LOGIN.h"

LOGIN::LOGIN()
{
    memset(user, 0, 15);
    memset(pwd, 0, 15);
    memset(id, 0, 10);
    par_id = false;
    par_pass = false;
    par_user = false;
}
void LOGIN::Logearse(LOGIN *disco){
    cout << "Datos del usuario" << endl;
    cout << "El id es: " << disco->id << endl;
    cout << "Usuario: " << disco->usuario << endl;
}
void LOGIN::limpiar(){
    memset(user, 0, 15);
    memset(pwd, 0, 15);
    memset(id, 0, 10);
    par_id = false;
    par_pass = false;
    par_user = false;
    try {
        memset(usuario->user, 0, 15);
        usuario->grupo=-1;
        usuario->estado=-1;
        memset(usuario->ruta_disco, 0, 50);
        memset(usuario->particion, 0, 50);

    } catch (int e) {
    }
}
objetos::superBloque LOGIN::obtener_SuperBlock(FILE * archivo_disco, char * name){
    fs * sistema = new fs();
    objetos::superBloque super_bloque = sistema->newSuperBloque();
    int pos_part = -1;
    objetos::MBR mbr;
    fseek(archivo_disco,0,SEEK_SET);
    fread(&mbr,sizeof(objetos::MBR),1,archivo_disco);
    //Obtengo la particion donde se formateara el sistema de archivos.
    for(int i=0; i<4; i++){
        if(strcmp(mbr.mbr_partitions[i].part_name, name)==0){
            pos_part = i;
            break;
        }
    }
    if(pos_part != -1){
        int inicio_particion = mbr.mbr_partitions[pos_part].part_start;
        fseek(archivo_disco,inicio_particion,SEEK_SET);
        fread(&super_bloque,sizeof(objetos::superBloque),1,archivo_disco);
    }
    return super_bloque;
}
void LOGIN::ejecutar_LOGIN(lista::list * lista , objetos::activeUser * usuario){
    if(usuario->estado !=-1){
        cout << "Error, ya existe una sesion iniciada" << endl;
        return;
    }
    //variables temporales de disco y particion
    char diskLOG[250]; //Disco en el que está la partición
    char partLOG[250]; //Partición en la que se inició sesión
    memset(diskLOG, 0, sizeof (diskLOG));
    memset(partLOG, 0, sizeof (partLOG));
    //Verificar si la partición está montada
    int idMountCorrecto = 0;
    int long_id = strlen(id);
    int letra = id[3];
    MOUNT * nuevo;
    lista::nodoC * disco_montado = nuevo->buscarLetra(letra, lista->first); //busca la lista del particiones del disco
    if(disco_montado != NULL){
        lista::nodoP * particion= nuevo->buscarExistente(id, lista->first);
        if(particion!= NULL){
            FILE * archivo_disco = fopen(disco_montado->path, "rb+");
            if(archivo_disco != NULL){
                objetos::superBloque super_bloque = obtener_SuperBlock(archivo_disco, particion->name);
                if(super_bloque.s_magic == 61267){ //indica que el sistema no se ha crasheado
                    //verifico que no exista ningun usuario logeado en el sistema.
                        if(strcmp(user, "root") == 0){
                            if(strcmp(pwd, "123") == 0){
                                strcpy(usuario->user, user);
                                usuario->grupo = 1;
                                usuario->estado = 1;
                                usuario->id_usuario = 1;
                                strcpy(usuario->particion,particion->id);
                                strcpy(usuario->ruta_disco,disco_montado->path);
                                strcpy(usuario->user,user);
                            }else{
                                cout << "Error, Contraseña incorrecta" << endl;
                            }
                        }else{
                            // si no es root buscar el usuario
                            //OBTENIENDO inodo DEL ARCHIVO USERS
                            objetos::inodo *users = (objetos::inodo*) malloc(sizeof (objetos::inodo));
                            int posUser = super_bloque.s_inode_start + sizeof (objetos::inodo);
                            fseek(archivo_disco, posUser, SEEK_SET);
                            fread(users, sizeof (objetos::inodo), 1, archivo_disco);
                            //OBTENIENDO TExTO DEL ARCHIVO
                            char Texto[14000];
                            strcpy(Texto, ObtenerTexto(archivo_disco, super_bloque, users));
                            char Text[14000];
                            strcpy(Text, strdup(Texto));
                            //ANALIZANDO  **********************************************************
                            int id = 0;
                            char tipo = 'A';
                            char nameGroup[11];
                            char nameUser[11];
                            char password[11];
                            int existe = 0;
                            int wrongPsw = 0;
                            char *end_str;
                            char *line = strtok_r(Text, "\n", &end_str);
                            int cont1=0;
                            int cont2=0;
                            int contador_usuarios=0;
                            while (line != NULL) {
                                cont1++;
                                char *end_token;
                                char *token = strtok_r(line, ",", &end_token);
                                while (token != NULL) {
                                    cont2++;
                                    //Limpiando variables
                                    id = 0;
                                    tipo = 'A';
                                    memset(nameGroup, 0, sizeof (nameGroup));
                                    memset(nameUser, 0, sizeof (nameUser));
                                    memset(password, 0, sizeof (password));
                                    //Almacenando datos
                                    id = atoi(token);
                                    token = strtok_r(NULL, ",", &end_token);
                                    tipo = token[0];
                                    token = strtok_r(NULL, ",", &end_token);
                                    strcpy(nameGroup, token);
                                    token = strtok_r(NULL, ",", &end_token);
                                    if (tipo == 'U') {
                                        contador_usuarios++;
                                        strcpy(nameUser, token);
                                        if (strcmp(nameUser, user) == 0) {
                                            token = strtok_r(NULL, ",", &end_token);
                                            strcpy(password, token);
                                            strcpy(usuario->user,user);
                                            usuario->id_usuario=contador_usuarios;
                                            if (strcmp(password, pwd) == 0) {
                                                existe = 1;
                                                break;
                                             } else {
                                                wrongPsw = 1;
                                                break;
                                             }
                                        } else {
                                            token = strtok_r(NULL, ",", &end_token);
                                        }
                                        token = strtok_r(NULL, ",", &end_token);
                                    }
                                }
                                if (existe == 1) {
                                    break;
                                }
                                if (wrongPsw == 1) {
                                    break;
                                }
                                line = strtok_r(NULL, "\n", &end_str);
                            }
                            fclose(archivo_disco);
                            if (wrongPsw == 1) {
                                memset(diskLOG, 0, sizeof (diskLOG));
                                memset(partLOG, 0, sizeof (partLOG));
                                cout << "Error, Contraseña incorrecta" << endl;
                                return;
                            }
                            if (existe == 1) {
                                //Falta obtener el id del grupo
                                strcpy(Text, strdup(Texto));
                                int searchIdGroup = ObtenerIdGrupo(Text, nameGroup);
                                if (searchIdGroup != -1) {
                                    usuario->grupo = searchIdGroup;
                                    usuario->estado=1;
                                    strcpy(usuario->particion,particion->id);
                                    strcpy(usuario->ruta_disco,disco_montado->path);
                                    usuario = usuario;
                                    cout << "Sesion iniciada" << endl;
                                } else {
                                    memset(diskLOG, 0, sizeof (diskLOG));
                                    memset(partLOG, 0, sizeof (partLOG));
                                    cout << "Error, no se encontro el grupo" << endl;
                                    return;
                                }
                            } else {
                                memset(diskLOG, 0, sizeof (diskLOG));
                                memset(partLOG, 0, sizeof (partLOG));
                                cout << "Error, no existe el usuario" << endl;
                                return;
                        }
                        usuario = usuario;
                    }
                }else{
                    cout << "Error, hay error en el sistema" << endl;
                }
            }else{
                cout << "Error, no existe el disco" << endl;
            }
        }else{
            cout << "Error, no existe la particion" << endl;
        }
    }
}
char* LOGIN::ObtenerTexto(FILE *fp, objetos::superBloque super, objetos::inodo * node) {
    int contador = 0;
    char * Texto = (char*)malloc(64);
    memset(Texto, 0, 64);
    /* Apuntadores directos*/
    for (int i = 0; i < 12; i++) {
        if (node->block[i] != -1) {
            contador++;
            objetos::bloqueArchivo *B_file = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
            fseek(fp, super.s_block_start + (node->block[i] * sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
            fread(B_file, sizeof (objetos::bloqueArchivo), 1, fp); //Recupero el bloque de Archivo
            strcat(Texto, B_file->b_content);
        } else {
            return Texto;
        }
    }
    /*Apuntador Indirecto Simple*/
    if (node->block[12] != -1) { //Si está en uso
        //Leer el bloque
        objetos::bloqueApuntadores *B_pointer = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
        fseek(fp, super.s_block_start + (node->block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(B_pointer, sizeof (objetos::bloqueApuntadores), 1, fp);
        for (int i = 0; i < 16; i++) {
            if (B_pointer->b_pointers[i] != -1) {
                contador++;
                objetos::bloqueArchivo *B_file = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
                fseek(fp, super.s_block_start + (B_pointer->b_pointers[i] + sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
                fread(B_file, sizeof (objetos::bloqueArchivo), 1, fp); //Recupero el bloque de Archivo
                strcat(Texto, B_file->b_content);
            } else {
                return Texto;
            }
        }
    }
    return Texto;
}
int LOGIN::ObtenerIdGrupo(char texto[], char name[]) {
    int encontrado = 0;
    int id = 0;
    char tipo = 'A';
    char nameGroup[11];
    char *end_str;
    char *line = strtok_r(texto, "\n", &end_str);
    while (line != NULL) {
        char *end_token;
        char *token = strtok_r(line, ",", &end_token);
        while (token != NULL) {
            //Limpiando variables
            id = 0;
            tipo = 'A';
            memset(nameGroup, 0, sizeof (nameGroup));
            //Almacenando datos
            id = atoi(token);
            token = strtok_r(NULL, ",", &end_token);
            tipo = token[0];
            token = strtok_r(NULL, ",", &end_token);
            strcpy(nameGroup, token);
            token = strtok_r(NULL, ",", &end_token);
            if (tipo == 'U') {
                token = strtok_r(NULL, ",", &end_token);
                token = strtok_r(NULL, ",", &end_token);
            } else if (tipo == 'G') {
                if (strcmp(nameGroup, name) == 0) {
                    encontrado = 1;
                    break;
                }
            }
        }
        if (encontrado == 1) {
            break;
        }
        line = strtok_r(NULL, "\n", &end_str);
    }
    if (encontrado == 1) {
        return id;
    } else {
        return -1;
    }
}
