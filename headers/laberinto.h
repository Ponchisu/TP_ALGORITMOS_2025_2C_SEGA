#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "../headers/matriz.h"

#define ANCHO 16
#define ALTO 16

typedef struct 
{
    SDL_Renderer* render;
    SDL_Texture* textureSuelo;
    SDL_Texture* texturePared;
    SDL_Texture* textureEntrada;
    SDL_Texture* textureSalida;
    char** laberinto;
    unsigned filas;
    unsigned columnas;
    unsigned alto;
    unsigned ancho;
}tlaberinto;

bool laberintoCreate(tlaberinto** laberinto, unsigned filas, unsigned columnas, SDL_Renderer* render);
void laberintoClean(tlaberinto** laberinto, unsigned filas);
void laberintoDraw(tlaberinto* laberinto);


#endif // LABERINTO_H_INCLUDED
