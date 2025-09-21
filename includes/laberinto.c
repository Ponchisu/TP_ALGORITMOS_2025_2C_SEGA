#include "../headers/laberinto.h"

bool laberintoCreate(tlaberinto** laberinto, int filas, int columnas, SDL_Renderer* render) {
    //tGhost tGhost;

    *laberinto = (tlaberinto*)malloc(sizeof(tlaberinto));
    if(*laberinto == NULL) {
        fprintf(stderr, "Error al crear laberinto");
        return false;
    }

    (*laberinto)->filas = filas;
    (*laberinto)->columnas = columnas;
    (*laberinto)->render = render;

    (*laberinto)->laberinto = (char**)matrizCrear(filas, columnas, sizeof(char));
    if((*laberinto)->laberinto == NULL) {
        fprintf(stderr, "Error al crear matriz de laberinto");
        return false;
    }

    if(!matrizCargarDeArchTxt((*laberinto)->laberinto, columnas)) {
        fprintf(stderr, "Error al cargar matriz de laberinto");
        return false;
    }


    if(!Vector_create(&(*laberinto)->vecTex, sizeof(tTexture))) {
        fprintf(stderr, "Error al crear vector");
        return false;
    }

    if(!TextureManager_load(&(*laberinto)->vecTex, "assets/entrada32x32.png", "entrada", render)) {
        fprintf(stderr, "Error al cargar imagen Entrada");
        return false;
    }

    if(!TextureManager_load(&(*laberinto)->vecTex, "assets/salida32x32.png", "salida", render)) {
        fprintf(stderr, "Error al cargar imagen Salida");
        return false;
    }

    if(!TextureManager_load(&(*laberinto)->vecTex, "assets/personaje32.png", "player", render)) {
        fprintf(stderr, "Error al cargar imagen Player");
        return false;
    }

    if(!TextureManager_load(&(*laberinto)->vecTex, "assets/suelo32x32.png", "suelo", render)) {
        fprintf(stderr, "Error al cargar imagen Suelo");
        return false;
    }

    if(!TextureManager_load(&(*laberinto)->vecTex, "assets/pared32x32.png", "pared", render)) {
        fprintf(stderr, "Error al cargar imagen Pared");
        return false;
    }

    if(!TextureManager_load(&(*laberinto)->vecTex, "assets/fantasma32.png", "ghost", render)) {
        fprintf(stderr, "Error al cargar imagen Fantasma");
        return false;
    }

    for (int i = 0; i < (*laberinto)->filas; i++) {
        for (int j = 0; j < (*laberinto)->columnas; j++) {
            // if ((*laberinto)->laberinto[i][j] == 'F') {
            //     ghostCreate(&ghost, i, j, "ghost");
            //     listaPonerAlFinal(&(*laberinto)->lista, &ghost, sizeof(tGhost));
            // }
            if ((*laberinto)->laberinto[i][j] == 'E') {
                playerCreate(&(*laberinto)->player, i, j);
            }
        }
    }

    matrizMostrar((*laberinto)->laberinto, filas, columnas);

    return true;
}

void laberintoClean(tlaberinto** laberinto, int filas) {
    matrizEliminar((void**)(*laberinto)->laberinto, filas);

    Vector_destroy(&(*laberinto)->vecTex);

    free(*laberinto);
}

void laberintoDraw(tlaberinto* laberinto) {
    for (int fila = 0; fila < laberinto->filas; fila++) {
        for (int col = 0; col < laberinto->columnas; col++) {
            if (laberinto->laberinto[fila][col] == '#') {
                TextureManagerDraw(&laberinto->vecTex, "pared", fila * ALTO, col * ANCHO, laberinto->render);
            }
            if (laberinto->laberinto[fila][col] == '.') {
                TextureManagerDraw(&laberinto->vecTex, "suelo", fila * ALTO, col * ANCHO, laberinto->render);
            }
            if (laberinto->laberinto[fila][col] == 'E') {
                TextureManagerDraw(&laberinto->vecTex, "entrada", fila * ALTO, col * ANCHO, laberinto->render);
            }
            if (laberinto->laberinto[fila][col] == 'S') {
                TextureManagerDraw(&laberinto->vecTex, "salida", fila * ALTO, col * ANCHO, laberinto->render);
            }
            if (laberinto->laberinto[fila][col] == 'F') {
                TextureManagerDraw(&laberinto->vecTex, "suelo", fila * ALTO, col * ANCHO, laberinto->render);
                TextureManagerDraw(&laberinto->vecTex, "ghost", fila * ALTO, col * ANCHO, laberinto->render);
            }

            TextureManagerDraw(&laberinto->vecTex, "player", laberinto->player.y * ALTO,  laberinto->player.x * ANCHO, laberinto->render);
        }
    }
}
