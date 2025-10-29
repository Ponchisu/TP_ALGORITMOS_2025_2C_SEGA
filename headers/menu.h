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
#include "../headers/game.h"

#define SIZE_VECTEXMEN 12
#define SIZE_VECBUTTON 4
#define SIZE_NAME 12

#define WIDTH_MENU 600
#define HEIGTH_MENU 800

#define X_INSRTNAME 88
#define Y_INSRTNAME 210
#define WIDTH_INSRTNAME 256
#define HEIGTH_INSRTNAME 24


#define ISLETTER(a) (((a) >= 'a' && (a) <= 'z') || ((a) >= 'A' && (a) <= 'Z'))
#define ISNUMBER(a) ((a) >= '0' && (a) <= '9')

typedef struct
{
    tGame* game;
    SDL_Window* window;
    SDL_Renderer* renderer;
    char name[SIZE_NAME];
    SDL_Event event;
    tVector vecTex;
    tVector vecButton;
    bool running;
    bool runningName;
    bool playGame;
    bool showRanking;
    Mix_Music* music;
    Mix_Chunk* click;
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
