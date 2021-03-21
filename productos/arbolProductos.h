#ifndef ARBOLPRODUCTOS_H_INCLUDED
#define ARBOLPRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "listaSimpleProductos.h"


typedef struct
{
    stProducto p;
    struct nodoArbolStProducto *izq;
    struct nodoArbolStProducto *der;

} nodoArbolStProducto;

//Funciones basicas arbol
nodoArbolStProducto *inicArbol ();
nodoArbolStProducto *crearNodoArbol (stProducto p);

//Funciones de busqueda
nodoArbolStProducto *buscarProductoArbolporID (nodoArbolStProducto* arbolP,int id);
nodoArbolStProducto* buscarProductoArbolporMarca(nodoArbolStProducto*arbolP,char marca[]);
nodoArbolStProducto *buscarProductoArbolporEstado (nodoArbolStProducto* arbolP,int estado);

//Funciones de insercion
nodoArbolStProducto *insertarNodoArbol(nodoArbolStProducto* arbolP,nodoArbolStProducto* nuevoP);//(ordenado por idProducto)
nodoArbolStProducto*insertarNodoPorNombre (nodoArbolStProducto*arbolP, stProducto p);//ordenado por nombre

//borrar
nodoArbolStProducto *borrarUnNodoArbolSegunID (nodoArbolStProducto* arbolP,int id);
nodoArbolStProducto *borrarUnNodoArbol (nodoArbolStProducto* arbolP,int id);
int subProgramaBorrarNodoArbol (int id);

//mostrar Arbol
void mostrarArbolProductosPreOrden (nodoArbolStProducto* arbolP); /// R I D
void mostrarArbolProductosEnOrden (nodoArbolStProducto* arbolP); ///  I R D
void mostrarArbolProductosPostOrden (nodoArbolStProducto* arbolP);/// I D R
//mostrarArbol  (son tres funciones, recorriendo inOrder, postOrder, preOrder)
void mostrarProductoPorID (nodoArbolStProducto*arbolP, int id);

//Funciones para modificar..

void subProgramaModificarProdNombre (nodoArbolStProducto**arbolP, int id);
void subProgramaModificarProdMarca (nodoArbolStProducto**arbolP, int id);
void subProgramaModificarProdPrecio (nodoArbolStProducto**arbolP, int id);
void subProgramaModificarProdEstado (nodoArbolStProducto**arbolP,int id);


///persistencia de datos

nodoArbolStProducto *archivoToArbolProductos (char arProductos[],nodoArbolStProducto*arbolP);
void arbolToArchivo (nodoArbolStProducto * arbolP, stProducto p,FILE * archi);
int subProgramaArbol2Arreglo (stProducto p[], int dim, stProducto k);
int agregarArreglo (stProducto p[], int i, stProducto k);
void subProgArbol2Archivo (nodoArbolStProducto*arbolP, char arProductos[]);

#endif // ARBOLPRODUCTOS_H_INCLUDED
