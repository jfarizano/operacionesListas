#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacionesListas.h"


void imprimir_nombre(struct _Persona *persona) {
  printf("%s\n", persona->nombre);
}

void agregar_uno_edad(struct _Persona *persona) {
  persona->edad = persona->edad + 1;
}

void kawaizar_persona(struct _Persona *persona) {
  int len = strlen(persona->nombre);
  persona->nombre = realloc(persona->nombre, (sizeof(char) * (len + 4)));
  persona->nombre[len] = '-';
  persona->nombre[len + 1] = 's';
  persona->nombre[len + 2] = 'a';
  persona->nombre[len + 3] = 'n';
  persona->nombre[len + 4] = '\0';

}

int nombre_corto(struct _Persona *persona) {
  if (strlen(persona->nombre) <= 8){
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
  map(lista, imprimir_nombre);
  lista = map(lista, kawaizar_persona);
  printf("===============\n");
  map(lista, imprimir_nombre);

  return 0;
}