#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "../headers/maze.h"
#include "../headers/bool.h"
#include "../headers/config.h"
#include "../headers/cola.h"
#include "../headers/soundManager.h"
#include "../headers/client.h"

#define SIZE_VECMUSIC 3
#define SIZE_RESPONSE 1024

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    SOCKET* socket;
    tMaze* maze;
    bool running;
    bool exit;
    tCola colaTurn;
    tCola colaMovement;
    tVector vecMusic;
} tGame;

bool Game_create(tGame** game, SDL_Window* window, SDL_Renderer * render, SOCKET* socket);
void Game_clean(tGame** game);
int Game_running(tGame* game, bool conect, char* name);


#endif // GAME_H_INCLUDED