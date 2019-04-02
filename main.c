#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacionesListas.h"


void imprimir_datos(struct _Persona *persona) {
  printf("%s\n", persona->nombre);
}

void agregar_uno_edad(struct _Persona *persona) {
  persona->edad = persona->edad + 1;
}

int nombre_corto(struct _Persona *persona) {
  if (strlen(persona->nombre) < 5){
    return 1;
  } else {
    return 0;
  }
}

int main() {
  SList lista = slist_crear();
  char nombre1[] = "PEPE";
  char nombre2[] = "Juan Ignacio Bernal";
  char nombre3[] = "Fede";
  char nombre4[] = "Federico";
  char lugarNac[] = "Narnia";
  lista = slist_agregar_inicio(lista, nombre1, 5, lugarNac);
  lista = slist_agregar_inicio(lista, nombre2, 3, lugarNac);
  lista = slist_agregar_final(lista, nombre3, 99, lugarNac);
  lista = slist_agregar_inicio(lista, nombre4, 4, lugarNac);
  map(lista, imprimir_datos);
  lista = filter(lista, nombre_corto);
  printf("===============\n");
  map(lista, imprimir_datos);
  slist_destruir(lista);
  map(lista, imprimir_datos);

  return 0;
}