#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "operacionesListas.h"


typedef struct _Elemento(){
  char *id;
  int ubicacion;
}Elemento;

typedef struct _LElementos(){
  struct _Elemento *elemento;
  struct _LElemento *sig;
  int cantidadTotal;
}ListElem;

ListElem Crear(){
  return NULL;
}
int ListElem_vacia(ListElem lista) {
  return lista == NULL;
}

ListElem agregar_final(ListElem lista, char *dato){
  int len = strlen(dato);

  ListElem *nuevoNodo = malloc(sizeof(Elemento));

  nuevoNodo->id = malloc(sizeof(char)*(len + 1));

  strcpy(nuevoNodo->id,dato);

  nuevoNodo->sig = NULL;

  if (ListElem_vacia(lista))
    return nuevoNodo;

  ListElem nodo;
  for(;!ListElem_vacia(nodo->sig); nodo = nodo->sig);

  nodo->sig = nuevoNodo;

  return lista;
}

void lectura_archivo(ListElem lista, char *nombre_archivo){
  FILE *archivo = fopen(nombre_archivo, "r");
  assert(archivo != NULL);
  char *strBuff = malloc(sizeof(char) * 50);
  int posicion = 0;
  while(fscanf(nombre_archivo) != EOF){
    fgets(strBuff, 50, archivo);
    agregar_final(lista, strBuff);
    ListaElem->elemento->ubicacion = posicion;
    posicion++;    
    ListElem->cantidadTotal = posicion;
  }
  fclose(archivo);
  free(strBuff);
}









int main(){
  srand(time(NULL));
  size_t volumenDatos = rand() % 5001 + 2000;
  ListElem listaNombres = Crear();
  ListElem listaPaises = Crear();
  FILE *prueba = fopen("censo.txt", "a");
  lectura_archivo(listaNombres, "nombres.txt");
  lectura_archivo(listaPaises, "paises.txt");

  for (int i = 0; i < volumenDatos; i++){
    int ubicNombre = rand() % listaNombres->cantidadTotal;
    for(;ubicNombre != listaNombres->elemento->ubicacion; listaNombres->sig);
    int ubicPais = rand() % listaPaises->cantidadTotal;
    for(;ubicPais != listaPaises->elemento->ubicacion; listaPaises->sig);
    int edad = rand() % 100 + 1;
    //ver como agregar eficientemente los datos al archivo
  }
  fclose(prueba);
  
  return 0;  
}