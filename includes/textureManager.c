#include "../headers/textureManager.h"
int compararTex (const void* a, const void* b);
int compararIdTex(const void* a, const void* b);


bool TextureManager_load(Vector* vec, const char* fileName, const char* id, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSurface = IMG_Load(fileName);

    if(pTempSurface == NULL){
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);


    if(pTexture != NULL){
        tTexture tex;
        tex.texture = pTexture;
        strncpy(tex.id, id, TAM_ID - 1);
        tex.id[TAM_ID - 1] = '\0';

        if(!Vector_insertInOrder(vec, &tex, sizeof(tTexture), compararTex)){
            return false;
        }

        return true;
    }

    return true;
}

void TextureManagerDraw(Vector* vec, const char* id, int y, int x, SDL_Renderer* pRenderer) {

    SDL_Rect srcRect;

    void* nodo = Vector_bsearch(vec, (void*)id, compararIdTex); //sacar cuando se saquen nodos

    if(nodo == NULL){
        fprintf(stderr,"Error, la id '%s' no se encuentra.\n", id);
        return;
    }

    tTexture texture = *(tTexture*)(nodo); //sacar cuando se saquen nodos

    SDL_Texture* tex = texture.texture;

    srcRect.w = ANCHO; //Cant de pixeles de ancho que tomamos de la imagen
    srcRect.h = ALTO;  //Cant de pixeles de alto que tomamos de la imagen
    srcRect.x = x;                         //Pos horizontal en la pantalla
    srcRect.y = y;                         //Pos vertical en la pantalla

    SDL_RenderCopy(pRenderer, tex, NULL, &srcRect);
}

int compararTex (const void* a, const void* b) {
    tTexture* a1 = (tTexture*)(a);
    tTexture* b1 = (tTexture*)(b);

    return strcmp(a1->id, b1->id);
}

int compararIdTex(const void* a, const void* b) {
    char* elem = (char*)a;
    tTexture* tex = (tTexture*)b;

    return strcmp(elem, tex->id);
}
