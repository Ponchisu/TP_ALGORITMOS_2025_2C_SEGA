#include "../headers/menu.h"

void _Menu_handleEvents(tMenu* pMenu);
void _Menu_draw(tMenu* pMenu);
void _Menu_rankingShow(tMenu* pMenu);
void  _Menu_handleEventsRank(tMenu* pMenu);
void _Menu_drawRank(tMenu* pMenu);
void _Menu_insertName(tMenu* pMenu, char* name);
void _Menu_handleinsertName(tMenu* pMenu, char* pName);
void _Menu_insertNameDraw(tMenu* pMenu, char* pName);

int _Button_cmp(const void* elem1, const void* elem2);
void _Button_update(void* elem1, const void* elem2);

bool Menu_create(tMenu** pMenu, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Color nameColor = {255, 255, 255, 255};
    *pMenu = (tMenu*)malloc(sizeof(tMenu));
    if(*pMenu == NULL) {
        fprintf(stderr, "Error al crear menu\n");
        return false;
    }

    Vector_init(&(*pMenu)->vecTex);
    Vector_init(&(*pMenu)->vecButton);

    (*pMenu)->music = Mix_LoadMUS("sound/musicMenu.mp3");
    if((*pMenu)->music == NULL) {
        fprintf(stderr, "Error al cargar musica musicMenu\n");
        return false;
    }

    (*pMenu)->click = Mix_LoadWAV("sound/click.wav");
    if((*pMenu)->click == NULL) {
        fprintf(stderr, "Error al cargar sonido click\n");
        return false;
    }
    Mix_VolumeChunk((*pMenu)->click, 15);

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

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/ranking.png", "rank", renderer)) {
        fprintf(stderr, "Error al cargar imagen ranking\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonExit.png", "bExit", renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonExit\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonExitH.png", "bExitH", renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonExitH\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/manuName.png", "mName", renderer)) {
        fprintf(stderr, "Error al cargar imagen manuName\n");
        return false;
    }
    
    (*pMenu)->font = TTF_OpenFont("assets/Monocraft.ttf", 24);

    if(!TextureManager_loadFont(&(*pMenu)->vecTex, "Insertar nombre:", "insrtName", (*pMenu)->font, nameColor, renderer)) {
        fprintf(stderr, "Error al cargar Insertar nombre:\n");
        return false;
    }

    (*pMenu)->window = window;
    (*pMenu)->renderer = renderer;

    (*pMenu)->running = true;
    (*pMenu)->runningName = true;
    (*pMenu)->playGame = false;
    (*pMenu)->showRanking = false;

    if(!Vector_create(&(*pMenu)->vecButton, sizeof(tButton), SIZE_VECBUTTON)) {
        fprintf(stderr, "Error al crear vectorButton\n");
        return false;
    }

    if(!Button_load(&(*pMenu)->vecButton, "play", 156, 260, 249, 89)) {
        fprintf(stderr, "Error al cargar button play\n");
        return false;
    }

    if(!Button_load(&(*pMenu)->vecButton, "ranking", 156, 359, 249, 89)) {
        fprintf(stderr, "Error al cargar button Ranking\n");
        return false;
    }

    if(!Button_load(&(*pMenu)->vecButton, "quit", 156, 458, 249, 89)) {
        fprintf(stderr, "Error al cargar button Quit\n");
        return false;
    }

    if(!Button_load(&(*pMenu)->vecButton, "exit", 8, 10, 93, 59)) {
        fprintf(stderr, "Error al cargar button Exit\n");
        return false;
    }

    return true;
}

void Menu_clean(tMenu** pMenu) {
    if(Vector_empty(&(*pMenu)->vecTex) == false) {
        TextureManager_clean(&(*pMenu)->vecTex);
    }
    Vector_clean(&(*pMenu)->vecTex);

    Vector_clean(&(*pMenu)->vecButton);

    if((*pMenu)->music != NULL) {
        Mix_FreeMusic((*pMenu)->music);
    }

    free(*pMenu);
}

