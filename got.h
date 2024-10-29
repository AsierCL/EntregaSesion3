#ifndef GOT_H
#define GOT_H

#include "abb.h"

/**
 * Añade un nuevo personaje al árbol de personajes.
 * Solicita al usuario los datos (nombre, casa, estatus real, padres, hermanos, asesinados)
 * y los inserta en el árbol binario de búsqueda.
 * 
 * @param arbol Puntero al árbol en el cual se insertará el personaje.
 */
void anhadirPersonaje(TABB *arbol);

/**
 * Lista todos los personajes en orden ascendente según sus nombres.
 * Realiza un recorrido en orden (IRD: izquierda-raíz-derecha) del árbol,
 * mostrando el nombre, casa, si es miembro de la realeza, padres, hermanos, y personajes asesinados.
 *
 * @param arbol Árbol de personajes a listar.
 */
void listarPersonajes(TABB arbol);

/**
 * Elimina un personaje del árbol de personajes.
 * Solicita al usuario el nombre del personaje a eliminar y lo elimina del árbol binario.
 * No considera si el personaje no existe en el árbol.
 *
 * @param arbol Puntero al árbol del cual se eliminará el personaje.
 */
void eliminarPersonaje(TABB *arbol);

//<------------------------------------------------------------------------------------------>//

/**
 * Carga los personajes desde un archivo al árbol.
 * Lee los datos del archivo especificado y los inserta en el árbol binario.
 * 
 * @param nombre_archivo Nombre del archivo desde donde se cargan los datos.
 * @param arbol_principal Puntero al árbol principal donde se almacenarán los datos.
 */
void cargarArchivo(char* nombre_archivo, TABB* arbol_principal);

/**
 * Guarda los personajes del árbol en un archivo.
 * Realiza un recorrido preorden del árbol y almacena los datos en el archivo.
 * 
 * @param nombre_archivo Nombre del archivo donde se guardarán los datos.
 * @param arbol Árbol de personajes a guardar.
 */
void guardarArchivo(const char* nombre_archivo, TABB arbol);

/**
 * Busca el personaje que ha asesinado a otro personaje.
 * Realiza una búsqueda en el árbol y muestra la información del personaje asesino.
 * 
 * @param arbol Árbol donde se realizará la búsqueda.
 */
void buscarAsesino(TABB arbol);

/**
 * Busca un personaje que sea hijo de otro personaje específico.
 * Permite al usuario introducir el nombre de un personaje padre para encontrar a su hijo en el árbol.
 * 
 * @param arbol Árbol donde se realizará la búsqueda.
 */
void buscarHijo(TABB arbol);

/**
 * Encuentra el personaje con la mayor cantidad de asesinatos.
 * Realiza un recorrido en el árbol para determinar el personaje con el mayor conteo de asesinatos.
 * 
 * @param arbol Árbol donde se realizará la búsqueda.
 */
void buscarMayorKiller(TABB arbol);

/**
 * Modifica los datos de un personaje en el árbol.
 * Permite al usuario cambiar los datos (nombre, casa, estatus real, listas de relaciones) de un personaje específico.
 * 
 * @param arbol Puntero al árbol donde se actualizarán los datos.
 */
void modificarPersonaje(TABB *arbol);

#endif // GOT_H
