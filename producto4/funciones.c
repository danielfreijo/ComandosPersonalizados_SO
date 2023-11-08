#define _CRT_SECURE_NO_WARNINGS
#include "funciones.h"

void mostrarAdaptador() {
    char buffer[TAMA�O_BUFFER]; // Almacenamiento para las l�neas le�das
    char* ipV4; // Puntero para almacenar la direcci�n IP IPv4 actual
    char* mascara; // Puntero para almacenar la m�scara de subred actual
    char* enlace; // Puntero para almacenar la puerta de enlace actual
    char* ipDNS; // Puntero para almacenar la direcci�n IP del servidor DNS actual
    int opcion, contador = 0, numOpciones = 0; // Variables para almacenar la opci�n seleccionada y el contador de adaptadores
    bool adaptadorEncontrado = false; // Variable para llevar registro de si se encontr� alg�n adaptador
    bool adaptadorConf = false; // Variable para llevar registro de si el adaptador est� configurado
    FILE* cmd; // Variable para almacenar la salida del comando ejecutado
    FILE* documento = fopen("adaptadores.txt", "w"); // Abrimos el documento en modo escritura, si no existe se crea
    FILE* archivo = fopen("confiAdaptador.txt", "w"); // Abrimos el documento en modo escritura, si no existe se crea

    // Se comprueba que el documento se abre correctamente
    if (documento == NULL) {
        printf("\nNo se ha podido abrir el documento\n"); // Texto que se muestra en caso de error
        system("pause");
        system("cls"); // Limpiamos la consola
        return; // Finaliza la funci�n
    }

    // Ejecutar el comando para obtener la configuraci�n de red completa
    cmd = _popen("ipconfig /all", "r"); /* Abre un nuevo proceso y ejecuta el comando "ipconfig /all" para obtener la adaptadores de red.
                                        La "r" en el segundo argumento indica que la salida del comando se leer� como texto.
                                        La salida del comando se almacena en una tuber�a que puede ser le�da por el programa.*/

                                        // Leemos el resultado del comando y almacenamos la configuraci�n de red en el archivo
    while (fgets(buffer, TAMA�O_BUFFER, cmd)) { /* Permite leer  las l�neas del resultado del comando ejecutado y almacenarlas en la variable "buffer".
                                                  El ciclo se ejecuta hasta que no haya m�s l�neas por leer o se alcance el tama�o m�ximo del buffer. */
        fprintf(documento, "%s", buffer); // Escribimos la configuraci�n de red en el archivo
    }
    _pclose(cmd);
    fclose(documento);
    printf("\n");
    fopen("adaptadores.txt", "r");

    // Mostrar la lista de adaptadores disponibles y pedir al usuario que seleccione uno
    while (fgets(buffer, TAMA�O_BUFFER, documento)) { // Leemos la liniea del archivo
        if (strstr(buffer, "Adaptador")) { /* Se utiliza la funcion buscar una subcadena en una cadena.
                                              Si se encuentra la palabra "Adaptador" en la l�nea, se trata de un adaptador de red */
            contador++; // Incrementamos el contador de adaptadores
            numOpciones++; // Incrementamos las opciones junto al contador pa utilizar posteriomente
            printf("%d. %s", contador, buffer); // Mostramos el nombre del adaptador y su n�mero de orden
            adaptadorEncontrado = true; // Indica que se encontr� al menos un adaptador
        }
    }
    if (adaptadorEncontrado == false) { // Si no se encontr� ning�n adaptador ...
        printf("No se encontraron adaptadores\n");
        fclose(documento); // Cerramos el documento
        system("pause"); 
        system("cls"); // Limpiamos consola
        return; // Finaliza la funci�n y volvemos al menu
    }
    
    while (adaptadorConf == false) { // bucle hasta sellecionar un adaptador configurado
       
        printf("\nIngrese el numero del adaptador que desea consultar: ");
        scanf_s("%d", &opcion);
        if (opcion > numOpciones || opcion == 0) { // Si el usuario selecciona una opcion con un numero mayor a los que ha disponibles o "0", muestra mensaje de error
            printf("Opcion no valida, Ingrese una opcion valida: ");
            scanf_s("%d", &opcion);
        }
        rewind(documento); // Vuelve al principio del archivo
        contador = 0; // Volvemos a inicializar el contador a 0

        // Buscar el adaptador seleccionado y mostrar su informaci�n
        while (fgets(buffer, TAMA�O_BUFFER, documento)) {
            if (strstr(buffer, "Adaptador")) { // Se utiliza la misma funci�n que anteriormente hasta encontrar el nombre del adaptador que se ha seleccionado 
                contador++; // Incrementamos el contador de adaptadores
                if (contador == opcion) { // Si el contador coincide con la opci�n seleccionada lo mostramos
                    printf("\nInformacion del adaptador:\n\n");
                    printf("%s", buffer); // Mostramos el nombre del adaptador

                    // Imprime el nombre del adaptador 
                    while (fgets(buffer, TAMA�O_BUFFER, documento)) { // Leemos el resto de la informaci�n del adaptador
                        if (strstr(buffer, "Adaptador")) {
                            break; // Salimos del ciclo si se encuentra otro adaptador
                        }
                        if (strstr(buffer, "Estado de los medios")) { // Buscar la l�nea que contiene el estado de los medios
                            if (strstr(buffer, "medios desconectados")) {     
                            }
                        }
                        else if (strstr(buffer, "IPv4")) { // Buscar la l�nea que contiene la direcci�n IP
                            printf(buffer); // Mostrar solo la direcci�n IP
                            ipV4 = strtok(buffer, ":");
                            ipV4 = strtok(NULL, ": ");
                            ipV4 = strtok(ipV4, "(");
                            strcat(ipV4, "\n");
                            fprintf(archivo, "Ip:%s", ipV4);
                        }
                        else if (strstr(buffer, "subred")) { // Buscar la l�nea que contiene la m�scara de subred
                            printf(buffer); // Mostrar solo la m�scara de subred
                            mascara = strtok(buffer, ":");
                            mascara = strtok(NULL, ": ");
                            fprintf(archivo, "Mascara_subred:%s", mascara);
                        }
                        else if (strstr(buffer, "Puerta de enlace predeterminada")) { // Buscar la l�nea que contiene la puerta de enlace
                            printf(buffer); // Mostrar solo la puerta de enlace
                            enlace = strtok(buffer, ":");
                            enlace = strtok(NULL, ": ");
                            fprintf(archivo, "Puerta_enlace:%s", enlace);
                        }
                        else if (strstr(buffer, "Servidores DNS")) { // Buscar la l�nea que contiene los servidores DNS
                            printf(buffer); // Mostrar solo los servidores DNS        
                            ipDNS = strtok(buffer, ":");
                            ipDNS = strtok(NULL, ": ");
                            fprintf(archivo, "DNS:\n");
                            fprintf(archivo, "Ip_dns:%s", ipDNS);
                            adaptadorConf = true;
                        }  
                    }
                    if (adaptadorConf == false) {
                        printf("Este adaptador se encuentra actualmente desconectado o no configurado por lo tanto eliga otro adaptador"); 
                    }
                    break; // Salimos del ciclo
                }
            }
        }
    }

    // Cerramos los archivos y el comando y limpiamos la consola
    fclose(documento);
    printf("\n");
    fclose(archivo);

    system("pause");
    system("cls"); // Limpiamos consola 
}

