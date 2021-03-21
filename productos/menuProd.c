#include "menuProd.h"

void menuPrincipalProductos (char arProductos[])
{
    nodoArbolStProducto* arbolP = inicArbol();

    arbolP =archivoToArbolProductos(arProductos,arbolP);


    int opcion = -1;
    system("cls");
    //const char opciones[6][30]= {"Alta","Baja","Modificacion","Consulta","Listado","Volver"};

    //int opcion = menuFlechas("Menú Principal",opciones,6); /// HACER LO DE LAS FLECHITASSSS.
 do
    {
    printf("\n\t BIENVENIDO QUERIDO CLIENTE !");
    printf("\n");
    printf("\n\t [1]. ALTA DE PRODUCTOS\n");
    printf("\n\t [2]. BAJA DE PRODUCTOS\n");
    printf("\n\t [3]. MODIFICACION DE PRODUCTOS\n");
    printf("\n\t [4]. CONSULTA DE PRODUCTOS\n");
    printf("\n\t [5]. LISTADO DE PRODUCTOS\n");
    printf("\n\t [6]. Salir");
    printf("\n\t Ingrese una opci%cn:",162);

    scanf("%i", &opcion);


        switch (opcion)
        {
        case 1:
            printf("ALTA DE PRODUCTOS\n");
            cargarMuchosProductos();
            system("pause");
            system("cls");
            break;
        case 2:
            printf("BAJA DE PRODUCTOS\n");
            int idNumber;
            printf("\nSELECCIONE PRODUCTO QUE DESEA BORRAR SEGUN ID\n");
            scanf("%d",&idNumber);
            arbolP = borrarUnNodoArbolSegunID(arbolP,idNumber);
            system("pause");
            system("cls");
            break;
        case 3:
            printf("MODIFICACION DE PRODUCTOS\n");
            system("pause");
            system("cls");
            break;
        case 4:
            printf("CONSULTA DE PRODUCTOS\n");
            int nro;
            printf("INGRESE NRO DE PRODUCTO A CONSULTAR:");
            scanf("%d",&nro);

            nodoArbolStProducto* arbolBu = buscarProductoArbolporID(arbolP,nro);

            mostrarUnProducto(arbolBu->p);

            system("pause");
            system("cls");
            break;
        case 5:
            printf("LISTADO DE PRODUCTOS\n");
            mostrarProductos();
            system("pause");
            system("cls");
            break;
        case 6:
            printf("VOLVER\n");
            break;

        default:
            printf("Opci%cn incorrecta. intente nuevamente",162);
            system("pause");
            system("cls");
            break;

            printf("\n\n\t Ingrese una opci%cn:",162);
        }

    }
    while (opcion!=0);


}
