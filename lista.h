#ifndef LISTA_H
#define LISTA_H
#include <objetos.h>

class lista{
public:
	lista();
	struct nodoP{
        char id[10];
		char name[16];
		struct nodoP *next;
		struct nodoP *prev;
	};
	struct listaParticiones{
		int size;
		struct nodoP *first;
		struct nodoP *last;
    };
	struct nodoC{
		int character;
		char path[255];
		struct nodoC *next;
		struct nodoC *prev;
		struct listaParticiones *particiones;
    };
	struct list{
		int size;
        struct nodoC *first;
		struct nodoC *last;
    };
    typedef struct list listx;
    typedef struct nodoP nodoP;
    typedef struct nodoC nodoC;
    typedef struct listaParticiones listaParticiones;
};
#endif
