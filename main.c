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
          edad = atoi(strBuff);
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
  free(strBuff);
  return persona;
}

GList lectura_censo(GList lista, char *nombre_archivo, int *cantElementos) {
  FILE *archivo = fopen(nombre_archivo, "r");
  assert(archivo != NULL);

  int charBuff;
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
  
  fclose(archivo);
  free(lineaBuff);
  
  return lista;
}

void imprimir_datos(void *dato) {
  Persona *persona = dato;
  printf("Nombre: %s, ", persona->nombre);
  printf("edad: %d ", persona->edad);
  printf("lugar de nac.: %s\n", persona->lugarDeNacimiento);
}

void agregar_uno_edad(Persona *persona) {
  persona->edad = persona->edad + 1;
}

void kawaizar_persona(Persona *persona) {
  int len = strlen(persona->nombre);
  persona->nombre = realloc(persona->nombre, (sizeof(char) * (len + 4)));
  persona->nombre[len] = '-';
  persona->nombre[len + 1] = 's';
  persona->nombre[len + 2] = 'a';
  persona->nombre[len + 3] = 'n';
  persona->nombre[len + 4] = '\0';

}

int nombre_corto(Persona *persona) {
  if (strlen(persona->nombre) <= 8){
    return 1;
  } else {
    return 0;
  }
}

int main() {
  GList listaPersonas = glist_crear();
  int cantPersonas = 0;
  listaPersonas = lectura_censo(listaPersonas, "censo.txt", &cantPersonas);
  map(listaPersonas, imprimir_datos);
  glist_persona_destruir(listaPersonas);

  return 0;
}