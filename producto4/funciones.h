#ifndef funciones

// Definición de constantes

#define funciones 
#define TAMAÑO_BUFFER 512  
#define BUFFER_IP 16  
#define ARCHIVO_TEMPORAL "temporal.txt"  
#define ARCHIVO_ADAPTADORES "adaptadores.txt"  

#include <stdio.h>  // Biblioteca estándar para operaciones de entrada/salida
#include <stdlib.h>  // Biblioteca estándar para funciones generales
#include <string.h>  // Biblioteca estándar para operaciones de cadenas de caracteres
#include <stdbool.h>  // Biblioteca estándar para tipos de datos booleanos
#include <locale.h>  // Biblioteca estándar para configuración regional
#include <ctype.h>  // Biblioteca estándar para funciones de caracteres

// Función que se encarga de mostrar los adapatadores de red disponibles para su selección.
void mostrarAdaptador();

// Función que se encarga de contabilizar el numero de saltos del DNS configurado utilizando el comando tracert.
int contadorSaltos(char* ipDNS);

// Función que se encarga de recopilar la información de las IPs de cada salto mediante un archivo generado en la función anterior.
void ipSaltos();

// Función que se encarga de comprobar la velocidad media con el comando ping y recopilarla en un archivo.
void checkearVelocidad();

// Función que se encarga de generar el archivo XML con toda la información recopilada en las anteriores funciones.
void generarXML();

#endif






