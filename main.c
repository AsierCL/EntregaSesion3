#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#include "./include/got.h"


////////////////////
////    Main    ////
////////////////////

int main(int argc, char** argv){

    // Declaro as variables globales
    char opcion;
    TABB arbol;
    crearAbb(&arbol);


    // BUCLE PARA A INTERFAZ GRÁFICA //

    do{
        //system("clear");
        printf("\n--------------------------------------------------------------\n");
        printf("\nBienvenido al programa de gestion de personajes de GoT\n");
        printf("\nA) Anhadir personaje\n");
        printf("\nL) Listar personajes\n");
        printf("\nE) Eliminar personaje\n");
        printf("\nS) Salir\n");
        printf("\n--------------------------------------------------------------\n");
        printf("\nOpción: ");
        scanf(" %c", &opcion);
        
        // Entramos no switch
        switch (opcion) {
            case 'A': 
            case 'a':
            printf("Anhadir\n");
            anhadirPersonaje(&arbol);
                break;

            case 'L':
            case 'l':
            printf("listar\n");
            listarPersonajes(arbol);
                break;

            case 'E':
            case 'e':
            printf("Eliminar\n");
            sleep(2);

                break;

            case 'S':
            case 's':
            printf("Salir\n");
            sleep(2);

                break;

            default:
                printf("\x1b[31m\nOpción incorrecta\x1b[0m\n");
                sleep(2);
                break;
        }
        while (getchar() != '\n');
    } while (opcion != 'S' && opcion !='s');
    return 0;
}