#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/bool.h"
#include "../headers/movement.h"

#define SIZE_NUMID 10
#define LOST_POINTS 150

#define FOLLOW 0
#define SEMI_RANDOM 1
#define RANDOM 2
#define CORNER 3

#define TOP_LEFT 4
#define TOP_RIGHT 5
#define BOT_LEFT 6
#define BOT_RIGHT 7

typedef struct 
{
    char id[10];
    int x;
    int y; 
    int vecX; 
    int vecY; 
    bool isAlive;
    int tipeMove;
}tGhost;

void Ghost_create(tGhost* pGhost, int y, int x, const char* id, int number);
int Ghost_cmp (const void* a, const void* b);
void Ghost_getId(const tGhost* pGhost, char* string);
void Ghost_changeId(tGhost* pGhost, const char* string);
void Ghost_numId(tGhost* pGhost, int num);
void Ghost_update(void* elem1, const void* elem2);
int Ghost_getX(const void* pGhost);
int Ghost_getY(const void* pGhost);
int Ghost_getDirX(const tGhost* pGhost);
int Ghost_getDirY(const tGhost* pGhost);
void Ghost_delete(tGhost* pGhost);
bool Ghost_isAlive(const void* pGhost);
void Ghost_movement(tGhost* pGhost, tMovement move);
int Ghost_getTipeMove(tGhost* pGhost);

#endif // GHOST_H_INCLUDED