bool Menu_running(tMenu* pMenu, char* pName) {
    Mix_PlayMusic(pMenu->music, -1);
    Mix_VolumeMusic(15);

    _Menu_insertName(pMenu, pName);
    while (pMenu->running == true && pMenu->playGame == false) {
        _Menu_handleEvents(pMenu);

        if(pMenu->showRanking == true) {
            _Menu_rankingShow(pMenu);
        } else {
            _Menu_draw(pMenu);
        }

        SDL_Delay(16);
    }

    Mix_HaltMusic();
    return pMenu->playGame;
}

void _Menu_handleEvents(tMenu* pMenu) {
    int x,y;
    tButton bPlay, bRanking, bQuit;

    Button_search(&pMenu->vecButton, "play", &bPlay);
    Button_search(&pMenu->vecButton, "ranking", &bRanking);
    Button_search(&pMenu->vecButton, "quit", &bQuit);

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
            default:
                break;
            }
        case SDL_MOUSEMOTION:
            x = pMenu->event.motion.x;
            y = pMenu->event.motion.y;

            if (x >= Button_getX(&bPlay) && x <= Button_getX(&bPlay) + Button_getW(&bPlay) && y >= Button_getY(&bPlay) && y <= Button_getY(&bPlay) + Button_getH(&bPlay)) {
                Button_trueHover(&bPlay);
                Vector_Update(&pMenu->vecButton, &bPlay, _Button_cmp, _Button_update);
            } else {
                Button_falseHover(&bPlay);
                Vector_Update(&pMenu->vecButton, &bPlay, _Button_cmp, _Button_update);
            }

            if (x >= Button_getX(&bRanking) && x <= Button_getX(&bRanking) + Button_getW(&bRanking) && y >= Button_getY(&bRanking) && y <= Button_getY(&bRanking) + Button_getH(&bRanking)) {
                Button_trueHover(&bRanking);
                Vector_Update(&pMenu->vecButton, &bRanking, _Button_cmp, _Button_update);
            } else {
                Button_falseHover(&bRanking);
                Vector_Update(&pMenu->vecButton, &bRanking, _Button_cmp, _Button_update);
            }

            if (x >= Button_getX(&bQuit) && x <= Button_getX(&bQuit) + Button_getW(&bQuit) && y >= Button_getY(&bQuit) && y <= Button_getY(&bQuit) + Button_getH(&bQuit)) {
                Button_trueHover(&bQuit);
                Vector_Update(&pMenu->vecButton, &bQuit, _Button_cmp, _Button_update);
            } else {
                Button_falseHover(&bQuit);
                Vector_Update(&pMenu->vecButton, &bQuit, _Button_cmp, _Button_update);
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (pMenu->event.button.button == SDL_BUTTON_LEFT) {
                    if (x >= Button_getX(&bPlay) && x <= Button_getX(&bPlay) + Button_getW(&bPlay) && y >= Button_getY(&bPlay) && y <= Button_getY(&bPlay) + Button_getH(&bPlay)) {
                        pMenu->playGame = true;
                        Mix_PlayChannel(-1, pMenu->click, 0);
                    }
                }
                if (pMenu->event.button.button == SDL_BUTTON_LEFT) {
                    if (x >= Button_getX(&bRanking) && x <= Button_getX(&bRanking) + Button_getW(&bRanking) && y >= Button_getY(&bRanking) && y <= Button_getY(&bRanking) + Button_getH(&bRanking)) {
                        pMenu->showRanking = true;
                        Mix_PlayChannel(-1, pMenu->click, 0);
                    }
                }
                if (pMenu->event.button.button == SDL_BUTTON_LEFT) {
                    if (x >= Button_getX(&bQuit) && x <= Button_getX(&bQuit) + Button_getW(&bQuit) && y >= Button_getY(&bQuit) && y <= Button_getY(&bQuit) + Button_getH(&bQuit)) {
                        Mix_PlayChannel(-1, pMenu->click, 0);
                        pMenu->running = false;
                    }
                }
                break;
        }
    }
 }

  void _Menu_draw(tMenu* pMenu) {
    SDL_RenderClear(pMenu->renderer);
    tButton button;
    int x, y, w, h;

    TextureManager_draw(&pMenu->vecTex, "menu", 0, 0, WIDTH_MENU, HEIGTH_MENU, pMenu->renderer);
    Button_search(&pMenu->vecButton, "play", &button);
    x = Button_getX(&button);
    y = Button_getY(&button);
    w = Button_getW(&button);
    h = Button_getH(&button);
    if(Button_isHover(&button) == true) {
        TextureManager_draw(&pMenu->vecTex, "bPlayH", y, x, w, h, pMenu->renderer);
    }else {
        TextureManager_draw(&pMenu->vecTex, "bPlay", y, x, w, h, pMenu->renderer);
    }

    Button_search(&pMenu->vecButton, "ranking", &button);
    x = Button_getX(&button);
    y = Button_getY(&button);
    w = Button_getW(&button);
    h = Button_getH(&button);
    if(Button_isHover(&button) == true) {
        TextureManager_draw(&pMenu->vecTex, "bRankH", y, x, w, h, pMenu->renderer);
    }else {
        TextureManager_draw(&pMenu->vecTex, "bRank", y, x, w, h, pMenu->renderer);
    }

    Button_search(&pMenu->vecButton, "quit", &button);
    x = Button_getX(&button);
    y = Button_getY(&button);
    w = Button_getW(&button);
    h = Button_getH(&button);
    if(Button_isHover(&button) == true) {
        TextureManager_draw(&pMenu->vecTex, "bQuitH", y, x, w, h, pMenu->renderer);
    }else {
        TextureManager_draw(&pMenu->vecTex, "bQuit", y, x, w, h, pMenu->renderer);
    }

    SDL_RenderPresent(pMenu->renderer);
 }

