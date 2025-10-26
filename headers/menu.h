#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <stdio.h>

#include "../headers/bool.h"
#include "../headers/vector.h"
#include "../headers/textureManager.h"

#define SIZE_VECTEXMEN 10

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    tVector vecTex;
    bool running;
    bool playGame;
    bool showRanking;
    Mix_Music* music;
    Mix_Chunk* click;
    SDL_Rect buttonPlay;
    bool buttonPlayH;
    SDL_Rect buttonRanking;
    bool buttonRankingH;
    SDL_Rect buttonQuit;
    bool buttonQuitH;
    SDL_Rect buttonExit;
    bool buttonExitH;
}tMenu;

bool Menu_create(tMenu** pMenu, SDL_Window* window, SDL_Renderer* renderer);
void Menu_clean(tMenu** pMenu);
bool Menu_running(tMenu* pMenu);

#endif // MENU_H_INCLUDED
