#ifndef LIVES_H_INCLUDED
#define LIVES_H_INCLUDED

#include <string.h>

typedef struct 
{
    char id[10];
    int x;
    int y;
}tLives;

void Lives_create(tLives* pLives, int y, int x, const char* id);
int Lives_cmp(const void* elem1, const void* elem2);
int Lives_getX(tLives* pLives);
int Lives_getY(tLives* pLives);

#endif // LIVES_H_INCLUDED
