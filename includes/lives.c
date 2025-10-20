#include "../headers/lives.h"

void Lives_create(tLives* pLives, int y, int x, const char* id) {
    strcpy(pLives->id, id);
    pLives->y = y;
    pLives->x = x;
}

int Lives_cmp(const void* elem1, const void* elem2) {
    const tLives* live1 = elem1;
    const tLives* live2 = elem2;

    return strcmp(live1->id, live2->id);
}

int Lives_getX(tLives* pLives) {
    return pLives->x;
}

int Lives_getY(tLives* pLives) {
    return pLives->y;
}