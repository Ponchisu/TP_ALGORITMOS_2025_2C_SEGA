#include "../headers/cross.h"

void Cross_create(tCross* pCross, int y, int x, const char* id) {
    strcpy(pCross->id, id);
    pCross->y = y;
    pCross->x = x;
    pCross->isAlive = true;
}

int Cross_cmp(const void* elem1, const void* elem2) {
    const tCross* cross1 = elem1;
    const tCross* cross2 = elem2;
    return strcmp(cross1->id, cross2->id);
}

void Cross_numIde(tCross* pCross, int num) {
    char idNum[SIZE_NUMID];
    strcpy(pCross->id, "cross");
    sprintf(idNum, "%d", num);
    strcat(pCross->id, idNum);
}

void Cross_update(void* elem1, const void* elem2) {
    tCross* pCross1 = elem1;
    const tCross* pCross2 = elem2;
    pCross1->isAlive = pCross2->isAlive;
}

int Cross_getX(const void* elem) {
    const tCross* pCross = elem;
    return pCross->x;
}

int Cross_getY(const void* elem) {
    const tCross* pCross = elem;
    return pCross->y;
}

void Cross_delete(tCross* pCross) {
    pCross->isAlive = false;
}

bool Cross_isAlive(const void* elem) {
    const tCross* pCross = elem;
    return pCross->isAlive;
}
