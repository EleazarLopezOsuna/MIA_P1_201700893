#ifndef MOUNT_H
#define MOUNT_H
#include <QString>
#include "string"
#include <lista.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;
class MOUNT{
public:
	//Variables
	string path = "";
	string name = "";
	objetos::MOUNT obj_mount;
	objetos::MOUNT obj_unmount;
	bool f_path;
	bool f_name;
	bool f_id;
	//Constructores
	MOUNT(int type);
	MOUNT();
	//Metodos
	void montar(mount*);
	void limpiar_m();
	void limpiar_u();
	void eliminar(lista::list **, int, lista::nodoC *pivote);
	void mostrar(lista::nodoC *pivote);
	void ejecutarM(objetos::MOUNT, lista::list *pivote);
	void agregarP(objetos::partList **, objetos::MOUNT);
	void insertarP(lista::listaParticiones **, lista::nodoC *, objetos::MOUNT, lista::nodoP *);
	void eliminarP(lista::listaParticiones **, objetos::UNMOUNT, lista::nodoC *);
	void ejecutarU(lista::list *, objetos::UNMOUNT);
	void eliminarName(lista::lista **, char [], lista::nodoC *pivote);
	//Funciones
	lista::nodoC *insertar(lista::list **, int, objetos::MOUNT, lista::nodoC *);
	lista::nodoC *buscar(char path[], lista::nodoC *pivote);
	lista::nodoP *crearP(objetos::MOUNT);
	lista::nodoP *buscarP(char name[], lista::nodoC *);
	int no_existe_logica(objetos::EBR, objetos::MOUNT, objetos::MBR);
	lista::nodoP *buscar_id(objetos::UNMOUNT, lista::nodoC *pivote);
	lista::nodoC *buscarLetra(int, lista::nodoC *pivote);
	lista::nodoP *buscar_id(objetos::REP, lista::nodoC *);
	lista::nodoP *buscarExistente(char *, lista::nodoC *);
};

#endif