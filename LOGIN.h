#ifndef LOGIN_H
#define LOGIN_H
#include <objetos.h>
#include <lista.h>
#include <stdio.h>
#include <MOUNT.h>
#include <fs.h>
using namespace std;

class LOGIN
{
public:
    LOGIN();
    string password="";
    void Logearse(LOGIN *disco);
    char user[15];
        char pwd[15];
        char id[10];
        bool par_user;
        bool par_pass;
        bool par_id;
        objetos::activeUser * usuario;
        void limpiar();
        void ejecutar_LOGIN(lista::list * lista , objetos::activeUser * usuario);
        objetos::superBloque  obtener_SuperBlock(FILE * archivo_disco, char * name);
        int buscar_user( lista::list *lista, FILE * archivo_disco, objetos::superBloque superbloque);
        char* ObtenerTexto(FILE *fp, objetos::superBloque super, objetos::inodo * node);
        int ObtenerIdGrupo(char texto[], char name[]);
};
#endif // LOGIN_H
