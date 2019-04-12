#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "glist.h"



// caracter_especial(): char -> int
//
// toma un caracter y devuelve 1 si esta dentro del rango
// de los caracteres permitidos (segun su valor en la 
// tabla ascii), o 0 si no pertenece

int caracter_especial(char charARevisar) {
  return ((charARevisar >= 33 && charARevisar <= 64) || 
          (charARevisar >= 91 && charARevisar <= 96) || 
          (charARevisar >= 123 && charARevisar <= 127));
}

// lectura_archivo(): GList, char, int -> GList
//
// Toma una lista (GList lista) y un archivo de texto que 
// contenga los elementos a agregar, y devuelve una lista
// con los elementos del archivo. Los caracteres especiales
// son eliminados por el uso de la funcion caracter_especial.
// El parametro *cantElementos es obtenido de la funcion main, 
// o donde se aplique, y se usa como contador de elementos de
// la lista.

GList lectura_archivo(GList lista, char *nombreArchivo, int *cantElementos) {
  FILE *archivo = fopen(nombreArchivo, "r");
  assert(archivo != NULL);

  char charBuff;
  char *strBuff = malloc(sizeof(char) * 50);

  for (int i = 0; (charBuff = fgetc(archivo)) != EOF;) {
    if (charBuff != '\n' && charBuff != '\r') {
      if (!caracter_especial(charBuff)) {
        strBuff[i] = charBuff;
        i++;
      }
    } else {
      strBuff[i] = '\0';
      i = 0;
      (*cantElementos)++;
      char *str = malloc(sizeof(char) * (strlen(strBuff) + 1));
      strcpy(str, strBuff);
      lista = glist_agregar_final(lista, str);
      charBuff = fgetc(archivo);
    }
  }
  
  fclose(archivo);
  free(strBuff);

  return lista;
}

// generar_archivo_persona(): size_t GList int GList int -> void
//
//




void generar_archivo_personas(size_t volumenDatos, GList listaNombres, int cantNombres, GList listaPaises, int cantPaises) {
  FILE *archivo = fopen("censo.txt", "w");
  
  for (int i = 0; i < volumenDatos; i++) {
    int ubicNombre = rand() % cantNombres;
    GNodo *nodoNombre = listaNombres;
    for (int j = 0; nodoNombre != NULL && j != ubicNombre; nodoNombre = nodoNombre->sig, j++);
    int ubicPais = rand() % cantPaises;
    GNodo *nodoPais = listaPaises;
    for (int j = 0; nodoPais != NULL && j != ubicPais; nodoPais = nodoPais->sig, j++);
    int edad = rand() % 100 + 1;

    fprintf(archivo, "%s,%d,%s\r\n", (char*)nodoNombre->dato ,edad, (char*)nodoPais->dato);
  }

  fclose(archivo);
}

int main() {
  srand(time(NULL));
  size_t volumenDatos = rand() % 50000 + 2000;

  GList listaNombres = glist_crear();
  GList listaPaises = glist_crear();
  int cantNombres = 0, cantPaises = 0;

  listaNombres = lectura_archivo(listaNombres, "nombres.txt", &cantNombres);
  listaPaises = lectura_archivo(listaPaises, "paises.txt", &cantPaises);

  generar_archivo_personas(volumenDatos, listaNombres, cantNombres, listaPaises, cantPaises);
  
  glist_destruir(listaNombres, free);
  glist_destruir(listaPaises, free);

  return 0;  
}
