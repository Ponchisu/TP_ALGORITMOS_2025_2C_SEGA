#include "../headers/ghost.h"

void Ghost_create(tGhost* ghost, int x, int y, const char* id) {
   strcpy(ghost->id, id);
   ghost->x = x;
   ghost->y = y;
}