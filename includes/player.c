#include "../headers/player.h"

void playerCreate(tPlayer* player, int y, int x) {
    player->x = x;
    player->y = y;
    player->lives = 3;
}

int Player_getX(tPlayer* player) {
    return player->x;
}

int Player_getY(tPlayer* player) {
    return player->y;
}
