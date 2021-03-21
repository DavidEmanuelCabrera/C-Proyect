#ifndef COMPUESTOS_H_INCLUDED
#define COMPUESTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "productos/productos.h"
#include "ListaSimple.h"
#include "productos/listaSimpleProductos.h"
#include "productos/productos.h"
#include "productos/arbolProductos.h"



typedef struct
{
    int idPedido;
    int idCliente;
    int idProducto;
}stPedido; // estructura del archivo


typedef struct _nodoProd
{
    int idPedido;
    stProducto producto;

    struct _nodoProd * siguiente;

}nodoProd;


typedef struct _nodoPedido
{
    int idC;
    char nombre[30];
    char apellido[30];

    nodoProd* lista;
    struct _nodoPedido * siguiente;

}nodoPedido;

//Funciones basicas
nodoPedido * crearNodoListaPedido (char nombreC[],char apellidoC[], int idCliente);
nodoPedido * buscarPedidoID (nodoPedido * listaP, int idCliente);
nodoPedido * buscarUltimoPedido (nodoPedido * lista);

nodoPedido * altaPedidoLDL (nodoPedido * listaP, char nombreC [], char apellidoC[], int idCliente, stProducto productoNuevo, int idPedido);

nodoPedido * generarPedido (nodoPedido * listaPedido, nLista * cliente, nodoArbolStProducto * arbolProd, int idCliente, int idProducto, int idPedidos);

//agregar
nodoPedido * agregarNodoPedidoLista (nodoPedido * listaP, char nombreC[], char apellidoC[],int idCliente);
nodoPedido * agregarAlFinalPedido (nodoPedido * lista, nodoPedido * nuevo);
nodoProd * crearNodoProd(stProducto p, int idPed);
nodoProd * agregarAlPrincipioPedido (nodoProd *listaP,nodoProd*nuevoP);


void pasarldl (FILE * archi, stPedido k, int idPedido, int idCliente, int idProducto);

nodoProd * borrarPedidoId(nodoProd * listaP, int id);

nodoPedido * agregarEnPosicionPedido (nodoPedido * p, nodoProd * nuevo, int id);



#endif // COMPUESTOS_H_INCLUDED
