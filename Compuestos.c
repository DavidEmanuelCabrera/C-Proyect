#include "Compuestos.h"


void arreglo2Matriz (stProducto ar[], int dim, int f, int c, char matriz[f][c])
{
    int i= 0;
    char producto [30];
    while (i < dim && i < f)
    {
        strcpy(matriz[i],ar[i].nombre);
        i++;
    }
    return i;
}

///-------------------------------MOSTRAR PEDIDOS -----------------------------------------------------------///

void mostrarArchivoPedidos (char archivoP [])
{
    FILE * archi = fopen(archivoP, "rb");
    stPedido c;
    if(archi)
    {
        while (fread(&c, sizeof(stPedido), 1, archi)> 0)
        {
            mostrarRegistro(c);
        }
        CerrarArchivo(archi);
    }
}

void mostrarRegistro (stPedido c)
{
    puts("-----------------------------------\n");
    printf("ID cliente:     %d \n", c.idCliente);
    printf("Id Pedido:      %d\n", c.idPedido);
    printf("Id Producto:    %d\n", c.idProducto);
    puts("-----------------------------------\n");

}

void mostrarPedidosDeUNCLIENTE (nodoPedido * p)
{
    color (9);
    puts( "-----------------   CLIENTE  ---------------------\n");
    color(7);
    color (9);
    printf("Nombre:     ");
    color(7);

    printf("%s \n", p->nombre);
    color (9);
    printf("Apellido:   ");
    color(7);

    printf("%s \n", p->apellido);

    color (9);
    printf("ID cliente: ");
    color(7);

    printf("%d \n", p->idC);

    mostrarListaPedidos(p->lista);
}

void mostrarListaClientePedidos (nodoPedido * p)
{
    while (p)
    {
        mostrarPedidosDeUNCLIENTE(p);
        p = p->siguiente;
    }
}

void mostrarListaPedidos (nodoProd * lista)
{
    while (lista)
    {
        puts("-------------------------------\n");
        color(12);
        printf("Pedido n°: %d\n", lista->idPedido);
        color(7);
        puts("-------------------------------\n");
        mostrarUnProducto(lista->producto);
        lista = lista->siguiente;
    }
}

void mostrarPedidos (nodoPedido * p, int id)
{
    nodoPedido * aux  = buscarPedidoID(p, id);

    if (aux)
        mostrarPedidosDeUNCLIENTE(aux);
    else
    {
        color(4);
        printf("Todavía no se registran pedidos\n");
        color(7);
    }

}

///---------------------------- ARCHIVO 2 LDL ----------------------------------------------------------------///
nodoPedido * archivo2Ldl (char archivoPedido[],nLista * cliente, nodoArbolStProducto * arbolProd, nodoPedido * listaPedido)
{
    FILE * archi = fopen(archivoPedido, "rb");
    stPedido a;

    if (archi)
    {
        while (fread(&a, sizeof(stPedido),1,archi)>0)
        {
            listaPedido = generarPedido(listaPedido,cliente, arbolProd, a.idCliente, a.idProducto, a.idPedido);
        }
        CerrarArchivo(archi);
    }
    return listaPedido;
}

nodoPedido * generarPedido (nodoPedido * listaPedido, nLista * cliente, nodoArbolStProducto * arbolProd, int idCliente, int idProducto, int idPedidos)
{

    nLista * aux = buscarNodoID(cliente, idCliente);
//            system("pause");
    nodoArbolStProducto * aux2 = buscarProductoArbolporID (arbolProd, idProducto);
/// HASTA AHORA MUESTRA TODO CORRECTAMENTE

//    listaPedido = altaPedidoLDL(listaPedido, aux->dato.nombre,aux->dato.apellido, idCliente, idProducto, aux2->p.nombre, aux2->p.marca, aux2->p.precio);
    listaPedido = altaPedidoLDL(listaPedido, aux->dato.nombre,aux->dato.apellido, idCliente, aux2->p, idPedidos);
    return listaPedido;
}





