#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../headers/bool.h"
#include "../headers/vector.h"
#include "../headers/textureManager.h"
#include "../headers/game.h"
#include "../headers/client.h"

#define SIZE_VECTEXMEN 13
#define SIZE_VECBUTTON 4
#define SIZE_VECRANK 10
#define SIZE_NAME 10

#define SIZE_PRANK 100

#define WIDTH_MENU 600
#define HEIGTH_MENU 800

#define X_INSERTNAME 119
#define Y_INSERTNAME 440

#define Y_RANK 346
#define X_RANK 50
#define DISTANCE_RANK 40

#define W_BSTART 206
#define W_BRANK 321
#define W_BEXIT 199
#define W_BBACK 116

#define H_BSTART 64
#define H_BRANK 56
#define H_BEXIT 64
#define H_BBACK 44

#define X_BSTART 189
#define X_BRANK 128
#define X_BEXIT 196
#define X_BBACK 24

#define Y_BSTART 409
#define Y_BRANK 514
#define Y_BEXIT 611
#define Y_BBACK 24


#define WIDTH_TCONECT 144
#define WIDTH_FCONECT 192

#define ISLETTER(a) (((a) >= 'a' && (a) <= 'z') || ((a) >= 'A' && (a) <= 'Z'))
#define ISNUMBER(a) ((a) >= '0' && (a) <= '9')

typedef struct
{
    tGame* game;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SOCKET socket;
    bool conect;
    int insertName;
    bool insertNameH;
    char name[SIZE_NAME];
    SDL_Event event;
    bool createRank;
    tVector vecRank;
    tVector vecTex;
    tVector vecButton;
    bool running;
    bool runningName;
    bool playGame;
    bool showRanking;
    Mix_Music* music;
    Mix_Chunk* click;
    TTF_Font* fontName;
    TTF_Font* font;
}tMenu;

typedef struct {
    char id[SIZE_ID];
    SDL_Rect button;
    bool hover;
}tButton;

bool Menu_create(tMenu** pMenu);
void Menu_clean(tMenu** pMenu);
bool Menu_running(tMenu* pMenu);

bool Button_load(tVector* pVec, const char* id, int x, int y, int w, int h);
bool Button_search(tVector* pVec, const char* id, tButton* button);
bool Button_isHover(tButton* button);
void Button_trueHover(tButton* button);
void Button_falseHover(tButton* button);
int Button_getX(tButton* button);
int Button_getY(tButton* button);
int Button_getW(tButton* button);
int Button_getH(tButton* button);



#endif // MENU_H_INCLUDED
