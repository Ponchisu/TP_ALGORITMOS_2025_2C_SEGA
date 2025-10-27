#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>

#include "../headers/bool.h"
#include "../headers/vector.h"
#include "../headers/textureManager.h"

#define SIZE_VECTEXMEN 11
#define SIZE_NAME 12

#define WIDTH_MENU 600
#define HEIGTH_MENU 800

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    tVector vecTex;
    bool running;
    bool runningName;
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
    TTF_Font* font;
    SDL_Texture* insName;
    SDL_Rect rectInsName;
}tMenu;

bool Menu_create(tMenu** pMenu, SDL_Window* window, SDL_Renderer* renderer);
void Menu_clean(tMenu** pMenu);
bool Menu_running(tMenu* pMenu, char* pName);

#endif // MENU_H_INCLUDED
