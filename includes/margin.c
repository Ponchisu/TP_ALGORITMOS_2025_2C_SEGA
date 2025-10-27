#include "../headers/margin.h"

bool Margin_create(tMargin* pMargin, int lives, int width, int key, SDL_Renderer* renderer) {
    if(Vector_create(&pMargin->vecTex, sizeof(tTexture), SIZE_VECTEXMARGIN) == false) {
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/0.png", "0", renderer)) {
        fprintf(stderr, "Error al cargar imagen 0\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/1.png", "1", renderer)) {
        fprintf(stderr, "Error al cargar imagen 1\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/2.png", "2", renderer)) {
        fprintf(stderr, "Error al cargar imagen 2\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/3.png", "3", renderer)) {
        fprintf(stderr, "Error al cargar imagen 3\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/4.png", "4", renderer)) {
        fprintf(stderr, "Error al cargar imagen 4\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/5.png", "5", renderer)) {
        fprintf(stderr, "Error al cargar imagen 5\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/6.png", "6", renderer)) {
        fprintf(stderr, "Error al cargar imagen 6\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/7.png", "7", renderer)) {
        fprintf(stderr, "Error al cargar imagen 7\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/8.png", "8", renderer)) {
        fprintf(stderr, "Error al cargar imagen 7\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/9.png", "9", renderer)) {
        fprintf(stderr, "Error al cargar imagen 9\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/xHeart.png", "xHeart", renderer)) {
        fprintf(stderr, "Error al cargar imagen xHeart\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/margin.png", "margin", renderer)) {
        fprintf(stderr, "Error al cargar imagen margin\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/points.png", "points", renderer)) {
        fprintf(stderr, "Error al cargar imagen points\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/marginL.png", "marginL", renderer)) {
        fprintf(stderr, "Error al cargar imagen marginL\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/marginR.png", "marginR", renderer)) {
        fprintf(stderr, "Error al cargar imagen marginR\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/win.png", "win", renderer)) {
        fprintf(stderr, "Error al cargar imagen win\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/winH.png", "winH", renderer)) {
        fprintf(stderr, "Error al cargar imagen winH\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/lost.png", "lost", renderer)) {
        fprintf(stderr, "Error al cargar imagen lost\n");
        return false;
    }
    if(!TextureManager_load(&pMargin->vecTex, "assets/lostH.png", "lostH", renderer)) {
        fprintf(stderr, "Error al cargar imagen lostH\n");
        return false;
    }

    if(!TextureManager_load(&pMargin->vecTex, "assets/key.png", "key", renderer)) {
        fprintf(stderr, "Error al cargar imagen lostH\n");
        return false;
    }

    sprintf(pMargin->lives, "%02d", lives);
    sprintf(pMargin->keys, "%d", key);
    strcpy(pMargin->points, "00000");
    pMargin->width = width;

    pMargin->lostH = false;
    pMargin->winH = false;

    return true;
}

void Margin_updateLives(tMargin* pMargin, int lives) {
    sprintf(pMargin->lives, "%02d", lives);
}

void Margin_updatePoints(tMargin* pMargin, int points) {
    sprintf(pMargin->points, "%05d", points);
}

void Margin_updateKey(tMargin* pMargin, int key) {
    sprintf(pMargin->keys, "%d", key);
}

