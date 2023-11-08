#ifndef funciones

// Definici�n de constantes

#define funciones 
#define TAMA�O_BUFFER 512  
#define BUFFER_IP 16  
#define ARCHIVO_TEMPORAL "temporal.txt"  
#define ARCHIVO_ADAPTADORES "adaptadores.txt"  

#include <stdio.h>  // Biblioteca est�ndar para operaciones de entrada/salida
#include <stdlib.h>  // Biblioteca est�ndar para funciones generales
#include <string.h>  // Biblioteca est�ndar para operaciones de cadenas de caracteres
#include <stdbool.h>  // Biblioteca est�ndar para tipos de datos booleanos
#include <locale.h>  // Biblioteca est�ndar para configuraci�n regional
#include <ctype.h>  // Biblioteca est�ndar para funciones de caracteres

// Funci�n que se encarga de mostrar los adapatadores de red disponibles para su selecci�n.
void mostrarAdaptador();

// Funci�n que se encarga de contabilizar el numero de saltos del DNS configurado utilizando el comando tracert.
int contadorSaltos(char* ipDNS);

// Funci�n que se encarga de recopilar la informaci�n de las IPs de cada salto mediante un archivo generado en la funci�n anterior.
void ipSaltos();

// Funci�n que se encarga de comprobar la velocidad media con el comando ping y recopilarla en un archivo.
void checkearVelocidad();

// Funci�n que se encarga de generar el archivo XML con toda la informaci�n recopilada en las anteriores funciones.
void generarXML();

#endif






