#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locale.h"
#include <conio.h>
#include <windows.h>
#include "gotoxy.h"
#include <stdbool.h>


#include "ListaSimple.h"
#include "Compuestos.h"
#include "cliente.h"
#include "productos/productos.h"
#include "productos/listaSimpleProductos.h"
#include "productos/arbolProductos.h"

//
///Constantes tipo int
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define TECLA_ENTER 13
#define TECLA_ESCAPE 27
#define TECLA_F1 112
#define TECLA_ENIE 164
#define TECLA_M 77



const char archivoCliente[] = "archivoCliente.dat";
const char arProductos [] = "archivoProductos.dat";
const char arPedidos [] = "archivoPedidos.dat";

int main()
{
    setlocale(LC_ALL, "spanish");
    SetConsoleTitle("TP FINAL - PROYECTO DE CATEDRA");
    srand(time(NULL));
    hidecursor(0);


///----------------------------------------///
    menuInicio();
    ///---------------------------------------///
    return 0;
}


///////////////////// MENU ////////////////////////////


//------------------------------------------------------------------------- CIERRE DE ARCHIVO

void cerrarArchi (FILE * archi)
{
    int val = 0;
    val = fclose(archi);
    if (val != 0)
    {
        printf("El archivo no fue cerrado correctamente\n");
    }
}
//------------------------------------------------------------------------- FIN CIERRE DE ARCHIVO

//------------------------------------------------------------------------- INICIO

void menuInicio()
{
    char opciones[3][30] = {"Iniciar Sesion","Registrarme","Salir"};
    int opcion = 0;
    do
    {
        opcion = menuFlechas("YOUTICS YA!",opciones,3);


        switch(opcion)
        {
        case 1:
            iniciarSesion(archivoCliente);
            break;
        case 2:
            menuRegistro(archivoCliente);
            break;
        case 3:
//        salir();
            break;
        }

    }
    while (opcion != 3);
}

void mostrarOpciones (char opciones[5][30], int validos)
{
    int i= 0;
    for(i=0; i<validos; i++)
    {
        color(3);
        gotoxy(30,10+i);
        printf("%s",opciones[i]);
        color(7);
    }
}

//La magia de nuestro proyectooo..

int menuFlechas( char titulo[], char opciones[5][30],int validosPrincipal)
{
    int opcionSeleccionada = 1;
    int tecla;
    bool flag = true;
//    int i;

    do
    {
        system("cls");
        gotoxy(25,9 + opcionSeleccionada);
        printf(">>");
        gotoxy(30,5);
        printf("%s",titulo);

        mostrarOpciones(opciones, validosPrincipal);

        //REPITE LA PANTALLA, SI REALIZAS UNA ACCIÓN NO VALIDA VA A SIMULAR QUE NO PASÓ NADA.
        do
        {
            fflush(stdin);
            tecla = toupper(getch());
        }
        while(tecla!=TECLA_ARRIBA && tecla!=TECLA_ABAJO && tecla!=TECLA_ENTER && tecla!=TECLA_ESCAPE && tecla!=TECLA_M);

        //PERMITE EL MOVIMIENTO MEDIANTE EL USO DE LAS FLECHAS.

        switch(tecla)
        {
        case TECLA_ARRIBA:
            opcionSeleccionada--;
            if(opcionSeleccionada<1)
            {
                opcionSeleccionada = validosPrincipal;
            }
            break;
        case TECLA_ABAJO:
            opcionSeleccionada++;

            if(opcionSeleccionada > validosPrincipal)
            {
                opcionSeleccionada = 1;
            }
            break;

        case TECLA_ENTER:
            // entra en la opción.
            flag=false;

            break;
        }
    }

    while(flag == true);

    return opcionSeleccionada;
}
//------------------------------------------------------------------------- FIN

//------------------------------------------------------------------------- REGISTRO

void menuRegistro (char archivo[])
{
    int opc = cargarCliente(archivo);

    if (opc = 1)
        menuPrincipalAdm();
    else
        menuPrincipalCliente();
}

//------------------------------------------------------------------------- FIN REGISTRO

//------------------------------------------------------------------------- DIFERENTES MENÚ PARA NAVEGAR

