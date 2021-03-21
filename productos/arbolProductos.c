#include "arbolProductos.h"

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdlib.h"

nodoArbolStProducto *inicArbol ()
{
    return NULL;
}

nodoArbolStProducto *crearNodoArbol (stProducto p)
{
    nodoArbolStProducto * aux = (nodoArbolStProducto*)malloc(sizeof(nodoArbolStProducto));

    aux->p = p;
    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}

//nodoArbolStProducto *buscarProductoArbolporID (nodoArbolStProducto* arbolP,int id)
//{
//    nodoArbolStProducto * rta = NULL;
//
//    if (arbolP)
//    {
//        if (arbolP->p.idProducto == id)
//        {
//            rta = arbolP;
//        }
//        else
//        {
//            if (id < arbolP->p.idProducto)
//                rta = buscarProductoArbolporID(arbolP->izq,id);
//            else
//            {
//                rta = buscarProductoArbolporID(arbolP->der,id);
//            }
//        }
//    }
//
//    return rta;
//}

nodoArbolStProducto *buscarProductoArbolporID (nodoArbolStProducto* arbolP,int id)
{
    nodoArbolStProducto * rta = NULL;

    if (arbolP)
    {
        if (arbolP->p.idProducto == id)
        {
            rta = arbolP;
        }
        else
        {
            rta = buscarProductoArbolporID(arbolP->izq,id);

            if (rta == NULL)
            {
                rta = buscarProductoArbolporID(arbolP->der,id);
            }
        }
    }

    return rta;
}



nodoArbolStProducto *buscarProductoArbolporEstado (nodoArbolStProducto* arbolP,int estado)
{
    nodoArbolStProducto * rta = NULL;

    if (arbolP)
    {
        if (arbolP->p.eliminado == estado)
        {
            rta = arbolP;
        }
        else
        {
            rta = buscarProductoArbolporID(arbolP->izq,estado);
            if (rta ==NULL)
            {
                rta = buscarProductoArbolporID(arbolP->der,estado);
            }
        }
    }

    return rta;
}



nodoArbolStProducto *buscarProductoArbolporNombre (nodoArbolStProducto* arbolP,char nombre[])
{
    nodoArbolStProducto * rta = NULL;

    if (arbolP)
    {
        if (strcmp(arbolP->p.nombre,nombre)==0)
        {
            rta = arbolP;
        }
        else
        {
            rta = buscarProductoArbolporNombre(arbolP->izq,nombre);

            if (rta == NULL)
            {
                rta = buscarProductoArbolporNombre(arbolP->der,nombre);
            }
        }
    }
    return rta;
}

nodoArbolStProducto* buscarProductoArbolporMarca(nodoArbolStProducto*arbolP,char marca[])
{
    nodoArbolStProducto*rta = NULL;

    if(arbolP)
    {
        if (strcmp(arbolP->p.marca,marca)==0)
        {
            rta = arbolP;
        }
        else
        {
            rta = buscarProductoArbolporMarca(arbolP->izq,marca);

            if (rta == NULL)
            {
                rta = buscarProductoArbolporMarca(arbolP->der,marca);
            }
        }
    }

    return rta;
}


nodoArbolStProducto*insertarNodoPorNombre (nodoArbolStProducto*arbolP, stProducto p)
{
    if (arbolP == NULL)
    {
        arbolP = crearNodoArbol(p);
    }
    else
    {
        if (strcmp(arbolP->p.nombre,p.nombre)<0)
        {
            arbolP->izq = insertarNodoPorNombre(arbolP->izq,p);
        }
        else
        {
            arbolP->der = insertarNodoPorNombre(arbolP->der,p);
        }
    }
    return arbolP;
}


nodoArbolStProducto * nodoMasDerecha(nodoArbolStProducto*arbolP)
{
    if (arbolP)
    {
        if (arbolP->der)
            arbolP = nodoMasDerecha(arbolP->der);
    }
    return arbolP;
}

nodoArbolStProducto * nodoMasIzquierda (nodoArbolStProducto * arbolP)
{
    if(arbolP->izq)
        arbolP = nodoMasIzquierda(arbolP->izq);
    return arbolP;
}

nodoArbolStProducto *borrarUnNodoArbolSegunID (nodoArbolStProducto* arbolP,int id)
{
    if (arbolP)
    {
        if (arbolP->p.idProducto == id)
        {
            if (arbolP->izq)
            {
                nodoArbolStProducto* moreDer = nodoMasDerecha(arbolP->izq);
                arbolP->p.idProducto = moreDer->p.idProducto;
                arbolP->izq = borrarUnNodoArbolSegunID(arbolP->izq,moreDer->p.idProducto);
            }
            else if (arbolP->der)
            {
                nodoArbolStProducto * moreIzq = nodoMasIzquierda(arbolP->der);
                arbolP->p.idProducto = moreIzq->p.idProducto;
                arbolP->der = borrarUnNodoArbolSegunID(arbolP->der,moreIzq->p.idProducto);
            }
            else
            {
                free(arbolP);
                arbolP = NULL;
            }
        }
        else if (id > arbolP->p.idProducto)
        {
            arbolP->der = borrarProductoPorId(arbolP->der,id);
        }
        else
        {
            arbolP->izq = borrarUnNodoArbolSegunID(arbolP->izq,id);
        }
    }

    return arbolP;

}

