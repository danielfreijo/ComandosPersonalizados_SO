#include "funciones.h"

int main() {
    
    printf("\nEn esta aplicacion podras recopilar informacion detallada sobre los adaptadores de red disponibles, identificar los adaptadores configurados y generar un archivo XML con la informacion recopilada.  \n");
    printf("A continuacion se va a mostrar la lista de adaptadores de red de su equipo... \n\n");
    system("pause");
    system("cls");
    
    // LLamada a la función para mostrar adaptadores de red
    mostrarAdaptador();
    remove(ARCHIVO_ADAPTADORES); // Eliminamos el archivo con la informacíon de todos los adaptadores
    
    // LLamada a la función para recopilar la velocidad
    checkearVelocidad();
    
    // LLamada a la función para recopilar la informacion de las IPs de cada salto
    ipSaltos();
    remove(ARCHIVO_TEMPORAL); // Eliminamos el archivo con la salida del comando tracert
    
    // LLamada a la función para generar el archivo XML
    generarXML();

    printf("\nSaliendo de la aplicacion... \n");
    system("pause");
    return 0;

}


