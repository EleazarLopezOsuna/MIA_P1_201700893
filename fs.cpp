#include "fs.h"
#include <stdio.h>
#include <string.h>
fs::fs()
{
    crear = contador = 0;
}
int fs::RecursivisdadCHOWN(objetos::superBloque superBlo, int pos_inodo, char *nombre, FILE *file_disco,int ugo,lista::list * lista , objetos::activeUser * usuario)  {
    objetos::inodo root ;
    fseek(file_disco, pos_inodo, SEEK_SET);
    fread(&root, sizeof (objetos::inodo), 1, file_disco);
    int inicio;
    /***********************     APUNTADORES DIRECTOS     ************************/
    for (int i = 0; i < 12; i++) {
        if (root.block[i] != -1) {
            objetos::bloqueCarpeta folder_block ;
            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
            if (i == 0) {
                inicio = 2;
            } else {
                inicio = 0;
            }
            for (int j = inicio; j < 4; j++) {
                if (folder_block.b_content[j].b_inodo != -1) {
                    int inode = superBlo.s_inode_start + (folder_block.b_content[j].b_inodo * sizeof (objetos::inodo));
                    string res = folder_block.b_content[j].b_name;
                    int pos = res.find(".");
                    objetos::inodo *inodo = (objetos::inodo*)malloc(sizeof (objetos::inodo));
                    fseek(file_disco, inode, SEEK_SET);
                    fread(inodo,sizeof (objetos::inodo),1,file_disco);
                    if(pos != -1){
                        //archivo
                        //cambiando permisos
                        int logueado = 0;
                        int grupoLogueado = -1;
                        logueado = usuario->id_usuario;
                        grupoLogueado = usuario->grupo;
                        int puede = 0;
                        if (logueado != 1) {
                            char buffer[7];
                            memset(buffer, 0, sizeof (buffer));
                            sprintf(buffer, "%d", inodo->i_perm);
                            puede = calcularPermisos(buffer);
                        } else {
                            puede = 1; //Si es root si puede hacer los cambios
                        }
                        if(puede = 1){
                            inodo->i_uid = ugo;
                             fseek(file_disco, inode, SEEK_SET);
                             fwrite(inodo,sizeof (objetos::inodo),1,file_disco);
                        }else{
                            cout << "Error, el uusario no tiene los permisos" << endl;
                            continue;
                        }
                    }else{
                        //carpeta
                        int logueado = 0;
                        int grupoLogueado = -1;
                        logueado = usuario->id_usuario;
                        grupoLogueado = usuario->grupo;
                        int puede = 0;
                        if (logueado != 1) {
                            char buffer[7];
                            memset(buffer, 0, sizeof (buffer));
                            sprintf(buffer, "%d", inodo->i_perm);
                            puede = calcularPermisos(buffer);
                        } else {
                            puede = 1; //Si es root si puede hacer los cambios
                        }
                        if(puede = 1){
                            inodo->i_uid = ugo;
                             fseek(file_disco, inode, SEEK_SET);
                             fwrite(inodo,sizeof (objetos::inodo),1,file_disco);
                        }else{
                            cout << "Error, el uusario no tiene los permisos" << endl;
                            continue;
                        }
                        RecursivisdadCHOWN(superBlo,inode,nombre,file_disco,ugo,lista,usuario);
                    }
                }else{
                    break;
                }
            }
        }
    }
    /***********************   APUNTADOR INDIRECTO SIMPLE    **********************/
    if (root.block[12] != -1) {
        //Obtener el bloque de apuntadores
        objetos::bloqueApuntadores pointer_block ;
        fseek(file_disco, superBlo.s_block_start + (root.block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(&pointer_block, sizeof (objetos::bloqueApuntadores), 1, file_disco);
        for (int i = 0; i < 16; i++) {
            if (pointer_block.b_pointers[i] != -1) {
                //Obtener el bloque de carpeta
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(file_disco, superBlo.s_block_start + (pointer_block.b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco);
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        int inode = superBlo.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo));
                        string res = folder_block->b_content[j].b_name;
                        int pos = res.find(".");
                        objetos::inodo *inodo = (objetos::inodo*)malloc(sizeof (objetos::inodo));
                        fseek(file_disco, inode, SEEK_SET);
                        fread(inodo,sizeof (objetos::inodo),1,file_disco);
                        if(pos != -1){
                            //archivo
                            //cambiando permisos
                            int logueado = 0;
                            int grupoLogueado = -1;
                            logueado = usuario->id_usuario;
                            grupoLogueado = usuario->grupo;
                            int puede = 0;
                            if (logueado != 1) {
                                char buffer[7];
                                memset(buffer, 0, sizeof (buffer));
                                sprintf(buffer, "%d", inodo->i_perm);
                                puede = calcularPermisos(buffer);
                            } else {
                                puede = 1; //Si es root si puede hacer los cambios
                            }
                            if(puede = 1){
                                inodo->i_uid = ugo;
                                 fseek(file_disco, inode, SEEK_SET);
                                 fwrite(inodo,sizeof (objetos::inodo),1,file_disco);
                            }else{
                                cout << "Error, el uusario no tiene los permisos" << endl;
                                continue;
                            }
                        }else{
                            //carpeta
                            int logueado = 0;
                            int grupoLogueado = -1;
                            logueado = usuario->id_usuario;
                            grupoLogueado = usuario->grupo;
                            int puede = 0;
                            if (logueado != 1) {
                                char buffer[7];
                                memset(buffer, 0, sizeof (buffer));
                                sprintf(buffer, "%d", inodo->i_perm);
                                puede = calcularPermisos(buffer);
                            } else {
                                puede = 1; //Si es root si puede hacer los cambios
                            }
                            if(puede = 1){
                                inodo->i_uid = ugo;
                                 fseek(file_disco, inode, SEEK_SET);
                                 fwrite(inodo,sizeof (objetos::inodo),1,file_disco);
                            }else{
                                cout << "Error, el uusario no tiene los permisos" << endl;
                                continue;
                            }
                            RecursivisdadCHOWN(superBlo,inode,nombre,file_disco,ugo,lista,usuario);
                        }
                    }else{
                        break;
                    }
                }
            }
        }
    }
    return -1;
}
void fs::ActualizarBitmap(FILE *archivo, int posicion, char estado) {
    objetos::bitmap *bip = (objetos::bitmap*) malloc(sizeof (objetos::bitmap));
    fseek(archivo, posicion, SEEK_SET);
    fread(bip, sizeof (objetos::bitmap), 1, archivo);
    bip->state = estado;
    fseek(archivo, posicion, SEEK_SET);
    fwrite(bip, sizeof (objetos::bitmap), 1, archivo);
}
int fs::RecursivisdadCHMOD(objetos::superBloque superBlo, int pos_inodo, char *nombre, FILE *file_disco, int ugo, lista::list * lista , objetos::activeUser * usuario)  {
    objetos::inodo root ;
    fseek(file_disco, pos_inodo, SEEK_SET);
    fread(&root, sizeof(objetos::inodo), 1, file_disco);
    int inicio;
    /***********************     APUNTADORES DIRECTOS     ************************/
    for (int i = 0; i < 12; i++) {
        if (root.block[i] != -1) {
            objetos::bloqueCarpeta folder_block ;
            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
            if (i == 0) {
                inicio = 2;
            } else {
                inicio = 0;
            }
            for (int j = inicio; j < 4; j++) {
                if (folder_block.b_content[j].b_inodo != -1) {
                    int inode = superBlo.s_inode_start + (folder_block.b_content[j].b_inodo * sizeof (objetos::inodo));
                    string res = folder_block.b_content[j].b_name;
                    int pos = res.find(".");
                    objetos::inodo *inodo = (objetos::inodo*)malloc(sizeof (objetos::inodo));
                    fseek(file_disco, inode, SEEK_SET);
                    fread(inodo, sizeof(objetos::inodo), 1, file_disco);
                    if(pos != -1){
                        //archivo
                        //cambiando permisos
                        int logueado = 0;
                        int grupoLogueado =-1;
                        logueado = usuario->id_usuario;
                        grupoLogueado = usuario->grupo;
                        int puede = 0;
                        if (logueado != 1) {
                            char buffer[7];
                            memset(buffer, 0, sizeof (buffer));
                            sprintf(buffer, "%d", inodo->i_perm);
                            puede = calcularPermisos(buffer);
                        } else {
                            puede = 1; //Si es root si puede hacer los cambios
                        }
                        if(puede = 1){
                            inodo->i_perm = ugo;
                            fseek(file_disco, inode, SEEK_SET);
                            fwrite(inodo,sizeof (objetos::inodo),1,file_disco);
                        }else{
                            cout << "Error, el uusario no tiene los permisos" << endl;
                            continue;
                        }
                    }else{
                        //carpeta
                        int logueado = 0;
                        int grupoLogueado =-1;
                        logueado = usuario->id_usuario;
                        grupoLogueado = usuario->grupo;
                        int puede = 0;
                        if (logueado != 1) {
                            char buffer[7];
                            memset(buffer, 0, sizeof (buffer));
                            sprintf(buffer, "%d", inodo->i_perm);
                            puede = calcularPermisos(buffer);
                        } else {
                            puede = 1; //Si es root si puede hacer los cambios
                        }
                        if(puede = 1){
                            inodo->i_perm = ugo;
                             fseek(file_disco, inode, SEEK_SET);
                             fwrite(inodo, sizeof(objetos::inodo), 1, file_disco);
                        }else{
                            cout << "Error, el uusario no tiene los permisos" << endl;
                            continue;
                        }
                        RecursivisdadCHMOD(superBlo,inode,nombre,file_disco,ugo,lista,usuario);
                    }
                }else{
                    break;
                }
            }
        }
    }
    /***********************   APUNTADOR INDIRECTO SIMPLE    **********************/
    if (root.block[12] != -1) {
        //Obtener el bloque de apuntadores
        objetos::bloqueApuntadores pointer_block ;
        fseek(file_disco, superBlo.s_block_start + (root.block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(&pointer_block, sizeof (objetos::bloqueApuntadores), 1, file_disco);
        for (int i = 0; i < 16; i++) {
            if (pointer_block.b_pointers[i] != -1) {
                //Obtener el bloque de carpeta
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(file_disco, superBlo.s_block_start + (pointer_block.b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco);
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        int inode = superBlo.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo));
                        string res = folder_block->b_content[j].b_name;
                        int pos = res.find(".");
                        objetos::inodo *inodo = (objetos::inodo*)malloc(sizeof (objetos::inodo));
                        fseek(file_disco, inode, SEEK_SET);
                        fread(inodo,sizeof (objetos::inodo),1,file_disco);
                        if(pos != -1){
                            //archivo
                            //cambiando permisos
                            int logueado = 0;
                            int grupoLogueado = -1;
                            logueado = usuario->id_usuario;
                            grupoLogueado = usuario->grupo;
                            int puede = 0;
                            if (logueado != 1) {
                                char buffer[7];
                                memset(buffer, 0, sizeof (buffer));
                                sprintf(buffer, "%d", inodo->i_perm);
                                puede = calcularPermisos(buffer);
                            } else {
                                puede = 1; //Si es root si puede hacer los cambios
                            }
                            if(puede = 1){
                                inodo->i_perm = ugo;
                                 fseek(file_disco, inode, SEEK_SET);
                                 fwrite(inodo,sizeof (objetos::inodo),1,file_disco);
                            }else{
                                cout << "Error, el uusario no tiene los permisos" << endl;
                                continue;
                            }
                        }else{
                            //carpeta
                            int logueado = 0;
                            int grupoLogueado = -1;
                            logueado = usuario->id_usuario;
                            grupoLogueado = usuario->grupo;
                            int puede = 0;
                            if (logueado != 1) {
                                char buffer[7];
                                memset(buffer, 0, sizeof (buffer));
                                sprintf(buffer, "%d", inodo->i_perm);
                                puede = calcularPermisos(buffer);
                            } else {
                                puede = 1; //Si es root si puede hacer los cambios
                            }
                            if(puede = 1){
                                inodo->i_perm = ugo;
                                 fseek(file_disco, inode, SEEK_SET);
                                 fwrite(inodo,sizeof (objetos::inodo),1,file_disco);
                            }else{
                                cout << "Error, el uusario no tiene los permisos" << endl;
                                continue;
                            }
                            RecursivisdadCHMOD(superBlo,inode,nombre,file_disco,ugo,lista,usuario);
                        }
                    }else{
                        break;
                    }
                }
            }
        }
    }
    return -1;
}
int fs::ObtenerNumeroBloque(objetos::superBloque super) {
    return (super.s_blocks_count - super.s_free_blocks_count);
}
int fs::ObtenerNumeroInodo(objetos::superBloque super) {
    return (super.s_inodes_count - super.s_free_inodes_count);
}
int fs::EliminarReferencia2(objetos::superBloque superBlo, int pos_inodo, char nombre[],FILE *file_disco,lista::list * lista , objetos::activeUser * usuario) {
    objetos::inodo root ;
    MKDIR *mk = new MKDIR();
    fseek(file_disco, pos_inodo, SEEK_SET);
    fread(&root, sizeof (objetos::inodo), 1, file_disco);
    int inicio;
    /***********************     APUNTADORES DIRECTOS     ************************/
    for (int i = 0; i < 12; i++) {
        if (root.block[i] != -1) {
            objetos::bloqueCarpeta folder_block ;
            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
            if (i == 0) {
                inicio = 2;
            } else {
                inicio = 0;
            }
            for (int j = inicio; j < 4; j++) {
                if (folder_block.b_content[j].b_inodo != -1) {
                    int inode = superBlo.s_inode_start + (folder_block.b_content[j].b_inodo * sizeof (objetos::inodo));
                    string res = folder_block.b_content[j].b_name;
                    //logica de direfenciar entre archivo y carpeta***********
                    int pos = res.find(".");
                    if(pos != -1){
                        //archivo
                        //obtener el contenido del archivo
                        objetos::inodo inodoArchivo;
                        fseek(file_disco, inode, SEEK_SET);
                        fread(&inodoArchivo, sizeof (objetos::inodo), 1, file_disco);
                        //CREAR ARCHIVO**************************************************************************
                        int logueado = 0;
                        int grupoLogueado = -1;
                        logueado = usuario->id_usuario;
                        grupoLogueado = usuario->grupo;
                        int puede = 0;
                        if (logueado != 1) {
                            char buffer[7];
                            memset(buffer, 0, sizeof (buffer));
                            sprintf(buffer, "%d", inodoArchivo.i_perm);
                            puede = calcularPermisos(buffer);
                        } else {
                            puede = 1; //Si es root si puede hacer los cambios
                        }
                        if(puede = 1){
                            //ELIMINAMOS
                            memset(folder_block.b_content[j].b_name,0,sizeof (folder_block.b_content[j].b_name));
                            folder_block.b_content[j].b_inodo = -1;
                            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                            fwrite(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
                            fseek(file_disco,inode,SEEK_SET);
                            fputc('0',file_disco);
                        }else{
                            continue;
                        }
                    }else {
                        //carpeta
                        objetos::inodo inodoArchivo;
                        fseek(file_disco, inode, SEEK_SET);
                        fread(&inodoArchivo, sizeof (objetos::inodo), 1, file_disco);
                        //CREAR ARCHIVO**************************************************************************
                        int logueado = 0;
                        int grupoLogueado =- 1;
                        logueado = usuario->id_usuario;
                        grupoLogueado = usuario->grupo;
                        int puede = 0;
                        if (logueado != 1) {
                            char buffer[7];
                            memset(buffer, 0, sizeof (buffer));
                            sprintf(buffer, "%d", inodoArchivo.i_perm);
                            puede = calcularPermisos(buffer);
                        } else {
                            puede = 1; //Si es root si puede hacer los cambios
                        }
                        if(puede = 1){
                            //ELIMINAMOS
                            EliminarReferencia(superBlo,inode,nombre,file_disco);
                        }else{
                            continue;
                        }
                        EliminarReferencia2(superBlo,inode,nombre,file_disco,lista,usuario);
                    }
                }
            }
        }
    }
    /***********************   APUNTADOR INDIRECTO SIMPLE    **********************/
    if (root.block[12] != -1) {
        //Obtener el bloque de apuntadores
        objetos::bloqueApuntadores pointer_block ;
        fseek(file_disco, superBlo.s_block_start + (root.block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(&pointer_block, sizeof (objetos::bloqueApuntadores), 1, file_disco);
        for (int i = 0; i < 16; i++) {
            if (pointer_block.b_pointers[i] != -1) {
                //Obtener el bloque de carpeta
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(file_disco, superBlo.s_block_start + (pointer_block.b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco);
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        int inode = superBlo.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo));
                        string res = folder_block->b_content[j].b_name;
                        //logica de direfenciar entre archivo y carpeta***********
                        int pos = res.find(".");
                        if(pos != -1){
                            //archivo
                            //obtener el contenido del archivo
                            objetos::inodo inodoArchivo;
                            fseek(file_disco, inode, SEEK_SET);
                            fread(&inodoArchivo, sizeof (objetos::inodo), 1, file_disco);
                            //Creando archivo
                            int logueado = 0;
                            int grupoLogueado =- 1;
                            logueado = usuario->id_usuario;
                            grupoLogueado = usuario->grupo;
                            int puede = 0;
                            if (logueado != 1) {
                                char buffer[7];
                                memset(buffer, 0, sizeof (buffer));
                                sprintf(buffer, "%d", inodoArchivo.i_perm);
                                puede = calcularPermisos(buffer);
                            } else {
                                puede = 1; //Si es root si puede hacer los cambios
                            }
                             if(puede = 1){
                                //ELIMINAMOS
                                memset(folder_block->b_content[j].b_name,0,sizeof (folder_block->b_content[j].b_name));
                                folder_block->b_content[j].b_inodo = -1;
                                fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                                fwrite(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
                                fseek(file_disco,inode,SEEK_SET);
                                fputc('0',file_disco);
                             }else{
                                 continue;
                             }
                        }else {
                            //carpeta
                            objetos::inodo inodoArchivo;
                            fseek(file_disco, inode, SEEK_SET);
                            fread(&inodoArchivo, sizeof (objetos::inodo), 1, file_disco);
                            //CREAR ARCHIVO**************************************************************************
                            int logueado = 0;
                            int grupoLogueado = -1;
                            logueado = usuario->id_usuario;
                            grupoLogueado = usuario->grupo;
                            int puede = 0;
                            if (logueado != 1) {
                                char buffer[7];
                                memset(buffer, 0, sizeof (buffer));
                                sprintf(buffer, "%d", inodoArchivo.i_perm);
                                puede = calcularPermisos(buffer);
                            } else {
                                puede = 1; //Si es root si puede hacer los cambios
                            }
                            if(puede = 1){
                                //ELIMINAMOS
                                EliminarReferencia(superBlo,inode,nombre,file_disco);

                            }else{
                                continue;
                            }
                            EliminarReferencia2(superBlo,inode,nombre,file_disco,lista,usuario);
                        }
                    }
                }
            }
        }
    }
    return -1;
}
objetos::inodo fs::Crear_Inodo(){
    objetos::inodo inodo ;
    inodo.i_uid = inodo.i_gid = inodo.i_type = inodo.i_perm = -1;
    inodo.i_size = 0;
    time_t mytime;
    mytime = time(0);
    inodo.i_ctime = inodo.i_atime = inodo.i_mtime = mytime;
    for(int i = 0; i < 15; i++){
        inodo.block[i] = -1;
    }
    return inodo;
}
int fs::EliminarReferencia(objetos::superBloque  superBlo, int pos_inodo, char nombre[],FILE *file_disco) {
    objetos::inodo root ;
    fseek(file_disco, pos_inodo, SEEK_SET);
    fread(&root, sizeof (objetos::inodo), 1, file_disco);
    int inicio;
    /***********************     APUNTADORES DIRECTOS     ************************/
    for (int i = 0; i < 12; i++) {
        if (root.block[i] != -1) {
            objetos::bloqueCarpeta folder_block ;
            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
            if (i == 0) {
                inicio = 2;
            } else {
                inicio = 0;
            }
            for (int j = inicio; j < 4; j++) {
                if (folder_block.b_content[j].b_inodo != -1) {
                    if (strcmp(folder_block.b_content[j].b_name, nombre) == 0) {
                         memset(folder_block.b_content[j].b_name,0,sizeof (folder_block.b_content[j].b_name));
                        folder_block.b_content[j].b_inodo = -1;
                        fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                        fwrite(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
                        //Retorna el inodo de la carpeta encontrada
                        return (superBlo.s_inode_start + (folder_block.b_content[j].b_inodo * sizeof (objetos::inodo)));
                    }
                }
            }
        }
    }
    /***********************   APUNTADOR INDIRECTO SIMPLE    **********************/
    if (root.block[12] != -1) {
        //Obtener el bloque de apuntadores
        objetos::bloqueApuntadores pointer_block ;
        fseek(file_disco, superBlo.s_block_start + (root.block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(&pointer_block, sizeof (objetos::bloqueApuntadores), 1, file_disco);
        for (int i = 0; i < 16; i++) {
            if (pointer_block.b_pointers[i] != -1) {
                //Obtener el bloque de carpeta
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(file_disco, superBlo.s_block_start + (pointer_block.b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco);
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        if (strcmp(folder_block->b_content[j].b_name, nombre) == 0) {
                            memset(folder_block->b_content[j].b_name,0,sizeof (folder_block->b_content[j].b_name));
                           folder_block->b_content[j].b_inodo = -1;
                           fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                           fwrite(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
                            return (superBlo.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)));
                        }
                    }
                }
            }
        }
    }
    return -1;
}
objetos::superBloque fs::newSuperBloque(){
    objetos::superBloque superBlo;
    superBlo.s_filesystem_type = superBlo.s_inodes_count = superBlo.s_blocks_count = -1;
    superBlo.s_free_blocks_count = superBlo.s_free_inodes_count = -1;
    superBlo.s_mtime = superBlo.s_umtime = time(NULL);
    superBlo.s_mnt_count = superBlo.s_magic = superBlo.s_inode_size = superBlo.s_block_size = -1;
    superBlo.s_first_ino = superBlo.s_first_blo = superBlo.s_bm_block_start = superBlo.s_bm_inode_start = -1;
    superBlo.s_inode_start = superBlo.s_block_start = -1;
    return superBlo;
}
int fs::ExisteInodo2(objetos::superBloque superBlo, int pos_inodo, char nombre[],FILE *file_disco,char rutaNueva[256],char rutaVieja[256],lista::list * lista , objetos::activeUser * usuario){
    objetos::inodo root ;
    MKDIR *mk = new MKDIR();
    fseek(file_disco, pos_inodo, SEEK_SET);
    fread(&root, sizeof (objetos::inodo), 1, file_disco);
    int inicio;
    /***********************     APUNTADORES DIRECTOS     ************************/
    for (int i = 0; i < 12; i++) {
        if (root.block[i] != -1) {
            objetos::bloqueCarpeta folder_block ;
            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
            if (i == 0) {
                inicio = 2;
            } else {
                inicio = 0;
            }
            for (int j = inicio; j < 4; j++) {
                if (folder_block.b_content[j].b_inodo != -1) {
                    int inode = superBlo.s_inode_start + (folder_block.b_content[j].b_inodo * sizeof (objetos::inodo));
                    string res = folder_block.b_content[j].b_name;
                    //logica de direfenciar entre archivo y carpeta***********
                    int pos = res.find(".");
                    if(pos != -1){
                        //archivo
                        string add = "/" + res;
                        char doc[add.length() + 1];
                        char aux[sizeof(rutaNueva)];
                        strcpy(aux,rutaNueva);
                        strcpy(doc,add.c_str());
                        strcat(aux,doc);//Ruta final
                        MKFILE *file = new MKFILE();
                        file->crear = 1;
                        file->par_ruta = true;
                        strcpy(file->ruta_nArchivo,aux);
                        char aux2[sizeof (rutaVieja)];
                        strcpy(aux2,rutaVieja);
                        strcat(aux2,doc);
                        //obtener el contenido del archivo
                        objetos::inodo inodoArchivo;
                        fseek(file_disco, inode, SEEK_SET);
                        fread(&inodoArchivo, sizeof (objetos::inodo), 1, file_disco);
                        char TxtEnChar[14000];
                        memset(TxtEnChar,'\0',256);
                        strcpy(TxtEnChar,ObtenerTexto(file_disco, superBlo, inodoArchivo));
                        //Creando el archivo
                        int logueado = 0;
                        int grupoLogueado = -1;
                        logueado = usuario->id_usuario;
                        grupoLogueado = usuario->grupo;
                        int puede = 0;
                        if (logueado != 1) {
                            char buffer[7];
                            memset(buffer, 0, sizeof (buffer));
                            sprintf(buffer, "%d", inodoArchivo.i_perm);
                            puede = calcularPermisos(buffer);
                        } else {
                            puede = 1; //Si es root si puede hacer los cambios
                        }
                        if(puede = 1){
                            //creamos el archivo
                            file->size = inodoArchivo.i_size;
                            file->ejecutar_MKFILE2(lista,usuario,TxtEnChar);
                            file->limpiar();
                        }else{
                            continue;
                        }
                        memset(aux,'\0',sizeof (rutaNueva));
                        memset(aux2,'\0',sizeof (rutaVieja));
                        memset(TxtEnChar,'\0',sizeof (TxtEnChar));
                    }else {
                        //carpeta
                        string add = "";
                        add.append("/");
                        add.append(res);
                        char doc[256];
                        strcpy(doc,add.c_str());
                        strcat(rutaNueva,doc);
                        strcat(rutaVieja,doc);
                        mk->ejecutar_MKDIR2(lista,usuario,rutaNueva);
                        ExisteInodo2(superBlo,inode,nombre,file_disco,rutaNueva,rutaVieja,lista,usuario);
                    }
                }
            }
        }
    }
    /***********************   APUNTADOR INDIRECTO SIMPLE    **********************/
    if (root.block[12] != -1) {
        //Obtener el bloque de apuntadores
        objetos::bloqueApuntadores pointer_block ;
        fseek(file_disco, superBlo.s_block_start + (root.block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(&pointer_block, sizeof (objetos::bloqueApuntadores), 1, file_disco);
        for (int i = 0; i < 16; i++) {
            if (pointer_block.b_pointers[i] != -1) {
                //Obtener el bloque de carpeta
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(file_disco, superBlo.s_block_start + (pointer_block.b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco);
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        int inode = superBlo.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo));
                        string res = folder_block->b_content[j].b_name;
                        //logica de direfenciar entre archivo y carpeta***********
                        int pos = res.find(".");
                        if(pos != -1){
                            //archivo
                            string add = "";
                            add.append("/");
                            add.append(res);
                            char doc[add.length()+1];
                            char aux[sizeof (rutaNueva)];
                            strcpy(aux,rutaNueva);
                            strcpy(doc,add.c_str());
                            strcat(aux,doc);//Ruta final
                            MKFILE *file = new MKFILE();
                            file->crear = 1;
                            file->par_ruta = true;
                            strcpy(file->ruta_nArchivo,aux);
                            char aux2[sizeof (rutaVieja)];
                            strcpy(aux2,rutaVieja);
                            strcat(aux2,doc);
                            //obtener el contenido del archivo
                            objetos::inodo inodoArchivo;
                            fseek(file_disco, inode, SEEK_SET);
                            fread(&inodoArchivo, sizeof (objetos::inodo), 1, file_disco);
                            char TxtEnChar[14000];
                            memset(TxtEnChar,'\0',256);
                            strcpy(TxtEnChar,ObtenerTexto(file_disco, superBlo, inodoArchivo));
                            //Creando archivo
                            int logueado = 0;
                            int grupoLogueado =-1;
                            logueado = usuario->id_usuario;
                            grupoLogueado = usuario->grupo;
                            int puede = 0;
                            if (logueado != 1) {
                                char buffer[7];
                                memset(buffer, 0, sizeof (buffer));
                                sprintf(buffer, "%d", inodoArchivo.i_perm);
                                puede = calcularPermisos(buffer);
                            } else {
                                puede = 1; //Si es root si puede hacer los cambios
                            }
                            if(puede = 1){
                                //creamos el archivo
                                file->size = inodoArchivo.i_size;
                                file->ejecutar_MKFILE2(lista,usuario,TxtEnChar);
                                file->limpiar();
                            }else{
                                continue;
                            }
                            memset(aux,'\0',sizeof (rutaNueva));
                            memset(aux2,'\0',sizeof (rutaVieja));
                            memset(TxtEnChar,'\0',sizeof (TxtEnChar));
                        }else {
                            //carpeta
                            string add = "";
                            add.append("/");
                            add.append(res);
                            char doc[256];
                            strcpy(doc,add.c_str());
                            strcat(rutaNueva,doc);//Ruta final
                            strcat(rutaVieja,doc);
                            mk->ejecutar_MKDIR2(lista,usuario,rutaNueva);
                            ExisteInodo2(superBlo,inode,nombre,file_disco,rutaNueva,rutaVieja,lista,usuario);
                        }
                    }
                }
            }
        }
    }
    return -1;
}
char * fs::Concatenar(char *param, char letra) {
    unsigned int size = strlen(param);
    char *palabra = (char*)malloc(size + 2);
    strcpy(palabra, param);
    palabra[size] = letra;
    palabra[size + 1] = '\0';
    return palabra;
}
void fs::EscribirTexto(FILE *fp, objetos::superBloque super, objetos::inodo *node, char text[]) {
        int longText = strlen(text);
        int contador, inicio;
        /*Apuntadores directos*/
        for (int n = 0; n < 12; n++) {
            if (node->block[n] != -1) {
                objetos::bloqueArchivo *B_file = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
                fseek(fp, super.s_block_start + (node->block[n] * sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
                fread(B_file, sizeof (objetos::bloqueArchivo), 1, fp); //Recupero el bloque de Archivo
                memset(B_file->b_content, 0, sizeof (B_file->b_content)); //Limpio el contenido
                if (inicio == longText) {
                    //Si ya terminó el texto y siguen nodos ocupados es porque se disminuyó contenido y hay que eliminar bloques
                    //Eliminar el bloque en el bitmap de bloques
                    int bipBloque = ((node->block[n] - super.s_block_start) / sizeof(objetos::bloqueArchivo));
                    int posBit = super.s_bm_block_start + (bipBloque * sizeof (objetos::bitmap));
                    ActualizarBitmap(fp, posBit, '0');
                    //Quitar referencia
                    node->block[n] = -1;
                } else {
                    int i;
                    for (i = inicio; i < longText; i++) {
                        if (contador != 63) {
                            strcpy(B_file->b_content, Concatenar(B_file->b_content, text[i]));
                            contador++;
                        } else {
                            inicio = i;
                            contador = 0;
                            break;
                        }
                    }
                    inicio = i;
                    //Escribiendo de nuevo
                    fseek(fp, super.s_block_start + (node->block[n] * sizeof (objetos::bloqueArchivo)), SEEK_SET);
                    fwrite(B_file, sizeof (objetos::bloqueArchivo), 1, fp);
                }
            } else { //No existe bloque
                if (inicio < longText) { //Aún falta texto por agregar
                    objetos::bloqueArchivo cont;
                    cont.b_content[0] = '\0';
                    int i;
                    for (i = inicio; i < longText; i++) {
                        if (contador != 63) {
                            strcpy(cont.b_content, Concatenar(cont.b_content, text[i]));
                            contador++;
                        } else {
                            inicio = i;
                            contador = 0;
                            break;
                        }
                    }
                    inicio = i;
                    //Escribiendo
                    fseek(fp, super.s_first_blo, SEEK_SET);
                    fwrite(&cont, sizeof (objetos::bloqueArchivo), 1, fp);
                    //Actualizando apuntador de inodo
                    node->block[n] = ObtenerNumeroBloque(super);
                    //Modificando Bitmap de Bloque
                    int bipBloque = ((super.s_first_blo - super.s_block_start) / sizeof(objetos::bloqueArchivo));
                    int posBit = super.s_bm_block_start + (bipBloque * sizeof (objetos::bitmap));
                    ActualizarBitmap(fp, posBit, 'A');
                    //Actualizando Super Bloque
                    super.s_first_blo = super.s_first_blo + sizeof (objetos::bloqueArchivo);
                    super.s_free_blocks_count--;
                    if (inicio == longText) {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
}
objetos::journal * fs::CrearJornal(char name[12], char op[256]){
    objetos::journal *j = (objetos::journal*) malloc(sizeof(objetos::journal));
    strcpy(j->user, name);
    strcpy(j->operacion, op);
    time_t mytime;
    mytime = time(NULL);
    j->hora = mytime;
    j->estado = '1';
    return j;
}
int fs::ExisteInodo(objetos::superBloque superBlo, int pos_inodo, char nombre[],FILE *file_disco) {
    objetos::inodo root ;
    fseek(file_disco, pos_inodo, SEEK_SET);
    fread(&root, sizeof (objetos::inodo), 1, file_disco);
    int inicio;
    /***********************     APUNTADORES DIRECTOS     ************************/
    for (int i = 0; i < 12; i++) {
        if (root.block[i] != -1) {
            objetos::bloqueCarpeta folder_block ;
            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
            if (i == 0) {
                inicio = 2;
            } else {
                inicio = 0;
            }
            for (int j = inicio; j < 4; j++) {
                if (folder_block.b_content[j].b_inodo != -1) {
                    if (strcmp(folder_block.b_content[j].b_name, nombre) == 0) {
                        return (superBlo.s_inode_start + (folder_block.b_content[j].b_inodo * sizeof (objetos::inodo)));
                    }
                }
            }
        }
    }
    /***********************   APUNTADOR INDIRECTO SIMPLE    **********************/
    if (root.block[12] != -1) {
        //Obtener el bloque de apuntadores
        objetos::bloqueApuntadores pointer_block ;
        fseek(file_disco, superBlo.s_block_start + (root.block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(&pointer_block, sizeof (objetos::bloqueApuntadores), 1, file_disco);
        for (int i = 0; i < 16; i++) {
            if (pointer_block.b_pointers[i] != -1) {
                //Obtener el bloque de carpeta
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(file_disco, superBlo.s_block_start + (pointer_block.b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco);
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        if (strcmp(folder_block->b_content[j].b_name, nombre) == 0) {
                            return (superBlo.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)));
                        }
                    }
                }
            }
        }
    }
    return -1;
}
int fs::CambiarNombre(objetos::superBloque superBlo, int pos_inodo, char nombre[],char nombrenuevo[],FILE *file_disco) {
    objetos::inodo root ;
    fseek(file_disco, pos_inodo, SEEK_SET);
    fread(&root, sizeof (objetos::inodo), 1, file_disco);
    int inicio;
    /***********************     APUNTADORES DIRECTOS     ************************/
    for (int i = 0; i < 12; i++) {
        if (root.block[i] != -1) {
            objetos::bloqueCarpeta folder_block ;
            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
            if (i == 0) {
                inicio = 2;
            } else {
                inicio = 0;
            }
            for (int j = inicio; j < 4; j++) {
                if (folder_block.b_content[j].b_inodo != -1) {
                    if (strcmp(folder_block.b_content[j].b_name, nombre) == 0) {
                        strcpy(folder_block.b_content[j].b_name,nombrenuevo);
                        fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                        fwrite(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
                        //Retorna el inodo de la carpeta encontrada
                        return (superBlo.s_inode_start + (folder_block.b_content[j].b_inodo * sizeof (objetos::inodo)));
                    }
                }
            }
        }
    }
    /***********************   APUNTADOR INDIRECTO SIMPLE    **********************/
    if (root.block[12] != -1) {
        //Obtener el bloque de apuntadores
        objetos::bloqueApuntadores pointer_block ;
        fseek(file_disco, superBlo.s_block_start + (root.block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(&pointer_block, sizeof (objetos::bloqueApuntadores), 1, file_disco);
        for (int i = 0; i < 16; i++) {
            if (pointer_block.b_pointers[i] != -1) {
                //Obtener el bloque de carpeta
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(file_disco, superBlo.s_block_start + (pointer_block.b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco);
                for (int j = 0; j < 4; j++) {
                    if (folder_block->b_content[j].b_inodo != -1) {
                        if (strcmp(folder_block->b_content[j].b_name, nombre) == 0) {
                            strcpy(folder_block->b_content[j].b_name,nombrenuevo);
                            fseek(file_disco, superBlo.s_block_start + (root.block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                            fwrite(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
                            return (superBlo.s_inode_start + (folder_block->b_content[j].b_inodo * sizeof (objetos::inodo)));
                        }
                    }
                }
            }
        }
    }
    return -1;
}
char* fs::ObtenerTexto(FILE *fp, objetos::superBloque super, objetos::inodo node) {
    int contador = 0;
    char *Texto = (char*)malloc(14000);
    /* Apuntadores directos*/
    for (int i = 0; i < 12; i++) {
        if (node.block[i] != -1) {
            contador++;
            objetos::bloqueArchivo *B_file = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
            fseek(fp, super.s_block_start + (node.block[i] * sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
            fread(B_file, sizeof (objetos::bloqueArchivo), 1, fp); //Recupero el bloque de Archivo
            strcat(Texto, B_file->b_content);
        } else {
            return Texto;
        }
    }
    /*Apuntador Indirecto Simple*/
    if (node.block[12] != -1) { //Si está en uso
        //Leer el bloque
        objetos::bloqueApuntadores *B_pointer = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
        fseek(fp, super.s_block_start + (node.block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
        fread(B_pointer, sizeof (objetos::bloqueApuntadores), 1, fp);
        for (int i = 0; i < 16; i++) {
            if (B_pointer->b_pointers[i] != -1) {
                contador++;
                objetos::bloqueArchivo B_file;
                fseek(fp, super.s_block_start + (B_pointer->b_pointers[i] + sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
                fread(&B_file, sizeof (objetos::bloqueArchivo), 1, fp); //Recupero el bloque de Archivo
                strcat(Texto, B_file.b_content);
            } else {
                return Texto;
            }
        }
    }
    return Texto;
}
int fs::calcularPermisos(char buffer[]) {
    switch(buffer[0]){
        case '4':
        case '5':
        case '6':
        case '7':
            return 1;
        default:
            return 0;
    }
}
int fs::PosBitmap(int inicio, int max, int tamanio) {
    int a = ((max - inicio) / tamanio);
    return a;
}