///MENU PRINCIPAL CLIENTES

void menuPrincipalCliente(int id)
{
    char opciones[5][30]= {"Mi Perfil", "Modificacion","Pedidos","Productos","Volver"};

    int opcion = 0;
    do
    {
        nLista * listaCliente = inicLista(); // lo ingreso acá para que no haya una repetición de datos al repetir menu.
        opcion = menuFlechas("Menú Principal",opciones,5);

        switch(opcion)
        {
        case 1:
            listaCliente = archivo2listaCliente(archivoCliente, listaCliente);
            system("cls");
            color(2);
            gotoxy(30,0);
            printf("---------------------------- PERFIL ----------------------------\n\n");
            color(7);

            nLista * cliente = buscarNodoID(listaCliente, id);
            mostrarCliente(cliente->dato);

            gotoxy(0,20);
            system("pause");

            break;
        case 2:
            menuModificacionCliente(id);

            break;
        case 3:
            menuPedidos(id);
            break;
        case 4:
            menuProductosCliente();
            break;
        case 5:

            break;

        }

    }while (opcion != 5);
}

///MENU PRINCIPAL ADMINISTRADOR
void menuPrincipalAdm()
{
    char opciones[6][30]= {"Cliente","Pedidos","Productos","Volver"};

    nLista * lista = inicLista();
    int opcion = 0;
    do
    {
        opcion = menuFlechas("Menú Principal Administrador",opciones,4);

        switch(opcion)
        {
        case 1:
//        menuPrincipalCliente(); ///PUEDE CAMBIAR VARIOS USUARIOS, DE MODO QUE TENGO QUE HACER NUEVAS FUNCIONES

            ///DEBERÍA PODER BUSCAR CLIENTES EN ESPECIFICO PARA QUE ESA FUNCIÓN DEVUELVA EL ID Y DE ESTE MODO REUTILIZAR LAS FUNCIONES
            /// HECHAS ESTRICTAMENTE PARA CLIENTES COMUNES

            menuAuxiliarAdmCliente();
            break;
        case 2:
            menuPedidosAuxADM();
            break;
        case 3:
            menuProductos();
            break;
        case 4:
            break;
        }

    }
    while (opcion != 4);
}

///SUB MENU DE ADMIN PARA MANEJAR CLIENTES
void menuAuxiliarAdmCliente ()
{
    char opciones[6][30]= {"Lista de Clientes","Buscar Cliente","Volver"};

    int opcion = 0;
    int id = 0;
    char opc [3][30] = {"si", "no"};
    int k = 0;

    do
    {
        nLista * lista = inicLista();
        lista = archivo2listaCliente(archivoCliente, lista);

        opcion = menuFlechas("Menú Clientes",opciones,3);


        switch(opcion)
        {
        case 1:

            ///DEBERÍA PODER BUSCAR CLIENTES EN ESPECIFICO PARA QUE ESA FUNCIÓN DEVUELVA EL ID Y DE ESTE MODO REUTILIZAR LAS FUNCIONES
            /// HECHAS ESTRICTAMENTE PARA CLIENTES COMUNES
            system("cls");

            mostrarLista(lista);
            system("pause");
            break;
        case 2:
            system("cls");


//        lista = archivo2listaCliente(archivoCliente, lista);
            id = subProgBuscarNodoID(lista);
            system("pause");

            k = menuFlechas("¿El cliente encontrado es correcto?", opc, 2);
            if (k == 1)
                menuPrincipalCliente(id);

            break;
        case 3:
            break;


        }
    }
    while (opcion != 3);
}

