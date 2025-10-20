#ifndef AWARDS_H_INCLUDED
#define AWARDS_H_INCLUDED

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
}tAwards;

void Awards_create(tAwards* pAwards, int y, int x, const char* id);
int Awards_cmp(const void* elem1, const void* elem2);
void Awards_numIde(tAwards* pAward, int num);
void Awards_update(void* elem1, const void* elem2);
int Awards_getX(tAwards* pAwards);
int Awards_getY(tAwards* pAwards);
void Awards_delete(tAwards* pAwards);
bool Awards_isAlive(tAwards* pAwards);

#endif // AWARDS_H_INCLUDED
