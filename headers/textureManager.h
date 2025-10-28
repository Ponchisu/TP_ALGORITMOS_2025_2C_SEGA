#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../headers/bool.h"
#include "../headers/vector.h"

#define SIZE_ID 20
#define WIDTH 32
#define WIDTH_NUMBERS 16
#define WIDTH_VICTORY 98
#define WIDTH_LOST 116
#define HEIGTH 32

typedef struct{
    SDL_Texture* texture;
    char id[SIZE_ID];
}tTexture;

bool TextureManager_load(tVector* pVec, const char* fileName, const char* id, SDL_Renderer* pRenderer);
bool TextureManager_loadFont(tVector* pVec, char* text, const char* id, TTF_Font* font, SDL_Color color, SDL_Renderer* pRenderer);
void TextureManager_draw(tVector* pVec, const char* id, int y, int x, int width, int heigth, SDL_Renderer* pRenderer);
void TextureManager_clean(tVector* pVec);

#endif // TEXTUREMANAGER_H_INCLUDED
