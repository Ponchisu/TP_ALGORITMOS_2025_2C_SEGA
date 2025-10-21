#include "../headers/player.h"

void playerCreate(tPlayer* pPlayer, int y, int x, int numLives) {
    pPlayer->x = x;
    pPlayer->y = y;
    pPlayer->xStart = x;
    pPlayer->yStart = y;
    pPlayer->lives = numLives;
}

int Player_getX(const void* elem) {
    const tPlayer* pPlayer = elem;
    return pPlayer->x;
}

int Player_getY(const void* elem) {
    const tPlayer* pPlayer = elem;
    return pPlayer->y;
}

int Player_getLives(const void* elem) {
    const tPlayer* pPlayer = elem;
    return pPlayer->lives;
}

void Player_lostLives(tPlayer* pPlayer) {
    pPlayer->lives --;
}

void Player_addLives(tPlayer* pPlayer) {
    pPlayer->lives ++;
}

void Player_resetPos(tPlayer* pPlayer) {
    pPlayer->x = pPlayer->xStart;
    pPlayer->y = pPlayer->yStart;
}

void Player_movement(tPlayer* pPlayer, char movement) {
    if(movement == 'D') {
        pPlayer->y ++;
        return;
    }
    if(movement == 'U') {
        pPlayer->y --;
        return;
    }
    if(movement == 'L') {
        pPlayer->x --;
        return;
    }
    if(movement == 'R') {
        pPlayer->x ++;
        return;
    }
}
