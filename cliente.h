#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//
//#include "Arboles.h"
//#include "ListaSimple.h"
//#include "Compuestos.h"
//#include "menu.h"

//const char archivoCliente[] = "archivoCliente.dat";


typedef struct
{
    int idCliente;
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char domicilio[30];
    char genero;
    int rol;          // 1: es admin - 0: cliente
    int eliminado;   // indica 1 o 0 si el cliente fue eliminado
} stCliente;

//Funciones basicas
void mostrarCliente (stCliente cliente);
int cargarCliente (char nombre[]);
int cargarUnCliente(FILE * archi,char archiCliente[]);
int clientesAcumulados(FILE * archi);
int buscarEnRegistro(char userName[30], char pass[30], char archivo[]);

//Persistencia de datos
void CerrarArchivo (FILE * archi);

//Avisos varios
void avisoValidacion ();

//Validaciones
int ValidarMail (char mail[], char archivo[]);
int validarUserName(char userName[], char archivo[]);

//Muestra
void mostrarArchivoClientes (char nombre[]);
void mostrarCliente (stCliente cliente);

#endif // CLIENTE_H_INCLUDED
