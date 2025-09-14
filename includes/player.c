#include "../headers/player.h"

void playerCreate(tPlayer* player, int x, int y, const char* id) {
    strcpy(player->id, id);
    player->x = x;
    player->y = y;
}
