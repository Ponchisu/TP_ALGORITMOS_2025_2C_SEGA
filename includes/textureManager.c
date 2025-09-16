#include "../headers/textureManager.h"

SDL_Texture* textureManagerLoad(const char* fileName, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load(fileName);

    if(pTempSurface == NULL) {
        return NULL;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    return pTexture;
}