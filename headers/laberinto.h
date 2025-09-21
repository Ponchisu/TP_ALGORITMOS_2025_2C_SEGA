#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../headers/bool.h"
#include "../headers/matriz.h"
#include "../headers/textureManager.h"
#include "../headers/tlista.h"
#include "../headers/player.h"
#include "../headers/ghost.h"
#include "../headers/vector.h"

typedef struct 
{
    SDL_Renderer* render;
    char** laberinto;
    int filas;
    int columnas;
    tPlayer player;
    Vector vecTex;
}tlaberinto;

bool laberintoCreate(tlaberinto** laberinto, int filas, int columnas, SDL_Renderer* render);
void laberintoClean(tlaberinto** laberinto, int filas);
void laberintoDraw(tlaberinto* laberinto);


#endif // LABERINTO_H_INCLUDED
