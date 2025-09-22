#include "../headers/player.h"

void playerCreate(tPlayer* player, int y, int x) {
    player->x = x;
    player->y = y;
    player->lives = 3;
}
