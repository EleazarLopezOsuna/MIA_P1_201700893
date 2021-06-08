#ifndef RMDISK_H
#define RMDISK_H
#include <QString>
#include "string"
#include <iostream>
using namespace std;

class RMDISK{
public:
	//Variables
	string path = "";
	char ruta[255];
	bool f_ruta;
	//Constructor
	MKDISK();
	//Metodos
	void setRuta(char * ruta);
	void limpiar();
	void ejecutar();
};
#endif;