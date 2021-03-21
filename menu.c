#include "menu.h"

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
    int opcion = menuFlechas("YOUTICS YA!",opciones,3);

    do
    {

        switch(opcion)
        {
        case 1:
            iniciarSesion("archivoCliente.dat");
            break;
        case 2:
            menuRegistro("archivoCliente.dat");
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
        gotoxy(30,10+i);
        printf("%s",opciones[i]);
    }
}

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

        //PERMITE EL MOVIMIENTO MEDIANTE EL USO DE LAS FLECHAS.
        do
        {
            fflush(stdin);
            tecla = toupper(getch());
        }
        while(tecla!=TECLA_ARRIBA && tecla!=TECLA_ABAJO && tecla!=TECLA_ENTER && tecla!=TECLA_ESCAPE && tecla!=TECLA_M);


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

void menuPrincipalCliente(int id)
{
    nLista * listaCliente = inicLista();
    const char opciones[6][30]= {"Alta","Baja","Modificacion","Consulta","Listado","Volver"};

    int opcion = menuFlechas("Menú Principal",opciones,6);

    switch(opcion)
    {
    case 1:

//        archivo2listaCliente("archivoCliente.dat", listaCliente);
//        recorrerMostrar(listaCliente);
//        printf("-----------------------------------------------------\n\n");
//        printf("-----------------------------------------------------\n\n");
//
//        listaCliente = modificarAltaCliente(listaCliente, userName);
//        printf("-----------------------------------------------------\n\n");
//        printf("-----------------------------------------------------\n\n");
//
//        recorrerMostrar(listaCliente);

        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
//        retornaSegunCuenta(tipoDeCuenta);
        break;
    }
}

void menuPrincipalAdm()
{
    const char opciones[6][30]= {"Cliente","Pedidos","Productos","Volver"};

    int opcion = menuFlechas("Menú Principal Administrador",opciones,4);

    switch(opcion)
    {
    case 1:
//        menuPrincipalCliente(); ///PUEDE CAMBIAR VARIOS USUARIOS, DE MODO QUE TENGO QUE HACER NUEVAS FUNCIONES
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
//        retornaSegunCuenta(tipoDeCuenta);
        break;
    }
}

//------------------------------------------------------------------------- FIN DIFERENTES MENÚ PARA NAVEGAR

void iniciarSesion(char archivo[])
{
    char userName[30];
    char pass[30];
    int error = 0;
    int cuenta;

    system("cls");
    printf("\nUserName: ");
    fflush(stdin);
    gets(userName);

    printf("\nPassword: ");
    fflush(stdin);
    gets(pass);

    cuenta = buscarEnRegistro(userName,pass,archivo);

    if(cuenta==3)
    {
        error=5;
    }

    system("cls");

    if (error>0)
    {
        mensaje2Usuario(error);
    }
    else
    {
        if(cuenta == 0)
            menuPrincipalCliente(userName);
        else if(cuenta == 1)
            menuPrincipalAdm(userName);
//            menuPrincipalAdm();

    }
}

//void eleccionMenu (int valor)
//{
//    if (valor == 0)
//        menuPrincipalCliente(userName);
//    else if(cuenta == 1)
//        menuPrincipalAdm();
//}
//void menuIniciarSesion ()
//{
//
//
//}


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

int menuModificacionCliente (int id)
{
    char opciones [8][30] = {"Alta, Baja, Nombre, Apellido, UserName, Contraseña, Dirección, Mail, Volver"};
    int opcion = menuFlechas("Menu de modificación", opciones, 9);

    nLista * lista = inicLista();

    switch(opcion)
    {
    case 1:
            lista = archivo2listaCliente("archivoCliente.dat", lista);
            modificarAltaCliente(&lista, id);

        break;
    case 2:
            lista = archivo2listaCliente("archivoCliente.dat", lista);
            modificarBajaCliente(&lista, id);
        break;
    case 3:
                lista = archivo2listaCliente("archivoCliente.dat", lista);
                subProgModNombreCliente(&lista, id);

        break;
    case 4:
         lista = archivo2listaCliente("archivoCliente.dat", lista);
                subProgModApellidoCliente(&lista, id);
        break;
    case 5:
        lista = archivo2listaCliente("archivoCliente.dat", lista);

        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    }

}

//    int menuRolCuenta()
//    {
//        int rol;
//        char opciones[2][30]= {"Usuario","Administrador"};
//        int opcion = menuFlechas("Selecciones el tipo de cuenta",opciones,2);
//
//        switch(opcion)
//        {
//        case 1:
//            rol = 0;
//
//            break;
//        case 2:
//            rol = 1;
//
//            break;
//        }
//        return rol;
//    }
