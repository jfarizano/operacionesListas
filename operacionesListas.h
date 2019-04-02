#ifndef __OPERACIONES_H__
#define __OPERACIONES_H__

#include <stddef.h>
#define NOMBRE dato->nombre
#define EDAD dato->edad
#define LUGAR_NAC dato->lugarDeNacimiento

////////////////////////////////////
// Definiciones de estructuras y tipos de datos

typedef struct _SNodo {
  struct _Persona *dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

typedef struct _Persona {
    char *nombre;
    int edad;
    char *lugarDeNacimiento; // Pais o capital
} Persona;

typedef int (*Predicado) (struct _Persona*);

typedef void (*Funcion) (struct _Persona*);

////////////////////////////////////
// Prototipos de funciones

SList slist_crear();

void slist_destruir(SList lista);

int slist_vacia(SList lista);

SList slist_agregar_inicio(SList lista, char *nombre, int edad, char *lugarDeNac);

SList slist_agregar_final(SList lista, char *nombre, int edad, char *lugarDeNac);

int slist_longitud(SList lista);

SList map(SList lista, Funcion f);

SList filter(SList lista, Predicado p);

#endif /* __OPERACIONES_H__ */
