#include "MKDIR.h"
MKDIR::MKDIR(){
    crear=0;
    memset(ruta_nuevaCarpeta,0,256);
    memset(ruta_carpeta, 0, 255);
    es_carpeta =1;
    par_path =-1;
    contador=0;
}
void MKDIR::limpiar(){
    crear=0;
    memset(ruta_nuevaCarpeta,0,256);
    memset(ruta_carpeta, 0, 255);
    es_carpeta =1;
    par_path =-1;
    contador=0;
}
void MKDIR::ejecutar_MKDIR(lista::list *lista, objetos::activeUser * usuario){
    int logueado=0;
    int grupoLogueado =-1;
    if(usuario->estado == -1){
        cout << "Error, no hay sesion iniciada" << endl;
        return;
    }
    //obtener la ruta de la carpeta y el nombre de la carpeta
    get_ruta(ruta_nuevaCarpeta);
    if(es_carpeta!=1){
       cout << "Error, ruta erronea" << endl;
       return;
    }
    char foldername[50];
    memset(foldername, 0, sizeof (foldername));
    strcpy(foldername, basename(ruta_nuevaCarpeta));
    int total = strlen(foldername);
    if (total > 10) {
       cout << "Error, el nombre es mayor a 10 caracteres" << endl;
       return;
    }
    int letra = usuario->particion[3];
    MOUNT * nuevo;
    //busca la lista del particiones del disco
    lista::nodoC * disco_montado = nuevo->buscar_porLetra(letra, lista->first);
    lista::nodoP * particion= nuevo->buscar_id_existente(usuario->particion, lista->first);
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
            if(super_bloque.s_magic == 61267){
            }else{
                cout << "Error, no se encontro el super bloque" << endl;
                return;
            }
            objetos::inodo father;
            int file_position;
            int n = ContadorBarras(ruta_nuevaCarpeta);
            //para usar los metodos de file system
            fs * sis = new fs();
            if (n == 1) {
                /* verificar que la carpeta no exista*/
                //Recuperar Inodo padre
                file_position = super_bloque.s_inode_start;
                fseek(archivo_disco, file_position, SEEK_SET);
                fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
            } else {
                Lista ruta[n - 1];
                //Limpiar
                for (int i = 0; i < n - 1; i++) {
                    memset(ruta[i].part_carpeta, 0, sizeof (ruta[i].part_carpeta));
                }
                int longPath = strlen(ruta_nuevaCarpeta);
                int k = -1;
                int contador = 0;
                for (int i = 0; i < longPath; i++) {
                    if (ruta_nuevaCarpeta[i] == '/') {
                        contador++;
                        k++;
                        if (contador == n) {
                            break;
                        }
                    } else {
                        strcpy(ruta[k].part_carpeta, Concatenar(ruta[k].part_carpeta, ruta_nuevaCarpeta[i]));
                    }
                }
                //BUSCAR RUTA
                file_position = BusquedaCarpeta(archivo_disco, super_bloque, super_bloque.s_inode_start, ruta, n - 1, 0);
                if (file_position == 0) { //La carpeta no existe
                    if (crear == 1) { //Se crea la ruta para crear la carpeta
                        int imposible=0;
                        int pos_inodo = super_bloque.s_inode_start; //Empezamos buscando desde la raíz.
                        for (int i = 0; i < n - 1; i++) {
                            int posicion = sis->ExisteInodo( super_bloque, pos_inodo, ruta[i].part_carpeta,archivo_disco);
                            if (posicion != -1) {
                                //REVISAR PERMISOS DE ESCRITURA EN LA CARPETA PADRE
                                objetos::inodo nuevofather;
                                fseek(archivo_disco, posicion, SEEK_SET);
                                fread(&nuevofather, sizeof (objetos::inodo), 1, archivo_disco);
                                int puede = 0;
                                if (logueado != 1) {
                                    char buffer[7];
                                    memset(buffer, 0, sizeof (buffer));
                                    sprintf(buffer, "%d", nuevofather.i_perm);
                                    //cout << "ESte es el buffer:"<<buffer;
                                    if (logueado == nuevofather.i_uid) { //Verificar permisos de propietario
                                        if (buffer[0] == 2 || buffer[0] == 3 || buffer[0] == 6 || buffer[0] == 7) {
                                            puede = 1;
                                        }
                                    } else if (grupoLogueado == nuevofather.i_gid) { //Verificar permisos de grupo
                                        if (buffer[1] == 2 || buffer[1] == 3 || buffer[1] == 6 || buffer[1] == 7) {
                                            puede = 1;
                                        }
                                    } else { //Verficar permisos de otros
                                        if (buffer[2] == 2 || buffer[2] == 3 || buffer[2] == 6 || buffer[2] == 7) {
                                            puede = 1;
                                        }
                                    }
                                } else {
                                    puede = 1; //Si es root si puede hacer los cambios
                                }
                                if (puede == 1) {
                                    pos_inodo = posicion;
                                } else {
                                    imposible = 1;
                                    break;
                                }
                            } else { //Hay que crearlo //************************************************
                                objetos::inodo nuevofather ;
                                fseek(archivo_disco, pos_inodo, SEEK_SET);
                                fread(&nuevofather, sizeof (objetos::inodo), 1, archivo_disco);
                                sb_aux = super_bloque;
                                father_aux = nuevofather;
                                int pos_nuevo = CrearInodoArchivo_Carpeta(archivo_disco, ruta[i].part_carpeta, '0', usuario->id_usuario, usuario->grupo,0);
                                super_bloque = sb_aux;
                                nuevofather = father_aux;
                                //Actualizar padre
                                fseek(archivo_disco, pos_inodo, SEEK_SET);
                                fwrite(&nuevofather, sizeof (objetos::inodo), 1, archivo_disco);
                                //Modificando bitmap de Inodo
                                int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
                                int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
                                sis->Actualizarbitmap(archivo_disco, posBit, '1');
                                //Actualizar super bloque
                                super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
                                super_bloque.s_free_inodes_count--;
                                pos_inodo = pos_nuevo;
                            }
                        }
                        if(imposible==1){
                            cout << "Error, el usuario no tiene permisos para escribir" << endl;
                            fclose(archivo_disco);
                            return;
                        }else{
                        file_position = pos_inodo;
                        fseek(archivo_disco, file_position, SEEK_SET);
                        fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
                        }
                    } else {
                        cout << "Error, la ruta no existe" << endl;
                        return;
                    }
                } else {
                    //RETORNA LA POCISIÓN DEL INODO QUE SERÁ LA CARPETA PADRE
                    //Recuperar Inodo
                    fseek(archivo_disco, file_position, SEEK_SET);
                    fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
                }
            }
            //Crear carpeta
            cout << "propietario inodopadre: "<<father.i_uid << endl;
            sb_aux = super_bloque;
            father_aux = father;
            CrearInodoArchivo_Carpeta(archivo_disco, foldername, '0', usuario->id_usuario, usuario->grupo,0);
            super_bloque = sb_aux;
            father = father_aux;
            //Actualiza padre
            fseek(archivo_disco, file_position, SEEK_SET);
            fwrite(&father, sizeof (objetos::inodo), 1, archivo_disco);
            //Modificando bitmap de Inodo/
            int inicio_inodos = super_bloque.s_bm_inode_start;
            int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
            int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
            fseek(archivo_disco, super_bloque.s_bm_inode_start, SEEK_SET);
            sis->Actualizarbitmap(archivo_disco, posBit, '1');
            fseek(archivo_disco, 0, SEEK_END);
            //Actualizar Super bloque
            super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
            super_bloque.s_free_inodes_count--;
            //Escribir super bloque
            fseek(archivo_disco, mbr.mbr_partitions[num_particion].part_start, SEEK_SET);
            fwrite(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            //actualizar el Journaling
            //--------------------------------- obtengo la posicion del journal
            int posJournal =-1;
            int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
            int a=0;
            for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::Journal)) {
                objetos::Journal j ;
                fseek(archivo_disco, i, SEEK_SET);
                fread(&j, sizeof (objetos::Journal), 1, archivo_disco);
                a++;
                if (j.estado =='0') {
                    posJournal =i ;
                    break;
                }
            }
            //--------------------------------
            if(posJournal == -1){
                cout << "Error, no se puede escribir en journal" << endl;
            }else{
                char comando[256];
                strcpy(comando,"MKDIR -path=");
                strcat(comando,ruta_nuevaCarpeta);
                if(crear==1){
                    strcat(comando," -p ");
                }
                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                journal = sis->CrearJornal(usuario->user,comando);
                fseek(archivo_disco, posJournal, SEEK_SET);
                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
            }
            fclose(archivo_disco);
        }else{
            cout << "Error, no se encontro el disco" << endl;
        }
    }else{
        cout << "Error, la particion no esta montada" << endl;
    }
}
void MKDIR::ejecutar_MKDIR2(lista::list *lista, objetos::activeUser * usuario,char rutaN[256]){
    int logueado=0;
    int grupoLogueado =-1;
    char foldername[500];
    memset(foldername, 0, sizeof (foldername));
    strcpy(foldername, basename(rutaN));
    int total = strlen(foldername);
    if (total > 10) {
        printf("ERROR: El nombre no puede ser mayor a 10 carácteres\n");
        return;
    }
    cout << "- nombre carpeta2: "<<foldername << endl;
    int letra = usuario->particion[3];
    MOUNT * nuevo;
    //busca la lista del particiones del disco
    lista::nodoC * disco_montado = nuevo->buscar_porLetra(letra, lista->first);
    lista::nodoP * particion= nuevo->buscar_id_existente(usuario->particion, lista->first);
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
            objetos::superBloque  super_bloque;
            fseek(archivo_disco, posicion_super, SEEK_SET);
            fread(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            if(super_bloque.s_magic == 61267){
            }else{
                cout << "Error, no se encontro el super bloque" << endl;
                return;
            }
            objetos::inodo father ;
            int file_position;
            int n = ContadorBarras(rutaN);
            //para usar los metodos de file system
            fs * sis = new fs();
            if (n == 1) {
                /* verificar que la carpeta no exista*/
                //Recuperar Inodo padre
                file_position = super_bloque.s_inode_start;
                fseek(archivo_disco, file_position, SEEK_SET);
                fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
            } else {
                Lista ruta[n - 1];
                //Limpiar
                for (int i = 0; i < n - 1; i++) {
                    memset(ruta[i].part_carpeta, 0, sizeof (ruta[i].part_carpeta));
                }
                int longPath = strlen(rutaN);
                int k = -1;
                int contador = 0;
                for (int i = 0; i < longPath; i++) {
                    if (rutaN[i] == '/') {
                        contador++;
                        k++;
                        if (contador == n) {
                            break;
                        }
                    } else {
                        strcpy(ruta[k].part_carpeta, Concatenar(ruta[k].part_carpeta, rutaN[i]));
                    }
                }
                //BUSCAR RUTA
                file_position = BusquedaCarpeta(archivo_disco, super_bloque, super_bloque.s_inode_start, ruta, n - 1, 0);
                if (file_position == 0) { //La carpeta no existe
                    if (crear == 1) { //Se crea la ruta para crear la carpeta
                        int imposible = 0;
                        int pos_inodo = super_bloque.s_inode_start; //Empezamos buscando desde la raíz.
                        for (int i = 0; i < n - 1; i++) {
                            int posicion = sis->ExisteInodo( super_bloque, pos_inodo, ruta[i].part_carpeta,archivo_disco);
                            if (posicion != -1) {
                                //REVISAR PERMISOS DE ESCRITURA EN LA CARPETA PADRE
                                objetos::inodo nuevofather;
                                fseek(archivo_disco, posicion, SEEK_SET);
                                fread(&nuevofather, sizeof (objetos::inodo), 1, archivo_disco);
                                int puede = 0;
                                if (logueado != 1) {
                                    char buffer[7];
                                    memset(buffer, 0, sizeof (buffer));
                                    sprintf(buffer, "%d", nuevofather.i_perm);
                                    cout << "ESte es el buffer:"<<buffer;
                                    if (logueado == nuevofather.i_uid) { //Verificar permisos de propietario
                                        if (buffer[0] == 2 || buffer[0] == 3 || buffer[0] == 6 || buffer[0] == 7) {
                                            puede = 1;
                                        }
                                    } else if (grupoLogueado == nuevofather.i_gid) { //Verificar permisos de grupo
                                        if (buffer[1] == 2 || buffer[1] == 3 || buffer[1] == 6 || buffer[1] == 7) {
                                            puede = 1;
                                        }
                                    } else { //Verficar permisos de otros
                                        if (buffer[2] == 2 || buffer[2] == 3 || buffer[2] == 6 || buffer[2] == 7) {
                                            puede = 1;
                                        }
                                    }
                                } else {
                                    puede = 1; //Si es root si puede hacer los cambios
                                }
                                if (puede == 1) {
                                    pos_inodo = posicion;
                                } else {
                                    imposible = 1;
                                    break;
                                }
                            } else { //Hay que crearlo //************************************************
                                objetos::inodo nuevofather ;
                                fseek(archivo_disco, pos_inodo, SEEK_SET);
                                fread(&nuevofather, sizeof (objetos::inodo), 1, archivo_disco);
                                sb_aux = super_bloque;
                                father_aux = nuevofather;
                                int pos_nuevo = CrearInodoArchivo_Carpeta(archivo_disco, ruta[i].part_carpeta, '0', usuario->id_usuario, usuario->grupo,0);
                                super_bloque = sb_aux;
                                nuevofather = father_aux;
                                //Actualizar padre
                                fseek(archivo_disco, pos_inodo, SEEK_SET);
                                fwrite(&nuevofather, sizeof (objetos::inodo), 1, archivo_disco);
                                //Modificando bitmap de Inodo
                                int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
                                int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
                                sis->Actualizarbitmap(archivo_disco, posBit, '1');
                                //Actualizar super bloque
                                super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
                                super_bloque.s_free_inodes_count--;
                                pos_inodo = pos_nuevo;
                            }
                        }
                        if(imposible==1){
                            cout << "Error, el usuario no cuenta con permisos para escribir" << endl;
                            fclose(archivo_disco);
                            return;
                        } else {
                            file_position = pos_inodo;
                            fseek(archivo_disco, file_position, SEEK_SET);
                            fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
                        }
                    } else {
                        cout << "Error, la ruta no existe" << endl;
                        return;
                    }
                } else {
                    //RETORNA LA POCISIÓN DEL INODO QUE SERÁ LA CARPETA PADRE
                    //Recuperar Inodo
                    fseek(archivo_disco, file_position, SEEK_SET);
                    fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
                }
            }
            //Crear carpeta
            sb_aux = super_bloque;
            father_aux = father;
            CrearInodoArchivo_Carpeta(archivo_disco, foldername, '0', usuario->id_usuario, usuario->grupo,0);
            super_bloque = sb_aux;
            father = father_aux;
            //Actualiza padre
            fseek(archivo_disco, file_position, SEEK_SET);
            fwrite(&father, sizeof (objetos::inodo), 1, archivo_disco);
            //Modificando bitmap de Inodo/
            int inicio_inodos = super_bloque.s_bm_inode_start;
            int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
            int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
            fseek(archivo_disco, super_bloque.s_bm_inode_start, SEEK_SET);
            sis->Actualizarbitmap(archivo_disco, posBit, '1');
            fseek(archivo_disco, 0, SEEK_END);
            //Actualizar Super bloque
            super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
            super_bloque.s_free_inodes_count--;
            //Escribir super bloque
            fseek(archivo_disco, mbr.mbr_partitions[num_particion].part_start, SEEK_SET);
            fwrite(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            //actualizar el Journaling
            //--------------------------------- obtengo la posicion del journal
            int posJournal =-1;
            int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
            int a=0;
            for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::Journal)) {
                objetos::Journal j ;
                fseek(archivo_disco, i, SEEK_SET);
                fread(&j, sizeof (objetos::Journal), 1, archivo_disco);
                a++;
                if (j.estado =='0') {
                    posJournal =i ;
                    break;
                }
            }
            //--------------------------------
            if(posJournal == -1){
                cout << "Error, no se pudo escribir el journal" << endl;
            }else{
                char comando[256];
                strcpy(comando,"MKDIR -path=");
                strcat(comando,rutaN);
                if(crear==1){
                    strcat(comando," -p ");
                }
                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                journal = sis->CrearJornal(usuario->user,comando);
                fseek(archivo_disco, posJournal, SEEK_SET);
                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
            }
            fclose(archivo_disco);
        }else{
            cout << "Error, no se encontro el disco" << endl;
        }
    }else{
        cout << "Error, la particion no esta montada" << endl;
    }
}
void MKDIR::get_ruta(char * path){
    int i=0;
    char caracter[2] = {0};
    char temp_path[500]={0};
    memset(caracter, 0, 2);
    memset(temp_path, 0, 500);
    while(path[i] != 0){
        caracter[0] = path[i];
        if(strcmp(caracter,"/")==0){
            strcat(temp_path, "/");
            strcat(ruta_carpeta, temp_path);
            memset(temp_path, 0, 500);
        }else if(strcmp(caracter,".")==0){
            es_carpeta =-1;
            break;
        }else{
            strcat(temp_path,caracter);
        }
        i++;
    }
    strcat(ruta_carpeta, temp_path);
}
int MKDIR::ContadorBarras(char *string) {
        int c = 0;
        while (*string) c += *(string++) == '/';
        return c;
}
char * MKDIR::Concatenar(char *param, char letra) {
    unsigned int size = strlen(param);
    char *palabra = (char*)malloc(size + 2); //tamaño + letra a concatenar + fin de string
    strcpy(palabra, param);
    palabra[size] = letra;
    palabra[size + 1] = '\0';
    return palabra;
}
int MKDIR::BusquedaCarpeta(FILE *fp, objetos::superBloque super, int posInodo, Lista ruta[], int n, int pos) {
    int i, j, encontrado = 0, inicio;
    objetos::inodo *root = (objetos::inodo*) malloc(sizeof (objetos::inodo));
    fseek(fp, posInodo, SEEK_SET);
    fread(root, sizeof (objetos::inodo), 1, fp);
    objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
    /*Apuntadores directos*/
    for (i = 0; i < 12; i++) {
        if (root->i_block[i] != -1) {
            fseek(fp, super.blocks_start + (root->i_block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
            fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, fp); //Recupero el bloque de Carpeta
            if (i == 0) {
                inicio = 2;
            } else {
                inicio = 0;
            }
            for (j = inicio; j < 4; j++) {
                if (folder_block->b_content[j].part_inodo != -1) {
                    if (strcmp(folder_block->b_content[j].part_name, ruta[pos].part_carpeta) == 0) {
                        encontrado = 1;
                        break;
                    }
                }
            }
            if (encontrado == 1) {
                break;
            }
        }
    }
    /************************************** apuntadores indirectos ************************/
    if(root->i_block[12]!=-1){
        //recuperar el bloque
        objetos::bloqueApuntadores * pointer_block = (objetos::bloqueApuntadores*) malloc(sizeof (objetos::bloqueApuntadores));
        fseek(fp, super.blocks_start + (root->i_block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET); //Me muevo al bloque de Carpeta
        fread(pointer_block, sizeof (objetos::bloqueApuntadores), 1, fp); //Recupero el bloque de Carpeta
        for(int j=0; j<16;j++){
            if(pointer_block->b_pointers[j] !=-1){
                objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                fseek(fp, super.blocks_start + (pointer_block->b_pointers[j] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, fp); //Recupero el bloque de Carpeta
                for (int k = 0; k < 4; k++) {
                    if (folder_block->b_content[j].part_inodo != -1) {
                        if (strcmp(folder_block->b_content[k].part_name, ruta[pos].part_carpeta) == 0) {
                            encontrado = 1;
                            break;
                        }
                    }
                }
                if (encontrado == 1) {
                    break;
                }
            }
        }
    }
    if (encontrado == 0) {
        return 0;
    } else {
        if (pos + 1 == n) { //Si lista->siguiente = NULL, quiere decir que ya llego al final
            return (super.inode_start + (folder_block->b_content[j].part_inodo * sizeof (objetos::inodo))); //Retorna el inodo de la última carpeta
        } else {
            return BusquedaCarpeta(fp, super, (super.inode_start + (folder_block->b_content[j].part_inodo * sizeof (objetos::inodo))), ruta, n, pos + 1);
        }
    }
}
void MKDIR::modificar_bitmap(FILE * archivo, int inicio,objetos::superBloque super_bloque){
    int contador = 0;
    int con_new=0;
    int r = super_bloque.s_bm_inode_start;
    int pos_aux=r;
    while (contador < super_bloque.s_inodes_count) {
        objetos::bitmap  bipI ;
        pos_aux = r;
        fread(&bipI,sizeof (objetos::bitmap),1,archivo);
        if(bipI.estado=='0'){
            con_new++;
            if(con_new==1){
                bipI.estado='1';
            }
        }else if(bipI.estado =='1'){
            bipI.estado ='1';
        }
        r=pos_aux;
        fseek(archivo, r, SEEK_SET);
        fwrite(&bipI, sizeof (objetos::bitmap), 1, archivo);
        r++;
        contador++;
    }
}
int MKDIR::verificarCarpeta(FILE *file_disco, objetos::superBloque super_bloque, int pos_Inodo, char nombre [10]) {
    int archivo=0;
    int encontrado =0;
    objetos::inodo root;
    fseek(file_disco, pos_Inodo, SEEK_SET);
    fread(&root, sizeof (objetos::inodo), 1, file_disco);
    int inicio;
    //verificar que el inodo sea carpeta o archivo
    if(root.i_type == '1'){ // es archivo
       archivo=1;
    }
   /***********************     APUNTADORES DIRECTOS     ************************/
    if(archivo ==0){
        for (int i = 0; i < 12; i++) {
            if (root.i_block[i] != -1) {
                objetos::bloqueCarpeta folder_block ;
                fseek(file_disco, super_bloque.s_block_start + (root.i_block[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET); //Me muevo al bloque de Carpeta
                fread(&folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco); //Recupero el bloque de Carpeta
               if (i == 0) {
                   inicio = 2;
               } else {
                   inicio = 0;
               }
               for (int j = inicio; j < 4; j++) {
                   if (folder_block.b_content[j].part_inodo != -1) {
                       if (strcmp(folder_block.b_content[j].part_name, nombre) == 0) {
                           //Retorna el inodo de la carpeta encontrada
                           encontrado=1;
                           return (super_bloque.s_inode_start + (folder_block.b_content[j].part_inodo * sizeof (objetos::inodo)));
                       }
                   }
               }
            }
        }
        /***********************   APUNTADOR INDIRECTO SIMPLE    **********************/
        if (root.i_block[12] != -1) {
            //Obtener el bloque de apuntadores
            objetos::bloqueApuntadores pointer_block ;
            fseek(file_disco, super_bloque.s_block_start + (root.i_block[12] * sizeof (objetos::bloqueApuntadores)), SEEK_SET);
            fread(&pointer_block, sizeof (objetos::bloqueApuntadores), 1, file_disco);
            for (int i = 0; i < 16; i++) {
                if (pointer_block.b_pointers[i] != -1) {
                    //Obtener el bloque de carpeta
                    objetos::bloqueCarpeta *folder_block = (objetos::bloqueCarpeta*) malloc(sizeof (objetos::bloqueCarpeta));
                    fseek(file_disco, super_bloque.s_block_start + (pointer_block.b_pointers[i] * sizeof (objetos::bloqueCarpeta)), SEEK_SET);
                    fread(folder_block, sizeof (objetos::bloqueCarpeta), 1, file_disco);
                    for (int j = 0; j < 4; j++) {
                        if (folder_block->b_content[j].part_inodo != -1) {
                            if (strcmp(folder_block->b_content[j].part_name, nombre) == 0) {
                                encontrado=1;
                                return (super_bloque.s_inode_start + (folder_block->b_content[j].part_inodo * sizeof (objetos::inodo)));
                            }
                        }
                    }
                }
            }
        }
    }
    contador++;
    int resultado;
    if(encontrado ==0){
        int total_inodos = super_bloque.s_inodes_count - super_bloque.s_free_inodes_count;
        if(contador == total_inodos){
            return  -1;
        }if(contador <total_inodos){
            int posactual = super_bloque.s_inode_start +(sizeof(objetos::inodo)*contador);
           encontrado= verificarCarpeta(file_disco,super_bloque,posactual,nombre);
        }
    }
    return encontrado;
}
void MKDIR::EscribirTexto(FILE *fp, char text[]) {
    int longText;
    longText = strlen(text);
    int contador = 0;
    int inicio = 0;
    fs * sis = new fs();
    /*Apuntadores directos*/
    for (int n = 0; n < 12; n++) {
        if (father_aux.blocks[n] != -1) {
            objetos::bloqueArchivo *B_file = (objetos::bloqueArchivo*) malloc(sizeof (objetos::bloqueArchivo));
            fseek(fp, sb_aux.blocks_start + (father_aux.blocks[n] * sizeof (objetos::bloqueArchivo)), SEEK_SET); //Me muevo al bloque de Archivo
            fread(B_file, sizeof (objetos::bloqueArchivo), 1, fp); //Recupero el bloque de Archivo
            memset(B_file->b_content, 0, sizeof (B_file->b_content)); //Limpio el contenido
            if (inicio == longText) {
                //Si ya terminó el texto y siguen nodos ocupados es porque se disminuyó contenido y hay que eliminar bloques
                //Eliminar el bloque en el bitmap de bloques
                int bipBloque = sis->Posbitmap(sb_aux.blocks_start, father_aux.blocks[n], sizeof (objetos::bloqueArchivo));
                int posBit = sb_aux.bitmap_block_start + (bipBloque * sizeof (objetos::bitmap));
                sis->Actualizarbitmap(fp, posBit, '0');
                //Quitar referencia
                father_aux.blocks[n] = -1;
            } else {
                int i;
                for (i = inicio; i < longText; i++) {
                    if (contador != 63) {
                        strcpy(B_file->b_content, sis->Concatenar(B_file->b_content, text[i]));
                        contador++;
                    } else {
                        inicio = i;
                        contador = 0;
                        break;
                    }
                }
                inicio = i;
                //Escribiendo de nuevo
                fseek(fp, sb_aux.blocks_start + (father_aux.blocks[n] * sizeof (objetos::bloqueArchivo)), SEEK_SET);
                fwrite(B_file, sizeof (objetos::bloqueArchivo), 1, fp);
            }
        } else { //No existe bloque
            if (inicio < longText) { //Aún falta texto por agregar
                objetos::bloqueArchivo cont = sis->CrearbloqueArchivo();
                int i;
                for (i = inicio; i < longText; i++) {
                    if (contador != 63) {
                        strcpy(cont.b_content, sis->Concatenar(cont.b_content, text[i]));
                        contador++;
                    } else {
                        inicio = i;
                        contador = 0;
                        break;
                    }
                }
                inicio = i;
                //Escribiendo
                fseek(fp, sb_aux.first_block, SEEK_SET);
                fwrite(&cont, sizeof (objetos::bloqueArchivo), 1, fp);
                //Actualizando apuntador de inodo
                father_aux.blocks[n] = sis->ObtenerNumeroBloque(sb_aux);
                //Modificando bitmap de Bloque
                int bipBloque = sis->Posbitmap(sb_aux.blocks_start, sb_aux.first_block, sizeof (objetos::bloqueArchivo));
                int posBit = sb_aux.bitmap_block_start + (bipBloque * sizeof (objetos::bitmap));
                sis->Actualizarbitmap(fp, posBit, 'A');
                //Actualizando Super Bloque
                sb_aux.first_block = sb_aux.first_block + sizeof (objetos::bloqueArchivo);
                sb_aux.free_blocks--;
                if (inicio == longText) {
                    break;
                }
            } else {
                break;
            }
        }
    }
}