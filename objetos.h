/* Aca se definiran las estructuras requeridas por el programa.
 * estas estructuras fueron definidas por el auxiliar en el 
 * enunciado del Proyecto 1
 */
#ifndef OBJETOS_H
#define OBJETOS_H
#include <time.h>
#include <stdio.h>

class objetos{
public:
	objetos();
	struct part{
		char part_status;
		char part_type;
		char part_fit;
		int part_start;
		int part_size;
		char part_name[16];
	};
	struct MBR{
		int mbr_tamano;
		time_t mbr_fecha_creacion;
		int mbr_disk_signature;
		int mbr_disk_fit;
		part mbr_partitions [4];
	};
	struct EBR{
		char part_status;
		char part_fit;
		int part_start;
		int part_size;
		int part_next;
		int part_name[16];
	};
	struct MOUNT{
		char path[255];
		char name[16];
		char id[10];
		int f_paht;
		int f_name;
		int error;
	};
	struct UNMOUNT{
		char id[10];
		int f_id;
		int error;
	};
	struct REP{
		char path[255];
		char ruta[255];
		char id[10];
		int f_disk;
		int f_mbr;
		int f_rep;
		int f_nombre;
		int f_path;
                int f_id;
	};
	struct mountedPart{
		char status;
		char id[3];
		char name[16];
		struct mountedPart *next;
	};
	struct partList{
		char letra;
		char status;
		char path[255];
		char partition[27];
		int size;
		struct mountedPart *head;
		struct mountedPart *tail;
	};

	struct superBloque{
		int s_filesystem_type;
		int s_inodes_count;
		int s_blocks_count;
		int s_free_blocks_count;
		int s_free_inodes_count;
		time_t s_mtime;
		time_t s_umtime;
		int s_mnt_count;
		int s_magic;
		int s_inode_size;
		int s_block_size;
		int s_first_ino;
		int s_first_blo;
		int s_bm_inode_start;
		int s_bm_block_start;
		int s_inode_start;
		int s_block_start;
	};
	struct journal{
		time_t hora;
		char user[12];
		char operacion[255];
		char estado;
	};
	struct inodo{
		int i_uid;
		int i_gid;
		int i_size;
		time_t i_atime;
		time_t i_ctime;
		time_t i_mtime;
		int block[15];
		char i_type;
		int i_perm;
	};
	struct contenido{
		char b_name[12];
		int b_inodo;
	};
	struct bloqueCarpeta{
		contenido b_content[4];
	};
	struct bloqueArchivo{
		char b_content[64];
	};
	struct bloqueApuntadores{
		int b_pointers[64];
	};
	struct bitmap{
		char state;
	};
	struct activeUser{
		int estado;
		char user[15];
		int id_usuario;
		int grupo;
		char particion[63];
		char ruta_disco[255];
	};
	struct content{
		char contenido[1024];
	};
};

#endif
