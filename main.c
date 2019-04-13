#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "glist.h"

/*
  linea_archivo_a_persona(): char* -> Persona*
  Dada una cadena de texto que representa una línea del archivo "censo.txt",
  separa los 3 datos espaciados en la cadena mediante una coma, 
  y devuelve una estructura de tipo Persona conformada por estos mismos.
*/
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

/*
  lectura_censo(): GList char* int* -> GList
  Toma una lista y el nombre de un archivo de texto que contenga los datos
  a utilizar siendo estos tres datos en tres cadenas de texto por cada
  línea del archivo, y devuelve una lista cuyos elementos
  son estructuras de tipo Persona, conformada por estos tres datos.
  El parametro *cantElementos es obtenido de la funcion main, 
  o donde se aplique, y se usa como contador de elementos de
  la lista.
*/
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

/*
  salida_archivo() GList *char -> None
  Recibe una lista cuyos elementos son estructuras de tipo Persona y realiza
  la salida de cada uno de los datos al archivo indicado.
*/
void salida_archivo(GList lista, char *nombreArchivo) {
  FILE *archivo = fopen(nombreArchivo, "w");
  assert(archivo != NULL);
  Persona *persona;
  GNodo *nodo = lista;

  for (; nodo->sig != lista; nodo = nodo->sig) {
    persona = (Persona*)nodo->dato;
    fprintf(archivo, "%s,%d,%s\r\n", persona->nombre ,persona->edad, persona->lugarDeNacimiento);
  }
  
  persona = (Persona*)nodo->dato;
  fprintf(archivo, "%s,%d,%s\r\n", persona->nombre ,persona->edad, persona->lugarDeNacimiento);

  fclose(archivo);
}

/*
  imprimir_datos(): GList -> None
  Función para testeo: Dada una lista imprime a consola los datos de todas las
  estructuras de tipo Persona y sus datos que se encuentren en la lista.
*/
void imprimir_datos(GList lista) {
  Persona *persona;

  for (GNodo *nodo = lista; !glist_vacia(nodo); nodo = nodo->sig) {
    persona = (Persona*)nodo->dato;
    printf("Nombre: %s, ", persona->nombre);
    printf("edad: %d ", persona->edad);
    printf("lugar de nac.: %s\n", persona->lugarDeNacimiento);
  } 
}

/*
  maradonizar(): void* -> None
  Dado un dato de tipo void*, se castea a un dato de tipo Persona*
  y se modifican los strings nombre y lugarDeNacimiento reemplazando todas
  sus vocales por la vocal 'e'.
*/
void maradonizar(void *dato) {
  Persona *persona = (Persona*)dato;
  char *nombre = persona->nombre;
  char *lugarNac = persona->lugarDeNacimiento;

  for (int i = 0; i < strlen(nombre); i++) {
    if (nombre[i] == 'a' || nombre[i] == 'i' || nombre[i] == 'o' || nombre[i] == 'u') {
      nombre[i] = 'e';
    } else if (nombre[i] == 'A' || nombre[i] == 'I' || nombre[i] == 'O' || nombre[i] == 'U') {
      nombre[i] = 'E';
    }
  }

  for (int i = 0; i < strlen(lugarNac); i++) {
    if (lugarNac[i] == 'a' || lugarNac[i] == 'i' || lugarNac[i] == 'o' || lugarNac[i] == 'u') {
      lugarNac[i] = 'e';
    } else if (lugarNac[i] == 'A' || lugarNac[i] == 'I' || lugarNac[i] == 'O' || lugarNac[i] == 'U') {
      lugarNac[i] = 'E';
    }
  }
}

/*
  karate_kid() void* -> None
  Dado un dato de tipo void*, se castea a un dato de tipo Persona*,
  y si el string nombre es igual a "Daniel" se modifica
  agregando un "-san" al final, quedando "Daniel-san".
*/
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

/*
  nombre_corto(): void* -> None
  Dado un dato de tipo void*, se castea a un dato de tipo Persona*,
  devuelve 1 si la longitud del string nombre es menor o igual a 6,
  en caso contrario devuelve 0.
*/
int nombre_corto(void *dato) {
  Persona *persona = (Persona*)dato;
  return strlen(persona->nombre) <= 6;
}

/*
  mercosur(): void* -> None
  Dado un dato de tipo void*, se castea a un dato de tipo Persona*,
  devuelve 1 si el lugar de nacimiento es uno de los países
  miembro del Mercosur, en caso contrario devuelve 0.
*/
int mercosur(void *dato) {
  int flag = 0;
  Persona *persona = (Persona*)dato;
  char *paises[] = {"Argentina", "Brasil", "Paraguay", "Uruguay"};
  
  for (int i = 0; i < 4 && flag == 0; i++) {
    if (strcmp(persona->lugarDeNacimiento, paises[i]) == 0) {
      flag = 1;
    }
  }

  return flag;
}

/*
  main(): None -> int
  Función principal del programa, 
*/
int main() {

  int cantPersonas = 0;
  
  GList listaPersonas = glist_crear();
  listaPersonas = lectura_censo(listaPersonas, "censo.txt", &cantPersonas);

  GList map1 = map(listaPersonas, karate_kid, copiar_persona);
  salida_archivo(map1, "map1.txt");
  glist_destruir(map1, destruir_persona);

  GList map2 = map(listaPersonas, maradonizar, copiar_persona);
  salida_archivo(map2, "map2.txt");
  glist_destruir(map2, destruir_persona);

  GList filter1 = filter(listaPersonas, nombre_corto, copiar_persona);
  salida_archivo(filter1,"filter1.txt");
  glist_destruir(filter1, destruir_persona);

  GList filter2 = filter(listaPersonas, mercosur, copiar_persona);
  salida_archivo(filter2, "filter2.txt");
  glist_destruir(filter2, destruir_persona);

  glist_destruir(listaPersonas, destruir_persona);
  
  return 0;
}