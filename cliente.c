#include "cliente.h"

//const char arCliente[] = "archivoCliente.bin";


////////////////////////////////////////////////////////////////////////////////////////////

void CerrarArchivo (FILE * archi)
{
    int val = 0;
    val = fclose(archi);
    if (val != 0)
    {
        printf("El archivo no fue cerrado correctamente\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

int cargarCliente (char archivo[])
{
    FILE * archi = fopen(archivo, "ab");
    int valor = 3;

    if (archi != NULL)
    {
        system("cls");

        valor = cargarUnCliente(archi, archivo);

        puts("-------------------------------------\n");

        system("cls");

//            color(13);
//            printf("desea continuar cargando clientes? S-N\n");
//            fflush(stdin);
//            scanf("%c", &control);
//            color(7);
//            printf("\n\n");
    }

    CerrarArchivo(archi);
    return valor;
}

int cargarUnCliente(FILE * archi,char archiCliente[])
{
    char opciones[2][30]= {"Si","No"}; /// valores de elección para el menú de flechas
    int clave = 2011; // Clave de registro para crear un Administrador
    int claveAdmin = 0; // opción donde se carga la clave para comparar
    int rta = 0; // se devuelve el valor del rol para poder ingresar al respectivo menú dsp del registro

    stCliente k;
    color(3);
    printf("Cargando cliente\n\n");
    color(7);
    color(3);
    printf("Ingresar Nombre: ");
    color(7);
    fflush(stdin);
    gets(k.nombre);
    printf("\n");
    color(3);
    printf("Ingresar Apellido: ");
    color(7);
    fflush(stdin);
    gets(k.apellido);
    printf("\n");
    color(3);
    printf("Ingresar Contraseña: ");
    color(7);
    fflush(stdin);
    gets(k.password);
    printf("\n");

    int p = 1;
    do
    {
        color(3);
        printf("Ingresar UserName: ");
        color(7);
        fflush(stdin);
        gets(k.userName);
        p = validarUserName(k.userName, archiCliente);
        if (p == 1)
        {
            avisoValidacion();
        }

    }
    while (p == 1);
    printf("\n");

    do
    {
        color(3);
        printf("Ingresar Mail: ");
        color(7);
        fflush(stdin);
        gets(k.mail);
        p = ValidarMail(k.mail, archiCliente);
        if (p == 1)
        {
            avisoValidacion();
        }
    }
    while (p == 1);
    printf("\n");
    color(3);
    printf("Ingresar Domicilio: ");
    color(7);
    fflush(stdin);
    gets(k.domicilio);
    printf("\n");
    color(3);
    printf("Ingresar Genero (h/m): ");
    color(7);
    fflush(stdin);
    scanf("%c", &k.genero);

    system("cls");

    // 0 LO TOMAMOS COMO CLIENTE NORMAL - 1 COMO ADMINISTRADOR
    printf("Posee clave de administrador?\n");
    rta = menuFlechas("Administradores", opciones, 2);
//            if (strcmp(rta, "si") == 0)
    if (rta == 1)
    {
        system("cls");
        printf("Ingresar clave\n");
        scanf("%d", &claveAdmin);

        if (claveAdmin == clave)
        {
            k.rol = 1;
            printf("\nNuevo administrador\n");
            rta = 1;

        }
        else
        {
            color(4);
            printf("\nClave erronea\n");
            color(7);
        }
    }
    else
    {
        k.rol = 0;
        printf("%d\n", k.rol);
    }

    // 0 ACTIVO - 1 ELIMINADO
    k.eliminado = 0;


    k.idCliente = 1 + clientesAcumulados(archi);
    fwrite(&k, sizeof(stCliente),1,archi);

    system("cls");
    puts("-----------------------------------------\n");
    color(3);
    printf("Cliente cargado: \n\n");
    color(7);
    mostrarCliente(k);
    puts("-----------------------------------------\n");
    system("pause");

    return rta;
}

//------------------------------------------------------------------ AVISOS
void avisoValidacion ()
{
    printf("Dato inválido y/o ya existente\n\n");

}
//------------------------------------------------------------------

//------------------------------------------------------------------ VALIDACIONES

int ValidarMail (char mail[], char archivo[])
{
    stCliente k;
    FILE *archiv = fopen(archivo, "rb");
    int flag = 0;

    if(archiv != NULL)
    {
        while ( flag == 0 && fread(&k, sizeof(stCliente), 1, archiv) > 0)
        {
            if(strcmp(mail, k.mail)== 0)
            {
                flag = 1;
            }
        }
        CerrarArchivo(archiv);
    }
    return flag;

}


int validarUserName(char userName[], char archivo[])
{
    stCliente k;
    FILE * archiv = fopen(archivo, "rb");
    int flag = 0;

    if(archiv != NULL)
    {
        while ( flag == 0 && fread(&k, sizeof(stCliente), 1, archiv) > 0)
        {
            if(strcmp(userName, k.userName)== 0)
            {
                flag = 1;
            }
        }
        CerrarArchivo(archiv);
    }
    return flag;
}


int clientesAcumulados(FILE * archi)
{
    int i = 0;

    fseek(archi,0,SEEK_END);///indicador de posicion al final

    i=ftell(archi)/sizeof(stCliente);/// i toma el valor de cantidad de bytes del archivo dividio en los bytes de un cliente


    return i;///retornamos cantidad de registros en el archivo
}

//------------------------------------------------------------------ FN DE MUESTRA

void mostrarArchivoClientes (char nombre[])
{
    FILE * archi =  fopen(nombre, "rb");
    stCliente c;


    if (archi != NULL)
    {

        while (fread(&c, sizeof(stCliente), 1, archi) > 0)
        {
            mostrarCliente(c);

        }
        CerrarArchivo(archi);
    }
}

void mostrarCliente (stCliente cliente)
{
    color(3);
    printf("ID:        ");
    color(7);
    printf("%d\n", cliente.idCliente);
    color(3);
    printf("Nombre:    ");
    color(7);
    printf("%s\n", cliente.nombre);
    color(3);
    printf("Apellido:  ");
    color(7);
    printf("%s\n", cliente.apellido);
    color(3);
    printf("UserName:  ");
    color(7);
    printf("%s\n", cliente.userName);
    color(3);
    printf("Password:  ");
    color(7);
    printf("%s\n", cliente.password);
    color(3);
    printf("Mail:      ");
    color(7);
    printf("%s\n", cliente.mail);
    color(3);
    printf("Domicilio: ");
    color(7);
    printf("%s\n", cliente.domicilio);
    color(3);
    printf("Genero:    ");
    color(7);
    printf("%c\n", cliente.genero);

    if (cliente.rol == 0)
    {
        printf("cliente\n");
    }
    else
    {
        color(3);
        printf("ADMINISTRADOR\n");
        color(7);
    }

    if (cliente.eliminado == 1)
    {
        color(4);
        printf("Eliminado\n");
        color(7);
    }
    else
    {
        color(2);
        printf("Activo\n");
        color(7);
    }

}

//------------------------------------------------------------------
int buscarEnRegistro(char userName[30], char pass[30], char archivo[])
{
    FILE * archi = fopen(archivo,"rb");
    stCliente k;
    int rta = 3;

    if(archi!=NULL)
    {
        while(fread(&k,sizeof(stCliente),1,archi))
        {
            if(strcmp(userName,k.userName)== 0)
            {
                if(strcmp(pass,k.password)== 0)
                {
                    rta = k.rol;

                }
            }

        }
        cerrarArchi(archi);
    }
    return rta;
}


int buscarEnRegistroID (char userName[30], char pass[30], char archivo[])
{
    FILE * archi = fopen(archivo,"rb");
    stCliente k;
    int rta = 3;

    if(archi!=NULL)
    {
        while(fread(&k,sizeof(stCliente),1,archi))
        {
            if(strcmp(userName,k.userName)== 0)
            {
                if(strcmp(pass,k.password)== 0)
                {
                    rta = k.idCliente;

                }
            }

        }
        cerrarArchi(archi);
    }
    return rta;
}
