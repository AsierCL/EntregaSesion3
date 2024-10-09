#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/abb.h"


void anhadirPersonaje(TABB *arbol){
    //char input[MAX]={0};
    TIPOELEMENTOLISTA input;
    input.nameP[0] = '\0';
    TIPOELEMENTOABB personaje;
    printf("\nIntroduce el nombre del personaje: ");
    scanf(" %[^\n\r]",personaje.name);

    printf("\nCasa (? si es desconocida): ");
    scanf(" %[^\n\r]",personaje.house);
    
    crearLista(&personaje.parents);
    while(strcmp(input.nameP, "fin")){
        printf("\nParents (fin para terminar): ");
        scanf(" %[^\n\r]",input.nameP);
        insertarElementoLista(&personaje.parents, finLista(personaje.parents), input);
    }
    input.nameP[0] = '\0';

    crearLista(&personaje.siblings);
    while(strcmp(input.nameP, "fin")){
        printf("\nSiblings (fin para terminar): ");
        scanf(" %[^\n\r]",input.nameP);
        insertarElementoLista(&personaje.siblings, finLista(personaje.siblings), input);
    }
    input.nameP[0] = '\0';

    crearLista(&personaje.killed);
    while(strcmp(input.nameP, "fin")){
        printf("\nKilled (fin para terminar): ");
        scanf(" %[^\n\r]",input.nameP);
        insertarElementoLista(&personaje.killed, finLista(personaje.killed), input);
    }
    input.nameP[0] = '\0';

    insertarElementoAbb(arbol, personaje);

}