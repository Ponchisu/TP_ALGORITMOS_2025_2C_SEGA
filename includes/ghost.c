#include "../headers/ghost.h"

void Ghost_create(tGhost* ghost, int y, int x, const char* id) {
   strcpy(ghost->id, id);
   ghost->x = x;
   ghost->y = y;
}

int Ghost_cmp (const void* a, const void* b) {
    tGhost* a1 = (tGhost*)(a);
    tGhost* b1 = (tGhost*)(b);

    return strcmp(a1->id, b1->id);
}

void Ghost_Update(void* elem1, const void* elem2) {
    tGhost* ghostUpd = (tGhost*) elem1;
    const tGhost* ghost =(tGhost*) elem2;

    ghostUpd->x = ghost->x;
    ghostUpd->y = ghost->y;
}

int Ghost_getX(tGhost* ghost) {
    return ghost->x;
}

int Ghost_getY(tGhost* ghost) {
    return ghost->y;
}

void Ghost_movement(tGhost* ghost, char movement) {
    if(movement == 'D') {
        ghost->y ++;
        return;
    }
    if(movement == 'U') {
        ghost->y --;
        return;
    }
    if(movement == 'L') {
        ghost->x --;
        return;
    }
    if(movement == 'R') {
        ghost->x ++;
        return;
    }
}
