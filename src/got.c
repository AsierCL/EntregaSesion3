#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "../include/abb.h"
#include "../include/colors.h"

void anhadirPersonaje(TABB *arbol){
    // Variables
    TIPOELEMENTOLISTA input;
    input.nameP[0] = '\0';
    TIPOELEMENTOABB personaje;

    // Solicita datos del personaje
    printf(AMARILLO);
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
    printf(RESET);
}

void imprimirLista(TLISTA lista){
    // Variables
    TIPOELEMENTOLISTA elemento;
    TPOSICION posicion = primeroLista(lista);
    
    if(longitudLista(lista)==0){
        printf("-");
    }else{
        // Recorre e imprime la lista
        for(int i = 0; i < longitudLista(lista); i++){
            recuperarElementoLista(lista, posicion, &elemento);
            posicion = siguienteLista(lista, posicion);
            printf("%s, ", elemento.nameP);
        }
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

    if (esMiembroAbb(*arbol, personaje)) {  // Si el nombre sigue vacío, no se encontró
        printf(ROJO);
        printf("No se encontró el personaje\n");
        printf(RESET);
        return;
    }

    suprimirElementoAbb(arbol, personaje);
}



//<------------------------------------------------------------------------------------------>//
// Función para procesar una línea del archivo y almacenar los datos en TIPOELEMENTOABB
void procesar_linea(char* linea, TIPOELEMENTOABB* elemento) {
    TIPOELEMENTOLISTA tempElement;
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
    if (token != NULL && *token != "-") {
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
    // Abro el archivo
    FILE *archivo_personajes = fopen(nombre_archivo, "r");
    if (archivo_personajes == NULL){
        printf(ROJO);
        perror("Fallo al intentar abrir el archivo\n");
        printf(RESET);
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

    // Cierro el archivo
    fclose(archivo_personajes);
}


// Función auxiliar para guardar una lista en el archivo
void guardarListaEnArchivo(FILE *archivo, TLISTA lista) {
    TIPOELEMENTOLISTA elemento;
    TPOSICION posicion = primeroLista(lista);

    for (int i = 0; i < longitudLista(lista); i++) {
        recuperarElementoLista(lista, posicion, &elemento);
        posicion = siguienteLista(lista, posicion);
        fprintf(archivo, "%s", elemento.nameP);
        if (i < longitudLista(lista) - 1) {
            fprintf(archivo, ","); // Añadimos coma entre elementos
        }
    }

    if(longitudLista(lista)==0){
        fprintf(archivo, "-");
    }
}

// Función auxiliar para guardar un personaje en el archivo
void guardarPersonaje(FILE *archivo, TIPOELEMENTOABB personaje) {
    // Guardar el nombre
    fprintf(archivo, "%s|", personaje.name);

    // Guardar la casa
    fprintf(archivo, "%s|", personaje.house);

    // Guardar el indicador de si es royal (0 o 1)
    fprintf(archivo, "%d|", personaje.royal);

    // Guardar la lista de padres
    guardarListaEnArchivo(archivo, personaje.parents);
    fprintf(archivo, "|");

    // Guardar la lista de hermanos
    guardarListaEnArchivo(archivo, personaje.siblings);
    fprintf(archivo, "|");

    // Guardar la lista de asesinados
    guardarListaEnArchivo(archivo, personaje.killed);
    fprintf(archivo, "|\n");
}

void escrituraPreorden(FILE *archivo,TABB arbol){
    // Recorrer el árbol e ir guardando los personajes
    if (!esAbbVacio(arbol)) {
        TIPOELEMENTOABB elemento;
        
        // Recorrido preorden del árbol (RID)
        leerElementoAbb(arbol, &elemento);
        guardarPersonaje(archivo, elemento);
        escrituraPreorden(archivo, izqAbb(arbol));
        escrituraPreorden(archivo, derAbb(arbol));
    }
}

// Función principal para guardar el árbol en un archivo
void guardarArchivo(const char* nombre_archivo, TABB arbol) {
    FILE *archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf(ROJO);
        printf("Error al abrir el archivo para escritura.\n");
        printf(RESET);
        return;
    }

    escrituraPreorden(archivo, arbol);

    fclose(archivo);
}


//<------------------------------------------------------------------------------------------>//
bool esAsesino(char* muerto, TIPOELEMENTOABB asesino){
    // Variables
    TIPOELEMENTOLISTA elemento;
    TPOSICION posicion = primeroLista(asesino.killed);
    
    // Recorre e imprime la lista
    for(int i = 0; i < longitudLista(asesino.killed); i++){
        recuperarElementoLista(asesino.killed, posicion, &elemento);
        posicion = siguienteLista(asesino.killed, posicion);
        if(!strcmp(muerto, elemento.nameP)){
            return true;
        }
    }
    return false;
}

void buscarAsesinoRecursivo(TABB arbol, char* muerto){
    TIPOELEMENTOABB elemento;
    if(esAbbVacio(arbol)){
        return;
    }
    buscarAsesinoRecursivo(izqAbb(arbol),muerto);
    leerElementoAbb(arbol, &elemento);
    if(esAsesino(muerto, elemento)){
        printf("%s,",elemento.name);
    }
    buscarAsesinoRecursivo(derAbb(arbol),muerto);
}

void buscarAsesino(TABB arbol){
    char muerto[MAX];
    printf("Introduce el nombre del personaje que queres buscar el asesino\n");
    scanf(" %[^\n\r]",muerto);
    
    if(!esAbbVacio(arbol)){
        buscarAsesinoRecursivo(arbol,muerto);
    }else{
        printf(ROJO);
        printf("Arbol vacio\n");
        printf(RESET);
    }
}

bool esHijo(char* padre, TIPOELEMENTOABB hijo){
    // Variables
    TIPOELEMENTOLISTA elemento;
    TPOSICION posicion = primeroLista(hijo.parents);
    
    // Recorre e imprime la lista
    for(int i = 0; i < longitudLista(hijo.parents); i++){
        recuperarElementoLista(hijo.parents, posicion, &elemento);
        posicion = siguienteLista(hijo.parents, posicion);
        if(!strcmp(padre, elemento.nameP)){
            return true;
        }
    }
    return false;
}

void buscarHijoRecursivo(TABB arbol, char* padre){
    TIPOELEMENTOABB elemento;
    if(esAbbVacio(arbol)){
        return;
    }
    buscarHijoRecursivo(izqAbb(arbol),padre);
    leerElementoAbb(arbol, &elemento);
    if(esHijo(padre, elemento)){
        printf("%s,",elemento.name);
    }
    buscarHijoRecursivo(derAbb(arbol),padre);
}

void buscarHijo(TABB arbol){
    char padre[MAX];
    printf("Introduce el nombre del personaje que queres buscar sus hijos\n");
    scanf(" %[^\n\r]",padre);
    
    if(!esAbbVacio(arbol)){
        buscarHijoRecursivo(arbol,padre);
    }else{
        printf(ROJO);
        printf("Arbol vacio\n");
        printf(RESET);
    }
}

void buscarMayorKillerRecursivo(TABB arbol, int *max_killed){
    TIPOELEMENTOABB elemento;
    if(esAbbVacio(arbol)){
        return;
    }
    buscarMayorKillerRecursivo(izqAbb(arbol), max_killed);
    leerElementoAbb(arbol, &elemento);
    if(longitudLista(elemento.killed) > *max_killed){
        *max_killed = longitudLista(elemento.killed);
    }
    buscarMayorKillerRecursivo(derAbb(arbol), max_killed);
}

void printearMayorKillerRecursivo(TABB arbol, int max_killed){
    TIPOELEMENTOABB elemento;
    if(esAbbVacio(arbol)){
        return;
    }
    printearMayorKillerRecursivo(izqAbb(arbol), max_killed);
    leerElementoAbb(arbol, &elemento);
    if(longitudLista(elemento.killed) == max_killed){
        printf("%s,",elemento.name);
    }
    printearMayorKillerRecursivo(derAbb(arbol), max_killed);
}

void buscarMayorKiller(TABB arbol){
    char padre[MAX];
    printf("Mayor killer:\n");
    int max_killed = 0;
    
    if(!esAbbVacio(arbol)){
        buscarMayorKillerRecursivo(arbol, &max_killed);
        printearMayorKillerRecursivo(arbol, max_killed);
        printf("\n");
    }else{
        printf(ROJO);
        printf("Arbol vacio\n");
        printf(RESET);
    }
}

void modificarPersonaje(TABB *arbol){
    // Variables
    TIPOELEMENTOABB personaje, nuevopersonaje;
    char input[MAX];
    char campo[MAX];
    TIPOELEMENTOLISTA valor;

    printf("Introduce el nombre del personaje que quieres modificar: ");
    scanf(" %[^\n\r]", input);

    buscarNodoAbb(*arbol, input, &personaje);

    // Verifica si se encontró el personaje
    if (esMiembroAbb(*arbol, personaje)) {  // Si el nombre sigue vacío, no se encontró
        printf(ROJO);
        printf("No se encontró el personaje\n");
        printf(RESET);
        return;
    }

    printf(VERDE);
    printf("PERSONAJE ENCONTRADO: \n");
    printf(RESET);
    printf("Que campo quieres modificar?\n");
    printf("\tname\n\thouse\n\troyal\n\tparents\n\tsiblings\n\tkilled\n");
    scanf(" %s", campo);

    // Comparaciones de campo con strcmp
    if (strcmp(campo, "name") == 0) {
        printf(AMARILLO);
        printf("Introduce el nuevo nombre: ");
        printf(RESET);
        scanf(" %[^\n\r]", personaje.name);

        buscarNodoAbb(*arbol, input, &nuevopersonaje);

        crearLista(&nuevopersonaje.parents);
        crearLista(&nuevopersonaje.siblings);
        crearLista(&nuevopersonaje.killed);

        modificarElementoAbb(*arbol, nuevopersonaje);
        suprimirElementoAbb(arbol, nuevopersonaje);
        insertarElementoAbb(arbol, personaje);

    } 
    else if (strcmp(campo, "house") == 0) {
        printf(AMARILLO);
        printf("Introduce la nueva casa: ");
        printf(RESET);
        scanf(" %s", valor.nameP);
        strcpy(personaje.house, valor.nameP);
    }
    else if (strcmp(campo, "royal") == 0) {
        printf(AMARILLO);
        printf("Introduce el nuevo valor para royal (0 o 1): ");
        printf(RESET);
        int intValor;
        scanf("%d", &intValor);
        personaje.royal = intValor;
    }
    else if (strcmp(campo, "parents") == 0) {
        destruirLista(&personaje.parents);
        crearLista(&personaje.parents);
        while(strcmp(valor.nameP, "fin")){
            printf(AMARILLO);
            printf("\nParents (fin para terminar): ");
            printf(RESET);
            scanf(" %[^\n\r]", valor.nameP);
            if(strcmp(valor.nameP, "fin")){
                insertarElementoLista(&personaje.parents, finLista(personaje.parents), valor);
            }
        }
    }
    else if (strcmp(campo, "siblings") == 0) {
        destruirLista(&personaje.siblings);
        crearLista(&personaje.siblings);
        while(strcmp(valor.nameP, "fin")){
            printf(AMARILLO);
            printf("\nSiblings (fin para terminar): ");
            printf(RESET);
            scanf(" %[^\n\r]", valor.nameP);
            if(strcmp(valor.nameP, "fin")){
                insertarElementoLista(&personaje.siblings, finLista(personaje.siblings), valor);
            }
        }
    }
    else if (strcmp(campo, "killed") == 0) {
        destruirLista(&personaje.killed);
        crearLista(&personaje.killed);
        while(strcmp(valor.nameP, "fin")){
            printf(AMARILLO);
            printf("\nKilled (fin para terminar): ");
            printf(RESET);
            scanf(" %[^\n\r]", valor.nameP);
            if(strcmp(valor.nameP, "fin")){
                insertarElementoLista(&personaje.killed, finLista(personaje.killed), valor);
            }
        }
    }
    else {
        printf(ROJO);
        printf("Campo incorrecto\n");
        printf(RESET);
    }

    modificarElementoAbb(*arbol, personaje);
}