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
    
    printf("\nRoyal (0/1): ");
    scanf("%d",&personaje.royal);
    
    crearLista(&personaje.parents);
    while(strcmp(input.nameP, "fin")){
        printf("\nParents (fin para terminar): ");
        scanf(" %[^\n\r]",input.nameP);
        if(strcmp(input.nameP, "fin")){
            insertarElementoLista(&personaje.parents, finLista(personaje.parents), input);
        }
    }
    input.nameP[0] = '\0';

    crearLista(&personaje.siblings);
    while(strcmp(input.nameP, "fin")){
        printf("\nSiblings (fin para terminar): ");
        scanf(" %[^\n\r]",input.nameP);
        if(strcmp(input.nameP, "fin")){
            insertarElementoLista(&personaje.siblings, finLista(personaje.siblings), input);
        }
    }
    input.nameP[0] = '\0';

    crearLista(&personaje.killed);
    while(strcmp(input.nameP, "fin")){
        printf("\nKilled (fin para terminar): ");
        scanf(" %[^\n\r]",input.nameP);
        if(strcmp(input.nameP, "fin")){
            insertarElementoLista(&personaje.killed, finLista(personaje.killed), input);
        }
    }
    input.nameP[0] = '\0';

    insertarElementoAbb(arbol, personaje);

}

void imprimirLista(TLISTA lista){
    //Elementos
    TIPOELEMENTOLISTA elemento;
    TPOSICION posicion = primeroLista(lista);
    
    for(int i=0;i<longitudLista(lista);i++){
        recuperarElementoLista(lista, posicion, &elemento);
        posicion = siguienteLista(lista, posicion);
        printf("%s, ",elemento.nameP);
    }
}

void imprimirPersonaje(TIPOELEMENTOABB personaje){
    //Nombre
    printf("%s\n",personaje.name);
    printf("\tHouse: \t%s\n",personaje.house);
    printf("\tRoyal\t%d\n",personaje.royal);
    printf("\n\tParents: ");
    imprimirLista(personaje.parents);
    printf("\n\tSiblings: ");
    imprimirLista(personaje.siblings);
    printf("\n\tKilled: ");
    imprimirLista(personaje.killed);
    printf("\n");
}

/* void listarPersonaje(TABB *arbol){
    TIPOELEMENTOABB personaje;
    char input[MAX];
    printf("Introduce el nombre del personaje que quieres buscar: ");
    scanf(" %s",input);

    buscarNodoAbb(*arbol, input, &personaje);

    imprimirPersonaje(personaje);
} */

void listarPersonajes(TABB arbol){
    if(!esAbbVacio(arbol)){
        TIPOELEMENTOABB elemento;
        listarPersonajes(izqAbb(arbol));
        leerElementoAbb(arbol, &elemento);
        imprimirPersonaje(elemento);
        listarPersonajes(derAbb(arbol));
    }
}

void eliminarPersonaje(TABB *arbol){
    TIPOELEMENTOABB personaje;
    char input[MAX];
    printf("Introduce el nombre del personaje que quieres eliminar: ");
    scanf(" %s",input);

    buscarNodoAbb(*arbol, input, &personaje);

    suprimirElementoAbb(arbol, personaje);
}