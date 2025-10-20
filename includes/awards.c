#include "../headers/awards.h"

void Awards_create(tAwards* pAwards, int y, int x, const char* id) {
    strcpy(pAwards->id, id);
    pAwards->y = y;
    pAwards->x = x;
}

int Awards_cmp(const void* elem1, const void* elem2) {
    const tAwards* award1 = elem1;
    const tAwards* award2 = elem2;

    return strcmp(award1->id, award2->id);
}

int Awards_getX(tAwards* pAwards) {
    return pAwards->x;
}

int Awards_getY(tAwards* pAwards) {
    return pAwards->y;
}