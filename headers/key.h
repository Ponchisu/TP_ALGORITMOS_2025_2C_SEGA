#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include "../headers/bool.h"

#define SIZE_NUMID 10
#define GET_POINTS 250

typedef struct 
{
    char id[10];
    int x;
    int y;
    bool isAlive;
}tKeys;

void Key_create(tKeys* pKey, int y, int x, const char* id);
int Key_cmp(const void* elem1, const void* elem2);
void Key_numIde(tKeys* pKey, int num);
void Key_update(void* elem1, const void* elem2);
int Key_getX(const void* elem);
int Key_getY(const void* elem);
void Key_delete(tKeys* pKey);
bool Key_isAlive(const void* elem);

#endif // KEY_H_INCLUDED