int contadorSaltos(char* ipDNS) {
    char comando[TAMA�O_BUFFER];  // Almacena el comando de ejecuci�n que se utilizar� para obtener informaci�n de los saltos de red.
    char palabra[100];  // Almacena una cadena utilizada para realizar operaciones de b�squeda en el programa.
    char salida[TAMA�O_BUFFER] = { NULL };  // Almacena la salida generada por un comando ejecutado en el sistema.
    int numSaltos = 0;  // Almacena el n�mero total de saltos de red encontrados durante la recopilaci�n de informaci�n.

    printf("Comprobando... Porfavor espere!\n");
    strcpy(comando, "tracert ");
    strcat(comando, ipDNS);
    strcat(comando, " > temporal.txt"); // Redirigir la salida al archivo "temporal.txt"
    system(comando); // Ejecutar el comando tracert

    // Abrir el archivo temporal.txt para leer su contenido
    FILE* archivo = fopen("temporal.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo temporal.txt\n");
        return 0;
    }

    // Leer el contenido del archivo l�nea por l�nea
    while (fgets(palabra, 100, archivo)) {
        if (isdigit(palabra[0]) || (palabra[0] == ' ' && isdigit(palabra[2]))) {
            if (!strstr(palabra, "Tiempo de espera agotado")) {
                numSaltos++;
            }
        }
    }
    fclose(archivo); // Cerrar el archivo
    
    printf("\nLos saltos han sido comprobados\n\n");

    system("pause");
    system("cls"); // Limpiamos consola
    return numSaltos; // Retornamos el numero de saltos
}

