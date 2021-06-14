#ifndef RMUSR_H
#define RMUSR_H
#include <QString>
#include "string"
#include <iostream>
#include <objetos.h>
#include <lista.h>
#include <MOUNT.h>
#include <fs.h>
#include <LOGIN.h>
using namespace std;


class RMUSR
{
public:
    RMUSR();
    string usr="";
    void EliminarUsuario(RMUSR*usuario);
    char nombre[10];
    void limpar();
    void ejecutar_RMUSR(objetos::activeUser * usuario, lista::list * lista);
};

#endif // RMUSR_H