//nodoPedido * altaPedidoLDL (nodoPedido * listaP, char nombreC [], char apellidoC[], int idCliente, int idProd, char nombreProd[], char marcaProd[], float precioProd)
nodoPedido * altaPedidoLDL (nodoPedido * listaP, char nombreC [], char apellidoC[], int idCliente, stProducto productoNuevo, int idPedido)
{


    nodoProd * aux = crearNodoProd (productoNuevo, idPedido);
    nodoPedido * pos = buscarPedidoID(listaP, idCliente);



    if (!pos)
    {
        listaP = agregarNodoPedidoLista(listaP, nombreC, apellidoC, idCliente);
        listaP->lista = agregarAlPrincipioPedido(listaP->lista, aux);

    }
    else
    {
        pos->lista = agregarAlPrincipioPedido(pos->lista, aux);
    }


    return listaP;
}

nodoPedido * agregarEnPosicionPedido (nodoPedido * p, nodoProd * nuevo, int id)
{
    while (id != p->idC)
    {
        p = p->siguiente;
    }
    if (p)
    {
        p->lista = agregarAlPrincipioPedido(p, nuevo);
    }
    return p;
}



//----------------------------FN AUXILIARES DEL ALTA ------------------------------------------//
nodoProd * agregarAlPrincipioPedido (nodoProd *listaP,nodoProd*nuevoP)
{
    if (!listaP)
    {
        listaP = nuevoP;
    }
    else
    {
        nuevoP->siguiente = listaP;
        listaP = nuevoP;
    }
    return listaP;
}

nodoPedido * agregarAlPrincipioClientePedido (nodoPedido *listaP,nodoPedido *nuevoP)
{
    if (!listaP)
        listaP = nuevoP;
    else
    {
        nuevoP->siguiente = listaP;
        listaP = nuevoP;
    }
    return listaP;
}

nodoProd * crearNodoProd(stProducto p, int idPed)
{
    nodoProd*aux = (nodoProd*)malloc(sizeof(nodoProd));
    aux->idPedido = idPed;

    aux->producto = p;
    aux->siguiente = NULL;

    return aux;
}

nodoPedido * inicListaPedidos ()
{
    return NULL;
}

nodoPedido * crearNodoListaPedido (char nombreC[],char apellidoC[], int idCliente)
{
    nodoPedido * aux = (nodoPedido*) malloc(sizeof(nodoPedido));
    strcpy(aux->nombre, nombreC);
    strcpy(aux->apellido, apellidoC);
    aux->idC = idCliente;
    aux->lista = inicListaPedidos ();

    aux->siguiente = NULL;
}
// LAS OTRAS FUNCIONES DE CREAR NODOS SE ENCUENTRAN EN LAS LIBRERÍAS DE PRODUCTO YA QUE USO SUS ESTRUCTURAS.


nodoPedido * buscarPedidoID (nodoPedido * listaP, int idCliente)
{
    nodoPedido * aux = inicListaPedidos();

    while (listaP) // agregar la segunda condición de corte para que no siga corriendo.
    {
        if (idCliente == listaP->idC)
            aux = listaP;

        listaP = listaP->siguiente;

    }

    return aux;
}
//nodoProd * BajaNodoProdID (nodoProd * listaP, int idPedido)
//{
//    nodoProd * aux = listaP;
//    if (listaP)
//    {
//        while ((aux) && (aux->idPedido != idPedido))
//        {
//            aux = aux->siguiente;
//        }
//        if (aux)
//        {
//            aux->activo = 1;
//        }
//        mostrarListaPedidos(listaP);
//        system("pause");
//    }
//    return listaP;
//}
//----------------------------------------- CONTINUAR FN AUXILIARES


nodoPedido * buscarUltimoPedido (nodoPedido * lista)
{
    nodoPedido * ultimo = lista;
    if (ultimo)
    {
        while (ultimo->siguiente)
            ultimo = ultimo->siguiente;
    }


    return ultimo;
}

