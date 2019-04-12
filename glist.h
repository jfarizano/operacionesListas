#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>



///////////////////////////////////////////////////////////////////////////////
// Definiciones de estructuras

// GList es una lista doblemente enlazada circular, con un dato genérico
// void *dato.
typedef struct _GNodo {
  void *dato;
  struct _GNodo *ant;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

// Representamos a una persona mediante una estructura de tipo Persona,
// cuyos datos contienen su nombre, edad y lugar de nacimiento(capital o país).
typedef struct _Persona {
    char *nombre;
    int edad;
    char *lugarDeNacimiento; // Pais o capital
} Persona;

///////////////////////////////////////////////////////////////////////////////
// Punteros a funciones.

typedef int (*Predicado) (void *dato);
 
typedef void (*Funcion) (void *dato);

typedef void* (*Copia) (void *dato);

typedef void (*Destruir ) ( void *dato );

///////////////////////////////////////////////////////////////////////////////
// Prototipos de funciones.

/*
* glist_crear(): None -> GList
* Devuelve una lista vacía.
*/
GList glist_crear();

/*
* glist_vacia(): GList -> int
* Determina si la lista es vacía.
*/
int glist_vacia(GList lista);

/*
* glist_destruir(): GList Destruir -> None
* Libera de la memoria una lista y sus datos.
*/
void glist_destruir(GList lista, Destruir destruir);

/*
* glist_agregar_inicio(): GList void* -> GList
* Agrega el dato dado al inicio de la lista.
*/
GList glist_agregar_inicio(GList lista, void *dato);

/*
* glist_agregar_final(): GList void* -> GList
* Agrega el dato dado al final de la lista.
*/
GList glist_agregar_final(GList lista, void *dato);

/*
* glist_longitud(): GList -> int
* Devuelve la longitud de la lista.
*/
int glist_longitud(GList lista);

/*
* map(): GList Funcion Copia -> GList
* Devuelve una nueva lista formada por las imágenes de cada elemento
* de la lista original luego de aplicarle la función f.
*/
GList map(GList lista, Funcion f, Copia c);

/*
* filter(): GList Predicado Copia -> GList
* Devuelve una nueva lista formada por los elementos 
* de la lista original que cumplen con el predicado p.
*/
GList filter(GList lista, Predicado p, Copia c);

/*
* crear_persona(): char* int char* -> Persona*
* Dados los datos que la conforman, devuelve una estructura de dato persona
* conteniendo los mismos.
*/
Persona *crear_persona(char *nombre, int edad, char *lugarNac);

/*
* destruir_persona(): void* -> None
* Libera de la memoria una estructura de tipo persona y sus datos.
*/
void destruir_persona(void *dato);

/*
* copiar_persona(): void* -> void*
* Devuelve una nueva estructura de tipo persona
* con los mismos datos que la dada.
*/
void *copiar_persona(void *dato);


#endif /* __GLIST_H__ */
