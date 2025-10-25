#include "../headers/menu.h"

void _Menu_handleEvents(tMenu* pMenu);
void _Menu_handleDraw(tMenu* pMenu);

bool Menu_create(tMenu** pMenu, SDL_Window* window, SDL_Renderer* renderer) {
    *pMenu = (tMenu*)malloc(sizeof(tMenu));
    if(*pMenu == NULL) {
        fprintf(stderr, "Error al crear menu\n");
        return false;
    }

    (*pMenu)->music = Mix_LoadMUS("sound/musicMenu.mp3");
    if((*pMenu)->music == NULL) {
        fprintf(stderr, "Error al cargar musica musicMenu\n");
        return false;
    }

    if(!Vector_create(&(*pMenu)->vecTex, sizeof(tTexture), SIZE_VECTEXMEN)) {
        fprintf(stderr, "Error al crear vector\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/menu.png", "menu", renderer)) {
        fprintf(stderr, "Error al cargar imagen menu\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonPlay.png", "bPlay", renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonPlay\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonPlayH.png", "bPlayH", renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonPlayH\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonRanking.png", "bRank", renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonRanking\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonRankingH.png", "bRankH", renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonRankingH\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonQuit.png", "bQuit", renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonQuit\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonQuitH.png", "bQuitH", renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonQuitH\n");
        return false;
    }

    (*pMenu)->window = window;
    (*pMenu)->renderer = renderer;

    (*pMenu)->running = true;
    (*pMenu)->playGame = false;
    
    (*pMenu)->buttonPlayH = false;
    (*pMenu)->buttonPlay.x = 156;
    (*pMenu)->buttonPlay.y = 260;
    (*pMenu)->buttonPlay.w = 249;
    (*pMenu)->buttonPlay.h = 89;

    (*pMenu)->buttonRankingH = false;
    (*pMenu)->buttonRanking.x = 156;
    (*pMenu)->buttonRanking.y = 359;
    (*pMenu)->buttonRanking.w = 249;
    (*pMenu)->buttonRanking.h = 89;
    
    (*pMenu)->buttonQuitH = false;
    (*pMenu)->buttonQuit.x = 156;
    (*pMenu)->buttonQuit.y = 458;
    (*pMenu)->buttonQuit.w = 249;
    (*pMenu)->buttonQuit.h = 89;

    return true;
}

void Menu_clean(tMenu** pMenu) {
    TextureManager_clean(&(*pMenu)->vecTex);
    Vector_clean(&(*pMenu)->vecTex);

    if((*pMenu)->music != NULL) {
        Mix_FreeMusic((*pMenu)->music);
    }

    free(*pMenu);
}

bool Menu_running(tMenu* pMenu) {
    Mix_PlayMusic(pMenu->music, -1);
    Mix_VolumeMusic(15);
    while (pMenu->running == true && pMenu->playGame == false) {
        _Menu_handleEvents(pMenu);

        _Menu_handleDraw(pMenu);

        SDL_Delay(16);
    }


    return pMenu->playGame;
}