nodoPedido * agregarNodoPedidoLista (nodoPedido * listaP, char nombreC[], char apellidoC[],int idCliente)
{
    nodoPedido * nuevo = crearNodoListaPedido(nombreC,apellidoC,idCliente);
//    printf(" \n CLIENTE A AGREGAR ----------------------------------------\n");
//      mostrarListaClientePedidos(nuevo, 0);
//    system("pause");


    // aca
    listaP = agregarAlPrincipioClientePedido(listaP, nuevo);

//    listaP = agregarAlFinalPedido(listaP, nuevo);
    // no me esta agregando el nuevo nodo.
//      mostrarListaClientePedidos(listaP, 1);
//    system("pause");
    return listaP;
}

nodoPedido * agregarAlFinalPedido (nodoPedido * lista, nodoPedido * nuevo)
{
    nodoPedido * aux = inicListaPedidos();

    if (!lista)
    {

        lista = nuevo;
    }
    else
    {
        aux = buscarUltimoPedido(lista);
// encuentra el ultimo cliente
//        // pero no me agrega el nuevo dsp del ultimo.
        aux->siguiente = nuevo;

    }

    return lista;
}

//---------------------------------------------------------------------------------------------//


///---------------------- FN PARA PASAR PRODUCTOS AL ARREGLO -----------------------------------------///



int archivo2ArrayProducto (char archivo[], stProducto p[], int dim)
{
    FILE * archi = fopen (archivo, "rb");

    stProducto k;
    int i = 0;

    if (archi != NULL)
    {
        while (fread(&k, sizeof(stProducto), 1, archi)>0 && i< dim)
        {

//            p[i].idProducto = k.idProducto;
//            strcpy(p[i].nombre, k.nombre);
//            strcpy(p[i].marca, k.marca);
//            p[i].precio = k.precio;
//            p[i].eliminado = k.eliminado;
            agregarProdArreglo(p, i, k);
            i++;
        }
    }
    cerrarArchi(archi);

    return i; // retorno los validos del arreglo.
}

void agregarProdArreglo (stProducto p[], int i, stProducto k)
{
    p[i].idProducto = k.idProducto;
    strcpy(p[i].nombre, k.nombre);
    strcpy(p[i].marca, k.marca);
    p[i].precio = k.precio;
    p[i].eliminado = k.eliminado;
}
///---------------------------------------------------------------///

