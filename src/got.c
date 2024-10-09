#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
