#ifndef MKDISK_H
#define MKDISK_H
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "objetos.h"
using namespace std;

class MKDISK{
public:
	//Variables
	int size = 0;
	string path = "";
	int f;
	int u;
	bool fruta;
	char ruta_raid[500];
	char ruta[255];
	char ruta_disco[255];
	char nombre_disco[63];
	char extension[10];
	//Constructor
	MKDISK();
	//Funciones
	char* getRutaRaid(char *path);
	int obtenerSize(int diskSize);
	objetos::MBR crearMBR(int size);
	//Metodos
	void setSize(int size);
	void setRuta(char *path);
	void ejecutar();
	void getRuta(char *path);
	void limpiar();
	void crearDisco(char *path, int tipo);
	void mostrarDatos(MKDISK *disco);
};