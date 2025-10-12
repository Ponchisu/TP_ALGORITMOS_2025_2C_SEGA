#include "../headers/textureManager.h"
int _TextureManager_compararTex (const void* a, const void* b);

bool TextureManager_load(tVector* tVec, const char* fileName, const char* id, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load(fileName);
    SDL_Texture* pTexture;

    if(pTempSurface == NULL){
        return false;
    }

    pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);


    if(pTexture != NULL){
        tTexture tex;
        tex.texture = pTexture;
        strncpy(tex.id, id, SIZE_ID - 1);
        tex.id[SIZE_ID - 1] = '\0';

        if(!Vector_insertInOrder(tVec, &tex, _TextureManager_compararTex, NULL)){
            return false;
        }

        return true;
    }

    return true;
}

void TextureManager_Draw(tVector* pVec, const char* id, int y, int x, SDL_Renderer* pRenderer) {

    SDL_Rect srcRect;
    tTexture texture;
    SDL_Texture* tex;


    strcpy(texture.id, id);

    if(Vector_bsearch(pVec, &texture, _TextureManager_compararTex) == -1) {
        fprintf(stderr,"Error, la id '%s' no se encuentra.\n", id);
        return;
    }

    tex = texture.texture;

    srcRect.w = WIDTH; //Cant de pixeles de ancho que tomamos de la imagen
    srcRect.h = HEIGTH;  //Cant de pixeles de alto que tomamos de la imagen
    srcRect.x = x;                         //Pos horizontal en la pantalla
    srcRect.y = y;                         //Pos vertical en la pantalla

    SDL_RenderCopy(pRenderer, tex, NULL, &srcRect);
}

int _TextureManager_compararTex (const void* a, const void* b) {
    tTexture* a1 = (tTexture*)(a);
    tTexture* b1 = (tTexture*)(b);

    return strcmp(a1->id, b1->id);
}