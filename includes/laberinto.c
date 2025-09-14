#include "../headers/laberinto.h"

bool laberintoCreate(tlaberinto** laberinto, unsigned filas, unsigned columnas, SDL_Renderer* render) {
    *laberinto = (tlaberinto*)malloc(sizeof(tlaberinto));
    if(*laberinto == NULL) {
        fprintf(stderr, "Error al crear laberinto");
        return false;
    }

    (*laberinto)->filas = filas;
    (*laberinto)->columnas = columnas;

    (*laberinto)->alto = ALTO;
    (*laberinto)->ancho = ANCHO;
    (*laberinto)->render = render;

    (*laberinto)->laberinto = (char**)matrizCrear(filas, columnas, sizeof(char));
    if((*laberinto)->laberinto == NULL) {
        fprintf(stderr, "Error al crear matriz de laberinto");
        free(*laberinto);
        return false;
    }

    if(!matrizCargarDeArchTxt((*laberinto)->laberinto, columnas)) {
        fprintf(stderr, "Error al cargar matriz de laberinto");
        free(*laberinto);
        matrizEliminar((void**)&(*laberinto)->laberinto, filas);
        return false;
    }

    SDL_Surface* surfSuelo = IMG_Load("assets/suelo.png");
    if(surfSuelo == NULL) {
        fprintf(stderr, "Error al cargar suelo: %s", SDL_GetError());
        free(*laberinto);
        matrizEliminar((void**)&(*laberinto)->laberinto, filas);
        return false;
    }

    SDL_Surface* surfPared = IMG_Load("assets/pared.png");
    if(surfPared == NULL) {
        fprintf(stderr, "Error al cargar suelo: %s", SDL_GetError());
        free(*laberinto);
        matrizEliminar((void**)&(*laberinto)->laberinto, filas);
        SDL_FreeSurface(surfSuelo);
        return false;
    }

    SDL_Surface* surfEntrada = IMG_Load("assets/entrada.png");
    if(surfEntrada == NULL) {
        fprintf(stderr, "Error al cargar suelo: %s", SDL_GetError());
        free(*laberinto);
        matrizEliminar((void**)&(*laberinto)->laberinto, filas);
        SDL_FreeSurface(surfSuelo);
        SDL_FreeSurface(surfPared);
        return false;
    }

    SDL_Surface* surfSalida = IMG_Load("assets/salida.png");
    if(surfSalida == NULL) {
        fprintf(stderr, "Error al cargar suelo: %s", SDL_GetError());
        free(*laberinto);
        matrizEliminar((void**)&(*laberinto)->laberinto, filas);
        SDL_FreeSurface(surfSuelo);
        SDL_FreeSurface(surfPared);
        SDL_FreeSurface(surfEntrada);
        return false;
    }

    (*laberinto)->texturePared = SDL_CreateTextureFromSurface(render, surfPared);
    (*laberinto)->textureSuelo = SDL_CreateTextureFromSurface(render, surfSuelo);
    (*laberinto)->textureEntrada = SDL_CreateTextureFromSurface(render, surfEntrada);
    (*laberinto)->textureSalida = SDL_CreateTextureFromSurface(render, surfSalida);

    SDL_FreeSurface(surfSuelo);
    SDL_FreeSurface(surfPared);
    SDL_FreeSurface(surfEntrada);
    SDL_FreeSurface(surfSalida);
    matrizMostrar((*laberinto)->laberinto, filas, columnas);

    return true;
}

void laberintoClean(tlaberinto** laberinto, unsigned filas) {
    matrizEliminar((void**)&(*laberinto)->laberinto, filas);
    SDL_DestroyTexture((*laberinto)->texturePared);
    SDL_DestroyTexture((*laberinto)->textureSuelo);
    SDL_DestroyTexture((*laberinto)->textureSalida);
    SDL_DestroyTexture((*laberinto)->textureEntrada);
    free(*laberinto);
}

void laberintoDraw(tlaberinto* laberinto) {
    for (int fila = 0; fila < laberinto->filas; fila++) {
        for (int col = 0; col < laberinto->columnas; col++) {
                SDL_Rect rect = {col * ANCHO, fila * ALTO, ANCHO, ALTO};

            if (laberinto->laberinto[fila][col] == '#') {
                SDL_RenderCopy(laberinto->render, laberinto->texturePared, NULL, &rect);
            }
            if (laberinto->laberinto[fila][col] == '.') {
                SDL_RenderCopy(laberinto->render, laberinto->textureSuelo, NULL, &rect);
            }
            if (laberinto->laberinto[fila][col] == 'E') {
                SDL_RenderCopy(laberinto->render, laberinto->textureEntrada, NULL, &rect);
            }
            if (laberinto->laberinto[fila][col] == 'S') {
                SDL_RenderCopy(laberinto->render, laberinto->textureSalida, NULL, &rect);
            }
        }
    }
}