///MENU PEDIDOS
void menuPedidos (int id)
{
    char opciones[4][30]= {"Realizar pedido","Ver pedidos","Dar de baja pedido","Volver"};

    stProducto arregloProducto [40];


    int val = 0;
    int posPedido;

    int opcion =0;
    do
    {

        nLista * lista = inicLista();
        nodoArbolStProducto * arbol = inicArbol();
        nodoPedido * pedidoNuevo = inicListaPedidos();

        data2StructPedido(&lista, &arbol, &pedidoNuevo);
        opcion = menuFlechas("Menú Pedidos",opciones,4);

        switch(opcion)
        {
        case 1:

            ///NECESITO FUNCION DE ARBOL A ARREGLO
            val = archivo2ArrayProducto(arProductos, arregloProducto, 40);

            posPedido = menuFlechasStruct("Seleccionar producto deseado", arregloProducto, val); // esto me va a dar la posición del producto
            // en el arreglo al cual baje el archivo

            posPedido -= 1; // el arreglo arranca de 0, por esto tengo que reducir una posición.
            ///NO CAMBIAR ESTA SENTENCIA SINO ROMPE.
            system("cls");

            color(3);
            gotoxy(30,0);
            printf("Producto seleccionado\n");
            color(7);
            mostrarUnProducto(arregloProducto[posPedido]);
            system("pause");

            int idPp = 1+ rand()%100 + pedidosAcumulados(arPedidos);
//        mostrarArchivoPedidos(arPedidos);
            pedidoNuevo = generarPedido(pedidoNuevo, lista, arbol, id, arregloProducto[posPedido].idProducto, idPp);
            system("cls");

//        mostrarListaPedidosdeUNCLIENTE(pedidoNuevo, id);
            mostrarPedidos(pedidoNuevo, id);

            ldl2Archivo(pedidoNuevo, arPedidos, "wb");
            printf("\n\n");


            system("pause");
            break;
        case 2:
            system("cls");

//        pedidoNuevo = archivo2Ldl(arPedidos, lista, arbol, pedidoNuevo);
            mostrarPedidos(pedidoNuevo, id);
            printf("\n\n");
            system("pause");

            break;
        case 3:
            system("cls");

//        pedidoNuevo = archivo2Ldl(arPedidos, lista, arbol, pedidoNuevo);
            pedidoNuevo = eliminarPedidoFISICO(pedidoNuevo, id);

            ldl2Archivo(pedidoNuevo, arPedidos, "wb");


            system("pause");

            break;
        case 4:
            break;
        }
    }
    while(opcion != 4);

}

void data2StructPedido (nLista ** lista, nodoArbolStProducto ** arbol, nodoPedido ** pedidoNuevo)
{
    (*lista) = archivo2listaCliente(archivoCliente, (*lista));
    (*arbol) = archivoToArbolProductos(arProductos, (*arbol));
    (*pedidoNuevo) = archivo2Ldl(arPedidos, (*lista), (*arbol), (*pedidoNuevo));
}


void menuPedidosAuxADM ()
{
    char opciones[3][30]= {"Ver pedidos","Dar de baja pedido","Volver"};
    char opciones2[2][30]= {"Si","No"};


    stProducto arregloProducto [40];

    int val = 0;



//    mostrarArchivoPedidos(arPedidos);
//   system("pause");

    int opcion = 0;
    do
    {
        nLista * lista = inicLista();
        nodoArbolStProducto * arbol = inicArbol();
        nodoPedido * pedidoNuevo = inicListaPedidos();

        data2StructPedido(&lista, &arbol, &pedidoNuevo);


        opcion = menuFlechas("Menú Pedidos",opciones,3);


        switch(opcion)
        {
        case 1:
            system("cls");
            mostrarListaClientePedidos(pedidoNuevo);
            system("pause");

            break;
        case 2:
            system("cls");

            //TENGO QUE ACLARAR DE QUE CLIENTE ES EL PEDIDO QUE QUIERO ELIMINAR.
            val = menuFlechas("¿Conoce el id del cliente dueño del pedido?", opciones2,2);
            if (val == 1)
            {
                system("cls");
                int idC;
                color(3);
                gotoxy(30,10);
                printf("Ingresar ID del cliente: ");
                color(7);
                gotoxy(60,10);
                scanf("%d", &idC);

                pedidoNuevo = eliminarPedidoFISICO(pedidoNuevo, idC);

                ldl2Archivo(pedidoNuevo, arPedidos, "wb");

            }
            break;
        case 3:
            break;
        }
    }
    while (opcion != 3);


}
//------------------------------------------------------------------------- FIN DIFERENTES MENÚ PARA NAVEGAR
//------------------------------------------------------------------------- INICIO DE SESIÓN