//int productosAcumulados(FILE * archi)
//{
//    int i = 0;
//
//    fseek(archi,0,SEEK_END);///indicador de posicion al final
//
//    i=ftell(archi)/sizeof(stProducto);/// i toma el valor de cantidad de bytes del archivo dividio en los bytes de un cliente
//
//    return i;///retornamos cantidad de registros en el archivo
//}
int productosAcumulados(char archProducto[])
{
    FILE * archi= archi=fopen(archProducto,"rb");
    int i = 0;

    if(archi!=NULL)///si esta todo ok retorna puntero a FILE
    {
        fseek(archi,0,SEEK_END);///indicador de posicion al final

        i=ftell(archi)/sizeof(stProducto);/// i toma el valor de cantidad de bytes del archivo dividio en los bytes de un cliente

        CerrarArchivo(archi);///cerramos el archivo
    }

    return i;///retornamos cantidad de registros en el archivo
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

int idUltimoPedido (char archiPedido[])
{
    int rta;
    FILE * archi = fopen(archiPedido, "rb");
    stPedido k;
    if (archi)
    {
        fread(&k, sizeof(stPedido), 1, archi);
        rta = k.idPedido;
        CerrarArchivo(archi);
    }

    return rta;
}

int pedidosAcumulados(char archPedidos[])
{
    FILE * archi= archi=fopen(archPedidos,"rb");
    int i = 0;

    if(archi!=NULL)///si esta todo ok retorna puntero a FILE
    {
        fseek(archi,0,SEEK_END);///indicador de posicion al final

        i=ftell(archi)/sizeof(stPedido);/// i toma el valor de cantidad de bytes del archivo dividio en los bytes de un cliente

        CerrarArchivo(archi);///cerramos el archivo
    }

    return i;///retornamos cantidad de registros en el archivo
}
///-------------------------------------------------------------------------------------------------------------///

void ldl2Archivo (nodoPedido * a, char archivo[], char aperturaDeArchivo [])
{
    int i = 0;
    FILE * archi = fopen(archivo, aperturaDeArchivo);
    stPedido b;
    int idC;
    int idPed;
    int idProd;

    if (archi)
    {
        while (a)
        {
            while (a->lista)
            {

                idC= a->idC;
                idPed = a->lista->idPedido;
                idProd = a->lista->producto.idProducto;

                pasarldl(archi, b, idPed,idC, idProd);
                a->lista = a->lista->siguiente;
            }

            a = a->siguiente;
        }
        fclose(archi);
    }

}
void pasarldl (FILE * archi, stPedido k, int idPedido, int idCliente, int idProducto)
{
    k.idCliente = idCliente;
    k.idPedido = idPedido;
    k.idProducto = idProducto;

    fwrite(&k, sizeof(stPedido), 1, archi);


}
///-------------------------------FN DAR DE BAJA UN PEDIDO -----------------------------------------///
nodoPedido * eliminarPedidoLogico (nodoPedido * p, int idCliente)
{
    nodoPedido * aux = buscarPedidoID(p, idCliente);
    if (aux)
    {
        char opciones [2][30] = {"si", "no"};

        int idPedido;

        mostrarListaPedidos(aux->lista);

        color(9);
        printf("\n\n Proporcionar el id del pedido a eliminar: ");
        color(7);
        scanf("%d", &idPedido);

//    aux->lista =  BajaNodoProdID(aux->lista, idPedido);

        color(3);
        printf("\n\nPedido eliminado satisfactoriamente\n\n\n");
        color(7);
    }
    else
    {
        color(4);
        printf("\n\nNo se encontro el cliente especificado\n");
        color(7);
    }

    return p;
}

nodoPedido * eliminarPedidoFISICO (nodoPedido * p, int idCliente)
{
    nodoPedido * aux = buscarPedidoID(p, idCliente);
    int idPedido;

    if (aux)
    {

        char opciones [2][30] = {"si", "no"};

        mostrarListaPedidos(aux->lista);

        color(9);
        printf("\n\n Proporcionar el id del pedido a eliminar: ");
        color(7);
        scanf("%d", &idPedido);

        aux->lista =  borrarPedidoId(aux->lista, idPedido);

        color(3);
        printf("Pedido eliminado satisfactoriamente\n\n\n");
        color(7);
        system("pause");
    }
    else
    {
        color(4);
        printf("\n\nNo se encontro el cliente especificado\n");
        color(7);
    }
    return p;
}


//int buscarPedidoCliente (nodoPedido p)
//{
//
//    return idP;
//}

//int listaPedidos2Arreglo (nodoProd * lista, stProducto ar[], int dim)
//{
//    int i = 0;
//    while (lista)
//    {
//        while (i<dim)
//        {
////            ar[i].idPedido = lista->lista->idPedido;
//            ar[i] = lista->lista->producto;
//            i++;
//        }
//
//        lista = lista->siguiente;
//    }
//    mostrarArregloPedidos(ar, i);
//    return i;
//}
//void mostrarArregloPedidos (nodoProd ar[], int dim)
//{
//    int i= 0;
//    while (i<dim)
//    {
//        printf("======================\n");
//        mostrarUnProducto(ar[i]);
//        i++;
//    }
//}

///------------------------------------------------------------------------///
nodoProd * borrarPedidoId(nodoProd * listaP, int id)
{
    nodoProd * seg;
    nodoProd * ante;

    if (listaP)
    {

        if (listaP->idPedido == id)
        {
            nodoProd * aux = listaP;
            listaP = listaP->siguiente;
            free(aux);
        }
        else
        {
            seg = listaP;
            while((seg) && (seg->idPedido != id) )
            {
                ante = seg;
                seg = seg->siguiente;
            }
            if (seg!=NULL)
            {
                ante->siguiente = seg->siguiente;
                free(seg);

            }
        }
    }
    return listaP;
}
