#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>



///////////////////////////////////////////////////////////////////////////////
// Definiciones de estructuras, tipos de datos y punteros a funciones.

typedef struct _GNodo {
  void *dato;
  struct _GNodo *ant;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

typedef struct _Persona {
    char *nombre;
    int edad;
    char *lugarDeNacimiento; // Pais o capital
} Persona;

typedef int (*Predicado) (void *dato);

typedef void (*Funcion) (void *dato);

typedef void* (*Copia) (void *dato);

typedef void (* Destruir ) ( void * dato );

///////////////////////////////////////////////////////////////////////////////
// Prototipos de funciones

/*
* Devuelve una lista vacía.
*/
GList glist_crear();

/*
* Determina si la lista es vacía.
*/
int glist_vacia(GList lista);

/*
* Agrega el dato dado al inicio de la lista.
*/
GList glist_agregar_inicio(GList lista, void *dato);

/*
* Agrega el dato dado al final de la lista.
*/
GList glist_agregar_final(GList lista, void *dato);

/*
* Devuelve la longitud de la lista.
*/
int glist_longitud(GList lista);

/*
* Devuelve una nueva lista formada por las imágenes de cada elemento
* de la lista original luego de aplicarle la función f.
*/
GList map(GList lista, Funcion f, Copia c);

/*
* Devuelve una nueva lista formada por los elementos 
* de la lista original que cumplen con el predicado p.
*/
GList filter(GList lista, Predicado p, Copia c);

/*
* Dados los datos que la conforman, devuelve una estructura de dato persona
* conteniendo los mismos.
*/
Persona *crear_persona(char *nombre, int edad, char *lugarNac);

/*
* Libera de la memoria una estructura de tipo persona y sus datos.
*/
void destruir_persona(void *dato);

/*
* Dados los datos que conforman una persona, agrega una estructura de este tipo
* con sus datos correspondientes al inicio de la lista.
*/
GList agregar_persona_inicio(GList lista, char *nombre, int edad, char *lugarNac);

/*
* Dados los datos que conforman una persona, agrega una estructura de este tipo
* con sus datos correspondientes al final de la lista.
*/
GList agregar_persona_final(GList lista, char *nombre, int edad, char *lugarNac);

/*
* Devuelve una nueva estructura de tipo persona
* con los mismos datos que la dada.
*/
void *copiar_persona(void *dato);

/*
* Libera de la memoria una lista y sus datos.
*/
void glist_destruir(GList lista, Destruir destruir);

#endif /* __GLIST_H__ */
