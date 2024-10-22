#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "./include/got.h"


////////////////////
////    Main    ////
////////////////////

int main(int argc, char** argv){

    // Variables globales
    char opcion;
    TABB arbol;
    crearAbb(&arbol);
    if(argc>1){
        if(strcmp(argv[1],"-f")==0){
            cargarArchivo(argv[2],&arbol);
        }
    }

    // BUCLE PARA INTERFAZ GRÁFICA //

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
        
        // Switch de menu
        switch (opcion) {
            case 'A': 
            case 'a':
            printf("Anhadir\n");
            anhadirPersonaje(&arbol);
                break;

            case 'B': 
            case 'b':
            printf("Buscar Asesino\n");
            buscarAsesino(arbol);
                break;

            case 'L':
            case 'l':
            printf("Listar\n");
            listarPersonajes(arbol);
                break;

            case 'E':
            case 'e':
            printf("Eliminar\n");
            eliminarPersonaje(&arbol);
                break;

            case 'S':
            case 's':
            printf("Salir\n");
                break;

            default:
                printf("\x1b[31m\nOpción incorrecta\x1b[0m\n");
                sleep(2);
                break;
        }
        while (getchar() != '\n');
    } while (opcion != 'S' && opcion !='s');

    // Guardar cambios, liberar memoria y salir

    if(argc>1){// Usamos el nombre pasado como parámetro
        if(strcmp(argv[1],"-f")==0){
            guardarArchivo(argv[2],arbol);
        }
    }else{// Pedimos el nombre al usurario
        printf("Introduce el nombre del archivo.txt en el que guardarás la información: ");
        char nombre_archivo[MAX];
        scanf(" %s",nombre_archivo);
        guardarArchivo(nombre_archivo,arbol);
    }

    destruirAbb(&arbol);
    return 0;
}