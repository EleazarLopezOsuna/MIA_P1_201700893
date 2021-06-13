#ifndef LOGOUT_H
#define LOGOUT_H
#include <QString>
#include "string"
#include <stdio.h>
#include <iostream>
using namespace std;

class LOGOUT
{
public:
    LOGOUT();
    bool salio = false;
    void Salir(LOGOUT *disco);
};
#endif // LOGOUT_H
