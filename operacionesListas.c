#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacionesListas.h"

GList glist_crear() {
  return NULL;
}

Persona *crear_persona(char *nombre, int edad, char *lugarNac) {
  Persona *persona = malloc(sizeof(Persona));
  persona->edad = edad;
  int len = strlen(nombre);
  persona->nombre = malloc(sizeof(char) * (len + 1));
  len = strlen(lugarNac);
  persona->lugarDeNacimiento = malloc(sizeof(char) * (len + 1));
  strcpy(persona->nombre, nombre);
  strcpy(persona->lugarDeNacimiento, lugarNac);
  
  return persona;
};


void glist_persona_destruir(GList lista) {
  GNodo *nodoAEliminar;
  while (!glist_vacia(lista)) {
    nodoAEliminar = lista;
    lista = lista->sig;
    destruir_persona(nodoAEliminar->dato);
    free(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
}

void destruir_persona(Persona *dato) {
  free(dato->nombre);
  free(dato->lugarDeNacimiento);
}

void glist_string_destruir(GList lista) {
  GNodo *nodoAEliminar;
  while (!glist_vacia(lista)) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
}

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList agregar_persona_inicio(GList lista, char *nombre, int edad, char *lugarNac) {
  Persona *persona = crear_persona(nombre, edad, lugarNac);
  lista = glist_agregar_inicio(lista, persona);
  return lista;
}

GList agregar_persona_final(GList lista, char *nombre, int edad, char *lugarNac) {
  Persona *persona = crear_persona(nombre, edad, lugarNac);
  lista = glist_agregar_final(lista, persona);
  return lista;
}


GList glist_agregar_inicio(GList lista, void *dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;

  return nuevoNodo;
}

GList glist_agregar_final(GList lista, void *dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (glist_vacia(lista))
    return nuevoNodo;

  GList nodo = lista;
  for (;!glist_vacia(nodo->sig); nodo = nodo->sig);

  nodo->sig = nuevoNodo;
  return lista;
}

int glist_longitud(GList lista) {
  int len = 0;
  for (GNodo *nodo = lista; !glist_vacia(nodo); nodo = nodo->sig, len++);

  return len;

}

GList map(GList lista, Funcion f) {
  GList nuevaLista = glist_crear();

  for (GNodo *nodo = lista; !glist_vacia(nodo); nodo = nodo->sig)
    nuevaLista = glist_agregar_final(nuevaLista, nodo->dato);
  
  for (GNodo *nodo = nuevaLista; !glist_vacia(nodo); nodo = nodo->sig)
    f(nodo->dato);

  return nuevaLista;
}

GList filter(GList lista, Predicado p) {
  GList nuevaLista = glist_crear();

  for (GNodo *nodo = lista; !glist_vacia(nodo); nodo = nodo->sig)
    if (p(nodo->dato))
      nuevaLista = glist_agregar_final(nuevaLista, nodo->dato);  

  return nuevaLista;
}