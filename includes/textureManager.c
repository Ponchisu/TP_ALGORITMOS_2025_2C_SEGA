#include "../headers/textureManager.h"
int _TextureManager_compararTex (const void* a, const void* b);

bool TextureManager_load(tVector* pVec, const char* fileName, const char* id, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load(fileName);
    SDL_Texture* pTexture;
    tTexture tex;

    if(pTempSurface == NULL){
        return false;
    }

    pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    tex.w = pTempSurface->w;
    tex.h = pTempSurface->h;
    SDL_FreeSurface(pTempSurface);


    if(pTexture != NULL){
        tex.texture = pTexture;
        strncpy(tex.id, id, SIZE_ID - 1);
        tex.id[SIZE_ID - 1] = '\0';

        if(!Vector_insertInOrder(pVec, &tex, _TextureManager_compararTex, NULL)){
            return false;
        }
    }

    return true;
}

bool TextureManager_loadFont(tVector* pVec, char* text, const char* id, TTF_Font* font, SDL_Color color, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* pTexture;
    tTexture tex;

    if(pTempSurface == NULL){
        return false;
    }

    pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    tex.w = pTempSurface->w;
    tex.h = pTempSurface->h;
    SDL_FreeSurface(pTempSurface);


    if(pTexture != NULL) {
        tex.texture = pTexture;
        strncpy(tex.id, id, SIZE_ID - 1);
        tex.id[SIZE_ID - 1] = '\0';

        if(!Vector_insertInOrder(pVec, &tex, _TextureManager_compararTex, NULL)) {
            return false;
        }
    }

    return true;
}

bool TextureManager_loadFontNotID(tVector* pVec, char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* pTexture;
    tTexture tex;

    if(pTempSurface == NULL){
        return false;
    }

    pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    if(pTexture == NULL) {
        SDL_FreeSurface(pTempSurface);
        return false;
    }

    tex.w = pTempSurface->w;
    tex.h = pTempSurface->h;
    SDL_FreeSurface(pTempSurface);


    tex.texture = pTexture;
    strcpy(tex.id, " ");

     if(!Vector_insert(pVec, &tex)) {
         return false;
     }

    return true;
}

void TextureManager_draw(tVector* pVec, const char* id, int y, int x, SDL_Renderer* pRenderer) {
    SDL_Rect srcRect;
    tTexture texture;
    SDL_Texture* tex;


    strcpy(texture.id, id);

    if(Vector_bsearch(pVec, &texture, _TextureManager_compararTex) == -1) {
        fprintf(stderr,"Error, la id '%s' no se encuentra.\n", id);
        return;
    }

    tex = texture.texture;

    srcRect.w = texture.w; //Cant de pixeles de ancho que tomamos de la imagen
    srcRect.h = texture.h;  //Cant de pixeles de alto que tomamos de la imagen
    srcRect.x = x;                         //Pos horizontal en la pantalla
    srcRect.y = y;                         //Pos vertical en la pantalla

    SDL_RenderCopy(pRenderer, tex, NULL, &srcRect);
}

void TextureManager_drawVec(tVector* pVec, int y, int x, int distance, SDL_Renderer* pRenderer) {
    tVectorIterator vecIter;
    tTexture texture;
    SDL_Texture* tex;
    SDL_Rect srcRect;
    VectorIterator_create(&vecIter, pVec);

    VectorIterator_first(&vecIter, &texture);
    while (!VectorIterator_finished(&vecIter)) {
        tex = texture.texture;

        srcRect.w = texture.w;
        srcRect.h = texture.h;
        srcRect.x = x;
        srcRect.y = y;

        SDL_RenderCopy(pRenderer, tex, NULL, &srcRect);
        y += distance;
        VectorIterator_next(&vecIter, &texture);
    }
}

int _TextureManager_compararTex (const void* a, const void* b) {
    tTexture* a1 = (tTexture*)(a);
    tTexture* b1 = (tTexture*)(b);

    return strcmp(a1->id, b1->id);
}

void TextureManager_clean(tVector* pVec) {
    tVectorIterator vecIter;
    tTexture texture;
    VectorIterator_create(&vecIter, pVec);

    VectorIterator_first(&vecIter, &texture);
    while (!VectorIterator_finished(&vecIter)) {
        SDL_DestroyTexture(texture.texture);
        VectorIterator_next(&vecIter, &texture);
    }
}
