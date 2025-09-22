#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../headers/maze.h"
#include "../headers/bool.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    tMaze* maze;
    bool running;
} tGame;

bool Game_create(tGame** game);
bool Game_init(tGame* game, int rows, int columns);
void Game_clean(tGame** game);
void Game_running(tGame* game);


#endif // GAME_H_INCLUDED