#include "ListaSimple.h"

//Iniciar lista

nLista * inicLista()
{
    return NULL;
}

//Crear nodo

nLista * crearNodo (stCliente dato)
{
    //crea un puntero de tipo nodo

    nLista * aux = (nLista*) malloc(sizeof(nLista));

    //asigna valores a sus campos de información
    aux ->dato =dato;

    //le asigna valor NULL a la casilla siguiente.
    aux ->siguiente = NULL;

    ////retorna la dirección de memoria del nuevo nodo, que deberá ser asignada a una variable de tipo "puntero a nodo".
    return aux;
}

// AGREGAR UN NODO AL PRINCIPIO DE LA LISTA

nLista * agregarPpio2 (nLista * lista, nLista* nNodo)
{
    nNodo ->siguiente = lista;
    lista = nNodo;
    return lista;
}

nLista * agregarPpio (nLista * lista, nLista * nNodo)
{
    if ( lista == NULL)
    {
        //si la lista esta vacia ahora va a apuntar al nuevo nodo
        lista = nNodo;
    }
    else
    {
        // si no esta vacia el nuevo nodo (solapa siguiente) va a apuntar al primer nodo preexistente
        nNodo->siguiente = lista;
        // la lista ahora apunta al nuevo nodo
        lista = nNodo;
    }
    return lista; // retorna la nueva dirección de memoria
}

// BUSCAR ULTIMO NODO