void _Menu_rankingShow(tMenu* pMenu) {
    while (pMenu->showRanking == true) {
        _Menu_handleEventsRank(pMenu);

        _Menu_drawRank(pMenu);

        SDL_Delay(16);
    }
 }

void  _Menu_handleEventsRank(tMenu* pMenu) {
    int x,y;
    tButton bExit;
    Button_search(&pMenu->vecButton, "exit", &bExit);
    while(SDL_PollEvent(&pMenu->event)) {
        switch (pMenu->event.type) {
        case SDL_QUIT:
            puts("Enter para salir");
            pMenu->running = false;
            pMenu->showRanking = false;
            break;
        case SDL_KEYDOWN:
            switch (pMenu->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                puts("Enter para salir");
                pMenu->running = false;
                pMenu->showRanking = false;
                break;
            default:
                break;
            }
        case SDL_MOUSEMOTION:
            x = pMenu->event.motion.x;
            y = pMenu->event.motion.y;
            if (x >= Button_getX(&bExit) && x <= Button_getX(&bExit) + Button_getW(&bExit) && y >= Button_getY(&bExit) && y <= Button_getY(&bExit) + Button_getH(&bExit)) {
                Button_trueHover(&bExit);
                Vector_Update(&pMenu->vecButton, &bExit, _Button_cmp, _Button_update);
            } else {
                Button_falseHover(&bExit);
                Vector_Update(&pMenu->vecButton, &bExit, _Button_cmp, _Button_update);
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (pMenu->event.button.button == SDL_BUTTON_LEFT) {
                    x = pMenu->event.button.x;
                    y = pMenu->event.button.y;

                    if (x >= Button_getX(&bExit) && x <= Button_getX(&bExit) + Button_getW(&bExit) && y >= Button_getY(&bExit) && y <= Button_getY(&bExit) + Button_getH(&bExit)) {
                        pMenu->showRanking = false;
                        Mix_PlayChannel(-1, pMenu->click, 0);
                    }
                }
                break;
        }
    }
 }

void _Menu_drawRank(tMenu* pMenu) {
    SDL_RenderClear(pMenu->renderer);
    tButton button;

    Button_search(&pMenu->vecButton, "exit", &button);

    TextureManager_draw(&pMenu->vecTex, "rank", 0, 0, 600, 800, pMenu->renderer);
    if(Button_isHover(&button) == true) {
        TextureManager_draw(&pMenu->vecTex, "bExitH", Button_getY(&button), Button_getX(&button), Button_getW(&button), Button_getH(&button), pMenu->renderer);
    }else {
        TextureManager_draw(&pMenu->vecTex, "bExit", Button_getY(&button), Button_getX(&button), Button_getW(&button), Button_getH(&button), pMenu->renderer);
    }

    SDL_RenderPresent(pMenu->renderer);
 }

 void _Menu_insertName(tMenu* pMenu, char* pName) {
    SDL_StartTextInput();
    while (pMenu->runningName == true && pMenu->running == true) {
        _Menu_handleinsertName(pMenu, pName);

        _Menu_insertNameDraw(pMenu, pName);

        SDL_Delay(16);
    }
    SDL_StopTextInput();
 }

 void _Menu_handleinsertName(tMenu* pMenu, char* pName) {
        while(SDL_PollEvent(&pMenu->event)) {
        switch (pMenu->event.type) {
        case SDL_QUIT:
            puts("Enter para salir");
            pMenu->running = false;
            break;
        case SDL_TEXTINPUT:
                char c = pMenu->event.text.text[0];
                if (strlen(pName) + strlen(pMenu->event.text.text) < SIZE_NAME && (ISNUMBER(c) || ISLETTER(c))) {
                    strcat(pName, pMenu->event.text.text);
                }
            break;
        case SDL_KEYDOWN:
            switch (pMenu->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                puts("Enter para salir");
                pMenu->running = false;
                break;
            case SDL_SCANCODE_RETURN:
                if(strlen(pName) > 0) {
                    pMenu->runningName = false;
                }
                break;
            case SDL_SCANCODE_BACKSPACE:
                if(strlen(pName) > 0) {
                    pName[strlen(pName) - 1] = '\0';
                }
                break;
            default:
                break;
            }
        }
    }
}

void _Menu_insertNameDraw(tMenu* pMenu, char* pName) {
    SDL_RenderClear(pMenu->renderer);

    TextureManager_draw(&pMenu->vecTex, "mName", 0, 0, WIDTH_MENU, HEIGTH_MENU, pMenu->renderer);
    TextureManager_draw(&pMenu->vecTex, "insrtName", Y_INSRTNAME, X_INSRTNAME, WIDTH_INSRTNAME, HEIGTH_INSRTNAME, pMenu->renderer);

    if(strlen(pName) > 0) {
        SDL_Color color = {255, 255, 255, 255};

        SDL_Surface* surface = TTF_RenderText_Solid(pMenu->font, pName, color);
        SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(pMenu->renderer, surface);
        SDL_Rect nameRect = {209, 329, surface->w, surface->h};
        SDL_RenderCopy(pMenu->renderer, nameTexture, NULL, &nameRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(nameTexture);

    }

    SDL_RenderPresent(pMenu->renderer);
}


bool Button_load(tVector* pVec, const char* id, int x, int y, int w, int h) {
    tButton button = {"", {x, y, w, h}, false};
    strcpy(button.id, id);

    if(!Vector_insertInOrder(pVec, &button, _Button_cmp, NULL)) {
        return false;
    }

    return true;
}

bool Button_search(tVector* pVec, const char* id, tButton* button) {
    strcpy(button->id, id);

    if(Vector_bsearch(pVec, button, _Button_cmp) == -1) {
        return false;
    }
    return true;
}

int _Button_cmp(const void* elem1, const void* elem2) {
    const tButton* button1 = elem1;
    const tButton* button2 = elem2;
    return strcmp(button1->id, button2->id);
}

void _Button_update(void* elem1, const void* elem2) {
    tButton* button1 = elem1;
    const tButton* button2 = elem2;
    button1->hover = button2->hover;
}

bool Button_isHover(tButton* button) {
    return button->hover;
}

void Button_trueHover(tButton* button) {
    button->hover = true;
}

void Button_falseHover(tButton* button) {
    button->hover = false;
}

int Button_getX(tButton* button) {
    return button->button.x;
}

int Button_getY(tButton* button) {
    return button->button.y;
}

int Button_getW(tButton* button) {
    return button->button.w;
}

int Button_getH(tButton* button) {
    return button->button.h;
}
