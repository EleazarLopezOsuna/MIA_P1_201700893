#include "MKFILE.h"
MKFILE::MKFILE(){
    memset(ruta_nArchivo,0,256);
    memset(cont_ruta,0,256);
    crear =0;
    size=0;
    par_ruta=false;
}
void MKFILE::limpiar(){
    memset(ruta_nArchivo,0,256);
    memset(cont_ruta,0,256);
    crear =0;
    size=0;
    par_ruta=false;
}
void MKFILE::ejecutar_MKFILE(lista::list * lista , objetos::activeUser * usuario){
    int logueado=0;
    int grupoLogueado =-1;
    if(usuario->estado == -1){
        cout << "Error, no se inicio sesion" << endl;
        return;
    }else{
        logueado = usuario->id_usuario;
        grupoLogueado = usuario->grupo;
    }
    if (size < 0) {
        cout << "Error, dimension erronea" << endl;
        return;
    }
    int copia = 0;
    if (cont_ruta[0] != '\0') {
        copia = 1;
    }
    //Verificar nombre de archivo
    char ts1[250];
    memset(ts1, 0, sizeof (ts1));
    char * c_aux;
    strcpy(ts1, strdup(ruta_nArchivo));
    char filename[50];
    memset(filename, 0, sizeof (filename));
    strcpy(filename, basename(ts1));
    int total = strlen(filename);
    //DISCO
    int letra = usuario->particion[3];
    MOUNT * nuevo;
    //busca la lista del particiones del disco
    lista::nodoC * disco_montado = nuevo->buscar_porLetra(letra, lista->first);
    lista::nodoP * particion= nuevo->buscar_id_exisbloqueApuntadb_poinroobloqueArchivoe(usuario->particion, lista->first);
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
            }
            //** para usar los metodos de la clase MKDIR
            MKDIR * MKDIR_ = new MKDIR();
            //** para usar los metodos de la clase file_system
            fs * sis = new fs();
            objetos::inodo father;
            int file_position;
            //AGREGAR CARPETAS DE LA RUTA A LA LISTA
            int n = MKDIR_->ContadorBarras(ruta_nArchivo);
            if (n == 1) {
                file_position = super_bloque.s_inode_start;
                fseek(archivo_disco, file_position, SEEK_SET);
                fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
            } else {
                MKDIR::list ruta[n - 1];
                //Limpiar
                for (int i = 0; i < n - 1; i++) {
                    memset(ruta[i].part_carpeta, 0, sizeof (ruta[i].part_carpeta));
                }
                int longPath = strlen(ruta_nArchivo);
                int k = -1;
                int contador = 0;
                for (int i = 0; i < longPath; i++) {
                    if (ruta_nArchivo[i] == '/') {
                        contador++;
                        k++;
                        if (contador == n) {
                            break;
                        }
                    } else {
                        strcpy(ruta[k].part_carpeta, MKDIR_->Concatenar(ruta[k].part_carpeta, ruta_nArchivo[i]));
                    }
                }
                //BUSCAR RUTA
                file_position = MKDIR_->BusquedaCarpeta(archivo_disco, super_bloque, super_bloque.s_inode_start, ruta, n - 1, 0);
                if (file_position == 0) {
                    //La carpeta no existe
                    if (crear == 1) { //Se crea la ruta para crear el archivo
                        int imposible = 0;
                        int pos_inodo = super_bloque.s_inode_start; //Empezamos buscando desde la raíz.
                        for (int i = 0; i < n - 1; i++) {
                            int posicion = sis->ExisteInodo(super_bloque, pos_inodo, ruta[i].part_carpeta,archivo_disco);
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
                                    if (buffer[0] == 2 || buffer[0] == 3 || buffer[0] == 6 || buffer[0] == 7) {
                                        puede = 1;
                                    }
                                } else {
                                    puede = 1; //Si es 1 si puede hacer los cambios
                                }
                                if (puede == 1) {
                                    pos_inodo = posicion;
                                } else {
                                    imposible = 1;
                                    break;
                                }
                            } else { //Hay que crearlo
                                objetos::inodo nuevofather;
                                fseek(archivo_disco, pos_inodo, SEEK_SET);
                                fread(&nuevofather, sizeof (objetos::inodo), 1, archivo_disco);
                                MKDIR_->sb_aux = super_bloque;
                                MKDIR_->father_aux = nuevofather;
                                int pos_nuevo = MKDIR_->CrearInodoArchivo_Carpeta(archivo_disco,ruta[i].part_carpeta, '0', logueado, grupoLogueado,size);
                                super_bloque = MKDIR_->sb_aux;
                                nuevofather = MKDIR_->father_aux;
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
                        if (imposible == 1) {
                            cout << "Error, el usuario no tiene permisos de escritura" << endl;
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
                    fseek(archivo_disco, file_position, SEEK_SET);
                    fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
                }
            }
            //REVISAR PERMISOS DE ESCRITURA EN LA CARPETA PADRE
            int puede = 0;
            if (logueado != 1) {
                char buffer[7];
                char buffer2[7];
                buffer2[0]=0;
                buffer2[1]=0;
                buffer2[2]=0;
                memset(buffer, 0, sizeof (buffer));
                sprintf(buffer, "%d", father.i_perm);
                if (buffer[0] == '2' || buffer[0] == '3' || buffer[0] == '6' || buffer[0] == '7') {
                    puede = 1;
                }
            } else {
                puede = 1; //Si es 1 si puede hacer los cambios
            }
            if (puede == 1) {
                //************************    CREANDO   **************************
                if (copia == 1) {
                    //El contenido del archivo a crear debe ser copia de otro
                    //Verificar que cont[] sea un archivo
                    int esArchivo = VerificarPath(cont_ruta);
                    if (esArchivo == 0 || esArchivo == -1) {
                        cout << "Error, la ruta no tiene archivo" << endl;
                        return;
                    }
                    if (access(cont_ruta, F_OK) != -1) {
                        char buf[14000];
                        memset(buf, 0, sizeof (buf));
                        FILE *file;
                        size_t nread;
                        file = fopen(cont_ruta, "r");
                        if (file) {
                            while ((nread = fread(buf, 1, sizeof (buf), file)) > 0) {
                                fwrite(buf, 1, nread, stdout);
                            }
                            if (ferror(file)) {
                                cout << "Error, no se pudo leer el archivo" << endl;
                            }
                            fclose(file);
                        }
                        //CREAR ARCHIVO
                        //Verificar si ya existe el archivo, si existe entonces se sobrescribe
                        int esta = sis->ExisteInodo( super_bloque, file_position, filename,archivo_disco);
                        if (esta == -1) {
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = father;
                            int posInodo = MKDIR_->CrearInodoArchivo_Carpeta(archivo_disco, filename, '1', logueado, grupoLogueado,size);
                            super_bloque = MKDIR_->sb_aux;
                            father = MKDIR_->father_aux;
                            //Actualiza padre
                            fseek(archivo_disco, file_position, SEEK_SET);
                            fwrite(&father, sizeof (objetos::inodo), 1, archivo_disco);
                            //Leer el Inodo del archivo
                            objetos::inodo newfile ;
                            fseek(archivo_disco, posInodo, SEEK_SET);
                            fread(&newfile, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = newfile;
                            MKDIR_->EscribirTexto(archivo_disco, buf);
                            super_bloque = MKDIR_->sb_aux;
                            newfile = MKDIR_->father_aux;
                            //Actualizar nuevo inodo
                            fseek(archivo_disco, posInodo, SEEK_SET);
                            fwrite(&newfile, sizeof (objetos::inodo), 1, archivo_disco);
                            //Modificando bitmap de Inodo
                            int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
                            int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
                            sis->Actualizarbitmap(archivo_disco, posBit, '1');
                            //Actualizar Super bloque
                            super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
                            super_bloque.s_free_inodes_count--;
                            // CREAR EL JURNALING ***********************************************************************
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
                                cout << "Error, no se pudo crear el journal" << endl;
                            }else{
                                char comando[256];
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //**********************************************************************************
                        } else {
                            //Sobrescribir el archivo
                            //Leer el Inodo del archivo
                            objetos::inodo overwrite ;
                            fseek(archivo_disco, esta, SEEK_SET);
                            fread(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = overwrite;
                            MKDIR_->EscribirTexto(archivo_disco, buf);
                            super_bloque = MKDIR_->sb_aux;
                            overwrite = MKDIR_->father_aux;
                            //Actualizar inodo
                            fseek(archivo_disco, esta, SEEK_SET);
                            fwrite(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            // CREAR EL JURNALING ***********************************************************************
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
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                //  cout << " escribe el journal i=" <<a << endl;
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //***********************************************************************************
                        }
                    } else {
                        //no existe
                        cout << "Error, el archivo no existe" << endl;
                        fclose(archivo_disco);
                        return;
                    }
                } else {
                    if (size == 0) {
                        //Crear Inodo de archivo
                        //Verificar si ya existe el archivo, si existe entonces se sobrescribe
                        int esta = sis->ExisteInodo(super_bloque, file_position, filename,archivo_disco);
                        if (esta == -1) {
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = father;
                            MKDIR_->CrearInodoArchivo_Carpeta(archivo_disco, filename, '1', logueado, grupoLogueado,size);
                            super_bloque = MKDIR_->sb_aux;
                            father = MKDIR_->father_aux;
                            //Actualiza padre
                            fseek(archivo_disco, file_position, SEEK_SET);
                            fwrite(&father, sizeof (objetos::inodo), 1, archivo_disco);
                            //Modificando bitmap de Inodo
                            int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
                            int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
                            sis->Actualizarbitmap(archivo_disco, posBit, '1');
                            //Actualizar Super bloque
                            super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
                            super_bloque.s_free_inodes_count--;
                            // CREAR EL JURNALING ***********************************************************************
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
                                cout << "Error, no se pudo escribir en el journal" << endl;
                            }else{
                                char comando[256];
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //**********************************************************************************
                        } else {
                            //Sobrescribir el archivo
                            //Leer el Inodo del archivo
                            objetos::inodo overwrite ;
                            fseek(archivo_disco, esta, SEEK_SET);
                            fread(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = overwrite;
                            MKDIR_->EscribirTexto(archivo_disco, "");
                            super_bloque = MKDIR_->sb_aux;
                            overwrite = MKDIR_->father_aux;
                            // CREAR EL JURNALING ***********************************************************************
                            int posJournal =-1;
                            int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
                            for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::Journal)) {
                                objetos::Journal j ;
                                fseek(archivo_disco, i, SEEK_SET);
                                fread(&j, sizeof (objetos::Journal), 1, archivo_disco);
                                if (j.estado =='0') {
                                    posJournal =i;
                                }
                            }
                            // CREAR EL JURNALING ***********************************************************************
                            //--------------------------------- obtengo la posicion del journal
                            posJournal =-1;
                            posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
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
                                cout << "Error, no se pudo escribir en el journal" << endl;
                            }else{
                                char comando[256];
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //**********************************************************************************
                        }
                    } else {
                        int correlative = 0;
                        char letter;
                        char contenido[size + 1];
                        memset(contenido, 0, sizeof (contenido));
                        for (int i = 0; i < size; i++) {
                            if (correlative == 10) {
                                correlative = 0;
                            }
                            letter = correlative + '0';
                            strcpy(contenido,MKDIR_->Concatenar(contenido, letter));
                            correlative++;
                        }
                        //Crear archivo
                        //Verificar si ya existe el archivo, si existe entonces se sobrescribe
                        int esta = sis->ExisteInodo(super_bloque, file_position, filename,archivo_disco);
                        if (esta == -1) {
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = father;
                            int posInodo = MKDIR_->CrearInodoArchivo_Carpeta(archivo_disco, filename, '1', logueado, grupoLogueado,size);
                            super_bloque = MKDIR_->sb_aux;
                            father = MKDIR_->father_aux;
                            //Actualiza padre
                            fseek(archivo_disco, file_position, SEEK_SET);
                            fwrite(&father, sizeof (objetos::inodo), 1, archivo_disco);
                            //Leer el Inodo del archivo
                            objetos::inodo newfile ;
                            fseek(archivo_disco, posInodo, SEEK_SET);
                            fread(&newfile, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = newfile;
                            MKDIR_->EscribirTexto(archivo_disco, contenido);
                            super_bloque = MKDIR_->sb_aux;
                            newfile = MKDIR_->father_aux;
                            //Actualizar nuevo inodo
                            fseek(archivo_disco, posInodo, SEEK_SET);
                            fwrite(&newfile, sizeof (objetos::inodo), 1, archivo_disco);
                            //Modificando bitmap de Inodo
                            int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
                            int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
                            sis->Actualizarbitmap(archivo_disco, posBit, '1');
                            //Actualizar Super bloque
                            super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
                            super_bloque.s_free_inodes_count--;
                            // CREAR EL JURNALING ***********************************************************************
                            int posJournal =-1;
                            int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
                            for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::Journal)) {
                                objetos::Journal j ;
                                fseek(archivo_disco, i, SEEK_SET);
                                fread(&j, sizeof (objetos::Journal), 1, archivo_disco);
                                if (j.estado =='0') {
                                    posJournal =i;
                                }
                            }
                            // CREAR EL JURNALING ***********************************************************************
                            //--------------------------------- obtengo la posicion del journal
                            posJournal =-1;
                            posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
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
                                cout << "Error, no se pudo escribir en el journal" << endl;
                            }else{
                                char comando[256];
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //**********************************************************************************
                        } else {
                            //Sobrescribir el archivo
                            //Leer el Inodo del archivo
                            objetos::inodo overwrite ;
                            fseek(archivo_disco, esta, SEEK_SET);
                            fread(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = overwrite;
                            MKDIR_->EscribirTexto(archivo_disco, contenido);
                            super_bloque = MKDIR_->sb_aux;
                            overwrite = MKDIR_->father_aux;
                            //Actualizar inodo
                            fseek(archivo_disco, esta, SEEK_SET);
                            fwrite(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            // CREAR EL JURNALING ***********************************************************************
                            int posJournal =-1;
                            int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
                            for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::Journal)) {
                                objetos::Journal j ;
                                fseek(archivo_disco, i, SEEK_SET);
                                fread(&j, sizeof (objetos::Journal), 1, archivo_disco);
                                if (j.estado =='0') {
                                    posJournal =i;
                                }
                            }
                            // CREAR EL JURNALING ***********************************************************************
                            //--------------------------------- obtengo la posicion del journal
                            posJournal =-1;
                            posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
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
                                cout << "Error, no se pudo escribir en el journal" << endl;
                            }else{
                                char comando[256];
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                        }
                    }
                }
                //Escribir super bloque
                fseek(archivo_disco, mbr.mbr_partitions[num_particion].part_start, SEEK_SET);
                fwrite(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
                fclose(archivo_disco);
            } else {
                cout << "Error, el usuario no tiene permisos de escritura" << endl;
                fclose(archivo_disco);
                return;
            }
        }else{
            cout << "Error, no se pudo leer el disco" << endl;
        }
    }else{
        cout << "Error, la particion no esta montada" << endl;
    }
}
void MKFILE::ejecutar_MKFILE2(lista::list * lista , objetos::activeUser * usuario, char txt[14000]){
    int logueado=0;
    int grupoLogueado =-1;
    if(usuario->estado == -1){
        cout << "Error, no se ha iniciado sesion" << endl;
        return;
    }else{
        logueado = usuario->id_usuario;
        grupoLogueado = usuario->grupo;
    }
    if (size < 0) {
        cout << "Error" << endl;
        printf("Error: dimension erronea");
        return;
    }
    int copia = 0;
    if (cont_ruta[0] != '\0') {
        copia = 1;
    }
    //Verificar nombre de archivo
    char ts1[250];
    memset(ts1, 0, sizeof (ts1));
    char * c_aux;
    strcpy(ts1, strdup(ruta_nArchivo));
    char filename[50];
    memset(filename, 0, sizeof (filename));
    strcpy(filename, basename(ts1));
    int total = strlen(filename);
    //DISCO
    int letra = usuario->particion[3];
    MOUNT * nuevo;
    //busca la lista del particiones del disco
    lista::nodoC * disco_montado = nuevo->buscar_porLetra(letra, lista->first);
    lista::nodoP * particion= nuevo->buscar_id_exisbloqueApuntadb_poinroobloqueArchivoe(usuario->particion, lista->first);
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
            }
            //** para usar los metodos de la clase MKDIR
            MKDIR * MKDIR_ = new MKDIR();
            //** para usar los metodos de la clase fs
            fs * sis = new fs();
            objetos::inodo father;
            int file_position;
            //AGREGAR CARPETAS DE LA RUTA A LA LISTA
            int n = MKDIR_->ContadorBarras(ruta_nArchivo);
            if (n == 1) {
                file_position = super_bloque.s_inode_start;
                fseek(archivo_disco, file_position, SEEK_SET);
                fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
            } else {
                MKDIR::list ruta[n - 1];
                //Limpiar
                for (int i = 0; i < n - 1; i++) {
                    memset(ruta[i].part_carpeta, 0, sizeof (ruta[i].part_carpeta));
                }
                int longPath = strlen(ruta_nArchivo);
                int k = -1;
                int contador = 0;
                for (int i = 0; i < longPath; i++) {
                    if (ruta_nArchivo[i] == '/') {
                        contador++;
                        k++;
                        if (contador == n) {
                            break;
                        }
                    } else {
                        strcpy(ruta[k].part_carpeta, MKDIR_->Concatenar(ruta[k].part_carpeta, ruta_nArchivo[i]));
                    }
                }
                //BUSCAR RUTA
                file_position = MKDIR_->BusquedaCarpeta(archivo_disco, super_bloque, super_bloque.s_inode_start, ruta, n - 1, 0);
                if (file_position == 0) {
                    //La carpeta no existe
                    if (crear == 1) { //Se crea la ruta para crear el archivo
                        int imposible = 0;
                        int pos_inodo = super_bloque.s_inode_start; //Empezamos buscando desde la raíz.
                        for (int i = 0; i < n - 1; i++) {
                            int posicion = sis->ExisteInodo(super_bloque, pos_inodo, ruta[i].part_carpeta,archivo_disco);
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
                                    if (buffer[0] == 2 || buffer[0] == 3 || buffer[0] == 6 || buffer[0] == 7) {
                                        puede = 1;
                                    }
                                } else {
                                    puede = 1; //Si es b_conbloqueApuntadb_poinroobloqueArchivo si puede hacer los cambios
                                }
                                if (puede == 1) {
                                    pos_inodo = posicion;
                                } else {
                                    imposible = 1;
                                    break;
                                }
                            } else { //Hay que crearlo
                                objetos::inodo nuevofather;
                                fseek(archivo_disco, pos_inodo, SEEK_SET);
                                fread(&nuevofather, sizeof (objetos::inodo), 1, archivo_disco);
                                MKDIR_->sb_aux = super_bloque;
                                MKDIR_->father_aux = nuevofather;
                                int pos_nuevo = MKDIR_->CrearInodoArchivo_Carpeta(archivo_disco,ruta[i].part_carpeta, '0', logueado, grupoLogueado,size);
                                super_bloque = MKDIR_->sb_aux;
                                nuevofather = MKDIR_->father_aux;
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
                        if (imposible == 1) {
                            cout << "Error, el usuario no tiene permisos de escritura" << endl;
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
                    fseek(archivo_disco, file_position, SEEK_SET);
                    fread(&father, sizeof (objetos::inodo), 1, archivo_disco);
                }
            }
            //REVISAR PERMISOS DE ESCRITURA EN LA CARPETA PADRE
            int puede = 0;
            if (logueado != 1) {
                char buffer[7];
                char buffer2[7];
                buffer2[0]=0;
                buffer2[1]=0;
                buffer2[2]=0;
                memset(buffer, 0, sizeof (buffer));
                sprintf(buffer, "%d", father.i_perm);
                if (buffer[0] == '2' || buffer[0] == '3' || buffer[0] == '6' || buffer[0] == '7') {
                    puede = 1;
                }
            } else {
                puede = 1; //Si es b_conbloqueApuntadb_poinroobloqueArchivo si puede hacer los cambios
            }
            if (puede == 1) {
                //************************    CREANDO   **************************
                if (copia == 1) {
                    //El contenido del archivo a crear debe ser copia de otro
                    //Verificar que cont[] sea un archivo
                    int esArchivo = VerificarPath(cont_ruta);
                    if (esArchivo == 0 || esArchivo == -1) {
                        cout << "Error, la ruta no tiene archivo" << endl;
                        return;
                    }
                    if (access(cont_ruta, F_OK) != -1) {
                        char buf[14000];
                        memset(buf, 0, sizeof (buf));
                        FILE *file;
                        size_t nread;
                        file = fopen(cont_ruta, "r");
                        if (file) {
                            while ((nread = fread(buf, 1, sizeof (buf), file)) > 0) {
                                fwrite(buf, 1, nread, stdout);
                            }
                            if (ferror(file)) {
                                cout << "Error, no se pudo leer el archivo" << endl;
                            }
                            fclose(file);
                        }
                        //CREAR ARCHIVO
                        //Verificar si ya existe el archivo, si existe entonces se sobrescribe
                        int esta = sis->ExisteInodo( super_bloque, file_position, filename,archivo_disco);
                        if (esta == -1) {
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = father;
                            int posInodo = MKDIR_->CrearInodoArchivo_Carpeta(archivo_disco, filename, '1', logueado, grupoLogueado,size);
                            super_bloque = MKDIR_->sb_aux;
                            father = MKDIR_->father_aux;
                            //Actualiza padre
                            fseek(archivo_disco, file_position, SEEK_SET);
                            fwrite(&father, sizeof (objetos::inodo), 1, archivo_disco);
                            //Leer el Inodo del archivo
                            objetos::inodo newfile ;
                            fseek(archivo_disco, posInodo, SEEK_SET);
                            fread(&newfile, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = newfile;
                            MKDIR_->EscribirTexto(archivo_disco, txt);
                            super_bloque = MKDIR_->sb_aux;
                            newfile = MKDIR_->father_aux;
                            //Actualizar nuevo inodo
                            fseek(archivo_disco, posInodo, SEEK_SET);
                            fwrite(&newfile, sizeof (objetos::inodo), 1, archivo_disco);
                            //Modificando bitmap de Inodo
                            int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
                            int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
                            sis->Actualizarbitmap(archivo_disco, posBit, '1');
                            //Actualizar Super bloque
                            super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
                            super_bloque.s_free_inodes_count--;
                            // CREAR EL JURNALING ***********************************************************************
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
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //**********************************************************************************
                        } else {
                            //Sobrescribir el archivo
                            //Leer el Inodo del archivo
                            objetos::inodo overwrite ;
                            fseek(archivo_disco, esta, SEEK_SET);
                            fread(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = overwrite;
                            MKDIR_->EscribirTexto(archivo_disco, txt);
                            super_bloque = MKDIR_->sb_aux;
                            overwrite = MKDIR_->father_aux;
                            //Actualizar inodo
                            fseek(archivo_disco, esta, SEEK_SET);
                            fwrite(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            // CREAR EL JURNALING ***********************************************************************
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
                                cout << "Error, no se puede escribir el journal" << endl;
                            }else{
                                char comando[256];
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //***********************************************************************************
                        }
                    } else {
                        //no existe
                        cout << "Error, el archivo no existe" << endl;
                        fclose(archivo_disco);
                        return;
                    }
                } else {
                    if (size == 0) {
                        //Crear Inodo de archivo
                        //Verificar si ya existe el archivo, si existe entonces se sobrescribe
                        int esta = sis->ExisteInodo(super_bloque, file_position, filename,archivo_disco);
                        if (esta == -1) {
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = father;
                            MKDIR_->CrearInodoArchivo_Carpeta(archivo_disco, filename, '1', logueado, grupoLogueado,size);
                            super_bloque = MKDIR_->sb_aux;
                            father = MKDIR_->father_aux;
                            //Actualiza padre
                            fseek(archivo_disco, file_position, SEEK_SET);
                            fwrite(&father, sizeof (objetos::inodo), 1, archivo_disco);
                            //Modificando bitmap de Inodo
                            int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
                            int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
                            sis->Actualizarbitmap(archivo_disco, posBit, '1');
                            //Actualizar Super bloque
                            super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
                            super_bloque.s_free_inodes_count--;
                            // CREAR EL JURNALING ***********************************************************************
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
                            if(posJournal == -1){
                                cout << "Error, no se pudo escribir el journal" << endl;
                            }else{
                                char comando[256];
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //**********************************************************************************
                        } else {
                            //Sobrescribir el archivo
                            //Leer el Inodo del archivo
                            objetos::inodo overwrite ;
                            fseek(archivo_disco, esta, SEEK_SET);
                            fread(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = overwrite;
                            MKDIR_->EscribirTexto(archivo_disco, txt);
                            super_bloque = MKDIR_->sb_aux;
                            overwrite = MKDIR_->father_aux;
                            // CREAR EL JURNALING ***********************************************************************
                            int posJournal =-1;
                            int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
                            for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::Journal)) {
                                objetos::Journal j ;
                                fseek(archivo_disco, i, SEEK_SET);
                                fread(&j, sizeof (objetos::Journal), 1, archivo_disco);
                                if (j.estado =='0') {
                                    posJournal =i;
                                }
                            }
                            // CREAR EL JURNALING ***********************************************************************
                            //--------------------------------- obtengo la posicion del journal
                            posJournal =-1;
                            posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
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
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                            //**********************************************************************************
                        }
                    } else {
                        int correlative = 0;
                        char letter;
                        char contenido[size + 1];
                        memset(contenido, 0, sizeof (contenido));
                        for (int i = 0; i < size; i++) {
                            if (correlative == 10) {
                                correlative = 0;
                            }
                            letter = correlative + '0';
                            strcpy(contenido,MKDIR_->Concatenar(contenido, letter));
                            correlative++;
                        }
                        //Crear archivo
                        //Verificar si ya existe el archivo, si existe entonces se sobrescribe
                        int esta = sis->ExisteInodo(super_bloque, file_position, filename,archivo_disco);
                        if (esta == -1) {
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = father;
                            int posInodo = MKDIR_->CrearInodoArchivo_Carpeta(archivo_disco, filename, '1', logueado, grupoLogueado,size);
                            super_bloque = MKDIR_->sb_aux;
                            father = MKDIR_->father_aux;
                            //Actualiza padre
                            fseek(archivo_disco, file_position, SEEK_SET);
                            fwrite(&father, sizeof (objetos::inodo), 1, archivo_disco);
                            //Leer el Inodo del archivo
                            objetos::inodo newfile ;
                            fseek(archivo_disco, posInodo, SEEK_SET);
                            fread(&newfile, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = newfile;
                            MKDIR_->EscribirTexto(archivo_disco, txt);
                            super_bloque = MKDIR_->sb_aux;
                            newfile = MKDIR_->father_aux;
                            //Actualizar nuevo inodo
                            fseek(archivo_disco, posInodo, SEEK_SET);
                            fwrite(&newfile, sizeof (objetos::inodo), 1, archivo_disco);
                            //Modificando bitmap de Inodo
                            int bipInodo = sis->Posbitmap(super_bloque.s_inode_start, super_bloque.s_first_inode, sizeof (objetos::inodo));
                            int posBit = super_bloque.s_bm_inode_start + (bipInodo * sizeof (objetos::bitmap));
                            sis->Actualizarbitmap(archivo_disco, posBit, '1');
                            //Actualizar Super bloque
                            super_bloque.s_first_inode = super_bloque.s_first_inode + sizeof (objetos::inodo);
                            super_bloque.s_free_inodes_count--;
                            // CREAR EL JURNALING ***********************************************************************
                            int posJournal =-1;
                            int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
                            for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::Journal)) {
                                objetos::Journal j ;
                                fseek(archivo_disco, i, SEEK_SET);
                                fread(&j, sizeof (objetos::Journal), 1, archivo_disco);
                                if (j.estado =='0') {
                                    posJournal =i;
                                }
                            }
                            // CREAR EL JURNALING ***********************************************************************
                            //--------------------------------- obtengo la posicion del journal
                               posJournal =-1;
                               posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
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
                                  strcpy(comando,"MKFILE -path=");
                                  strcat(comando,ruta_nArchivo);
                                  if(crear==1){
                                      strcat(comando," -r ");
                                  }
                                  if(size >0){
                                      char char_size[20];
                                      sprintf(char_size, "%d", size);
                                      strcat(comando," -size = ");
                                      strcat(comando,char_size);
                                  }
                                  if(cont_ruta[0] != '\0'){
                                      strcpy(comando," -cont=");
                                      strcat(comando,cont_ruta);
                                  }
                                  objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                  journal = sis->CrearJornal(usuario->user,comando);
                                  fseek(archivo_disco, posJournal, SEEK_SET);
                                  fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                              }
                            //**********************************************************************************
                        } else {
                            //Sobrescribir el archivo
                            //Leer el Inodo del archivo
                            objetos::inodo overwrite ;
                            fseek(archivo_disco, esta, SEEK_SET);
                            fread(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            //Escribir contenido
                            MKDIR_->sb_aux = super_bloque;
                            MKDIR_->father_aux = overwrite;
                            MKDIR_->EscribirTexto(archivo_disco, txt);
                            super_bloque = MKDIR_->sb_aux;
                            overwrite = MKDIR_->father_aux;
                            //Actualizar inodo
                            fseek(archivo_disco, esta, SEEK_SET);
                            fwrite(&overwrite, sizeof (objetos::inodo), 1, archivo_disco);
                            // CREAR EL JURNALING ***********************************************************************
                            int posJournal =-1;
                            int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
                            for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::Journal)) {
                                objetos::Journal j ;
                                fseek(archivo_disco, i, SEEK_SET);
                                fread(&j, sizeof (objetos::Journal), 1, archivo_disco);
                                if (j.estado =='0') {
                                    posJournal =i;
                                }
                            }
                            // CREAR EL JURNALING ***********************************************************************
                            //--------------------------------- obtengo la posicion del journal
                            posJournal =-1;
                            posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
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
                                strcpy(comando,"MKFILE -path=");
                                strcat(comando,ruta_nArchivo);
                                if(crear==1){
                                    strcat(comando," -r ");
                                }
                                if(size >0){
                                    char char_size[20];
                                    sprintf(char_size, "%d", size);
                                    strcat(comando," -size = ");
                                    strcat(comando,char_size);
                                }
                                if(cont_ruta[0] != '\0'){
                                    strcpy(comando," -cont=");
                                    strcat(comando,cont_ruta);
                                }
                                objetos::Journal * journal = (objetos::Journal*)malloc(sizeof (objetos::Journal));
                                journal = sis->CrearJornal(usuario->user,comando);
                                fseek(archivo_disco, posJournal, SEEK_SET);
                                fwrite(journal, sizeof (objetos::Journal), 1, archivo_disco);
                            }
                               //**********************************************************************************
                        }
                    }
                }
                //Escribir super bloque
                fseek(archivo_disco, mbr.mbr_partitions[num_particion].part_start, SEEK_SET);
                fwrite(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
                fclose(archivo_disco);
            } else {
                cout << "Error, el usuario no tiene permisos de escritura" << endl;
                fclose(archivo_disco);
                return;
            }
        }else{
            cout << "Error, no se pudo leer el disco" << endl;
        }
    }else{
        cout << "Error, la particion no esta montada" << endl;
    }
}
int MKFILE::VerificarPath(char path[]) {
    char pathToAnalyze[300];
    strcpy(pathToAnalyze, strdup(path));
    char filename[50];
    strcpy(filename, basename(pathToAnalyze));
    int num = ContadorTipoPunto(filename);
    if (num == 1) {
        return 1; //Archivo
    } else if (num == 0) {
        return 0; //Carpeta
    } else {
        return -1; //Error
    }
}
int MKFILE::ContadorTipoPunto(char *string) {
    int c = 0;
    while (*string) c += *(string++) == '.';
        return c;
}