void ipSaltos() {
    char linea[TAMA�O_BUFFER];  // Almacena una cadena utilizada para realizar operaciones de b�squeda en el programa
    char* inicioCorchetes = "";  // Puntero utilizado para marcar el inicio de un conjunto de corchetes en una cadena
    char* inicioIP = "";  // Puntero utilizado para marcar el inicio de una direcci�n IP en una cadena
    FILE* archivoAdaptador = fopen("confiAdaptador.txt", "a");  // Abrimos el documento en modo escritura
    FILE* archivo = fopen("temporal.txt", "r");  // Abrimos el documento en modo lectura
    int ipSalto = 0;  // Variable que lleva el contador de la cantidad de saltos de IP encontrados

    if (archivo == NULL) {
        printf("Error al abrir el archivo temporal.txt\n");
        return;
    }

    printf("\nRecopilando las IPs de los saltos...\n\n");
    fprintf(archivoAdaptador, "Ip_saltos:\n");

    while (fgets(linea, sizeof(linea), archivo)) { // Leemos cada linea del archivo
        if (isdigit(linea[0]) || (linea[0] == ' ' && isdigit(linea[2]))) { // Compobamos que el primer caracter sea un digito o 2 espacios y un digito
            if (!strstr(linea, "Tiempo de espera agotado")) { // si empieza por un digito y no encuentra la cadena especifica el contador suma 1
                ipSalto++;

                // Si la IP est� entre corchetes, la extraemos eliminando los corchetes
                inicioCorchetes = strchr(linea, ']');
                if (inicioCorchetes) {
                    *inicioCorchetes = '\0';
                    inicioIP = strchr(linea, '[') + 1;
                }
                else {
                    // Si la IP no est� entre corchetes, la extraemos a partir de la posici�n 32
                    inicioIP = &linea[32];
                    inicioIP[strcspn(inicioIP, "\n")] = '\0';  // Eliminamos el salto de l�nea al final de la IP
                }
                // Guardar la IP en el archivo
                fprintf(archivoAdaptador, "Ip_salto:%s\n", inicioIP);              
            }
        }
    }
    //Cerramos archivo y limpiamos consola
    fclose(archivoAdaptador);
    fclose(archivo);
    system("pause");
    system("cls");
}

void checkearVelocidad() {
    char buffer[TAMA�O_BUFFER]; // Variable que se utiliza para almacenar temporalmente datos que se leen desde un archivo y almacena las IP de los DNS
    char comando[TAMA�O_BUFFER] = "", velocidad[5]; // Variable que se utiliza para almacenar el comando que se va a ejecutar y variable donde se alamacena la velocidad media en caracteres
    char salidaCMD[TAMA�O_BUFFER]; // Variable para leer la salida almacenada del comando ejecutado "ping"
    char* puntero; // Variable que se utiliza para apuntar a la velocidad media del comando ping
    char ipDNS[BUFFER_IP]; // Variable para guardar la direccion IP del DNS
    FILE* archivoAdaptador = fopen("confiAdaptador.txt", "r"); // Archivo donde se encuentra los datos que nos interesa del adaptador seleccionado
    FILE* cmd; // Variable para almacenar la salida del comando ejecutado
    bool pingExitoso = false; // Variable para determinar si se ha podido hacer ping a la IP configurada
    int saltos = 0; // Variable para calcular los saltos del DNS

    if (archivoAdaptador == NULL) {  // Mensaje de error en caso de no poder abrir el archivo 
        printf("Error al abrir el archivo con la configuraci�n DNS\n");
        return;
    }
    else {
        // Leemos la direcci�n IP del DNS configurado y la almacenamos en la variable "Adaptador"
        while (fgets(buffer, TAMA�O_BUFFER, archivoAdaptador)) {
            if (strstr(buffer, "Ip_dns:")) {
                sscanf(buffer, "Ip_dns:%s", ipDNS);
                break;
            }
        }
        fclose(archivoAdaptador);

        // Ejecutamos comando ping
        comando[0] = '\0'; // Reiniciamos la variable en cada iteraci�n
        strcat(comando, "ping "); // Se concatena a la cadena command el comando de ping
        strcat(comando, ipDNS); // Se concatena a la cadena commando la direcci�n IP configurada
        
        cmd = _popen(comando, "r");
        printf("\nCalculando velocidad media ...\n");
        while (fgets(salidaCMD, TAMA�O_BUFFER, cmd)) {
            
            // Buscamos la velocidad media en el resultado del comando
            puntero = strstr(salidaCMD, "Media = ");
            if (puntero != NULL) {
                puntero += 8; // Movemos 8 caracteres a la derecha para obtener lo que nos interesa
                int i = 0;
                while (isdigit(puntero[i])) {
                    velocidad[i] = puntero[i];
                    i++;
                }
                velocidad[i] = '\0'; // Aseguramos que la cadena de velocidad est� terminada correctamente
                printf("Velocidad media: %s\n\n", velocidad);

                archivoAdaptador = fopen("confiAdaptador.txt", "a"); //Abrimos el archivo en modo escritura para guardar la velocidad
                if (archivoAdaptador != NULL) {
                    fprintf(archivoAdaptador, "Velocidad:%s\n", velocidad);
                    fclose(archivoAdaptador);
                }
                else {
                    printf("Error al abrir el archivo para escribir la velocidad\n");
                }
                pingExitoso = true;
                break;
            }
        }// Cerramos la tuberia del comando
        _pclose(cmd);

        if (!pingExitoso) {
            printf("No se ha podido hacer ping a la IP configurada: %s\n", buffer);
        }
    } // Limpiamos consola
    system("pause");
    system("cls");

    // Comprobamos el n�mero de saltos utilizando la funci�n anterior
    printf("\nSe va a comprobar el numero de saltos del DNS selecionado. Este proceso puede tardar varios minutos.\n");
    saltos = contadorSaltos(ipDNS);
   
    // Guardamos la info en el archivo
    archivoAdaptador = fopen("confiAdaptador.txt", "a");
    printf("\nEl servidor DNS que estas utilizando tiene un total de %d salto/s", saltos);
    fprintf(archivoAdaptador, "Saltos:%d\n", saltos);
    fclose(archivoAdaptador);
}

