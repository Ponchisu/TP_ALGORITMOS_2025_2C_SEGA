#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../headers/bool.h"
#include "../headers/vector.h"

#define SIZE_ID 20
#define WIDTH 32
#define HEIGTH 32

typedef struct{
    SDL_Texture* texture;
    char id[SIZE_ID];
}tTexture;

bool TextureManager_load(Vector* vec, const char* fileName, const char* id, SDL_Renderer* pRenderer);
void TextureManager_Draw(Vector* vec, const char* id, int y, int x, SDL_Renderer* pRenderer);

#endif // TEXTUREMANAGER_H_INCLUDED
