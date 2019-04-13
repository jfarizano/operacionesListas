#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "glist.h"


/*
  caracter_especial(): char -> int
  Recibe un caracter y devuelve 1 si esta dentro del rango 
  de los caracteres permitidos (según su valor en la 
  tabla ASCII), o 0 si no pertenece.
*/
int caracter_especial(char charARevisar) {
  return ((charARevisar >= 33 && charARevisar <= 64) || 
          (charARevisar >= 91 && charARevisar <= 96) || 
          (charARevisar >= 123 && charARevisar <= 127));
}


/*
  lectura_archivo(): GList char* int* -> GList
  Toma una lista y el nombre de un archivo de texto que contenga los elementos
  a agregar siendo estos elementos una cadena de texo por cada
  línea del archivo, y devuelve una lista cuyos elementos son estas cadenas.
  Los caracteres especiales son eliminados
  por el uso de la funcion caracter_especial.
  El parametro *cantElementos es obtenido de la funcion main, 
  o donde se aplique, y se usa como contador de elementos de
  la lista.
*/
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
/*
  generar_archivo_personas(): size_t GList int GList int -> None
  Toma el valor volumenDatos para definir la cantidad de datos a crear,
  y genera un archivo en la que cada línea es una entrada de la forma nombre,
  obtenido aleatoriamente de listaNombres, la edad obtenida en un rango 
  de 1 a 100, y la nacionalidad, obtenida aleatoriamente de
  listaPaises. 
  */
void generar_archivo_personas(size_t volumenDatos, GList listaNombres, 
                              int cantNombres, GList listaPaises, 
                              int cantPaises) {

  FILE *archivo = fopen("censo.txt", "w");
  
  for (int i = 0; i < volumenDatos; i++) {
    int ubicNombre = rand() % cantNombres;
    GNodo *nodoNombre = listaNombres;
    for (int j = 0; nodoNombre != NULL && j != ubicNombre; 
          nodoNombre = nodoNombre->sig, j++);
    int ubicPais = rand() % cantPaises;
    GNodo *nodoPais = listaPaises;
    for (int j = 0; nodoPais != NULL && j != ubicPais; 
          nodoPais = nodoPais->sig, j++);
    int edad = rand() % 100 + 1;

    fprintf(archivo, "%s,%d,%s\r\n", (char*)nodoNombre->dato , 
            edad, (char*)nodoPais->dato);
  }

  fclose(archivo);
}

/*
  main(): None -> int
  Función principal del programa, inicializa el generador de números aleatorios
  utilizando una semilla basada en el tiempo epoch y elige aleatoriamente la
  cantidad de datos a generar (en el rango [2000, 52000]). 
  Se crean y se rellenan las listas que contienen a las cadenas de texto
  que se encuentran en los archivos "nombres.txt" y "paises.txt".
  Se realiza la generación de datos aleatorios y su salida
  al archivo "censo.txt" mediante la función generar_archivo_personas
  y una vez concluido se libera la memoria utilizada, finalizando el programa.
*/
int main() {
  srand(time(NULL));
  size_t volumenDatos = rand() % 50000 + 2000;

  GList listaNombres = glist_crear();
  GList listaPaises = glist_crear();
  int cantNombres = 0, cantPaises = 0;

  listaNombres = lectura_archivo(listaNombres, "nombres.txt", &cantNombres);
  listaPaises = lectura_archivo(listaPaises, "paises.txt", &cantPaises);

  generar_archivo_personas(volumenDatos, listaNombres, cantNombres, 
                            listaPaises, cantPaises);
  
  glist_destruir(listaNombres, free);
  glist_destruir(listaPaises, free);

  return 0;  
}
