#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdio.h>

typedef struct {
    int xStart;
    int yStart;
    int x;
    int y;
    int lives;
}tPlayer;

void playerCreate(tPlayer* pPlayer, int y, int x, int numLives) ;
void playerUpdate();
int Player_getX(const void* elem);
int Player_getY(const void* elem);
int Player_getLives(const void* elem);
void Player_lostLives(tPlayer* pPlayer);
void Player_addLives(tPlayer* pPlayer);
void Player_resetPos(tPlayer* pPlayer);
void Player_movement(tPlayer* pPlayer, char movement);

#endif // PLAYER_H_INCLUDED
