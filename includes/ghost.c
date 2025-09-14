#include "../headers/ghost.h"

void ghostCreate(tGhost* ghost, int x, int y, const char* id) {
   strcpy(ghost->id, id);
   ghost->x = x;
   ghost->y = y;
}