void iniciarSesion(char archivo[])
{
    char userName[30];
    char pass[30];
    int error = 0;
    int cuenta;
    int id = 0;

    system("cls");
    color(3);

    gotoxy(30,10);
    printf("UserName: ");
    color(7);
    fflush(stdin);
    gotoxy(40,10);
    gets(userName);

    color(3);

    gotoxy(30,11);
    printf("Password: ");
    color(7);
    fflush(stdin);
    gotoxy(40,11);
    gets(pass);

    cuenta = buscarEnRegistro(userName,pass,archivo);
    if (cuenta != 3)
    {
        id = buscarEnRegistroID(userName,pass,archivo);
    }
    else
        error=5;


    system("cls");

    if (error>0)
    {
        mensaje2Usuario(error);
    }
    else
    {
        eleccionMenu(cuenta, id);
    }
}

void eleccionMenu (int cuenta, int id)
{
    if(cuenta == 0)
        menuPrincipalCliente(id);
    else if(cuenta == 1)
        menuPrincipalAdm(id);
}


//------------------------------------------------------------------------- AVISO DE ERRORES
void mensaje2Usuario(int usado)
{
    if(usado == 1)
        printf("Ese nombre de usuario ya esta en uso, elija otro");
    else if(usado == 2)
        printf("Las password no coinciden");
    else if(usado == 3)
        printf("La password debe tener al menos 6 caracteres");
    else if(usado == 4)
        printf("La password debe tener como mucho 12 caracteres");
    else if(usado == 5)
    {
        printf("UserName o Password invalidos");
//        interrupcion();
    }
}

//------------------------------------------------------------------------- FIN AVISO DE ERRORES

//------------------------------------------------------------------------- DIFERENTES MENÚ PARA NAVEGAR
///SUB MENU MODIFICACION DE CLIENTES
void menuModificacionCliente (int id)
{
    char opciones [9][30] = {"Alta", "Baja", "Nombre", "Apellido", "UserName", "Contraseña", "Dirección", "Mail", "Volver"};
    int opcion = 0;

    do
    {

        nLista * lista = inicLista();

        lista = archivo2listaCliente(archivoCliente, lista);

        opcion = menuFlechas("Menu de modificación", opciones, 9);

        switch(opcion)
        {
        case 1:
            system("cls");
            modificarAltaCliente(&lista, id);
            color(2);
            printf("pasando a archivo\n");
            puts("--------------------------------\n");
            color(7);
            lista2archivoCliente(archivoCliente, lista, "wb");
            system("pause");
            break;

        case 2:
            system("cls");

            modificarBajaCliente(&lista, id);
            color(2);
            printf("pasando a archivo\n");
            puts("--------------------------------\n");
            color(7);


            lista2archivoCliente(archivoCliente, lista, "wb");

            system("pause");

            break;
        case 3:
            system("cls");

//            lista = archivo2listaCliente(archivoCliente, lista);
            subProgModNombreCliente(&lista, id);
            lista2archivoCliente(archivoCliente, lista, "wb");
            system("pause");

            break;
        case 4:
            system("cls");

//            lista = archivo2listaCliente(archivoCliente, lista);
            subProgModApellidoCliente(&lista, id);
            lista2archivoCliente(archivoCliente, lista, "wb");
            system("pause");

            break;
        case 5:
            system("cls");

//            lista = archivo2listaCliente(archivoCliente, lista);
            subProgModUserNameCliente(&lista, id);
            lista2archivoCliente(archivoCliente, lista, "wb");
            system("pause");

            break;
        case 6:
            system("cls");

//            lista = archivo2listaCliente(archivoCliente, lista);
            subProgModPassCliente(&lista, id);
            lista2archivoCliente(archivoCliente, lista, "wb");
            system("pause");

            break;
        case 7:
            system("cls");

//            lista = archivo2listaCliente(archivoCliente, lista);
            subProgModDireCliente(&lista, id);
            lista2archivoCliente(archivoCliente, lista, "wb");
            system("pause");

            break;
        case 8:
            system("cls");

//            lista = archivo2listaCliente(archivoCliente, lista);
            subProgModMailCliente(&lista, id);
            lista2archivoCliente(archivoCliente, lista, "wb");
            system("pause");

            break;
        case 9:
            break;
        }
    }
    while (opcion != 9);

}


