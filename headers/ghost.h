#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include <string.h>

typedef struct 
{
    char id[10];
    int x;
    int y; 
    int direction;
}tGhost;

void Ghost_create(tGhost* ghost, int y, int x, const char* id);
int Ghost_cmp (const void* a, const void* b);
void Ghost_Update(void* ghostUpd, const void* ghost);
int Ghost_getX(tGhost* ghost);
int Ghost_getY(tGhost* ghost);
void Ghost_movement(tGhost* ghost, char movement);

#endif // GHOST_H_INCLUDED