void Margin_draw(tMargin* pMargin, SDL_Renderer* renderer) {
    int i;
    char lives[LIVES_SIZE];
    char points[POINTS_SIZE];
    char* number;
    strcpy(lives, pMargin->lives);
    strcpy(points, pMargin->points);
    for (i = 0; i < pMargin->width; i++) {
        TextureManager_Draw(&pMargin->vecTex, "margin", 0,  i * WIDTH, WIDTH, HEIGTH, renderer);
    }
    number = strchr(lives,  '\0');
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, WIDTH + WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH, renderer);
    *number = '\0';
    TextureManager_Draw(&pMargin->vecTex, lives, 0, WIDTH, WIDTH_NUMBERS, HEIGTH, renderer);
    TextureManager_Draw(&pMargin->vecTex, "xHeart", 0,  2 * WIDTH, WIDTH, HEIGTH, renderer);

    TextureManager_Draw(&pMargin->vecTex, "marginL", 0, 0, WIDTH, HEIGTH, renderer);

    i = pMargin->width / 2 * WIDTH - WIDTH;
    strcpy(lives, pMargin->keys);

    TextureManager_Draw(&pMargin->vecTex, lives, 0, i + WIDTH_NUMBERS, WIDTH_NUMBERS, HEIGTH, renderer);
    TextureManager_Draw(&pMargin->vecTex, "key", 0, i + WIDTH, WIDTH, HEIGTH, renderer);


    i = pMargin->width * WIDTH - WIDTH;
    TextureManager_Draw(&pMargin->vecTex, "marginR", 0,  i, WIDTH, HEIGTH, renderer);
    TextureManager_Draw(&pMargin->vecTex, "points", 0,  i -= WIDTH, WIDTH, HEIGTH, renderer);
    number = strchr(points,  '\0');
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
}

void Margin_drawWin(tMargin* pMargin, SDL_Renderer* renderer) {
    int i;
    char points[POINTS_SIZE];
    char* number;
    strcpy(points, pMargin->points);
    for (i = 0; i < pMargin->width; i++) {
        TextureManager_Draw(&pMargin->vecTex, "margin", 0,  i * WIDTH, WIDTH, HEIGTH, renderer);
    }

    if(pMargin->winH == false) {
        TextureManager_Draw(&pMargin->vecTex, "win", 0, WIDTH, WIDTH_VICTORY, HEIGTH, renderer);
        pMargin->winH = true;
    } else {
        TextureManager_Draw(&pMargin->vecTex, "winH", 0, WIDTH, WIDTH_VICTORY, HEIGTH, renderer);
        pMargin->winH = false;
    }
    TextureManager_Draw(&pMargin->vecTex, "marginL", 0, 0, WIDTH, HEIGTH, renderer);

    i = pMargin->width * WIDTH - WIDTH;
    TextureManager_Draw(&pMargin->vecTex, "marginR", 0,  i, WIDTH, HEIGTH, renderer);
    TextureManager_Draw(&pMargin->vecTex, "points", 0,  i -= WIDTH, WIDTH, HEIGTH, renderer);
    number = strchr(points,  '\0');
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
}

void Margin_drawLost(tMargin* pMargin, SDL_Renderer* renderer) {
    int i;
    char points[POINTS_SIZE];
    char* number;
    strcpy(points, pMargin->points);
    for (i = 0; i < pMargin->width; i++) {
        TextureManager_Draw(&pMargin->vecTex, "margin", 0,  i * WIDTH, WIDTH, HEIGTH, renderer);
    }

    if(pMargin->lostH == false) {
        TextureManager_Draw(&pMargin->vecTex, "lost", 0, WIDTH, WIDTH_LOST, HEIGTH, renderer);
        pMargin->lostH = true;
    } else {
        TextureManager_Draw(&pMargin->vecTex, "lostH", 0, WIDTH, WIDTH_LOST, HEIGTH, renderer);
        pMargin->lostH = false;
    }
    TextureManager_Draw(&pMargin->vecTex, "marginL", 0, 0, WIDTH, HEIGTH, renderer);

    i = pMargin->width * WIDTH - WIDTH;
    TextureManager_Draw(&pMargin->vecTex, "marginR", 0,  i, WIDTH, HEIGTH, renderer);
    TextureManager_Draw(&pMargin->vecTex, "points", 0,  i -= WIDTH, WIDTH, HEIGTH, renderer);
    number = strchr(points,  '\0');
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
    *number = '\0';
    number --;
    TextureManager_Draw(&pMargin->vecTex, number, 0, i -= WIDTH_NUMBERS,  WIDTH_NUMBERS, HEIGTH,renderer);
}

void Margin_clean(tMargin* pMargin) {
    if(Vector_empty(&pMargin->vecTex) == false) {
        TextureManager_clean(&pMargin->vecTex);
    }
    Vector_clean(&pMargin->vecTex);
}