///-----------------------------------------------------------------------------///
void mostrarOpcionesStruct (stProducto a[], int validos)
{
    int i= 0;
    for(i=0; i<validos; i++)
    {
        color(3);
        gotoxy(30,10+i);
        printf("%s",a[i].nombre);
        color(7);
    }
}

///OTRO POCO MAS DE MAGIA CON FLECHAS...
int menuFlechasStruct( char titulo[], stProducto a[],int validosPrincipal)
{
    int opcionSeleccionada = 1;
    int tecla;
    bool flag = true;
//    int i;

    do
    {
        system("cls");
        gotoxy(25,9 + opcionSeleccionada);
        printf(">>");
        gotoxy(30,5);
        printf("%s",titulo);

        mostrarOpcionesStruct(a, validosPrincipal);

        //REPITE LA PANTALLA, SI REALIZAS UNA ACCIÓN NO VALIDA VA A SIMULAR QUE NO PASÓ NADA.
        do
        {
            fflush(stdin);
            tecla = toupper(getch());
        }
        while(tecla!=TECLA_ARRIBA && tecla!=TECLA_ABAJO && tecla!=TECLA_ENTER && tecla!=TECLA_ESCAPE && tecla!=TECLA_M);

        //PERMITE EL MOVIMIENTO MEDIANTE EL USO DE LAS FLECHAS.

        switch(tecla)
        {
        case TECLA_ARRIBA:
            opcionSeleccionada--;
            if(opcionSeleccionada<1)
            {
                opcionSeleccionada = validosPrincipal;
            }
            break;
        case TECLA_ABAJO:
            opcionSeleccionada++;

            if(opcionSeleccionada > validosPrincipal)
            {
                opcionSeleccionada = 1;
            }
            break;

        case TECLA_ENTER:
            // entra en la opción.
            flag=false;

            break;
        }
    }

    while(flag == true);

    return opcionSeleccionada;
}
///------------------------------------------------------------------------------///

//------------------------------------------------------------------------- DIFERENTES MENÚ PARA NAVEGAR

///MENU PRODUCTOS
void menuProductos()
{


    char opciones[6][30] = {"Alta Productos","Baja Productos","Modificacion Productos","Consulta Productos","Listado Productos","Salir"};

    int opcion = 0;
    char rta = 's';
    int idNumberBorrar;
    int idNumberModif;

    do
    {
        nodoArbolStProducto* arbolP = inicArbol();
        arbolP = archivoToArbolProductos(arProductos,arbolP);

        opcion = menuFlechas("PRODUCTOS",opciones,6);

        switch(opcion)
        {
        case 1:
            system("cls");
            cargarMuchosProductos(arProductos);
            system("pause");

            break;
        case 2:
            system("cls");
            color(3);
            printf("Ingrese Id de producto a borrar: ");
            color(7);
            scanf("%d",&idNumberBorrar);

            subProgramaModificarProdEstado(&arbolP, idNumberBorrar);
            subProgArbol2Archivo(arbolP, arProductos);

            system("pause");
            break;
        case 3:
            system("cls");
            printf("Ingrese Id de producto a modificar: ");
            scanf("%d",&idNumberModif);

            //busco producto
            nodoArbolStProducto * arbolMod = buscarProductoArbolporID(arbolP,idNumberModif);

            printf("\nProducto a modificar....\n\n");
            mostrarUnProducto(arbolMod->p);
            system("pause");

            //entro al menu para modificar
            if (arbolMod!=NULL)
            {
                menuModificacionesProducto(idNumberModif);
            }

            subProgArbol2Archivo(arbolP,arProductos);
            break;
        case 4:
            system("cls");
            int idNumber;
            color(7);
            //consultar de acuerdo a distintos criterios
            menuConsultaProducto();
            system("pause");
            system("cls");
            break;
        case 5:
            system("cls");
            mostrarArbolProductosEnOrden(arbolP);
            system("pause");
            break;
        case 6:
            system("cls");
            break;
        }

    }
    while (opcion != 6);
}