nLista * buscarUltimo (nLista * lista)
{
    nLista * seg = lista;
    if (seg != NULL)
    {
        while ( seg->siguiente !=NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}

//BUSCAR NODO SEGÚN VALOR DE CAMPO

nLista * buscarNodoNombre (nLista * lista, char nombre[])
{
    //busca un nodo por nombre y retorna su posición de memoria
    //si no lo encuentra retorna NULL.

    nLista * seg;
    seg = lista;

    while (seg->siguiente != NULL && strcmp(nombre, seg->dato.nombre) == 0)
    {
        //busco mientras me quede lista por recorrer y no haya encontrado el nombre
        seg = seg->siguiente;// apunto al siguiente
    }
    return seg; // va a dar el nodo apuntado si es que lo encontró.
}

nLista * buscarNodoUserName (nLista * lista, char username[])
{
    //busca un nodo por su username y retorna su posición de memoria
    //si no lo encuentra retorna NULL.

    nLista * seg;
    seg = lista;

    while (seg->siguiente != NULL && strcmp(username, seg->dato.userName) == 0)
    {
        //busco mientras me quede lista por recorrer y no haya encontrado el nombre
        seg = seg->siguiente;// apunto al siguiente
    }
    return seg; // va a dar el nodo apuntado si es que lo encontró.
}


nLista * buscarNodoID (nLista * lista, int id)
{
    //busca un nodo por su id y retorna su posición de memoria
    //si no lo encuentra retorna NULL.
    nLista * seg = lista;
    while ((seg) && (id != seg->dato.idCliente))
    {
        //busco mientras me quede lista por recorrer y no haya encontrado el id
        seg = seg->siguiente;// apunto al siguiente
    }

    return seg; // va a dar el nodo apuntado si es que lo encontró.
}

nLista * subProgBuscarNodoID (nLista * lista)
{
    nLista * aux;
    int id = 0;

    color (9);
    printf("ID a buscar: ");
    color (7);
    scanf("%d", &id);

    aux = buscarNodoID(lista, id);
    system("cls");
    mostrarNodo(aux);

    return id;
}



//AGREGAR NODO AL FINAL./////////////////////////////////////


nLista * agregarAlFinal (nLista * lista, nLista * nuevoN)
{
    nLista * aux;
    if (lista == NULL)
    {
        lista = nuevoN;
    }
    else
    {
        aux = buscarUltimo(lista);
        aux->siguiente = nuevoN;
    }
    return lista;
}


//BORRAR NODO
nLista * borrarPrimero (nLista * lista)
{
    nLista * aux = lista;
    lista = lista->siguiente;
    free(aux);
    return aux;
}

nLista * borrarNodo (nLista * lista, char nombre[])
{
    nLista * seg;
    nLista * ante;

    // POR SI EL NODO ESTA AL PRINCIPIO
    if ( lista != NULL && strcmp(nombre, lista->dato.nombre)== 0)
    {
//        nodo * aux = lista;
//        lista = lista->siguiente;
//        free(aux);
        lista = borrarPrimero(lista);
    }
    // PARA BUSCAR EL NODO DENTRO DE LA LISTA
    else
    {
        seg = lista;
        //BUCLE PARA BUSCAR EL NODO DENTRO DE LA LISTA
        while(lista != NULL && strcmp(nombre, lista->dato.nombre) != 0)
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if (seg != NULL)//SI ES NULL NO ES NECESARIO SALTEAR EL NODO YA QUE SERÍA EL ÚLTIMO.
        {
            ante->siguiente = seg ->siguiente; // para saltear el nodo encontrado y a eliminar
            free(seg);
        }
    }
    return lista; // retorno la lista modificada.
}


//FUNCIÓN AGREGAR EN ORDEN

nLista * agregarEnOrden (nLista * lista, nLista * nuevoN)
{
    if ( lista == NULL)
    {
        lista = nuevoN;
    }
    else
    {
        //SI EL ELEMENTO VA ANTES QUE EL PRIMERO DE LA LISTA
        // SI ES MENOR QUE EL PRIMERO

        if (strcmp(nuevoN->dato.nombre, lista->dato.nombre)< 0)
        {
            lista = agregarPpio(lista, nuevoN);
        }
        else
        {
            //BUSCO EL LUGAR DENTRO DE LA LISTA PARA UBICAR EL NUEVO ARCHIVO
            nLista * ante = lista;
            nLista * seg = lista->siguiente; // para poder hacer el espacio de ser necesario
            while (seg != NULL && strcmp(nuevoN->dato.nombre, seg->dato.nombre)>0)
                // si el primero no es, esto comprueba desde el segundo.
            {
                ante = seg;
                seg = seg->siguiente;
            }
            // NUEVO NODO APUNTA A SIGUIENTE
            nuevoN->siguiente = seg;
            // ANTE QUE TENIA A SEG AHORA APUNTA A NUEVO NODO, LO QUE CREA ES ESPACIO DE LA LISTA
            ante->siguiente = nuevoN;
        }
    }
    return lista;
}


//BORRAR TODA LA LISTA

nLista * borrarLista (nLista * lista)
{
    nLista * proximo;
    nLista * aux;
    aux = lista;
    while (lista != NULL)
    {
        proximo = aux->siguiente;
        free(aux);
        aux = proximo;
    }
}



// ELIMINAR PRIMER NODO DE UNA LISTA

nLista * eliminarPrimero (nLista * lista)
{
    nLista * aux = NULL;

    if (lista != NULL)
    {
        aux = lista;
        lista = lista->siguiente;
        aux->siguiente = NULL; // desvincula el nodo.
        free(aux);
    }

    return lista;
}

//ELIMINAR ULTIMO NODO DE UNA LISTA

nLista * eliminarUltimo (nLista * lista)
{
    nLista * ultimo = NULL;
    if (lista != NULL)
    {
        ultimo = lista;
        while (ultimo->siguiente != NULL)
        {
            ultimo = ultimo->siguiente;
        }
        if (ultimo->siguiente == NULL)
        {
            free(ultimo);
        }

    }
    return lista;
}

// MOSTRAR UN nodo

void mostrarNodo ( nLista * n)
{
    mostrarCliente(n->dato);
}

void mostrarLista (nLista * lista)
{
    nLista * aux = lista;

    while(aux != NULL)
    {

        puts("\n------------------------------");
        mostrarNodo(aux);
        aux = aux->siguiente;
    }

}


//------------------------------------------------------- ARCHIVO A LISTA - LISTA A ARCHIVO
nLista * subProgIngresaCliente (stCliente p, nLista * lista)
{
    lista = agregarPpio2(lista, crearNodo(p));
    return lista;
}

nLista * archivo2listaCliente (char archivo[], nLista * lista)
{
    FILE * archi = fopen (archivo, "rb");

    stCliente k;

    if (archi != NULL)
    {
        while (fread(&k, sizeof(stCliente), 1, archi)>0)
        {
            lista = subProgIngresaCliente(k, lista);
        }
    }
    cerrarArchi(archi);

    return lista;
}

void lista2archivoCliente (char archivo[], nLista * lista, char aperturaArchi [])
{
    FILE * archi = fopen (archivo, aperturaArchi);
    stCliente k;
    if (archi)
    {
        while (lista)
        {
            k = lista->dato;
            lista = lista->siguiente;
            fwrite(&k, sizeof(stCliente), 1, archi);
        }

    }
    cerrarArchi(archi);
}

//------------------------------------------------------- FIN


///----------------------------------------------------------------- MODIFICACIONES
//------------------------------------------------------------------ ALTA Y BAJA
// REALIZADO SOBRE UNA LISTA DE CLIENTES

void modificarAltaCliente (nLista ** lista,  int id)
{
    nLista * aux;
    if (lista)
    {
        aux = buscarNodoID((*lista), id);// busco la posición de memoria del nodo y lo devuelvo

        if (aux)
            aux->dato.eliminado = 0;

    }
}


void  modificarBajaCliente (nLista ** lista, int id)
{
    nLista * aux;
    if (lista)
    {
        aux = buscarNodoID((lista), id);

        if (aux)
        {
            aux->dato.eliminado = 1;
        }

    }
}


//------------------------------------------------------------------ FIN ALTA Y BAJA


//------------------------------------------------------------------ MODIFICACIÓN DE DATOS

nLista ** subProgModNombreCliente (nLista ** lista, int id)
{

    char nombreNuevo[20];
    color(3);
    printf("Ingresar nombre nuevo: ");
    color(7);
    fflush(stdin);
    gets(nombreNuevo);

//    nombreNuevo[20] = ingresoModificacionString("nombre");

    modificarNombreCliente2(lista, id, nombreNuevo);

//    return lista;
}


void modificarNombreCliente2 (nLista ** lista, int id, char nombre[])
{
    nLista * aux;
    if (*lista)
    {
        aux = buscarNodoID((*lista), id);
        if (aux);
        strcpy(aux->dato.nombre, nombre);
    }
}

void modificarUnClienteArchivo (nLista * cliente, char archiCliente [])
{
    FILE* archi = fopen(archiCliente, "r+b");
    stCliente k;
    printf("ENTRO A LA FUNCIÓN\n");
    if(archi)
    {
        while ((fread(&k, sizeof(stCliente), 1, archi)>0) && (k.idCliente != cliente->dato.idCliente))
        {
            printf("BUSCANDO\n");
            if (k.idCliente != cliente->dato.idCliente)
            {
                printf("LO ENCONTRO\n");
                k = cliente->dato;
                fwrite(&k, sizeof(stCliente),1,archi);

//                data2ArchivoCliente(k, cliente, archi);
            }
        }
        CerrarArchivo(archi);
    }
}

void data2ArchivoCliente (stCliente k, nLista * c, FILE * archi)
{
    strcpy(k.userName, c->dato.userName);
    k.rol = c->dato.rol;
    strcpy(k.apellido, c->dato.apellido);
    strcpy(k.nombre, c->dato.nombre);
    strcpy(k.mail, c->dato.mail);
    strcpy(k.domicilio, c->dato.domicilio);
    strcpy(k.genero, c->dato.genero);
    k.eliminado = c->dato.eliminado;
    strcpy(k.password, c->dato.password);
    fwrite(&k, sizeof(stCliente),1,archi);

}

//APELLIDO

nLista ** subProgModApellidoCliente (nLista ** lista, int id)
{
    char apellidoNuevo[20];

    color(3);
    printf("Ingresar apellido nuevo: ");
    color(7);
    fflush(stdin);
    gets(apellidoNuevo);

    modificarApellidoCliente(lista, id, apellidoNuevo);

//    return lista;
}

void modificarApellidoCliente (nLista ** lista, int id, char apellido[])
{
    nLista * aux;
    if (lista)
    {
        aux = buscarNodoID((*lista), id);// busco la posición de memoria del nodo y lo modifico.
        strcpy(aux->dato.apellido, apellido);
    }
//    return lista;
}

//USERNAME
void subProgModUserNameCliente (nLista ** lista, int id)
{
    char usuario [20];
    int p = 0;
    do
    {
        color(3);
        printf("Ingresar UserName: ");
        color(7);
        fflush(stdin);
        gets(usuario);
        p = validarUserName(usuario, "archivoCliente.dat");
        if (p == 1)
        {
            avisoValidacion();
        }

    }
    while (p == 1);

    modificarUserNameCliente(lista, id, usuario);


}

void modificarUserNameCliente (nLista ** lista, int id, char userName[])
{
    nLista * aux;
    if (lista)
    {
        aux = buscarNodoID((*lista), id);// busco la posición de memoria del nodo y lo modifico.
        strcpy(aux->dato.userName, userName);
    }
//    return lista;
}

//CONTRASEÑA
void subProgModPassCliente (nLista ** lista, int id)
{
    char passNuevo[20];

    color(3);
    printf("Ingresar contraseña nueva: ");
    color(7);
    fflush(stdin);
    gets(passNuevo);
    modificarPassCliente(lista, id, passNuevo);
}


void modificarPassCliente (nLista ** lista, int id, char pass[])
{
    nLista * aux;
    if (lista)
    {
        aux = buscarNodoID((*lista), id);
        strcpy(aux->dato.password, pass);
    }
}


//DIRECCIÓN

void subProgModDireCliente (nLista * lista, int id)
{
    char direNueva[20];

    color(3);
    printf("Ingresar dirección nueva: ");
    color(7);
    fflush(stdin);
    gets(direNueva);

    modificarDireCliente(lista, id, direNueva);
}

void modificarDireCliente (nLista ** lista, int id, char direccion[])
{
    nLista * aux;
    if (lista)
    {
        aux = buscarNodoID((*lista), id);
        strcpy(aux->dato.domicilio, direccion);
    }
}

// MAIL


void subProgModMailCliente(nLista ** lista, int id)
{
    char mailNuevo[20];
    int p = 0;
    do
    {
        color(4);
        printf("Ingresar Mail: ");
        color(7);
        fflush(stdin);
        gets(mailNuevo);
        p = ValidarMail(mailNuevo, "archivoCliente.dat");
        if (p == 1)
        {
            avisoValidacion();
        }
    }
    while (p == 1);
}

void modificarMailCliente(nLista ** lista, int id, char mail[])
{
    nLista * aux;
    if (lista)
    {
        aux = buscarNodoID((*lista), id);
        strcpy(aux->dato.mail, mail);
    }
}
//------------------------------------------------------------------ FIN MODIFICACIÓN DE DATOS
