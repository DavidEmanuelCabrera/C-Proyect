#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"


typedef struct _nodo
{
    stCliente dato;
    struct _nodo * siguiente;
} nLista;


//funciones basicas lista
nLista * inicLista();
nLista * crearNodo (stCliente dato);
nLista * agregarPpio2 (nLista * lista, nLista* nNodo);
nLista * agregarPpio (nLista * lista, nLista * nNodo);

//busquedas
nLista * buscarUltimo (nLista * lista);
nLista * buscarNodoNombre (nLista * lista, char nombre[]);
nLista * buscarNodoUserName (nLista * lista, char username[]);
nLista * buscarNodoID (nLista * lista, int id);
nLista * subProgBuscarNodoID (nLista * lista);

//agregar
nLista * agregarAlFinal (nLista * lista, nLista * nuevoN);
nLista * agregarEnOrden (nLista * lista, nLista * nuevoN);

//borrar
nLista * borrarNodo (nLista * lista, char nombre[]);
nLista * borrarPrimero (nLista * lista);
nLista * borrarLista (nLista * lista);
nLista * eliminarPrimero (nLista * lista);
nLista* eliminarUltimo (nLista * lista);

//mostrar
void mostrarLista (nLista * lista);
void mostrarNodo ( nLista * n);

//modificaciones
void modificarAltaCliente (nLista ** lista,  int id);
void  modificarBajaCliente (nLista ** lista, int id);
nLista ** subProgModNombreCliente (nLista ** lista, int id);
void modificarNombreCliente2 (nLista ** lista, int id, char nombre[]);
void modificarUnClienteArchivo (nLista * cliente, char archiCliente []);
nLista ** subProgModApellidoCliente (nLista ** lista, int id);
void modificarApellidoCliente (nLista ** lista, int id, char apellido[]);
void subProgModUserNameCliente (nLista ** lista, int id);
void modificarUserNameCliente (nLista ** lista, int id, char userName[]);
void subProgModPassCliente (nLista ** lista, int id);
void modificarPassCliente (nLista ** lista, int id, char pass[]);
void subProgModDireCliente (nLista * lista, int id);
void modificarDireCliente (nLista ** lista, int id, char direccion[]);
void subProgModMailCliente(nLista ** lista, int id);
void modificarMailCliente(nLista ** lista, int id, char mail[]);
//Persistencia de datos
nLista * subProgIngresaCliente (stCliente p, nLista * lista);
nLista * archivo2listaCliente (char archivo[], nLista * lista);
void lista2archivoCliente (char archivo[], nLista * lista, char aperturaArchi []);
void data2ArchivoCliente (stCliente k, nLista * c, FILE * archi);


#endif // LISTASIMPLE_H_INCLUDED
