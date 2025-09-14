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

#define ANCHO 32
#define ALTO 32

typedef struct 
{
    SDL_Renderer* render;
    SDL_Texture* textureSuelo;
    SDL_Texture* texturePared;
    SDL_Texture* textureEntrada;
    SDL_Texture* textureSalida;
    SDL_Texture* texturePlayer;
    SDL_Texture* textureFantasma;
    char** laberinto;
    int filas;
    int columnas;
    tlista lista;
}tlaberinto;

bool laberintoCreate(tlaberinto** laberinto, int filas, int columnas, SDL_Renderer* render);
void laberintoClean(tlaberinto** laberinto, int filas);
void laberintoDraw(tlaberinto* laberinto);


#endif // LABERINTO_H_INCLUDED
