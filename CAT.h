#ifndef CAT_H
#define CAT_H
#include <QString>
#include "string"
#include <iostream>
#include <vector>  //for std::vector
#include "objetos.h"
#include "lista.h"
#include <MOUNT.h>
#include <stdio.h>
#include <fs.h>
#include "MKDIR.h"
using namespace std;

class CAT
{
public:
    CAT();
    char ruta[256];
    struct LIST{
        char path[300];
    };
    typedef struct LIST LIST;
    void ejecutar_CAT(lista::list * lista , objetos::activeUser * usuario);
	vector <string>files;
    void Mostrar(CAT*file);
};
#endif // CAT_H
