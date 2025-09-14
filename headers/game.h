#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

#include "../headers/laberinto.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    tlaberinto* laberinto;
    bool running;
} Game;

bool gameCreate(Game** game);
bool gameInit(Game* game, unsigned filas, unsigned columnas);
void gameClean(Game** game);
void gameRunning(Game* game);
void gameDraw(Game* game);


#endif // GAME_H_INCLUDED