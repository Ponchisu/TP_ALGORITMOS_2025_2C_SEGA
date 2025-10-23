#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../headers/maze.h"
#include "../headers/bool.h"
#include "../headers/config.h"
#include "../headers/cola.h"
#include "../headers/soundManager.h"

#define SIZE_VECMUSIC 3

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    tMaze* maze;
    bool running;
    tCola colaTurn;
    tCola colaMovement;
    tVector vecMusic;
} tGame;

bool Game_create(tGame** game);
bool Game_init(tGame* game);
void Game_clean(tGame** game);
void Game_running(tGame* game);


#endif // GAME_H_INCLUDED