void _Menu_handleEvents(tMenu* pMenu) {
    int x,y;
        while(SDL_PollEvent(&pMenu->event)) {
        switch (pMenu->event.type) {
        case SDL_QUIT:
            puts("Enter para salir");
            pMenu->running = false;
            break;
        case SDL_KEYDOWN:
            switch (pMenu->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                puts("Enter para salir");
                pMenu->running = false;
                break;
            case SDL_SCANCODE_RETURN:
                pMenu->playGame = true;
                break;
            default:
                break;
            }
        case SDL_MOUSEMOTION:
            x = pMenu->event.motion.x;
            y = pMenu->event.motion.y;
            if (x >= pMenu->buttonPlay.x && x <= pMenu->buttonPlay.x + pMenu->buttonPlay.w && y >= pMenu->buttonPlay.y && y <= pMenu->buttonPlay.y + pMenu->buttonPlay.h) {
                pMenu->buttonPlayH = true;
            } else {
                pMenu->buttonPlayH = false;
            }
            x = pMenu->event.motion.x;
            y = pMenu->event.motion.y;
            if (x >= pMenu->buttonRanking.x && x <= pMenu->buttonRanking.x + pMenu->buttonRanking.w && y >= pMenu->buttonRanking.y && y <= pMenu->buttonRanking.y + pMenu->buttonRanking.h) {
                pMenu->buttonRankingH = true;
            } else {
                pMenu->buttonRankingH = false;
            }
            x = pMenu->event.motion.x;
            y = pMenu->event.motion.y;
            if (x >= pMenu->buttonQuit.x && x <= pMenu->buttonQuit.x + pMenu->buttonQuit.w && y >= pMenu->buttonQuit.y && y <= pMenu->buttonQuit.y + pMenu->buttonQuit.h) {
                pMenu->buttonQuitH = true;
            } else {
                pMenu->buttonQuitH = false;
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (pMenu->event.button.button == SDL_BUTTON_LEFT) {
                    int x = pMenu->event.button.x;
                    int y = pMenu->event.button.y;

                    if (x >= pMenu->buttonPlay.x && x <= pMenu->buttonPlay.x + pMenu->buttonPlay.w &&
                        y >= pMenu->buttonPlay.y && y <= pMenu->buttonPlay.y + pMenu->buttonPlay.h) {
                        pMenu->playGame = true;
                    }
                }
                // if (pMenu->event.button.button == SDL_BUTTON_LEFT) {
                //     int x = pMenu->event.button.x;
                //     int y = pMenu->event.button.y;

                //     if (x >= pMenu->buttonRanking.x && x <= pMenu->buttonRanking.x + pMenu->buttonRanking.w &&
                //         y >= pMenu->buttonRanking.y && y <= pMenu->buttonRanking.y + pMenu->buttonRanking.h) {
                //     }
                // }
                if (pMenu->event.button.button == SDL_BUTTON_LEFT) {
                    int x = pMenu->event.button.x;
                    int y = pMenu->event.button.y;

                    if (x >= pMenu->buttonQuit.x && x <= pMenu->buttonQuit.x + pMenu->buttonQuit.w &&
                        y >= pMenu->buttonQuit.y && y <= pMenu->buttonQuit.y + pMenu->buttonQuit.h) {
                        pMenu->running = false;
                    }
                }
                break;
        }
    }
 }

  void _Menu_handleDraw(tMenu* pMenu) {
    SDL_RenderClear(pMenu->renderer);

    TextureManager_Draw(&pMenu->vecTex, "menu", 0, 0, 600, 800, pMenu->renderer);
    if(pMenu->buttonPlayH == true) {
        TextureManager_Draw(&pMenu->vecTex, "bPlayH", pMenu->buttonPlay.y, pMenu->buttonPlay.x, pMenu->buttonPlay.w, pMenu->buttonPlay.h, pMenu->renderer);
    }else {
        TextureManager_Draw(&pMenu->vecTex, "bPlay", pMenu->buttonPlay.y, pMenu->buttonPlay.x, pMenu->buttonPlay.w, pMenu->buttonPlay.h, pMenu->renderer);
    }
    if(pMenu->buttonRankingH == true) {
        TextureManager_Draw(&pMenu->vecTex, "bRankH", pMenu->buttonRanking.y, pMenu->buttonRanking.x, pMenu->buttonRanking.w, pMenu->buttonRanking.h, pMenu->renderer);
    }else {
        TextureManager_Draw(&pMenu->vecTex, "bRank", pMenu->buttonRanking.y, pMenu->buttonRanking.x, pMenu->buttonRanking.w, pMenu->buttonRanking.h, pMenu->renderer);
    }
    if(pMenu->buttonQuitH == true) {
        TextureManager_Draw(&pMenu->vecTex, "bQuitH", pMenu->buttonQuit.y, pMenu->buttonQuit.x, pMenu->buttonQuit.w, pMenu->buttonQuit.h, pMenu->renderer);
    }else {
        TextureManager_Draw(&pMenu->vecTex, "bQuit", pMenu->buttonQuit.y, pMenu->buttonQuit.x, pMenu->buttonQuit.w, pMenu->buttonQuit.h, pMenu->renderer);
    }

    SDL_RenderPresent(pMenu->renderer);
 }