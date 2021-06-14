#ifndef RMGRP_H
#define RMGRP_H
#include <QString>
#include "string"
#include <iostream>
#include <objetos.h>
#include <lista.h>
#include <MOUNT.h>
#include <fs.h>
#include <LOGIN.h>
using namespace std;

class RMGRP
{
public:
    RMGRP();
    string name="";
    void ELiminarGrupo(RMGRP*grupo);
    char nombre[10];
    void limpar();
    void ejecutar_RMGRP(objetos::activeUser * usuario, lista::list * lista);
};

#endif // RMGRP_H