///SUBMENU PARA MODIFICAR PRODUCTOS COMO ADMIN
void menuModificacionesProducto (int id)
{
    char opciones [5][30] = {"Nombre","Marca","Precio","Estado","Volver"};


    int opcion = 0;
    do
    {
        nodoArbolStProducto* arbolP = inicArbol();
        arbolP = archivoToArbolProductos(arProductos,arbolP);

        opcion = menuFlechas("Modificacion Productos", opciones, 5);

        switch (opcion)
        {

        case 1:
            system("cls");
            subProgramaModificarProdNombre(&arbolP,id);
           //  printf("NOMBRE: %s",arbolP->p.nombre);
             mostrarArbolProductosEnOrden(arbolP);
           subProgArbol2Archivo(arbolP,arProductos);
            system("pause");
            break;
        case 2:
            system("cls");
            subProgramaModificarProdMarca(&arbolP,id);
            subProgArbol2Archivo(arbolP, arProductos);

            system("pause");

            break;
        case 3:
            system("cls");
            subProgramaModificarProdPrecio(&arbolP,id);
            subProgArbol2Archivo(arbolP,arProductos);

            system("pause");
            break;
        case 4:
            system("cls");
            subProgramaModificarProdEstado(&arbolP,id);
            subProgArbol2Archivo(arbolP,arProductos);
            system("pause");
            break;
        case 5:
            break;
        }
    }while (opcion!=5);
}

///SUBMENU PARA CONSULTAR PRODUCTOS
void menuConsultaProducto ()
{
    char opciones [5][30] = {"ID","Nombre","Marca","Estado","Volver"};

    int idNumber;

    int opcion = 0;
    do
    {
        nodoArbolStProducto* arbolP = inicArbol();
        arbolP = archivoToArbolProductos(arProductos,arbolP);

        opcion = menuFlechas("Consulta Productos", opciones, 5);

        switch (opcion)
        {

        case 1:
            system("cls");
            int idNumber;
            color(3);
            printf("\nIndique nro de ID de producto a consultar:");
            scanf("%d",&idNumber);
            color(7);
            nodoArbolStProducto* arbolBu = buscarProductoArbolporID(arbolP,idNumber);
            mostrarUnProducto(arbolBu->p);
            system("pause");
            break;
        case 2:
            system("cls");
            char nombreBusc [20];
            color(3);
            printf("Ingrese nombre de producto a consultar:");
            fflush(stdin);
            gets(nombreBusc);
            color(7);
            nodoArbolStProducto*arbolName = buscarProductoArbolporNombre(arbolP,nombreBusc);
            mostrarUnProducto(arbolName->p);
            system("pause");
            break;
        case 3:
            system("cls");
            char marca[20];
            color(3);
            printf("Ingrese marca de producto a consultar:");
            fflush(stdin);
            gets(marca);
            color(7);
            nodoArbolStProducto *arbolMarc = buscarProductoArbolporMarca(arbolP,marca);
            mostrarUnProducto(arbolMarc->p);
            system("pause");
            break;
        case 4:
            system("cls");
            int estado;
            printf("Ingrese estado de producto a consultar:");
            scanf("%d",&estado);
            mostrarProdActivos(arbolP,estado);
            system("pause");
            break;
        case 5:
            system("cls");
            break;
        }
    }
    while (opcion!=5);
}

///SUB MENU DE PRODUCTOS EXCLUSIVO CLIENTES (NO PUEDEN BORRAR NI MODIFICAR)
void menuProductosCliente()
{


    char opciones[3][30] = {"Consulta","Listado","Salir"};

    int opcion = 0;

    do
    {
        nodoArbolStProducto* arbolP = inicArbol();
        arbolP = archivoToArbolProductos(arProductos,arbolP);
        opcion = menuFlechas("Productos",opciones,3);

        switch (opcion)
        {
        case 1:
            system("cls");
            int idNumber;
            printf("\nIndique nro de ID de producto a consultar:\n");
            scanf("%d",&idNumber);
            nodoArbolStProducto* arbolBu = buscarProductoArbolporID(arbolP,idNumber);
            mostrarUnProducto(arbolBu->p);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            mostrarArbolProductosEnOrden(arbolP);
            system("pause");
            break;
        case 3:
            break;

        }
    }
    while (opcion!=3);


}

