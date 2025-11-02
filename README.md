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
