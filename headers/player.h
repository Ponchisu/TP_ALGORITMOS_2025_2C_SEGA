#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string.h>

typedef struct {
    char id[10];
    int x;
    int y;
    int vidas;
}tPlayer;

void playerCreate(tPlayer* player, int x, int y, const char* id);
void playerUpdate();

#endif // PLAYER_H_INCLUDED
