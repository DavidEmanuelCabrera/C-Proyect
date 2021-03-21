#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

//const char arProductos [] = "archivoProductos.dat";

///Estructura del producto
typedef struct {
   int idProducto;
   char nombre[30];
   char marca[20];
   float precio;
   int eliminado;  // indica 1 o 0 si el producto fue eliminado
} stProducto;


void cargarUnProductoArchi (char arProductos[]);
void cargarMuchosProductos ();
void mostrarUnProducto ();
void estadoProducto ();
void mostrarProductos ();
//int buscarPosProducto (stProducto p, char nombre[]);
//void darDeBajaProducto (int posicion);
int cuentaRegistrosProd (char arProductos[]);
void bajaProductoParaMenu ();

int buscarPosProducto (char archiProd[], stProducto p, char nombre[]);

void darDeBajaProducto (char archiProductos[], int posicion);


#endif // PRODUCTOS_H_INCLUDED
