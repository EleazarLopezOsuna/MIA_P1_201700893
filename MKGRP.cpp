#include "MKGRP.h"

MKGRP::MKGRP()
{
    grupo = (char*)malloc(sizeof (10));
    memset(nombre, 0, 10);
    memset(grupo, 0, 10);
    memset(password, 0, 10);
    tipo=0;
    par_usr = false;
    par_pwd = false;
    par_grp = false;
}
void MKGRP::limpiar(){
    memset(nombre, 0, 10);
    memset(grupo, 0, 10);
    memset(password, 0, 10);
    tipo=0;
    par_usr = false;
    par_pwd = false;
    par_grp = false;
}
void MKGRP::ejecutar(objetos::activeUser * usuario,lista::list * lista ){
    if(tipo==1){ // ejecutar mkgrp
        cout<<" * creacion de grupos  *"<<endl;
            ejecutar_mkgrp(usuario,lista);
    }else if(tipo==2){
        cout<<" * creacion de usuario  *"<<endl;
        ejecutar_mkusr(usuario,lista);
    }
}
void MKGRP::ejecutar_mkgrp(objetos::activeUser * usuario,lista::list * lista ){
    // si el usuario no es root no puede crear grupos
    if(strcmp(usuario->user, "root") != 0){
        cout << "Error, no se tienen los permisos para crear" << endl;
        return;
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
            objetos::MBR  mbr ;
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
            objetos::superBloque  super_bloque;
            fseek(archivo_disco, mbr.mbr_partitions[num_particion].part_start, SEEK_SET);
            fread(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            //inodo del archivo de Users -- siempre sera el segundo inodo
            objetos::inodo users;
            int posUser = super_bloque.s_inode_start + sizeof (objetos::inodo);
            fseek(archivo_disco, posUser, SEEK_SET);
            fread(&users, sizeof (objetos::inodo), 1, archivo_disco);
            //obtener el contenido del archivo para analizarlo
            char Texto[14000];
            memset(Texto, 0, sizeof (Texto));
            //para usar el metodo de LOGIN
            LOGIN * n_log = new LOGIN();
            strcpy(Texto, n_log->ObtenerTexto(archivo_disco, super_bloque, &users));
            char Text[14000];
            memset(Text, 0, sizeof (Text));
            strcpy(Text, strdup(Texto));
            int id = 1;
            char tipo = 'A';
            char nameGroup[11];
            int existe = 0;
            int saveLastGroup = 0;
            char *end_str;
            char *line = strtok_r(Text, "\n", &end_str);
            while (line != NULL) {
                char *end_token;
                char *token = strtok_r(line, ",", &end_token);
                while (token != NULL) {
                    id = 1;
                    tipo = 'A';
                    memset(nameGroup, 0, sizeof (nameGroup));
                    id = atoi(token);
                    token = strtok_r(NULL, ",", &end_token);
                    tipo = token[0];
                    token = strtok_r(NULL, ",", &end_token);
                    strcpy(nameGroup, token);
                    token = strtok_r(NULL, ",", &end_token);
                    if (tipo == 'U') {
                        //Solo nos interesan los grupos
                        token = strtok_r(NULL, ",", &end_token);
                        token = strtok_r(NULL, ",", &end_token);
                    } else if (tipo == 'G') {
                        if (strcmp(nameGroup, nombre) == 0) {
                            existe = 1;
                            break;
                        } else {
                            saveLastGroup = id;
                        }
                    }
                }
                if (existe == 1) {
                    break;
                }
                line = strtok_r(NULL, "\n", &end_str);
            }
             if (existe == 1) {
                 fclose(archivo_disco);
                 cout << "Error, el grupo ya existe" << endl;
                 return;
             } else {
                //Generando el registro para el nuevo grupo
                char lineNewGroup[20];
                sprintf(lineNewGroup, "%d", saveLastGroup + 1);
                strcat(lineNewGroup, ",G,");
                strcat(lineNewGroup, nombre);
                strcat(lineNewGroup, "\n");
                //Concatenando nueva linea al texto
                strcat(Texto, lineNewGroup);
                //Escribiendo
                fs * sis = new fs();
                MKDIR * mkd = new MKDIR();
                mkd->sb_aux = super_bloque;
                mkd->father_aux = users;
                mkd->EscribirTexto(archivo_disco,  Texto);
                super_bloque = mkd->sb_aux;
                users = mkd->father_aux;
                //Actualizando inodo
                fseek(archivo_disco, posUser, SEEK_SET);
                fwrite(&users, sizeof (objetos::inodo), 1, archivo_disco);
                //Actualizando Super Bloque
                fseek(archivo_disco, mbr.mbr_partitions[num_particion].part_start, SEEK_SET);
                fwrite(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
                //Actualizando el Journaling
                int posJournal =-1;
                int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
                int a=0;
                for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::journal)) {
                    objetos::journal j ;
                    fseek(archivo_disco, i, SEEK_SET);
                    fread(&j, sizeof (objetos::journal), 1, archivo_disco);
                    a++;
                    if (j.estado =='0') {
                        posJournal =i ;
                        break;
                    }
                }
                if(posJournal == -1){
                    cout << "Error, no se pudo actualizad el journal" << endl;
                }else{
                    char comando[256];
                    strcpy(comando,"MKgrp -name=");
                    strcat(comando,nombre);
                    objetos::journal * journal = (objetos::journal*)malloc(sizeof (objetos::journal));
                    journal = sis->CrearJornal(usuario->user,comando);
                    journal->estado ='1';
                    fseek(archivo_disco, posJournal, SEEK_SET);
                    fwrite(journal, sizeof (objetos::journal), 1, archivo_disco);
                }
                fclose(archivo_disco);
             }
       //------------------------------
        }else{
            cout << "Error, no se pudo leer el disco" << endl;
        }
    }else {
         cout << "Error, la particion no esta montada" << endl;
         return;
    }
}
void MKGRP::ejecutar_mkusr(objetos::activeUser *usuario, lista::list *lista){
    if(strcmp(usuario->user, "root") != 0){
        cout << "Error, no se tienen permisos para crear" << endl;
        return;
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
            objetos::MBR mbr ;
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
            objetos::superBloque  super_bloque;
            fseek(archivo_disco, mbr.mbr_partitions[num_particion].part_start, SEEK_SET);
            fread(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            //inodo del archivo de Users -- siempre sera el segundo inodo
            objetos::inodo users ;
            int posUser = super_bloque.s_inode_start + sizeof (objetos::inodo);
            fseek(archivo_disco, posUser, SEEK_SET);
            fread(&users, sizeof (objetos::inodo), 1, archivo_disco);
            //obtener el contenido del archivo para analizarlo
            char Texto[14000];
            memset(Texto, 0, sizeof (Texto));
            LOGIN * n_log = new LOGIN();
            strcpy(Texto, n_log->ObtenerTexto(archivo_disco, super_bloque, &users));
            char Text[14000];
            memset(Text, 0, sizeof (Text));
            strcpy(Text, strdup(Texto)); //Hacer una copia de Texto para análisis
            int id = 0;
            char tipo = 'A';
            char nameGroup[11];
            char nameUser[11];
            int existeUser = 0;
            int existeGrupo = 0;
            int saveLastUser = 0;
            char *end_str;
            char *line = strtok_r(Text, "\n", &end_str);
            while (line != NULL) {
                char *end_token;
                char *token = strtok_r(line, ",", &end_token);
                while (token != NULL) {
                    id = 0;
                    tipo = 'A';
                    memset(nameGroup, 0, sizeof (nameGroup));
                    memset(nameUser, 0, sizeof (nameUser));
                    id = atoi(token);
                    token = strtok_r(NULL, ",", &end_token);
                    tipo = token[0];
                    token = strtok_r(NULL, ",", &end_token);
                    strcpy(nameGroup, token);
                    token = strtok_r(NULL, ",", &end_token);
                    if (tipo == 'U') {
                        strcpy(nameUser, token);
                        if (strcmp(nameUser, nombre) == 0) {
                            existeUser = 1;
                            break;
                        } else {
                            saveLastUser = id;
                        }
                        token = strtok_r(NULL, ",", &end_token);
                        token = strtok_r(NULL, ",", &end_token);
                    } else if (tipo == 'G') {
                        if (strcmp(nameGroup, grupo) == 0) {
                            existeGrupo = 1;
                        }
                    }
                }
                if (existeUser == 1) {
                    break;
                }
                line = strtok_r(NULL, "\n", &end_str);
            }
            if (existeUser == 1) {
                fclose(archivo_disco);
                cout << "Error, el usuario ya existe" << endl;
                return;
            } else if (existeGrupo == 0) {
                fclose(archivo_disco);
                cout << "Error, el grupo no existe" << endl;
                return;
            } else {
                //Generando el registro del nuevo usuario
                char lineNewUser[40];
                memset(lineNewUser, 0, sizeof (lineNewUser));
                sprintf(lineNewUser, "%d", saveLastUser + 1);
                strcat(lineNewUser, ",U,");
                strcat(lineNewUser, grupo);
                strcat(lineNewUser, ",");
                strcat(lineNewUser, nombre);
                strcat(lineNewUser, ",");
                strcat(lineNewUser, password);
                strcat(lineNewUser, "\n");
                //Concatenar la nueva linea
                strcat(Texto, lineNewUser);
                //Escribiendo
                fs * sis = new fs();
                MKDIR * mkd = new MKDIR();
                mkd->sb_aux = super_bloque;
                mkd->father_aux = users;
                mkd->EscribirTexto(archivo_disco,  Texto);
                super_bloque = mkd->sb_aux;
                users = mkd->father_aux;
                //Actualizando inodo
                fseek(archivo_disco, posUser, SEEK_SET);
                fwrite(&users, sizeof (objetos::inodo), 1, archivo_disco);
                //Actualizar Super Bloque
                fseek(archivo_disco, mbr.mbr_partitions[num_particion].part_start, SEEK_SET);
                fwrite(&super_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
                //obtengo la posicion del journal
                int posJournal =-1;
                int posicion = mbr.mbr_partitions[num_particion].part_start + sizeof (super_bloque);
                int a=0;
                for (int i = posicion; i < super_bloque.s_bm_inode_start; i = i + sizeof (objetos::journal)) {
                    objetos::journal j ;
                    fseek(archivo_disco, i, SEEK_SET);
                    fread(&j, sizeof (objetos::journal), 1, archivo_disco);
                    a++;
                    if (j.estado =='0') {
                        posJournal =i ;
                        break;
                    }
                }
                if(posJournal == -1){
                    cout << "Error, no se pudo escribir en el journal" << endl;
                }else{
                    char comando[256];
                    strcpy(comando,"mkusr -name=");
                    strcat(comando,nombre);
                    strcat(comando," -pwd=");
                    strcat(comando,password);
                    strcat(comando," -grp=");
                    strcat(comando,grupo);
                    objetos::journal * journal = (objetos::journal*)malloc(sizeof (objetos::journal));
                    journal = sis->CrearJornal(usuario->user,comando);
                    fseek(archivo_disco, posJournal, SEEK_SET);
                    fwrite(journal, sizeof (objetos::journal), 1, archivo_disco);
                }
            }
            fclose(archivo_disco);
        }
    }else {
        cout << "Error, la particion no esta montada" << endl;
        return;
    }
}
