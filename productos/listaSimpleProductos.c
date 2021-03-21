#include "listaSimpleProductos.h"

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdlib.h"

nodoListaProducto*inicListaProducto()
{
    return NULL;
}

nodoListaProducto* crearNodoListaProducto(stProducto p)
{
    nodoListaProducto*aux = (nodoListaProducto*)malloc(sizeof(nodoListaProducto));
    aux->p = p;
    aux->sig = NULL;

    return aux;
}

//---------------------------------------- OPCIÓN 2 --------------------------------//
//nodoListaProducto * crearNodoListaProducto2(int idProd, char nombreProd[], char marcaProd[], float precioProd)
//{
//    nodoListaProducto * aux = (nodoListaProducto*)malloc(sizeof(nodoListaProducto));
//    aux->p = crearNodoStProducto(aux->p, idProd, nombreProd, marcaProd, precioProd);
//    aux->sig = NULL;
//
//    return aux;
//}
//------------------------------------------------------------------------//

nodoListaProducto *agregarAlPrincipioProducto(nodoListaProducto*listaP,nodoListaProducto*nuevoP)
{
   if (!listaP)
        listaP = nuevoP;
        else
    {
        nuevoP->sig = listaP;
        listaP = nuevoP;
    }
    return listaP;
}


nodoListaProducto *buscarUltimoProducto(nodoListaProducto*listaP)
{
    nodoListaProducto*aux = listaP;

    while(aux->sig !=NULL)
    {
        aux = aux->sig;
    }

    return aux;
}

nodoListaProducto *agregarAlFinalProducto(nodoListaProducto*listaP,nodoListaProducto*nuevoP)
{
    if (listaP==NULL)
    {
        listaP = nuevoP;
    }
    else
    {
        nodoListaProducto*ultimo = buscarUltimoProducto(listaP);
        ultimo->sig = nuevoP;
    }

    return listaP;
}

nodoListaProducto *agregarEnOrdenPorNombreDeProducto(nodoListaProducto*listaP,nodoListaProducto*nuevoP)
{
    if (listaP==NULL)
    {
        listaP =nuevoP;
    }
    else
    {
        if (atol(listaP->p.nombre)> atol(nuevoP->p.nombre))
        {
            listaP = agregarAlPrincipioProducto(listaP,nuevoP);
        }
        else
        {
            nodoListaProducto*seg = listaP->sig;
            nodoListaProducto*ante = listaP;

            while(seg!=NULL && (atol(seg->p.nombre)< atol(nuevoP->p.nombre)))
            {
                ante = seg;
                seg = seg->sig;
            }
            ante->sig = nuevoP;
            nuevoP->sig = seg;
        }
    }

    return listaP;
}

nodoListaProducto *borrarProductoPorId(nodoListaProducto*listaP,int id)
{
    nodoListaProducto*seg;
    nodoListaProducto*ante;

    if ((listaP) && listaP->p.idProducto < id)
    {
        nodoListaProducto* aux = listaP;
        listaP = listaP->sig;
        free(aux);
        //esto se puede hacer como borrar primero.
    }
    else
    {
        seg = listaP;
        while((seg) && listaP->p.idProducto > id )
        {
            ante = seg;
            seg = seg->sig;
        }
        if (seg)
        {
            ante->sig = seg->sig;
            free(seg);
        }
    }
    return listaP;
}

void mostrarListaProductos(nodoListaProducto*listaP)
{
    nodoListaProducto*aux = listaP;

    if(listaP)
    {
        while(aux!=NULL)
        {
            mostrarUnProducto(aux->p);
            aux = aux->sig;
        }
    }
}
void mostrarArregloProductos (stProducto p[], int dim)
{
    int i = 0;
    while (i<dim)
    {
        mostrarUnProducto(p[i]);
        i++;
    }
}

stProducto retornaProducto (nodoListaProducto*listaP,int pos, int inicio)
{
    stProducto nuevo;

    if (listaP)
    {
        if (pos==inicio)
        {
            nuevo = listaP->p;
        }
        else
        {
            nuevo = retornaProducto(listaP->sig,pos,inicio+1);
        }
    }

    return nuevo;
}


int cuentaNodosLista(nodoListaProducto*listaP)
{
    nodoListaProducto* aux;
    int cont =0;

    if (aux)
    {
        cont++;
        aux = aux->sig;
    }
    return cont;
}

nodoListaProducto *buscarProductoID (nodoListaProducto*listaP, int datoID)
{
    nodoListaProducto *aux = listaP;

    if (listaP)
    {
        while ((aux!=NULL) && (aux->p.idProducto !=datoID))
    {
        aux = aux->sig;
    }
}
return aux;
}

nodoListaProducto *buscarProductoNombre (nodoListaProducto*listaP,char nombre[20])
{
    nodoListaProducto *aux = listaP;

    while ((aux) && (strcmp(nombre,aux->p.nombre)!=0))
    {
        aux = aux->sig;
    }

    return aux;
}

nodoListaProducto *borrarProductoPorNombre(nodoListaProducto*listaP,char nombre[20])
{
    nodoListaProducto * seg;
    nodoListaProducto * ante;

    if ((listaP) && strcmp(listaP->p.nombre,nombre)==0)
    {
        nodoListaProducto * aux = listaP;
        listaP = listaP->sig;
        free(aux);
    }
    else
    {
        seg = listaP;

        while ((seg)&& strcmp(listaP->p.nombre,nombre)!=0)
        {
            ante = seg;
            seg = seg->sig;
        }
        if (seg)
        {
            ante->sig = seg->sig;
            free(seg);
        }
    }

    return listaP;
}


nodoListaProducto *archivoToListaProductos (char arProductos[],nodoListaProducto* listaP)
{
    FILE *archi = fopen(arProductos,"rb");

    stProducto p;

    if (archi)
    {
        while(fread(&p,sizeof(stProducto),1,archi)>0)
        {
            listaP = agregarAlPrincipioProducto(listaP,crearNodoListaProducto(p));
        }
        fclose(archi);
    }
    return listaP;
}

void listaProdToArchiProd (char archiProductos[], nodoListaProducto * listaP)
{
    int i=0;
    int pos = cuentaNodosLista (listaP);
    stProducto nuevo;

    FILE*archi = fopen(archiProductos,"ab");

    if (archi)
    {
        while (i<pos)
        {
            nuevo = retornaProducto(listaP,i,0);
            fwrite(&nuevo,sizeof(stProducto),1,archi);
            i++;
        }
    }
    fclose(archi);
}
