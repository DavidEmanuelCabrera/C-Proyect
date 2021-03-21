#include "productos.h"

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdlib.h"


//--------------------------------------------------------------///
stProducto crearNodoStProducto (stProducto k, int idProd, char nombreProd[], char marcaProd[], float precioProd)
{
    k.eliminado = 1;
    k.idProducto = idProd;
    strcpy(k.nombre, nombreProd);
    strcpy(k.marca, marcaProd);
    k.precio = precioProd;

    return k;
}

//--------------------------------------------------------------//


void cargarUnProductoArchi (char arProductos [])
{
    stProducto p;

    int i = 1;

    FILE *archi = fopen(arProductos,"ab");


    if (archi)
    {
        int idProd = 1 + cuentaRegistrosProd(arProductos);

        color(3);
        printf("Nombre del Producto: ");
        color(7);
        fflush(stdin);
        scanf("%s",&p.nombre);

        color(3);
        printf("Marca del Producto: ");
        color(7);
        fflush(stdin);
        scanf("%s",&p.marca);

        color(3);
        printf("Precio del Producto: ");
        color(7);
        printf("$");
        scanf("%f",&p.precio);

        color(3);
        printf("Estado (1:VIGENTE / 0:ELIMINADO):\n");
        scanf("%d",&p.eliminado);
        color(7);
        p.idProducto = idProd;

        fwrite(&p,sizeof(stProducto),1,archi);

        i ++;

        fclose(archi);
    }
}

void cargarMuchosProductos (char arProductos[])
{
    char control = 's';

    while(control == 's' || control == 'S')
    {
        cargarUnProductoArchi(arProductos);
        color(13);
        printf("Desea seguir ingresando productos ? S/N \n");
        fflush(stdin);
        scanf("%c",&control);
        color(7);
    }
}

void mostrarArchiProd (char archiProd[])
{
    FILE* archi = fopen(archiProd, "rb");
    stProducto p;
    if (archi)
    {
        while(fread(&p, sizeof(stProducto),1,archi)>0)
        {
            mostrarUnProducto(p);
        }
        CerrarArchivo(archi);
    }
}
void mostrarUnProducto ( stProducto p)
{

    color(9);
    printf("======================\n");
    color(7);

    printf("    Id Producto: %d\n",p.idProducto);
    printf("Nombre Producto: %s\n",p.nombre);
    printf(" Marca Producto: %s\n",p.marca);
    printf("Precio Producto: $ %.2f\n",p.precio);
    if (p.eliminado == 1)
    {
        color(2);
        printf("Producto vigente\n");
        color(7);
    }
    else
    {
        color(4);
        printf("Producto no vigente \n");
        color(7);
    }
    printf("======================\n");
}

void estadoProducto ()
{
    stProducto p;
    if (p.eliminado == 1)
    {
        printf("El producto se encuentra vigente \n");
    }
    else
    {
        printf("El producto no se encuentra vigente\n");
    }
}

void mostrarProductos (char archiProd[])
{
    FILE*archi = fopen(archiProd,"rb");
    stProducto p;

    if (archi)
    {
        while (fread(&p,sizeof(stProducto),1,archi)>0)
        {
            mostrarUnProducto(p);
        }

        fclose(archi);
    }
}

int buscarPosProducto (char archiProd[], stProducto p, char nombre[])
{
    FILE *archi = fopen(archiProd,"rb");
    int pos = -1;

    if (archi)
    {
        while ((fread(&p,sizeof(stProducto),1,archi)>0) && pos == -1 )
        {
            if (strcmp(p.nombre,nombre)==0)
                pos = ftell(archi) / sizeof(stProducto);
        }

        fclose(archi);
    }

    return pos;
}

void darDeBajaProducto (char archiProductos[], int posicion)
{
    stProducto p;
    FILE *archi = fopen(archiProductos,"r+b");

    if (archi)
    {
        fseek(archi,sizeof(stProducto)*(posicion-1),SEEK_SET);
        fread(&p,sizeof(stProducto),1,archi);

        p.eliminado = 0;

        fseek(archi,sizeof(stProducto)*(posicion-1),SEEK_SET);
        fwrite(&p,sizeof(stProducto),1,archi);
    }

    fclose(archi);
}

int cuentaRegistrosProd (char arProductos[])
{
    FILE*archi = fopen(arProductos,"rb");
    int contador=0;


    if (archi)
    {
        fseek(archi,0,SEEK_END);
        contador = ftell(archi)/sizeof(stProducto);
        fclose(archi);
    }

    return contador;
}


void bajaProductoParaMenu (char archiProductos[])
{
    stProducto p;

    int pos;
    char control = 's';
    char nombre[20];

    do
    {
        color(3);
        printf("Ingrese el nombre del producto a dar de baja: \n");
        fflush(stdin);
        scanf("%s",&nombre);

        pos = buscarPosProducto(archiProductos, p,nombre);

        if (pos == -1)

            printf("Producto no encontrado. \n");

    }
    while(pos!= -1);

    color(3);
    printf("Confirma que desea eliminar el producto S\N? \n");
    fflush(stdin);
    scanf("%c",&control);
    color(7);
    if (control == 's' || control == 'S')
        darDeBajaProducto(archiProductos, pos);
}
