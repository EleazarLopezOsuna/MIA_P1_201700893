#include "MKFS.h"
#include <math.h>
MKFS::MKFS()
{
    type=2;
    par_id =false;
}
void MKFS::ejecutar_MKFS(lista::list * lista){
	/*
	 * Este metodo sirve para dar comprobar el tipo de formato que vamos a aplicar
	 * 1. Verificamos si la particion esta montada
	 * 2. Asignamos la letra
	 * 3. Obtenemos el disco al cual se va a aplicar el formateo de la particion
	 * 4. Enviamos los datos a su respectivo metodo
	 */
    int letra = id[3];
    MOUNT * nuevo;
    lista::nodoC * disco_montado = nuevo->buscarLetra(letra, lista->first);
    if(disco_montado != NULL){
        lista::nodoP * particion = nuevo-> buscarExistente(id, lista->first);
        if(particion!= NULL){
            FILE * archivo_disco = fopen(disco_montado->path, "rb");
            if(archivo_disco != NULL){
                if(ext2==true){
                    fclose(archivo_disco);
                    formatear_sistema(particion->name, disco_montado->path, 2);
                    cout<<"La particion se formateo con "<<particion->id<<" ext2"<<endl;
                }else if(ext3==true){
                    fclose(archivo_disco);
                     formatear_sistema( particion->name, disco_montado->path, 3);
                     cout<<"La particion se formateo con "<<particion->id<<" en ext3"<<endl;
                }
            }
        }else{
            printf("Error, la particion no esta montada");
        }
    }
}
void MKFS::formatear_sistema(char *name, char *path, int tfs){
	/* 
	 * Metodo para formatear una particion con el sistema de archivos EXT2
	 * 1. Obtenemos la particion
	 * 2. Busco la particion que me interesa
	 * ...Explicacion continua abajo...
	 */
    FILE * archivo_disco = fopen(path, "rb+");
    if(archivo_disco != NULL){
        int pos_part = -1;
        objetos::MBR mbr;
        fseek(archivo_disco,0,SEEK_SET);
        fread(&mbr,sizeof(objetos::MBR),1,archivo_disco);
        for(int i=0; i<4; i++){
             if(strcmp(mbr.mbr_partitions[i].part_name, name)==0){
                 pos_part = i;
                 break;
             }
        }
        /*
         * 3. Calculo las objetos que necesito en el super bloque (formulas se explican mas abajo)
         * 4. Hago un formateo (por si acaso)
         * 5. Creamos el super bloque
         */
        if(pos_part != -1){
        	//tamanio_particion e inicio_particion sirve para la escritura del archivo
            int tamanio_particion = mbr.mbr_partitions[pos_part].part_size;
            int inicio_particion = mbr.mbr_partitions[pos_part].part_start;
            int s = sizeof (objetos::superBloque);// -> tamanio del struct superBloque
            int t = tamanio_particion;// -> tamanio de la particion
            int j = sizeof (objetos::journal);// -> tamanio del struct journal
            int In = sizeof (objetos::inodo);// -> tamanio del struct inodo
            int B = sizeof (objetos::bloqueArchivo);// -> tamanio del struct bloqueArchivo
            int n = (t - s)/(4 + j + In + 3 * B);// Obtengo el numero de objetos
            //Escribo en el disco
            if(type == 2){
                fseek(archivo_disco, inicio_particion, SEEK_SET);
                for(int i=0; i< tamanio_particion ; i++){
                    fputc(0,archivo_disco);
                }
            }
            objetos::superBloque s_bloque;
            s_bloque.s_filesystem_type = tfs;//Tipo de sistema
            s_bloque.s_inodes_count = n;//Numero de inodos
            s_bloque.s_blocks_count = 3 * n;//3 veces el numero de inodos
            s_bloque.s_free_inodes_count = n - 1; //Quito 1 inodo por que debemos crear la root
            s_bloque.s_free_blocks_count = 3 * n - 1; //Quito 1 bloque por que debemos crear la root
            s_bloque.s_mtime = s_bloque.s_umtime = time(0);
            s_bloque.s_mnt_count = 1;
            s_bloque.s_magic = 61267;//Valor decimal de 0xEF53 (pagina 33 del enunciado)
            s_bloque.s_inode_size = sizeof(objetos::inodo);//Size del inodo
            s_bloque.s_block_size = sizeof(objetos::bloqueArchivo);//Size del bloque
            s_bloque.s_bm_inode_start = inicio_particion + sizeof(objetos::superBloque) + (n * sizeof(objetos::journal));//Posicion inicial del bitmap de inodos
            s_bloque.s_bm_block_start = s_bloque.s_bm_inode_start + sizeof(char) * n;//Posicion inicial del bitmap de bloques
            s_bloque.s_inode_start = s_bloque.s_bm_block_start + sizeof(char) * (3 * n);//Posicion del inodo inicial
            s_bloque.s_block_start = s_bloque.s_inode_start + sizeof(objetos::inodo) *n;//Posicion del bloque inicial
            s_bloque.s_first_ino = s_bloque.s_inode_start;//Posicion del primer inodo
            s_bloque.s_first_blo = s_bloque.s_block_start;//Posicion del primer bloque
            objetos::journal  bloque_j;
            bloque_j.estado='0';
            int inicioBitmapInodo = s_bloque.s_inode_start;//Inicializo el bitmap de inodos
            int posicion = inicio_particion + sizeof (objetos::superBloque);//Me posiciono luego del super bloque
            //Escribo el journal
            for (int i = posicion; i < inicioBitmapInodo; i = i + sizeof (objetos::journal)) {
                fseek(archivo_disco, i, SEEK_SET);
                fwrite(&bloque_j, sizeof (objetos::journal), 1, archivo_disco);
            }
            //Escribiendo los bitmap
            escribirBitmapInodos(s_bloque, n, archivo_disco);
            escribirBitmapBloques(s_bloque, archivo_disco);
            fs *sistema = new fs();
          	//Creando el nodo root
            objetos::inodo  root = sistema->Crear_Inodo();
            root.i_uid = 1; //Usuario propietario: root
            root.i_gid = 1; //Grupo al que pertenece root;
            root.i_mtime = time(0); //fecha en la que se modificó el inodo
            root.i_type = '0'; //Es una carpeta
            root.i_perm = 664; //Permisos
            root.block[0] = 0; //Primer apuntador directo a Bloque cero.
           	//Escribiendo la root
            fseek(archivo_disco, s_bloque.s_inode_start, SEEK_SET);
            fwrite(&root, sizeof (objetos::inodo), 1, archivo_disco);
           	//Creando el directorio raiz
            objetos::bloqueCarpeta Bloque ;
            for(int i = 0; i < 4; i++){
                Bloque.b_content[i].b_inodo = -1;
                Bloque.b_content[i].b_name[0] = '\0';
            }
            strcpy(Bloque.b_content[0].b_name, "."); //Actualizando inodo padre y actual
            Bloque.b_content[0].b_inodo = 0;
            strcpy(Bloque.b_content[1].b_name, "..");
            Bloque.b_content[1].b_inodo = 0;
           	//Escribiendo el directorio raiz
            fseek(archivo_disco, s_bloque.s_block_start, SEEK_SET);
            fwrite(&Bloque, sizeof (objetos::bloqueCarpeta), 1, archivo_disco);
            //Actualizando el bitmap de inodo
            sistema->ActualizarBitmap(archivo_disco, s_bloque.s_bm_inode_start, '1');
            s_bloque.s_first_ino = s_bloque.s_first_ino + sizeof (objetos::inodo);
			//Actualizando el bitmap de bloque
			sistema->ActualizarBitmap(archivo_disco, s_bloque.s_bm_block_start, 'C');
            s_bloque.s_first_blo = s_bloque.s_first_blo + sizeof (objetos::bloqueCarpeta);
            //Escribiendo super bloque
            fseek(archivo_disco, mbr.mbr_partitions[pos_part].part_start, SEEK_SET);
            fwrite(&s_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            //Creando el archivo de usuarios
            crearArchivoUsuarios(Bloque, archivo_disco, s_bloque, sistema);
            //Actualizando el super bloque
            s_bloque.s_first_ino = s_bloque.s_first_ino + sizeof (objetos::inodo);
            s_bloque.s_first_blo = s_bloque.s_first_blo + sizeof (objetos::bloqueCarpeta);
            s_bloque.s_free_blocks_count--;
            s_bloque.s_free_inodes_count--;
            //Escribiendo el super bloque
            fseek(archivo_disco, mbr.mbr_partitions[pos_part].part_start, SEEK_SET);
            fwrite(&s_bloque, sizeof (objetos::superBloque), 1, archivo_disco);
            fclose(archivo_disco);
        }else{
            printf("** ERROR: no se encontro la particion en el disco ** \n");
        }
    }
}
int MKFS::PosBitmap(int inicio, int max, int tamanio) {
    int a = ((max - inicio) / tamanio);
    return a;
}
void MKFS::escribirBitmapInodos(objetos::superBloque s_bloque, int n, FILE* archivo_disco){
	int contador = 0;
	int r = s_bloque.s_bm_inode_start;
	while(contador < n){
		objetos::bitmap bMap;
        bMap.state = '0';
		fseek(archivo_disco, r, SEEK_SET);
		fwrite(&bMap, sizeof(objetos::bitmap), 1, archivo_disco);
		r++;
		contador++;
	}
}
void MKFS::escribirBitmapBloques(objetos::superBloque s_bloque, FILE* archivo_disco){
	int contador = 0;
	int r = s_bloque.s_bm_inode_start;
	int n_bloques = s_bloque.s_inodes_count * 3;
	while(contador < n_bloques){
		objetos::bitmap bMap;
        bMap.state = '0';
		fseek(archivo_disco, r, SEEK_SET);
		fwrite(&bMap, sizeof(objetos::bitmap), 1, archivo_disco);
		r++;
		contador++;
	}
}
void MKFS::crearArchivoUsuarios(objetos::bloqueCarpeta Bloque, FILE *archivo_disco, objetos::superBloque s_bloque, fs *sistema){
	//Agregando el apuntador
    strcpy(Bloque.b_content[2].b_name, "users.txt");
    Bloque.b_content[2].b_inodo = sistema->ObtenerNumeroInodo(s_bloque);
	//Actualizando el bloque root
	fseek(archivo_disco, s_bloque.s_block_start, SEEK_SET);
    fwrite(&Bloque, sizeof(objetos::bloqueCarpeta), 1, archivo_disco);
    //Creando el inodo del archivo users.i_txt
    objetos::inodo users = sistema->Crear_Inodo();
    users.i_uid = 1; //Usuario propietario: root
    users.i_gid = 1; //Grupo al que pertenece root;
    time_t now; //fecha en la que se modificó el inodo
    now = time(0);
    users.i_mtime = now;
    users.i_type = '1'; //Es un archivo
    users.i_perm = 664; //Permisos
    users.block[0] = sistema->ObtenerNumeroBloque(s_bloque); //Primer apuntador directo a Bloque dos
    //Escribiendo el inodo
    fseek(archivo_disco, s_bloque.s_first_ino, SEEK_SET);
    fwrite(&users, sizeof (objetos::inodo), 1, archivo_disco);
    //Creando el bloque de archivo
    objetos::bloqueArchivo cont;
    cont.b_content[0] = '\0';
    strcpy(cont.b_content, "1,G,root\n1,U,root,root,123\n");
    //Escribiendo el bloque
    fseek(archivo_disco, s_bloque.s_first_blo, SEEK_SET);
    fwrite(&cont, sizeof(objetos::bloqueArchivo), 1, archivo_disco);
    //Modificando el bitmap de inodo
    int bMap = PosBitmap(s_bloque.s_inode_start, s_bloque.s_first_ino, sizeof (objetos::inodo));
    int posBit = s_bloque.s_bm_inode_start + (bMap * sizeof (objetos::bitmap));
    //Reescribiendo el bitmap de inodo
    objetos::bitmap bip;
    //Obtengo el bitmap
    	fseek(archivo_disco, posBit, SEEK_SET);
        fread(&bip, sizeof (objetos::bitmap), 1, archivo_disco);
    //Modifico y escribo en el bitmap
        bip.state = '1';
    	fseek(archivo_disco, posBit, SEEK_SET);
        fwrite(&bip, sizeof (objetos::bitmap), 1, archivo_disco);
    //Modificando el bitmap de bloque
    bMap = PosBitmap(s_bloque.s_block_start, s_bloque.s_first_blo, sizeof (objetos::bloqueCarpeta));
    posBit = s_bloque.s_bm_block_start + (bMap * sizeof (objetos::bitmap));
    //Reescribiendo el bitmap de bloque
    //Obtengo el bitmap
    	fseek(archivo_disco, posBit, SEEK_SET);
        fread(&bip, sizeof (objetos::bitmap), 1, archivo_disco);
   	//Modifico y escribo en el bitmap
        bip.state = 'A';
    	fseek(archivo_disco, posBit, SEEK_SET);
        fwrite(&bip, sizeof (objetos::bitmap), 1, archivo_disco);
}
