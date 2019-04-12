#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glist.h"



GList glist_crear() {
  return NULL;
}

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_agregar_inicio(GList lista, void *dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  
  if (glist_vacia(lista)) {
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
  } else {
    nuevoNodo->sig = lista;
    nuevoNodo->ant = lista->ant;
    nuevoNodo->ant->sig = nuevoNodo;
    lista->ant = nuevoNodo;
  }

  return nuevoNodo;
}

GList glist_agregar_final(GList lista, void *dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;

  if (glist_vacia(lista)) {
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
    return nuevoNodo;
  } else {
    nuevoNodo->sig = lista;
    nuevoNodo->ant = lista->ant;
    nuevoNodo->ant->sig = nuevoNodo;
    lista->ant = nuevoNodo;

    return lista;
  }
}

int glist_longitud(GList lista) {
  int len = 0;
  
  for (GNodo *nodo = lista; nodo->sig != lista; nodo = nodo->sig, len++);
  len++;

  return len;

}

GList map(GList lista, Funcion f, Copia c) {
  GList nuevaLista = glist_crear();
  GNodo *nodo = lista;
  void *copiaDato;
  
  for (; nodo->sig != lista; nodo = nodo->sig) {
    copiaDato = c(nodo->dato);
    f(copiaDato);
    nuevaLista = glist_agregar_final(nuevaLista, copiaDato);
  }
    copiaDato = c(nodo->dato);
    f(copiaDato);
    nuevaLista = glist_agregar_final(nuevaLista, copiaDato);

  return nuevaLista;
}

GList filter(GList lista, Predicado p, Copia c) {
  GList nuevaLista = glist_crear();
  GNodo *nodo = lista;

  for (; nodo->sig != lista; nodo = nodo->sig) {
    if (p(nodo->dato)){
      nuevaLista = glist_agregar_final(nuevaLista, c(nodo->dato));
    }
  }

  if (p(nodo->dato)){
      nuevaLista = glist_agregar_final(nuevaLista, c(nodo->dato));
  }
  
  return nuevaLista;
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
}

void destruir_persona(void *dato) {
  Persona *persona = (Persona*)dato;
  free(persona->nombre);
  free(persona->lugarDeNacimiento);
  free(persona);
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

void *copiar_persona(void *dato){
  Persona *persona = (Persona*)dato;
  Persona *copia = crear_persona(persona->nombre, persona->edad, persona->lugarDeNacimiento);

  return (void*)copia; 
}

void glist_destruir(GList lista, Destruir destruir) {
  GNodo *nodoAEliminar;
  GNodo *nodoInicial = lista;

  while (lista->sig != nodoInicial) {
    nodoAEliminar = lista;
    lista = lista->sig;
    destruir(nodoAEliminar->dato);
    free(nodoAEliminar);
  }

  destruir(lista->dato);
  free(lista);
}