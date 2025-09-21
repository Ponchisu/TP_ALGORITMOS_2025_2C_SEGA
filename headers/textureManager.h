#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../headers/bool.h"
#include "../headers/vector.h"

#define TAM_ID 20
#define ANCHO 32
#define ALTO 32

typedef struct{
    SDL_Texture* texture;
    char id[TAM_ID];
}tTexture;

bool TextureManager_load(Vector* vec, const char* fileName, const char* id, SDL_Renderer* pRenderer);
void TextureManagerDraw(Vector* vec, const char* id, int y, int x, SDL_Renderer* pRenderer);

#endif // TEXTUREMANAGER_H_INCLUDED
