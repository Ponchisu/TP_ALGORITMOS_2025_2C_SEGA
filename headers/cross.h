#ifndef CROSS_H_INCLUDED
#define CROSS_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include "../headers/bool.h"

#define SIZE_NUMID 10
#define GET_KILLPOINTS 200

typedef struct 
{
    char id[10];
    int x;
    int y;
    bool isAlive;
}tCross;

void Cross_create(tCross* pCross, int y, int x, const char* id);
int Cross_cmp(const void* elem1, const void* elem2);
void Cross_numIde(tCross* pCross, int num);
void Cross_update(void* elem1, const void* elem2);
int Cross_getX(const void* elem);
int Cross_getY(const void* elem);
void Cross_delete(tCross* pCross);
bool Cross_isAlive(const void* elem);

#endif // CROSS_H_INCLUDED
