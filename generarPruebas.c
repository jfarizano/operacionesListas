#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "operacionesListas.h"

char **leer_archivo(char *nombreArchivo, int *tamagno) {
  FILE *archivo = fopen(nombreArchivo, "r");
  assert(archivo != NULL);
  int cantLineas = 0, len;
  char charBuff;

  while ((charBuff = fgetc(archivo)) != EOF) {
    if (charBuff == '\n') {
      cantLineas++;
    }  
  }
  
  rewind(archivo);

  char **arrayStr = malloc(sizeof(char*) * cantLineas);
  char *strBuff = malloc(sizeof(char) * 50);

  // Copiar strings a arrayw

  fclose(archivo);
  *tamagno = cantLineas;

  return arrayStr;
}



int main(){
  srand(time(NULL));
  size_t volumenDatos = rand();
  int tamao=0;
  char **arrayNombres = leer_archivo("paises.txt", &tamao);

  printf("%d\n", tamao);

  /*
  for (int i = 0; i < tamao; i++){
    printf("%s\n", arrayNombres[i]);
  }
  */

  return 0;  
}