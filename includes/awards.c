#include "../headers/awards.h"

void Awards_create(tAwards* pAwards, int y, int x, const char* id) {
    strcpy(pAwards->id, id);
    pAwards->y = y;
    pAwards->x = x;
    pAwards->isAlive = true;
}

int Awards_cmp(const void* elem1, const void* elem2) {
    const tAwards* award1 = elem1;
    const tAwards* award2 = elem2;
    return strcmp(award1->id, award2->id);
}

void Awards_numIde(tAwards* pAward, int num) {
    char idNum[SIZE_NUMID];
    strcpy(pAward->id, "award");
    sprintf(idNum, "%d", num);
    strcat(pAward->id, idNum);
}

void Awards_update(void* elem1, const void* elem2) {
    tAwards* pAward1 = elem1;
    const tAwards* pAward2 = elem2;
    pAward1->isAlive = pAward2->isAlive;
}

int Awards_getX(const void* elem) {
    const tAwards* pAwards = elem;
    return pAwards->x;
}

int Awards_getY(const void* elem) {
    const tAwards* pAwards = elem;
    return pAwards->y;
}

void Awards_delete(tAwards* pAwards) {
    pAwards->isAlive = false;
}

bool Awards_isAlive(const void* elem) {
    const tAwards* pAwards = elem;
    return pAwards->isAlive;
}