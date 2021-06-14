#include "CAT.h"

CAT::CAT(){
    memset(ruta,0,256);
}
void CAT::Mostrar(CAT*file){

}
void CAT::ejecutar_CAT(lista::list * lista , objetos::activeUser * usuario) {
    int logueado=0;
    int grupoLogueado =-1;
    if(usuario->estado == -1){
        cout << "Error, no hay una sesion iniciada" << endl;
        return;
    }else{
        logueado = usuario->id_usuario;
        grupoLogueado = usuario->grupo;
    }
    int letra = usuario->particion[3];
    MOUNT * nuevo;
    //busca la lista del particiones del disco
    lista::nodoC * disco_montado = nuevo->buscarLetra(letra, lista->first);
    lista::nodoP * particion= nuevo->buscarExistente(usuario->particion, lista->first);
    if(disco_montado !=NULL){
        FILE * archivo_disco = fopen(disco_montado->path, "rb+");
        if(archivo_disco != NULL){
            //obtener el mbr del disco
            objetos::MBR  mbr  ;
            fseek(archivo_disco, 0, SEEK_SET);
            fread(&mbr, sizeof (objetos::MBR), 1, archivo_disco);
            //buscar particion en el mbr
            int num_particion=-1;
            for(int i=0;i<4;i++){
                if(strcmp(mbr.mbr_partitions[i].part_name,particion->name)==0){
                    num_particion=i;
                    break;
                }
            }
            //obtener super bloque
            int posicion_super=mbr.mbr_partitions[num_particion].part_start;
            objetos::superBloque  super_bloque ;
            fseek(archivo_disco, posicion_super, SEEK_SET);
            fread(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            if(super_bloque.s_magic == 61267){ // asegurando que si se este leyendo bien

            }else{
                cout << "No se encontro el super bloque" << endl;
                return;
            }
            //*** ejecucion del CAT
            MKDIR * mkdr = new MKDIR();
            fs * sis = new fs();
            objetos::inodo father ;
            int inode_position;
            int n = mkdr->ContadorBarras(ruta);
            if (n == 1) {
                //Recuperar Inodo padre
                inode_position = super_bloque.s_inode_start;
                fseek(archivo_disco, inode_position, SEEK_SET);
                fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
            } else {
                MKDIR::Lista ruta[n - 1];
                for (int i = 0; i < n - 1; i++) {
                    memset(ruta[i].carpeta, 0, sizeof (ruta[i].carpeta));
                }
                int longPath = strlen(this->ruta);
                int k = -1;
                int contador = 0;
                for (int i = 0; i < longPath; i++) {
                    if (this->ruta[i] == '/') {
                        contador++;
                        k++;
                        if (contador == n) {
                            break;
                        }
                    } else {
                        strcpy(ruta[k].carpeta, mkdr->Concatenar(ruta[k].carpeta, this->ruta[i]));
                    }
                }
                //Busqueda de la ruta
                inode_position = mkdr->BusquedaCarpeta(archivo_disco, super_bloque, super_bloque.s_inode_start, ruta, n - 1, 0);
                    if (inode_position == 0) {
                        cout << "Error, la ruta no existe" << endl;
                        return;
                    } else {
                        //Recuperar Inodo padre
                        fseek(archivo_disco, inode_position, SEEK_SET);
                        fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
                    }
            }
            //Obtener el Inodo del archivo
            char ts1[300];
            memset(ts1, 0, sizeof (ts1));
            strcpy(ts1, strdup(ruta));
            char filename[50];
            memset(filename, 0, sizeof (filename));
            //obtener el nombre de archivo o carpeta
            strcpy(filename, basename(ts1));
            int pos_object = sis->ExisteInodo(super_bloque, inode_position, filename,archivo_disco);
            if (pos_object != -1) {
                //Inodo de archivo
                objetos::inodo inodoArchivo;
                fseek(archivo_disco, pos_object, SEEK_SET);
                fread(&inodoArchivo, sizeof (objetos::inodo), 1, archivo_disco);
                //Verficar si usuario logueado tiene permisos de lectura
                int puede = 0;
                if (logueado != 1) {
                    char buffer[7];
                    memset(buffer, 0, sizeof (buffer));
                    sprintf(buffer, "%d", inodoArchivo.i_perm);
                    if (buffer[0] == '4' || buffer[0] == '5' || buffer[0] == '6' || buffer[0] == '7') {
                        puede = 1;
                    }
                } else {
                    puede = 1; //Si es root si puede hacer los cambios
                }
                if (puede == 1) {
                    cout << "El contenido del archivo es: " << endl;
                    cout << sis->ObtenerTexto(archivo_disco, super_bloque, inodoArchivo) << endl;
                    fclose(archivo_disco);
                } else {
                    cout << "Error, el usuario no tiene permisos" << endl;
                    fclose(archivo_disco);
                }
            } else {
                cout << "Error, el archivo no existe" << endl;
            }
        }else{
            cout << "Error, no se pudo leer el disco" << endl;
        }
    }else{
        cout << "Error, la particion no esta montada" << endl;
    }
}
