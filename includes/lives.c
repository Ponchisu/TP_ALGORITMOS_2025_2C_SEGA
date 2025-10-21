#include "../headers/lives.h"

void Lives_create(tLives* pLives, int y, int x, const char* id) {
    strcpy(pLives->id, id);
    pLives->y = y;
    pLives->x = x;
    pLives->isAlive = true;
}

int Lives_cmp(const void* elem1, const void* elem2) {
    const tLives* live1 = elem1;
    const tLives* live2 = elem2;
    return strcmp(live1->id, live2->id);
}

void Lives_numId(tLives* pLives, int num) {
    char idNum[SIZE_NUMID];
    strcpy(pLives->id, "live");
    sprintf(idNum, "%d", num);
    strcat(pLives->id, idNum);
}

void Lives_update(void* elem1, const void* elem2) {
    tLives* pLive1 = elem1;
    const tLives* pLive2 = elem2;
    pLive1->isAlive = pLive2->isAlive;
}

int Lives_getX(const void* elem) {
    const tLives* pLives = elem;
    return pLives->x;
}

int Lives_getY(const void* elem) {
    const tLives* pLives = elem;
    return pLives->y;
}

void Lives_delete(tLives* pLives) {
    pLives->isAlive = false;
}

bool Lives_isAlive(const void* elem) {
    const tLives* pLives = elem;
    return pLives->isAlive;
}
