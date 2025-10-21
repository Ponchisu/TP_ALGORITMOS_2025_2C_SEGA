#ifndef MARGIN_H_INCLUDED
#define MARGIN_H_INCLUDED

#include "../headers/vector.h"
#include "../headers/bool.h"
#include "../headers/textureManager.h"

#define MARGIN_TOP 32
#define SIZE_VECTEXMARGIN 13
#define LIVES_SIZE 3
#define POINTS_SIZE 6

typedef struct
{
    tVector vecTex;
    char lives[LIVES_SIZE];
    char points[POINTS_SIZE];
    int width;
}tMargin;

bool Margin_create(tMargin* pMargin, int lives, int width, SDL_Renderer* renderer);
void Margin_updateLives(tMargin* pMargin, int lives);
void Margin_updatePoints(tMargin* pMargin, int points);
void Margin_draw(tMargin* pMargin, SDL_Renderer* renderer);
void Margin_clean(tMargin* pMargin);

#endif // MARGIN_H_INCLUDED
