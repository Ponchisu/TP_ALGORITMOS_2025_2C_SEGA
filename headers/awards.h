#ifndef AWARDS_H_INCLUDED
#define AWARDS_H_INCLUDED

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
}tAwards;

void Awards_create(tAwards* pAwards, int y, int x, const char* id);
int Awards_cmp(const void* elem1, const void* elem2);
void Awards_numIde(tAwards* pAward, int num);
void Awards_update(void* elem1, const void* elem2);
int Awards_getX(const void* elem);
int Awards_getY(const void* elem);
void Awards_delete(tAwards* pAwards);
bool Awards_isAlive(const void* elem);

#endif // AWARDS_H_INCLUDED
