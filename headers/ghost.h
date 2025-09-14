#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include <string.h>

typedef struct 
{
    char id[10];
    int x;
    int y; 
}tGhost;

void ghostCreate(tGhost* ghost, int x, int y, const char* id);


#endif // GHOST_H_INCLUDED
