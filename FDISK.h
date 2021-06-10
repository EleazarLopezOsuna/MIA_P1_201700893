#ifndef FDISK_H
#define FDISK_H
#include <QString>
#include "string"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <lista.h>
#include <MOUNT.h>
using namespace std;

class FDISK{
public:
	//Constructor
	FDISK();
	//Variables
	string u, f, name;
	int size, type, fit, unit, borrar, add, size_add, operacion;
	char path[255];
	char nombre[255];
	bool f_nombre, f_path;
	//Metodos
	void infoDisco(FDISK *disco);
	void limpiar();
	void setName(char nombre[]);
	void setRuta(char ruta[]);
	void ejecutar(lista::list *lista);
	void nuevaParticion(objetos::MBR mbr, int size);
	void ordenamiento(objetos::MBR mbr);
	void crearLogica(objetos::MBR mbr, int size, int extendida);
	void eliminarParticion(objetos::MBR mbr, lista::list *listx);
	void eliminarFull(objetos::MBR mbr, char path[], int particion);
	//Funciones
	int calculoInicio(objetos::MBR mbr, int size, int disponible, int start);
	int calculoFit(objetos::MBR mbr, int size, int disponible, int start);
	objetos::EBR crearEBR(int size, int start, int next);
	int particionE(objetos::MBR mbr, objetos::EBR ebr, int pos);
	int no_existe_logica(objetos::EBR ebr, objetos::MBR mbr);
	objetos::EBR existe_logica(objetos::EBR ebr, char nombre[], char path[], objetos::MBR mbr);
};
#endif