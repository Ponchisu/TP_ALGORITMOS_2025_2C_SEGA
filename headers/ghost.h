#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include <string.h>
#include "../headers/bool.h"

typedef struct 
{
    char id[10];
    int x;
    int y; 
    int direction;
    bool isAlive;
}tGhost;

void Ghost_create(tGhost* pGhost, int y, int x, const char* id);
int Ghost_cmp (const void* a, const void* b);
void Ghost_Update(void* ghostUpd, const void* pGhost);
int Ghost_getX(tGhost* pGhost);
int Ghost_getY(tGhost* pGhost);
void Ghost_delete(tGhost* pGhost);
bool Ghost_isAlive(tGhost* pGhost);
void Ghost_movement(tGhost* pGhost, char movement);

#endif // GHOST_H_INCLUDED
