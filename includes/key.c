#include "../headers/key.h"

void Key_create(tKeys* pKey, int y, int x, const char* id) {
    strcpy(pKey->id, id);
    pKey->y = y;
    pKey->x = x;
    pKey->isAlive = true;
}

int Key_cmp(const void* elem1, const void* elem2) {
    const tKeys* key1 = elem1;
    const tKeys* key2 = elem2;
    return strcmp(key1->id, key2->id);
}

void Key_numIde(tKeys* pKey, int num) {
    char idNum[SIZE_NUMID];
    strcpy(pKey->id, "key");
    sprintf(idNum, "%d", num);
    strcat(pKey->id, idNum);
}

void Key_update(void* elem1, const void* elem2) {
    tKeys* pKey1 = elem1;
    const tKeys* pKey2 = elem2;
    pKey1->isAlive = pKey2->isAlive;
}

int Key_getX(const void* elem) {
    const tKeys* pKey = elem;
    return pKey->x;
}

int Key_getY(const void* elem) {
    const tKeys* pKey = elem;
    return pKey->y;
}

void Key_delete(tKeys* pKey) {
    pKey->isAlive = false;
}

bool Key_isAlive(const void* elem) {
    const tKeys* pKey = elem;
    return pKey->isAlive;
}