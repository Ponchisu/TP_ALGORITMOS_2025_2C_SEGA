#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* textureManagerLoad(const char* fileName, SDL_Renderer* pRenderer);

#endif // TEXTUREMANAGER_H_INCLUDED