#ifndef GOT_H
#define GOT_H

#include "../include/abb.h"

/**
 * Añade un nuevo personaje al árbol de personajes [arbol].
 * Se solicitan al usuario los datos del personaje (nombre, casa, estatus real, padres, hermanos, personajes asesinados)
 * y se inserta en el árbol binario de búsqueda.
 * 
 * @param arbol Puntero al árbol donde se va a insertar el personaje.
 */
void anhadirPersonaje(TABB *arbol);

/**
 * Lista todos los personajes del árbol [arbol] en orden ascendente de acuerdo a sus nombres.
 * El recorrido del árbol es en orden (IRD: izquierda-raíz-derecha), mostrando el nombre,
 * casa, si es miembro de la realeza, padres, hermanos y personajes asesinados.
 *
 * @param arbol Árbol de personajes a listar.
 */
void listarPersonajes(TABB arbol);

/**
 * Elimina un personaje del árbol de personajes [arbol].
 * Solicita al usuario el nombre del personaje a eliminar y lo elimina del árbol binario de búsqueda.
 * No se contempla la situación en la que el personaje no exista en el árbol.
 *
 * @param arbol Puntero al árbol del cual se eliminará el personaje.
 */
void eliminarPersonaje(TABB *arbol);

//<------------------------------------------------------------------------------------------>//
void cargarArchivo(char* nombre_arquivo, TABB* arbol_principal);
void guardarArchivo(const char* nombre_archivo, TABB arbol);
//<------------------------------------------------------------------------------------------>//
void buscarAsesino(TABB arbol);
void buscarHijo(TABB arbol);

#endif
