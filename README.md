# Laberintos y Fantasmas
## Como Instalar
Este Trabajo Practico lo realizamos utilizando librerias de SDL2. A continuacion se detalla como descargarlas e instalarlas:

### **SDL2**
> Libreria principal de SDL
  1. Buscar en el [repositorio de SDL](https://github.com/libsdl-org/SDL/releases) la version `2.32.10`.
  2. Descargar `SDL2-devel-2.32.10-mingw.zip`.
  3. Descomprimir el .zip.
  4. Dentro de la carpeta descomprimida buscar la carpeta `x86_64-w64-mingw32` y renombrarla a `SDL2`.
  5. Mover la carpeta SDL2 a la carpeta donde se encuentra el juego.

### **SDL2_image**
> Libreria de SDL para el manejo de imagenes
  1. Buscar en el [repositorio de SDL_image](https://github.com/libsdl-org/SDL_image/releases?page=2) la version `2.8.6`.
  2. Descargar `SDL2_image-devel-2.8.6-mingw.zip`.
  3. Descomprimir el .zip.
  4. Dentro de la carpeta descomprimida buscar la carpeta `x86_64-w64-mingw32` y renombrarla a `SDL2_image`.
  5. Mover la carpeta SDL2 a la carpeta donde se encuentra el juego.

### **SDL2_mixer**
> Libreria de SDL para el manejo de sonido
  1. Buscar en el [repositorio de SDL_mixer](https://github.com/libsdl-org/SDL_mixer/releases) la version `2.8.1`.
  2. Descargar `SDL2_mixer-devel-2.8.1-mingw.zip`.
  3. Descomprimir el .zip.
  4. Dentro de la carpeta descomprimida buscar la carpeta `x86_64-w64-mingw32` y renombrarla a `SDL2_mixer`.
  5. Mover la carpeta SDL2 a la carpeta donde se encuentra el juego.

### **SDL2_ttf**
> Libreria de SDL para el manejo de texto
  1. Buscar en el [repositorio de SDL_ttf](https://github.com/libsdl-org/SDL_ttf/releases) la version `2.24.0`.
  2. Descargar `SDL2_ttf-devel-2.24.0-mingw.zip`.
  3. Descomprimir el .zip.
  4. Dentro de la carpeta descomprimida buscar la carpeta `x86_64-w64-mingw32` y renombrarla a `SDL2_ttf`.
  5. Mover la carpeta SDL2 a la carpeta donde se encuentra el juego.

### Archivos .dll
  1. Dentro de las carpetas `SDL2`, `SDL2_image`, `SDL2_mixer` y `SDL2_ttf` buscar la carpeta `bin`.
  2. Copiar los archivos `SDL2.dll`, `SDL2_image.dll`, `SDL2_mixer.dll` y `SDL2_ttf.dll` respectivamente de cada carpeta.
  3. Pegar los archivos a la carpeta `bin\debug` o `bin\release`.

### Linkear librerias
Dentro del proyecto `Database.cbp` y `TP_ALGORIMOS_2025_2C_SEGA.cbp` es necesario enlazar a ciertas librerias para su correcto funcionamiento.

> Ignorar este paso en caso de ya estar linkeado

En `Database.cbp`:
1. Click derecho a `DataBase` y luego seleccionar `Build options...`.
2. Seleccionar la solapa `Linker settings` y luego seleccionar en la parte de abajo `Add`.
3. Agregar:
   ```
   ws2_32
   ```

En `TP_ALGORIMOS_2025_2C_SEGA.cbp`:
1. Click derecho a `TP_ALGORIMOS_2025_2C_SEGA` y luego seleccionar `Build options...`.
2. Seleccionar la solapa `Linker settings` y luego seleccionar en la parte de abajo `Add`.
3. Agregar:
   ```
   SDL2
   SDL2main
   SDL2_image
   SDL2_mixer
   SDL2_ttf
   ws2_32
   ```
> Agregar uno por uno

4. Luego seleccionar la solapa `Search directories`, luego `Compiler` y agregar en `Add`:
   ```
   SDL2\include
   SDL2\include\SDL2
   SDL2_image\include
   SDL2_mixer\include
   SDL2_ttf\include
   ```
> Agregar uno por uno
   
5. Luego en la misma solapa `Search directorios` seleccionar `Linker` y agregar en `Add`:
   ```
   SDL2\lib
   SDL2_image\lib
   SDL2_mixer\lib
   SDL2_ttf\lib
   ```
> Agregar uno por uno

## Archivo config
Para el funcionamiento del juego es necesario crear un archivo `config.txt`, el mismo se creara en la carpeta del proyecto y contendra los parametros con los cuales se generaran los laberintos.
> Ejemplo de archivo `config.txt`
```
rows: 15
columns: 15
lives_initial: 3
number_of_ghost: 3
number_of_award: 10
lives_additional: 4
```
|Parametro|Descripcion|
|---|---|
|rows|Cantidad de filas de laberinto|
|columns|Cantidad de columnas de laberinto|
|lives_initial|Cantidad de vidas del jugador iniciales|
|number_of_ghost|Cantidad de fantasmas iniciales|
|number_of_award|Cantidad de premios generados en laberinto|
|lives_additional|Cantidad de vidas adicionales generadas en el laberinto|

## Recomendaciones
Para una mejor experiencia se recomienda:

1. ***Primero ejecutar la Base de Datos.***

2. ***En el archivo `config.txt`, los parametros `rows` y `columns` se recomienda que sean numeros impares.***
