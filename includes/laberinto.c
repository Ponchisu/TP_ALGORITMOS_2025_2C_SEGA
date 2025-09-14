#include "../headers/laberinto.h"

bool laberintoCreate(tlaberinto** laberinto, int filas, int columnas, SDL_Renderer* render) {
    tPlayer player;
    tGhost ghost;

    *laberinto = (tlaberinto*)malloc(sizeof(tlaberinto));
    if(*laberinto == NULL) {
        fprintf(stderr, "Error al crear laberinto");
        return false;
    }

    (*laberinto)->filas = filas;
    (*laberinto)->columnas = columnas;
    (*laberinto)->render = render;

    (*laberinto)->texturePared = NULL;
    (*laberinto)->textureSalida = NULL;
    (*laberinto)->textureSuelo = NULL;
    (*laberinto)->textureEntrada = NULL;

    (*laberinto)->laberinto = (char**)matrizCrear(filas, columnas, sizeof(char));
    if((*laberinto)->laberinto == NULL) {
        fprintf(stderr, "Error al crear matriz de laberinto");
        return false;
    }

    if(!matrizCargarDeArchTxt((*laberinto)->laberinto, columnas)) {
        fprintf(stderr, "Error al cargar matriz de laberinto");
        return false;
    }

    listaCrear(&(*laberinto)->lista);
    for (int i = 0; i < (*laberinto)->filas; i++) {
        for (int j = 0; j < (*laberinto)->columnas; j++) {
            if ((*laberinto)->laberinto[i][j] == 'F') {
                ghostCreate(&ghost, i, j, "ghost");
                listaPonerAlFinal(&(*laberinto)->lista, &ghost, sizeof(tGhost));
            }
            if ((*laberinto)->laberinto[i][j] == 'E') {
                playerCreate(&player, i + 1, j, "player");
                listaPonerAlFinal(&(*laberinto)->lista, &player, sizeof(tPlayer));
            }
        }
    }

    (*laberinto)->textureSuelo = textureManagerLoad("assets/suelo32x32.png", render);
    if((*laberinto)->textureSuelo == NULL) {
        return false;
    }

    (*laberinto)->texturePared = textureManagerLoad("assets/pared32x32.png", render);
    if((*laberinto)->texturePared == NULL) {
        return false;
    }

    (*laberinto)->textureEntrada = textureManagerLoad("assets/entrada32x32.png", render);
    if((*laberinto)->textureEntrada == NULL) {
        return false;
    }

    (*laberinto)->textureSalida = textureManagerLoad("assets/salida32x32.png", render);
    if((*laberinto)->textureSalida == NULL) {
        return false;
    }

    (*laberinto)->texturePlayer = textureManagerLoad("assets/personaje32.png", render);
    if((*laberinto)->texturePlayer == NULL) {
        return false;
    }

    (*laberinto)->textureFantasma = textureManagerLoad("assets/fantasma32.png", render);
    if((*laberinto)->textureFantasma == NULL) {
        return false;
    }

    matrizMostrar((*laberinto)->laberinto, filas, columnas);

    return true;
}

void laberintoClean(tlaberinto** laberinto, int filas) {
    matrizEliminar((void**)(*laberinto)->laberinto, filas);

    listaVaciar(&(*laberinto)->lista);

    if((*laberinto)->texturePared != NULL) {
        SDL_DestroyTexture((*laberinto)->texturePared);
    }
    if((*laberinto)->textureSuelo != NULL) {
        SDL_DestroyTexture((*laberinto)->textureSuelo);
    }
    if((*laberinto)->textureEntrada != NULL) {
            SDL_DestroyTexture((*laberinto)->textureEntrada);
    }
    if((*laberinto)->textureSalida != NULL) {
        SDL_DestroyTexture((*laberinto)->textureSalida);
    }
    if((*laberinto)->texturePlayer != NULL) {
        SDL_DestroyTexture((*laberinto)->texturePlayer);
    }
    if((*laberinto)->textureFantasma != NULL) {
        SDL_DestroyTexture((*laberinto)->textureFantasma);
    }
    free(*laberinto);
}

void laberintoDraw(tlaberinto* laberinto) {
    for (int fila = 0; fila < laberinto->filas; fila++) {
        for (int col = 0; col < laberinto->columnas; col++) {
                SDL_Rect rect = {col * ANCHO, fila * ALTO + 50, ANCHO, ALTO};

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
            if (laberinto->laberinto[fila][col] == 'F') {
                SDL_RenderCopy(laberinto->render, laberinto->textureSuelo, NULL, &rect);
                SDL_RenderCopy(laberinto->render, laberinto->textureFantasma, NULL, &rect);
            }
            if (laberinto->laberinto[fila][col] == 'P') {
                SDL_RenderCopy(laberinto->render, laberinto->textureSuelo, NULL, &rect);
                SDL_RenderCopy(laberinto->render, laberinto->texturePlayer, NULL, &rect);
            }
        }
    }
}