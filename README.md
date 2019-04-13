# Implementación de map y filter en una lista genérica
Trabajo práctico 1 - Estructuras de Datos y Algoritmos

Realizado por:
Bernal, Pablo
Farizano, Juan Ignacio

### Requisitos para correr el programa:

Los archivos **glist.c**, **glist.h**, **generarPruebas.c** y **main.c** se deberán encontrar en
el directorio.
Los archivo "nombres.txt" y "paises.txt" son necesarios para el funcionamiento de **generarPruebas**
El archivo "censo.txt" es necesario para el funcionamiento de **main**

### Sobre los archivos de texto "nombres.txt" y "paises.txt":
En estos archivos cada cadena de texto debe estar separada por un salto de línea la una de la otra.

### Sobre los caracteres especiales:
Durante la lectura de los archivos "nombres.txt" y "paises.txt", los caracters que no pertenezcan al alfabeto se 
omitirán.

### Sobre el archivo de texto "censo.txt":
En este archivo se encuentran los datos de las personas generadas aleatoriamente por **generarPruebas**.
En cada línea se encuentran los datos de una persona cumpliendo el siguiente formato (sin espacios entre cada dato, solo comas):
nombre,edad,lugarDeNacimiento.

### Sobre los archivo de texto "map1.txt", "map2.txt", "filter1.txt", "filter2.txt":
Estos archivos de texto son la salida del programa **main**, no es necesario que se encuentren en el directorio,
ya que al correr el programa estos se crean automáticamente en caso de que no lo estén.

### Como compilar y correr los programas:

- Para correr **generarPruebas** y **main** automáticamente se debe correr el script otorgado escribiendo en consola:
"./correrGeneradorYMain.sh"

- Para cada programa individual se encuentra un script en el directorio que permite compilar y correrlo de manera automática.
En consola:
"./compilarYCorrerGenerador.sh" para compilar y correr *generarPruebas*
"./compilarYCorrerMain.sh" para compilar y correr *main*

- Para compilar manualmente **generarPruebas** se debe ingresar en consola:
"generarPruebas.c glist.c -o generarPruebas.o"
y posteriormente correrlo con el comando ./generarPruebas.o

- Para compilar manualmente **main** se debe ingresar en consola:
"main.c glist.c -o main.o"
y posteriormente correrlo con el comando ./main.o

- Para medir el tiempo de ejecución de **generarPruebas** y **main** simultaneamente, se debe escribir en consola:
"./cronometrar.sh"
