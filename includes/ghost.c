#include "../headers/ghost.h"

void Ghost_create(tGhost* pGhost, int y, int x, const char* id, int number) {
   strcpy(pGhost->id, id);
   pGhost->x = x;
   pGhost->y = y;
   pGhost->isAlive = true;
   pGhost->vecX = 0;
   pGhost->vecY = 0;
   
   if(number == 0) {
    pGhost->tipeMove = FOLLOW;
   } else {
    pGhost->tipeMove = (rand() % 5);
   }
   printf("%s %d\n", id, pGhost->tipeMove);
}

void Ghost_getId(const tGhost* pGhost, char* string) {
    strcpy(string, pGhost->id);
}

void Ghost_changeId(tGhost* pGhost, const char* string) {
    strcpy(pGhost->id, string);
}

void Ghost_numId(tGhost* pGhost, int num) {
    char idNum[SIZE_NUMID];
    strcpy(pGhost->id, "ghost");
    sprintf(idNum, "%d", num);
    strcat(pGhost->id, idNum);
}

int Ghost_cmp (const void* a, const void* b) {
    tGhost* a1 = (tGhost*)(a);
    tGhost* b1 = (tGhost*)(b);
    return strcmp(a1->id, b1->id);
}

void Ghost_update(void* elem1, const void* elem2) {
    tGhost* ghostUpd = (tGhost*) elem1;
    const tGhost* pGhost =(tGhost*) elem2;

    ghostUpd->x = pGhost->x;
    ghostUpd->y = pGhost->y;
    ghostUpd->vecX = pGhost->vecX;
    ghostUpd->vecY = pGhost->vecY;
    ghostUpd->isAlive = pGhost->isAlive;
}

int Ghost_getX(const void* elem) {
    const tGhost* pGhost = elem;
    return pGhost->x;
}

int Ghost_getY(const void* elem) {
    const tGhost* pGhost = elem;
    return pGhost->y;
}

int Ghost_getDirX(const tGhost* pGhost) {
    return pGhost->vecX;
}

int Ghost_getDirY(const tGhost* pGhost) {
    return pGhost->vecY;
}

void Ghost_delete(tGhost* pGhost) {
    pGhost->isAlive = false;
}

bool Ghost_isAlive(const void* elem) {
    const tGhost* pGhost = elem;
    return pGhost->isAlive;
}

void Ghost_movement(tGhost* pGhost, tMovement move) {
    pGhost->x += move.vecX;
    pGhost->y += move.vecY;
    pGhost->vecX = move.vecX;
    pGhost->vecY = move.vecY;
}

int Ghost_getTipeMove(tGhost* pGhost) {
    return pGhost->tipeMove;
}
