#include "../headers/player.h"

void playerCreate(tPlayer* player, int y, int x, int numLives) {
    player->x = x;
    player->y = y;
    player->xStart = x;
    player->yStart = y;
    player->lives = numLives;
}

int Player_getX(tPlayer* player) {
    return player->x;
}

int Player_getY(tPlayer* player) {
    return player->y;
}

void Player_movement(tPlayer* player, char movement) {
    if(movement == 'D') {
        player->y ++;
        return;
    }
    if(movement == 'U') {
        player->y --;
        return;
    }
    if(movement == 'L') {
        player->x --;
        return;
    }
    if(movement == 'R') {
        player->x ++;
        return;
    }
}
