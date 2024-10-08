#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/abb.h"


void anhadirPersonaje(TABB *arbol){
    char input[MAX]={0};
    TIPOELEMENTOABB personaje;
    printf("\nIntroduce el nombre del personaje: ");
    scanf(" %[^\n\r]",personaje.name);

    printf("\nCasa (? si es desconocida): ");
    scanf(" %[^\n\r]",personaje.house);
    
    crearLista(&personaje.parents);
    while(strcmp(input, "fin")){
        printf("\nParents (fin para terminar): ");
        scanf(" %[^\n\r]",input);
    }

    insertarElementoAbb(arbol, personaje);

}