#include "../headers/margin.h"

bool Margin_create(tMargin* pMargin, int lives, int width, SDL_Renderer* renderer) {
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
    if(!TextureManager_load(&pMargin->vecTex, "assets/award.png", "award", renderer)) {
        fprintf(stderr, "Error al cargar imagen award\n");
        return false;
    }

    sprintf(pMargin->lives, "%02d", lives);
    strcpy(pMargin->points, "00000");
    pMargin->width = width;

    return true;
}

void Margin_updateLives(tMargin* pMargin, int lives) {
    sprintf(pMargin->lives, "%02d", lives);
}

void Margin_updatePoints(tMargin* pMargin, int points) {
    sprintf(pMargin->points, "%05d", points);
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

    i = pMargin->width * WIDTH - WIDTH;
    TextureManager_Draw(&pMargin->vecTex, "award", 0,  i, WIDTH, HEIGTH, renderer);
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
    Vector_clean(&pMargin->vecTex);
}
