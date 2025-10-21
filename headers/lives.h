#ifndef LIVES_H_INCLUDED
#define LIVES_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include "../headers/bool.h"

#define SIZE_NUMID 10

typedef struct 
{
    char id[10];
    int x;
    int y;
    bool isAlive;
}tLives;

void Lives_create(tLives* pLives, int y, int x, const char* id);
int Lives_cmp(const void* elem1, const void* elem2);
void Lives_numId(tLives* pLives, int num);
void Lives_update(void* elem1, const void* elem2);
int Lives_getX(const void* elem);
int Lives_getY(const void* elem);
void Lives_delete(tLives* pLives);
bool Lives_isAlive(const void* elem);

#endif // LIVES_H_INCLUDED
