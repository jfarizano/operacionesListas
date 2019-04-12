#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "operacionesListas.h"


Persona *linea_archivo_a_persona(char *lineaBuff) {
  int lenLinea = strlen(lineaBuff), edad;
  char *strBuff = malloc(sizeof(char) * 50);
  char *nombre, *lugarNac;

  for (int i = 0, charActual = 0, strActual = 0; i <= lenLinea; i++) {
    if (lineaBuff[i] != ',' && lineaBuff[i] != '\0') {
      strBuff[charActual] = lineaBuff[i];
      charActual++;
    } else {
      strBuff[charActual] = '\0';
      charActual = 0;
      switch (strActual) {
        case 0:
          nombre = malloc(sizeof(char) * (strlen(strBuff) + 1));
          strcpy(nombre, strBuff);
          strActual++;
          break;
        case 1:
          edad = atoi(strBuff); // Convierte el string de un int a un int
          strActual++;
          break;
        case 2:
          lugarNac = malloc(sizeof(char) * (strlen(strBuff) + 1));
          strcpy(lugarNac, strBuff);
          break;
      }
    }
  }

  Persona *persona = crear_persona(nombre, edad, lugarNac);
  free(nombre);
  free(lugarNac);
  free(strBuff);
  return persona;
}

GList lectura_censo(GList lista, char *nombre_archivo, int *cantElementos) {
  FILE *archivo = fopen(nombre_archivo, "r");
  assert(archivo != NULL);

  char charBuff;
  char *lineaBuff = malloc(sizeof(char) * 70);
  
  for (int i = 0; (charBuff = fgetc(archivo)) != EOF;){
    if (charBuff != '\n' && charBuff != '\r'){
      lineaBuff[i] = charBuff;
      i++;
    }else{
      lineaBuff[i] = '\0';
      i = 0;
      (*cantElementos)++;
      Persona *persona = linea_archivo_a_persona(lineaBuff);
      lista = glist_agregar_final(lista, persona);
      charBuff = fgetc(archivo);
    }
  }

  free(lineaBuff);
  fclose(archivo);
  
  return lista;
}

void imprimir_datos(GList lista) {
  Persona *persona;

  for (GNodo *nodo = lista; !glist_vacia(nodo); nodo = nodo->sig) {
    persona = (Persona*)nodo->dato;
    printf("Nombre: %s, ", persona->nombre);
    printf("edad: %d ", persona->edad);
    printf("lugar de nac.: %s\n", persona->lugarDeNacimiento);
  } 
}

// void maradonizar()

// void argentinizar()

void karate_kid(void *dato) {
  Persona *persona = (Persona*)dato;
  
  if (strcmp(persona->nombre, "Daniel") == 0){
    int len = strlen(persona->nombre);
    persona->nombre = realloc(persona->nombre, (sizeof(char) * (len + 5)));
    persona->nombre[len] = '-';
    persona->nombre[len + 1] = 's';
    persona->nombre[len + 2] = 'a';
    persona->nombre[len + 3] = 'n';
    persona->nombre[len + 4] = '\0';
  }
}

int nombre_corto(void *dato) {
  Persona *persona = (Persona*)dato;
  if (strlen(persona->nombre) <= 6){
    return 1;
  } else {
    return 0;
  }
}

// int dolar()

// int g20()

int main() {
  int cantPersonas = 0;
  
  GList listaPersonas = glist_crear();
  listaPersonas = lectura_censo(listaPersonas, "censo.txt", &cantPersonas);

  GList map1 = map(listaPersonas, karate_kid, copiar_persona);
  // GList map2 = .....
  GList filter1 = filter(listaPersonas, nombre_corto, copiar_persona);
  // GList filter2 = filter.....

  // salida_archivo(map1);
  // salida_archivo(map2);
  // salida_archivo(filter1);
  // salida_archivo(filter2);
  
  glist_persona_destruir(listaPersonas);
  glist_persona_destruir(map1);
  // glist_persona_destruir(map2);
  glist_persona_destruir(filter1);
  // glist_persona_destruir(filter2);


  return 0;
}