int subProgramaBuscarNodoArbol (int idNumber)
{

    nodoArbolStProducto*arbolBu= buscarProductoArbolporID(arbolBu,idNumber);
    mostrarUnProducto(arbolBu->p);

    return idNumber;
}

void mostrarArbolProductosPreOrden (nodoArbolStProducto* arbolP)
{
    if (arbolP)
    {
        mostrarUnProducto(arbolP->p);
        mostrarArbolProductosPreOrden(arbolP->izq);
        mostrarArbolProductosPreOrden(arbolP->der);
    }
}

void mostrarArbolProductosEnOrden (nodoArbolStProducto* arbolP)
{
    if (arbolP)
    {
        mostrarArbolProductosEnOrden(arbolP->izq);
        mostrarUnProducto(arbolP->p);
        mostrarArbolProductosEnOrden(arbolP->der);
    }
}

void mostrarArbolProductosPostOrden (nodoArbolStProducto* arbolP)
{
    if (arbolP)
    {
        mostrarArbolProductosPostOrden(arbolP->izq);
        mostrarArbolProductosPostOrden(arbolP->der);
        mostrarUnProducto(arbolP->p);

    }
}

void mostrarProductoPorID (nodoArbolStProducto*arbolP, int id)
{
    if (arbolP)
        if (arbolP->p.idProducto == id)
        {
            mostrarArbolProductosEnOrden(arbolP);
        }
}

void mostrarProductosPorEstado (nodoArbolStProducto* arbolP,int estado)
{
    if (arbolP)
    {
        if (arbolP->p.eliminado== estado)
        {
            mostrarUnProducto(arbolP->p);
        }
    }
}

///SOLUCION AL BALANCEO DEL ARBOL..
nodoArbolStProducto *archivoToArbolProductos (char arProductos[],nodoArbolStProducto*arbolP)
{
    FILE *archi = fopen(arProductos,"rb");

    stProducto p;

    if (archi)
    {
        while (fread(&p,sizeof(stProducto),1,archi)>0)
        {
            //Agregamos los datos al arbol por nombre para que quede balanceado
            arbolP = insertarNodoPorNombre(arbolP,p);

        }
        fclose(archi);
    }
    return arbolP;
}
void arbolToArchivo (nodoArbolStProducto * arbolP, stProducto p,FILE * archi) //HACER ESTA FN
{

    if(arbolP)
    {

        arbolToArchivo(arbolP->izq,p,archi); //RECORRO LA RAMA DERECHA
        p = arbolP->p;                             //LO GUARDO EN LA ESTRUCTURA P AUXILIAR
        fwrite(&p, 1, sizeof(stProducto), archi); //SE GUARDA EN EL ARCHIVO
        arbolToArchivo(arbolP->der,p,archi); //RECORRO LA RAMA IZQUIERDA
    }

}

void subProgArbol2Archivo (nodoArbolStProducto *arbolP, char arProductos[])
{
    FILE * archi = fopen(arProductos,"wb");
    stProducto k;
    if (archi)
        arbolToArchivo(arbolP, k, archi);

    CerrarArchivo(archi);
}



//--------------------------------------------------------------------------//


int subProgramaArbol2Arreglo (stProducto p[], int dim, stProducto k)
{
    int i= 0;
    while (i<dim)
    {
        i = agregarArreglo(p,i,k);
    }
    return i; //validos del arreglo
}
int agregarArreglo (stProducto p[], int i, stProducto k)
{
    p[i] = k;
    i++;
    return i;
}

void subProgramaModificarProdNombre (nodoArbolStProducto**arbolP, int id)
{
    nodoArbolStProducto *aux;
    char nombre[20];
    color(3);
    printf("Ingrese nombre nuevo: ");
    color(7);
    fflush(stdin);
    gets(nombre);

    if(arbolP)
    {
        aux = buscarProductoArbolporID((*arbolP),id);
        strcpy(aux->p.nombre,nombre);
    }


}

void subProgramaModificarProdMarca (nodoArbolStProducto**arbolP, int id)
{
    nodoArbolStProducto *aux;
    char marca[20];
    color(3);
    printf("Ingrese marca nueva: ");
    color(7);
    fflush(stdin);
    gets(marca);

    if(arbolP)
    {
        aux = buscarProductoArbolporID((*arbolP),id);
        strcpy(aux->p.marca,marca);
    }
}

void subProgramaModificarProdPrecio (nodoArbolStProducto**arbolP, int id)
{
    nodoArbolStProducto *aux;
    float precio;
    color(3);
    printf("Ingrese precio nuevo: $");
    color(7);
    scanf("%f",&precio);

    if(arbolP)
    {
        aux = buscarProductoArbolporID((*arbolP),id);
        aux->p.precio = precio;
    }
}

void subProgramaModificarProdEstado (nodoArbolStProducto**arbolP,int id)
{
    nodoArbolStProducto*aux;
    int estado;
    color(3);
    printf("Ingrese estado nuevo: (1:VIGENTE / 0: NO VIGENTE)");
    color(7);
    scanf("%d", &estado);

    if (arbolP)
    {
        aux = buscarProductoArbolporID((*arbolP),id);
        aux->p.eliminado = estado;
    }

}

void mostrarProdActivos (nodoArbolStProducto* arbolP, int estado)
{
    if (arbolP)
    {
        if (arbolP->p.eliminado == estado)
            mostrarUnProducto(arbolP->p);

        mostrarProdActivos(arbolP->izq,estado);
        mostrarProdActivos(arbolP->der,estado);

    }
}













