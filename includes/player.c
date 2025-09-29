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

void Player_movement(tPlayer* player, char movement) {
    if(movement == 'D') {
        player->y ++;
        return;
    }
    if(movement == 'A') {
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
