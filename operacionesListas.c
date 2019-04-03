#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacionesListas.h"

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (!slist_vacia(lista)) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar->NOMBRE);
    free(nodoAEliminar->LUGAR_NAC);
    free(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_inicio(SList lista, char *nombre, int edad, char *lugarNac) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = malloc(sizeof(Persona));

  // Pasar este bloque a crear_persona()
  nuevoNodo->EDAD = edad;
  int len = strlen(nombre);
  nuevoNodo->NOMBRE = malloc(sizeof(char) * (len + 1));
  len = strlen(lugarNac);
  nuevoNodo->LUGAR_NAC = malloc(sizeof(char) * (len + 1));
  strcpy(nuevoNodo->NOMBRE, nombre);
  strcpy(nuevoNodo->LUGAR_NAC, lugarNac);

  nuevoNodo->sig = lista;

  return nuevoNodo;
}

SList slist_agregar_final(SList lista, char *nombre, int edad, char *lugarNac) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = malloc(sizeof(Persona));

  nuevoNodo->EDAD = edad;
  int len = strlen(nombre);
  nuevoNodo->NOMBRE = malloc(sizeof(char) * (len + 1));
  len = strlen(lugarNac);
  nuevoNodo->LUGAR_NAC = malloc(sizeof(char) * (len + 1));
  strcpy(nuevoNodo->NOMBRE, nombre);
  strcpy(nuevoNodo->LUGAR_NAC, lugarNac);

  nuevoNodo->sig = NULL;

  if (slist_vacia(lista))
    return nuevoNodo;

  SList nodo = lista;
  for (;!slist_vacia(nodo->sig); nodo = nodo->sig);

  nodo->sig = nuevoNodo;
  return lista;
}

int slist_longitud(SList lista) {
  int len = 0;
  for (SNodo *nodo = lista; !slist_vacia(nodo); nodo = nodo->sig, len++);

  return len;

}

SList map(SList lista, Funcion f) {
  SList nuevaLista = slist_crear();

  for (SNodo *nodo = lista; !slist_vacia(nodo); nodo = nodo->sig)
    nuevaLista = slist_agregar_final(nuevaLista, nodo->NOMBRE, nodo->EDAD, nodo->LUGAR_NAC);
  
  for (SNodo *nodo = nuevaLista; !slist_vacia(nodo); nodo = nodo->sig)
    f(nodo->dato);

  return nuevaLista;
}

SList filter(SList lista, Predicado p) {
  SList nuevaLista = slist_crear();

  for (SNodo *nodo = lista; !slist_vacia(nodo); nodo = nodo->sig)
    if (p(nodo->dato))
      nuevaLista = slist_agregar_final(nuevaLista, nodo->NOMBRE, nodo->EDAD, nodo->LUGAR_NAC);  

  return nuevaLista;
}