void generarXML() {
    char linea[TAMA�O_BUFFER];
    char etiqueta[TAMA�O_BUFFER], valor[TAMA�O_BUFFER];
    FILE* archivoAdaptador = fopen("confiAdaptador.txt", "r");
    FILE* archivoXML = fopen("adaptador.xml", "w");

    if (archivoAdaptador == NULL) {
        printf("Error al abrir el archivo confiAdaptador.txt\n");
        return;
    }

    printf("\nSe va a generar el archivo XML con la informacion recopilada del adaptador de red que ha seleccionado...\n");

    // Escribir la cabecera del archivo XML
    fprintf(archivoXML, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"); 
    fprintf(archivoXML, "<Adaptador>\n");

    while (fgets(linea, sizeof(linea), archivoAdaptador)) {
        if (sscanf(linea, "%[^:]:%[^\n]", etiqueta, valor) == 2) {
            if (strcmp(etiqueta, "Ip") == 0) {
                fprintf(archivoXML, "    <%s>%s </%s>\n", etiqueta, valor, etiqueta);
            }
            else if (strcmp(etiqueta, "Mascara_subred") == 0) {
                fprintf(archivoXML, "    <%s>%s </%s>\n", etiqueta, valor, etiqueta);
            }
            else if (strcmp(etiqueta, "Puerta_enlace") == 0) {
                fprintf(archivoXML, "    <%s>%s </%s>\n", etiqueta, valor, etiqueta);
                
                // Leemos la siguiente l�nea para obtener la etiqueta "DNS"
                fgets(linea, sizeof(linea), archivoAdaptador); 
                sscanf(linea, "%[^:]:%[^\n]", etiqueta, valor); 
                fprintf(archivoXML, "    <%s>\n", etiqueta);
            } 
            else if (strcmp(etiqueta, "Ip_dns") == 0) {
                fprintf(archivoXML, "        <%s>%s </%s>\n", etiqueta, valor, etiqueta);
            }
            else if (strcmp(etiqueta, "Velocidad") == 0) {
                fprintf(archivoXML, "        <%s>%s </%s>\n", etiqueta, valor, etiqueta);
            }
            else if (strcmp(etiqueta, "Saltos") == 0) {
                fprintf(archivoXML, "        <%s>%s </%s>\n", etiqueta, valor, etiqueta);
                
                // Leemos la siguiente l�nea para obtener la etiqueta "Ip_saltos"
                fgets(linea, sizeof(linea), archivoAdaptador);
                sscanf(linea, "%[^:]:%[^\n]", etiqueta, valor);
                fprintf(archivoXML, "        <%s>\n", etiqueta);
            }
            else if (strcmp(etiqueta, "Ip_salto") == 0) {
                fprintf(archivoXML, "            <%s>%s </%s>\n", etiqueta, valor, etiqueta);
            }
        }
    }
    fprintf(archivoXML, "        </Ip_saltos>\n");
    fprintf(archivoXML, "    </DNS>\n");
    fprintf(archivoXML, "</Adaptador>\n");
    
    fclose(archivoAdaptador);
    fclose(archivoXML);

    printf("\nArchivo XML generado con exito.\n\n");
    system("pause");
    system("cls");
    return;
}

