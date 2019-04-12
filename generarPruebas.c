#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "operacionesListas.h"


// char caracteres_especiales(char charARevisar) {
//   unsigned int valor = (unsigned int)charARevisar;
//   char *punteroChar = &charARevisar;
//   printf("%c %d\n", charARevisar, valor);
//   if (valor >= 32 && valor <= 126) {
//     return charARevisar;
//   } else {
    
//     switch(valor) {
//         case 160: // á -> a
//           return 97;
//         case 130: // é -> e
//           return 101;
//         case 161: // í -> i
//           return 105;
//         case 162: // ó -> o
//           return 111;
//         case 163: // ú -> u
//           return 117;
//         case 129: // ü -> u
//           return 177;
//         case 181: // Á -> A
//           return 65;
//         case 144: // É -> E
//           return 69;
//         case 214: // Í -> I
//           return 73;
//         case 224: // Ó -> O
//           return 79;
//         case 233: // Ú -> u
//           return 85;
//         case 164: // ñ -> n
//           return 110;
//         case 165: // Ñ -> n
//           return 78;  
//     }
//   }
//   } else if (memcmp(punteroChar, "é", 2)) {
//     printf("HOLA, LLEGAMOS ACA, char\n");
//   }
// }

GList lectura_archivo(GList lista, char *nombre_archivo, int *cantElementos) {
  FILE *archivo = fopen(nombre_archivo, "r");
  assert(archivo != NULL);

  char charBuff;
  char *strBuff = malloc(sizeof(char) * 50);

  for (int i = 0; (charBuff = fgetc(archivo)) != EOF;) {
    if (charBuff != '\n' && charBuff != '\r') {
      strBuff[i] = charBuff;
      i++;
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

void imprimirStr(void *str) {
  printf("%s\n", (char*)str);
}


int main() {
  srand(time(NULL));
  //size_t volumenDatos = rand() % 50000 + 2000;
  size_t volumenDatos = 50;
  GList listaNombres = glist_crear();
  GList listaPaises = glist_crear();
  int cantNombres = 0, cantPaises = 0;
  listaNombres = lectura_archivo(listaNombres, "nombres.txt", &cantNombres);
  listaPaises = lectura_archivo(listaPaises, "paises.txt", &cantPaises);

  FILE *prueba = fopen("censo.txt", "w");
  
  for (int i = 0; i < volumenDatos; i++) {
    int ubicNombre = rand() % cantNombres;
    GNodo *nodoNombre = listaNombres;
    for (int j = 0; nodoNombre != NULL && j != ubicNombre; nodoNombre = nodoNombre->sig, j++);
    int ubicPais = rand() % cantPaises;
    GNodo *nodoPais = listaPaises;
    for (int j = 0; nodoPais != NULL && j != ubicPais; nodoPais = nodoPais->sig, j++);
    int edad = rand() % 100 + 1;

    fprintf(prueba, "%s,%d,%s\r\n", (char*)nodoNombre->dato ,edad, (char*)nodoPais->dato);
  }
  
  glist_string_destruir(listaNombres);
  glist_string_destruir(listaPaises);

  fclose(prueba);
  
  return 0;  
}