#ifndef MKGRP_H
#define MKGRP_H
#include <QString>
#include "string"
#include <iostream>
#include <objetos.h>
#include <lista.h>
#include <MOUNT.h>
#include <fs.h>
#include "LOGIN.h"
#include "Mkdir.h"

using namespace std;

class mkgrp
{
public:
    mkgrp();
    char nombre[10];
        char password[10];
        char * grupo;
        int tipo; // 1 para grupo / 2 para usuario
        bool par_usr;
        bool par_pwd;
        bool par_grp;
        void limpiar();
        void ejecutar(objetos::activeUser * usuario, lista::list * lista );
        void ejecutar_mkgrp(objetos::activeUser * usuario,lista::list * lista );
        void ejecutar_mkusr(objetos::activeUser * usuario,lista::list * lista );
};
#endif // MKGRP_H
