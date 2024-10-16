#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "../include/abb.h"

void anhadirPersonaje(TABB *arbol){
    // Variables
    TIPOELEMENTOLISTA input;
    input.nameP[0] = '\0';
    TIPOELEMENTOABB personaje;

    // Solicita datos del personaje
    printf("\nIntroduce el nombre del personaje: ");
    scanf(" %[^\n\r]", personaje.name);

    printf("\nCasa (? si es desconocida): ");
    scanf(" %[^\n\r]", personaje.house);
    
    printf("\nRoyal (0/1): ");
    scanf("%d", &personaje.royal);
    
    // Lista de padres
    crearLista(&personaje.parents);
    while(strcmp(input.nameP, "fin")){
        printf("\nParents (fin para terminar): ");
        scanf(" %[^\n\r]", input.nameP);
        if(strcmp(input.nameP, "fin")){
            insertarElementoLista(&personaje.parents, finLista(personaje.parents), input);
        }
    }
    input.nameP[0] = '\0';

    // Lista de hermanos
    crearLista(&personaje.siblings);
    while(strcmp(input.nameP, "fin")){
        printf("\nSiblings (fin para terminar): ");
        scanf(" %[^\n\r]", input.nameP);
        if(strcmp(input.nameP, "fin")){
            insertarElementoLista(&personaje.siblings, finLista(personaje.siblings), input);
        }
    }
    input.nameP[0] = '\0';

    // Lista de asesinados
    crearLista(&personaje.killed);
    while(strcmp(input.nameP, "fin")){
        printf("\nKilled (fin para terminar): ");
        scanf(" %[^\n\r]", input.nameP);
        if(strcmp(input.nameP, "fin")){
            insertarElementoLista(&personaje.killed, finLista(personaje.killed), input);
        }
    }
    input.nameP[0] = '\0';

    // Inserta personaje en el árbol
    insertarElementoAbb(arbol, personaje);
}

void imprimirLista(TLISTA lista){
    // Variables
    TIPOELEMENTOLISTA elemento;
    TPOSICION posicion = primeroLista(lista);
    
    // Recorre e imprime la lista
    for(int i = 0; i < longitudLista(lista); i++){
        recuperarElementoLista(lista, posicion, &elemento);
        posicion = siguienteLista(lista, posicion);
        printf("%s, ", elemento.nameP);
    }
}

void imprimirPersonaje(TIPOELEMENTOABB personaje){
    // Imprime los datos del personaje
    printf("\n%s\n", personaje.name);
    printf("\tHouse: \t%s\n", personaje.house);
    printf("\tRoyal\t%d", personaje.royal);

    // Imprime listas asociadas (padres, hermanos, asesinados)
    printf("\n\tParents: ");
    imprimirLista(personaje.parents);
    printf("\n\tSiblings: ");
    imprimirLista(personaje.siblings);
    printf("\n\tKilled: ");
    imprimirLista(personaje.killed);
    printf("\n");
}

void listarPersonajes(TABB arbol){ // Recorrido IRD (inorden)
    if(!esAbbVacio(arbol)){
        TIPOELEMENTOABB elemento;
        listarPersonajes(izqAbb(arbol));
        leerElementoAbb(arbol, &elemento);
        imprimirPersonaje(elemento);
        listarPersonajes(derAbb(arbol));
    }
}

void eliminarPersonaje(TABB *arbol){
    // Variables
    TIPOELEMENTOABB personaje;
    char input[MAX];

    // Solicita nombre del personaje a eliminar
    printf("Introduce el nombre del personaje que quieres eliminar: ");
    scanf(" %s", input);

    // Busca y elimina el personaje
    buscarNodoAbb(*arbol, input, &personaje);
    suprimirElementoAbb(arbol, personaje);
}



//<------------------------------------------------------------------------------------------>//
// Función para procesar una línea del archivo y almacenar los datos en TIPOELEMENTOABB

// Función para procesar una línea del archivo y almacenar los datos en TIPOELEMENTOABB
void procesar_linea(char* linea, TIPOELEMENTOABB* elemento) {
    TIPOELEMENTOLISTA tempElement;  // Usaremos este elemento para agregar a las listas
    char* token;
    char* rest = linea;  // Variable auxiliar para strtok_r

    // Token para el nombre
    token = strtok_r(rest, "|", &rest);
    if (token != NULL) {
        strcpy(elemento->name, token);
    }

    // Token para la casa
    token = strtok_r(rest, "|", &rest);
    if (token != NULL) {
        strcpy(elemento->house, token);
    }

    // Token para si es de la realeza (royal)
    token = strtok_r(rest, "|", &rest);
    if (token != NULL) {
        elemento->royal = atoi(token);  // Convertimos el string a entero
    }

    // Token para los padres
    token = strtok_r(rest, "|", &rest);
    if (token != NULL) {
        crearLista(&elemento->parents);  // Inicializamos la lista de padres
        char* subtoken;
        char* subrest = token;  // Variable auxiliar para los subtokens
        while ((subtoken = strtok_r(subrest, ",", &subrest)) != NULL) {
            strcpy(tempElement.nameP, subtoken);  // Copiamos el nombre al elemento de lista
            insertarElementoLista(&elemento->parents, finLista(elemento->parents), tempElement);  // Insertamos en la lista
        }
    }

    // Token para los hermanos
    token = strtok_r(rest, "|", &rest);
    if (token != NULL) {
        crearLista(&elemento->siblings);  // Inicializamos la lista de hermanos
        char* subtoken;
        char* subrest = token;
        while ((subtoken = strtok_r(subrest, ",", &subrest)) != NULL) {
            strcpy(tempElement.nameP, subtoken);  // Copiamos el nombre al elemento de lista
            insertarElementoLista(&elemento->siblings, finLista(elemento->siblings), tempElement);  // Insertamos en la lista
        }
    }

    // Token para los asesinados
    token = strtok_r(rest, "|", &rest);
    if (token != NULL) {
        crearLista(&elemento->killed);  // Inicializamos la lista de asesinados
        char* subtoken;
        char* subrest = token;
        while ((subtoken = strtok_r(subrest, ",", &subrest)) != NULL) {
            strcpy(tempElement.nameP, subtoken);  // Copiamos el nombre al elemento de lista
            insertarElementoLista(&elemento->killed, finLista(elemento->killed), tempElement);  // Insertamos en la lista
        }
    }
}


void cargarArchivo(char* nombre_archivo, TABB* arbol_principal){
    // Abro o arquivo
    FILE *archivo_personajes = fopen(nombre_archivo, "r");
    if (archivo_personajes == NULL){
        perror("\x1b[31mErro ao abrir o arquivo de impresoras\x1b[0m\n");
        exit(1);
    }

    char linea[1024];
    while (fgets(linea, sizeof(linea), archivo_personajes)) {
        // Eliminar el salto de línea si existe
        linea[strcspn(linea, "\n")] = 0;

        TIPOELEMENTOABB elemento;
        procesar_linea(linea, &elemento);

        insertarElementoAbb(arbol_principal,elemento);
    }

    // Cerramos o arquivo
    fclose(archivo_personajes);
}