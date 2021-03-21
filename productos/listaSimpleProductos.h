#ifndef LISTASIMPLEPRODUCTOS_H_INCLUDED
#define LISTASIMPLEPRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "productos.h"

typedef struct
{
    stProducto p;
    struct nodoListaProducto * sig;
}nodoListaProducto;


//Funciones basicas manejo de lista
nodoListaProducto *inicListaProducto();
nodoListaProducto *crearNodoListaProducto(stProducto p);
//OPCIÓN 2 DE CREAR NODO
nodoListaProducto * crearNodoListaProducto2(int idProd, char nombreProd[], char marcaProd[], float precioProd);
//nodoListaProducto * crearNodoListaProducto2(stProducto k,int idProd, char nombreProd[], char marcaProd[], float precioProd)

nodoListaProducto *agregarAlPrincipioProducto(nodoListaProducto*listaP,nodoListaProducto*nuevoP);
nodoListaProducto *agregarAlFinalProducto(nodoListaProducto*listaP,nodoListaProducto*nuevo);
nodoListaProducto *agregarEnOrdenPorNombreDeProducto(nodoListaProducto*listaP,nodoListaProducto*nuevoP);

//Funciones de busqueda
nodoListaProducto *buscarUltimoProducto(nodoListaProducto*listaP);
nodoListaProducto *buscarProductoID (nodoListaProducto*listaP, int datoID);
nodoListaProducto *buscarProductoNombre (nodoListaProducto*listaP,char nombre[20]);
//Funciones para borrar
nodoListaProducto *borrarProductoPorId(nodoListaProducto*listaP,int id);
nodoListaProducto *borrarProductoPorNombre(nodoListaProducto*listaP,char nombre[20]);

//Fn de muestra, cuenta, pos
void mostrarListaProductos(nodoListaProducto*listaP);
int cuentaNodosLista(nodoListaProducto*listaP);
stProducto retornaProducto (nodoListaProducto*listaP,int pos, int inicio);

//Persistencia de datos.
nodoListaProducto *archivoToListaProductos (char arProductos[],nodoListaProducto* listaP);
void listaProdToArchiProd (char archiProductos[], nodoListaProducto * listaP);





#endif // LISTASIMPLEPRODUCTOS_H_INCLUDED
