#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string.h>

typedef struct {
    int x;
    int y;
    int lives;
}tPlayer;

void playerCreate(tPlayer* player, int y, int x);
void playerUpdate();
int Player_getX(tPlayer* player);
int Player_getY(tPlayer* player);

#endif // PLAYER_H_INCLUDED
