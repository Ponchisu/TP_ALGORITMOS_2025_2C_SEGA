#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdio.h>

typedef struct {
    int x;
    int y;
    int lives;
}tPlayer;

void playerCreate(tPlayer* player, int y, int x);
void playerUpdate();
int Player_getX(tPlayer* player);
int Player_getY(tPlayer* player);
void Player_movement(tPlayer* player, char movement);

#endif // PLAYER_H_INCLUDED
