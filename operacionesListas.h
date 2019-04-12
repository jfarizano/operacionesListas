#ifndef __OPERACIONES_H__
#define __OPERACIONES_H__

#include <stddef.h>
/*
#define NOMBRE dato->nombre
#define EDAD dato->edad
#define LUGAR_NAC dato->lugarDeNacimiento
*/

////////////////////////////////////
// Definiciones de estructuras y tipos de datos

typedef struct _GNodo {
  void *dato;
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

////////////////////////////////////
// Prototipos de funciones

GList glist_crear();

void glist_string_destruir(GList lista);

int glist_vacia(GList lista);

GList glist_agregar_inicio(GList lista, void *dato);

GList glist_agregar_final(GList lista, void *dato);

int glist_longitud(GList lista);

GList map(GList lista, Funcion f, Copia c);

GList filter(GList lista, Predicado p, Copia c);

Persona *crear_persona(char *nombre, int edad, char *lugarNac);

void glist_persona_destruir(GList lista);

void destruir_persona(Persona *persona);

GList agregar_persona_inicio(GList lista, char *nombre, int edad, char *lugarNac);

GList agregar_persona_final(GList lista, char *nombre, int edad, char *lugarNac);

void *copiar_persona(void *dato);

#endif /* __OPERACIONES_H__ */
