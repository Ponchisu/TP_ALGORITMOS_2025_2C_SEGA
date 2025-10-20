#include "../headers/ghost.h"

void Ghost_create(tGhost* pGhost, int y, int x, const char* id) {
   strcpy(pGhost->id, id);
   pGhost->x = x;
   pGhost->y = y;
   pGhost->isAlive = true;
}

void Ghost_getId(tGhost* pGhost, char* string) {
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

void Ghost_Update(void* elem1, const void* elem2) {
    tGhost* ghostUpd = (tGhost*) elem1;
    const tGhost* pGhost =(tGhost*) elem2;

    ghostUpd->x = pGhost->x;
    ghostUpd->y = pGhost->y;
    ghostUpd->isAlive = pGhost->isAlive;
}

int Ghost_getX(tGhost* pGhost) {
    return pGhost->x;
}

int Ghost_getY(tGhost* pGhost) {
    return pGhost->y;
}

void Ghost_delete(tGhost* pGhost) {
    pGhost->isAlive = false;
}

bool Ghost_isAlive(tGhost* pGhost) {
    return pGhost->isAlive;
}

void Ghost_movement(tGhost* pGhost, char movement) {
    if(movement == 'D') {
        pGhost->y ++;
        return;
    }
    if(movement == 'U') {
        pGhost->y --;
        return;
    }
    if(movement == 'L') {
        pGhost->x --;
        return;
    }
    if(movement == 'R') {
        pGhost->x ++;
        return;
    }
}
