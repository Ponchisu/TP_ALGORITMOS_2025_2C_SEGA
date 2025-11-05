#include "../headers/menu.h"

void _Menu_handleEvents(tMenu* pMenu);
void _Menu_draw(tMenu* pMenu);
void _Menu_rankingShow(tMenu* pMenu);
void  _Menu_handleEventsRank(tMenu* pMenu);
void _Menu_drawRank(tMenu* pMenu);
void _Menu_insertName(tMenu* pMenu);
void _Menu_handleinsertName(tMenu* pMenu);
void _Menu_insertNameDraw(tMenu* pMenu);
bool _Menu_createRanking(tMenu* pMenu);

int _Button_cmp(const void* elem1, const void* elem2);
void _Button_update(void* elem1, const void* elem2);

bool Menu_create(tMenu** pMenu) {
    SDL_Surface* icon;
    SDL_Color colorConected = {152, 229, 80, 255};
    SDL_Color colorDisconected = {216, 18, 18, 255};
    *pMenu = (tMenu*)malloc(sizeof(tMenu));
    if(*pMenu == NULL) {
        fprintf(stderr, "Error al crear menu\n");
        return false;
    }

    Vector_init(&(*pMenu)->vecTex);
    Vector_init(&(*pMenu)->vecButton);
    Vector_init(&(*pMenu)->vecRank);
    (*pMenu)->game = NULL;
    (*pMenu)->font = NULL;
    (*pMenu)->music = NULL;
    (*pMenu)->click = NULL;
    (*pMenu)->window = NULL;
    (*pMenu)->renderer = NULL;
    (*pMenu)->click = NULL;
    (*pMenu)->music = NULL;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        return false;
    }

    (*pMenu)->window = SDL_CreateWindow("Maze and Ghost", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_MENU, HEIGTH_MENU, 0);
    if(!(*pMenu)->window) {
        fprintf(stderr, "Error al crear window: %s\n", SDL_GetError());
        return false;
    }

    (*pMenu)->renderer = SDL_CreateRenderer((*pMenu)->window, -1, SDL_RENDERER_ACCELERATED);
    if(!(*pMenu)->renderer) {
        (*pMenu)->renderer = SDL_CreateRenderer((*pMenu)->window, -1, 0);
    }

    if(!(*pMenu)->renderer) {
        fprintf(stderr, "Error al crear renderer: %s\n", SDL_GetError());
        return false;
    }

    icon = IMG_Load("assets/icon.jpg");
    if(!icon) {
        fprintf(stderr, "Error al cargar icono: %s\n", SDL_GetError());
        return false;
    }

    if (init_winsock() != 0) {
        fprintf(stderr, "Error al inicializar Winsock\n");
        return false;
    }

    (*pMenu)->socket = connect_to_server(SERVER_IP, PORT);
    if ((*pMenu)->socket == INVALID_SOCKET) {
        fprintf(stderr, "No se pudo conectar al servidor\n");
        WSACleanup();
        (*pMenu)->conect = false;
    } else {
        (*pMenu)->conect = true;
    }

    SDL_SetWindowIcon((*pMenu)->window, icon);
    SDL_FreeSurface(icon);
    icon = NULL;

    if(!Game_create(&(*pMenu)->game, (*pMenu)->window, (*pMenu)->renderer, &(*pMenu)->socket)) {
        fprintf(stderr, "Error al crear juego\n");
        return false;
    }

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

    if(!Vector_create(&(*pMenu)->vecRank, sizeof(tTexture), SIZE_VECRANK)) {
        fprintf(stderr, "Error al crear vector\n");
        return false;
    }

    if(!Vector_create(&(*pMenu)->vecTex, sizeof(tTexture), SIZE_VECTEXMEN)) {
        fprintf(stderr, "Error al crear vector\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/menu.png", "menu", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen menu\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonStart.png", "bStart", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonStart\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonStartH.png", "bStartH", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonStartH\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonRanking.png", "bRank", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonRanking\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonRankingH.png", "bRankH", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonRankingH\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonExit.png", "bExit", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonExit\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonExitH.png", "bExitH", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonExitH\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/ranking.png", "rank", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen ranking\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonBack.png", "bBack", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonBack\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/buttonBackH.png", "bBackH", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen buttonBackH\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/manuName.png", "mName", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen manuName\n");
        return false;
    }

    if(!TextureManager_load(&(*pMenu)->vecTex, "assets/insertNameH.png", "insertNameH", (*pMenu)->renderer)) {
        fprintf(stderr, "Error al cargar imagen insertNameH\n");
        return false;
    }

    (*pMenu)->fontName = TTF_OpenFont("assets/Monocraft.ttf", 60);
    if((*pMenu)->fontName == NULL) {
        fprintf(stderr, "Error al cargar fuente\n");
        return false;
    }

    (*pMenu)->font = TTF_OpenFont("assets/Monocraft.ttf", 24);
    if((*pMenu)->fontName == NULL) {
        fprintf(stderr, "Error al cargar fuente\n");
        return false;
    }

    if((*pMenu)->conect == true) {
        if(!TextureManager_loadFont(&(*pMenu)->vecTex, "Connected", "conection", (*pMenu)->font, colorConected, (*pMenu)->renderer)) {
            fprintf(stderr, "Error al cargar Insertar conect:\n");
            return false;
        }
    } else {
        if(!TextureManager_loadFont(&(*pMenu)->vecTex, "Disconnected", "conection", (*pMenu)->font, colorDisconected, (*pMenu)->renderer)) {
            fprintf(stderr, "Error al cargar Insertar conect:\n");
            return false;
        }
    }

    (*pMenu)->running = true;
    (*pMenu)->runningName = true;
    (*pMenu)->playGame = false;
    (*pMenu)->showRanking = false;
    (*pMenu)->createRank = true;
    (*pMenu)->insertNameH = false;
    (*pMenu)->insertName = 0;
    strcpy((*pMenu)->name, "");

    if(!Vector_create(&(*pMenu)->vecButton, sizeof(tButton), SIZE_VECBUTTON)) {
        fprintf(stderr, "Error al crear vectorButton\n");
        return false;
    }

    if(!Button_load(&(*pMenu)->vecButton, "start", X_BSTART, Y_BSTART, W_BSTART, H_BSTART)) {
        fprintf(stderr, "Error al cargar button start\n");
        return false;
    }

    if(!Button_load(&(*pMenu)->vecButton, "ranking", X_BRANK, Y_BRANK, W_BRANK, H_BRANK)) {
        fprintf(stderr, "Error al cargar button Ranking\n");
        return false;
    }

    if(!Button_load(&(*pMenu)->vecButton, "exit", X_BEXIT, Y_BEXIT, W_BEXIT, H_BEXIT)) {
        fprintf(stderr, "Error al cargar button exit\n");
        return false;
    }

    if(!Button_load(&(*pMenu)->vecButton, "back", X_BBACK, Y_BBACK, W_BBACK, H_BBACK)) {
        fprintf(stderr, "Error al cargar button back\n");
        return false;
    }

    return true;
}

void Menu_clean(tMenu** pMenu) {
    if(Vector_isEmpty(&(*pMenu)->vecTex) == false) {
        TextureManager_clean(&(*pMenu)->vecTex);
    }
    Vector_clean(&(*pMenu)->vecTex);

    Vector_clean(&(*pMenu)->vecButton);

    if(Vector_isEmpty(&(*pMenu)->vecRank) == false) {
        TextureManager_clean(&(*pMenu)->vecRank);
    }
   Vector_clean(&(*pMenu)->vecRank);


    if((*pMenu)->game != NULL) {
        Game_clean(&(*pMenu)->game);
    }

    if((*pMenu)->renderer != NULL) {
        SDL_DestroyRenderer((*pMenu)->renderer);
        (*pMenu)->renderer = NULL;
    }

    if((*pMenu)->window != NULL) {
        SDL_DestroyWindow((*pMenu)->window);
        (*pMenu)->window = NULL;
    }

    if((*pMenu)->music != NULL) {
            Mix_FreeMusic((*pMenu)->music);
        }

    if((*pMenu)->click != NULL) {
        Mix_FreeChunk((*pMenu)->click);
    }

    if((*pMenu)->font != NULL) {
        TTF_CloseFont((*pMenu)->font);
    }

    close_connection(&(*pMenu)->socket);

    Mix_CloseAudio();
    SDL_Quit();
    TTF_Quit();

    free(*pMenu);
}

bool Menu_running(tMenu* pMenu) {
    int state = OK;
    char response[BUFFER_SIZE];
    Mix_PlayMusic(pMenu->music, -1);
    Mix_VolumeMusic(10);

    _Menu_insertName(pMenu);
    if(pMenu->conect == true) {
        sendPlayer(&pMenu->socket, pMenu->name, response);
    }


    while (pMenu->running == true && state != EXIT) {
        _Menu_handleEvents(pMenu);

        if(pMenu->playGame == true) {
            pMenu->playGame = false;
            state = Game_running(pMenu->game, pMenu->conect, pMenu->name);
            Mix_PlayMusic(pMenu->music, -1);
            Mix_VolumeMusic(10);
            SDL_SetWindowSize(pMenu->window, WIDTH_MENU , HEIGTH_MENU);
            SDL_SetWindowPosition(pMenu->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        } else if(pMenu->showRanking == true) {
            _Menu_rankingShow(pMenu);
        } else {
            _Menu_draw(pMenu);
        }

        if(state == VICTORY) {
            pMenu->createRank = true;
        }

        SDL_Delay(16);
    }

    Mix_HaltMusic();
    return pMenu->playGame;
}

void _Menu_handleEvents(tMenu* pMenu) {
    int x,y;
    tButton bPlay, bRanking, bQuit;

    Button_search(&pMenu->vecButton, "start", &bPlay);
    Button_search(&pMenu->vecButton, "ranking", &bRanking);
    Button_search(&pMenu->vecButton, "exit", &bQuit);

    while(SDL_PollEvent(&pMenu->event)) {
        switch (pMenu->event.type) {
        case SDL_QUIT:
            puts("Enter para salir");
            pMenu->running = false;
            break;
        case SDL_MOUSEMOTION:
            x = pMenu->event.motion.x;
            y = pMenu->event.motion.y;

            if (x >= Button_getX(&bPlay) && x <= Button_getX(&bPlay) + Button_getW(&bPlay) && y >= Button_getY(&bPlay) && y <= Button_getY(&bPlay) + Button_getH(&bPlay)) {
                Button_trueHover(&bPlay);
                Vector_update(&pMenu->vecButton, &bPlay, _Button_cmp, _Button_update);
            } else {
                Button_falseHover(&bPlay);
                Vector_update(&pMenu->vecButton, &bPlay, _Button_cmp, _Button_update);
            }

            if (x >= Button_getX(&bRanking) && x <= Button_getX(&bRanking) + Button_getW(&bRanking) && y >= Button_getY(&bRanking) && y <= Button_getY(&bRanking) + Button_getH(&bRanking)) {
                Button_trueHover(&bRanking);
                Vector_update(&pMenu->vecButton, &bRanking, _Button_cmp, _Button_update);
            } else {
                Button_falseHover(&bRanking);
                Vector_update(&pMenu->vecButton, &bRanking, _Button_cmp, _Button_update);
            }

            if (x >= Button_getX(&bQuit) && x <= Button_getX(&bQuit) + Button_getW(&bQuit) && y >= Button_getY(&bQuit) && y <= Button_getY(&bQuit) + Button_getH(&bQuit)) {
                Button_trueHover(&bQuit);
                Vector_update(&pMenu->vecButton, &bQuit, _Button_cmp, _Button_update);
            } else {
                Button_falseHover(&bQuit);
                Vector_update(&pMenu->vecButton, &bQuit, _Button_cmp, _Button_update);
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
                        if(pMenu->conect == true) {
                            pMenu->showRanking = true;
                        }
                        Mix_PlayChannel(-1, pMenu->click, 0);
                    }
                }
                if (pMenu->event.button.button == SDL_BUTTON_LEFT) {
                    if (x >= Button_getX(&bQuit) && x <= Button_getX(&bQuit) + Button_getW(&bQuit) && y >= Button_getY(&bQuit) && y <= Button_getY(&bQuit) + Button_getH(&bQuit)) {
                        Mix_PlayChannel(-1, pMenu->click, 0);
                        puts("Enter para salir");
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

    TextureManager_draw(&pMenu->vecTex, "menu", 0, 0, pMenu->renderer);
    TextureManager_draw(&pMenu->vecTex, "conection", 0, WIDTH_MENU - (pMenu->conect == true ? WIDTH_TCONECT : WIDTH_FCONECT), pMenu->renderer);
    Button_search(&pMenu->vecButton, "start", &button);
    if(Button_isHover(&button) == true) {
        TextureManager_draw(&pMenu->vecTex, "bStartH", Button_getY(&button), Button_getX(&button), pMenu->renderer);
    }else {
        TextureManager_draw(&pMenu->vecTex, "bStart", Button_getY(&button), Button_getX(&button), pMenu->renderer);
    }

    Button_search(&pMenu->vecButton, "ranking", &button);
    if(Button_isHover(&button) == true) {
        TextureManager_draw(&pMenu->vecTex, "bRankH", Button_getY(&button), Button_getX(&button),  pMenu->renderer);
    }else {
        TextureManager_draw(&pMenu->vecTex, "bRank", Button_getY(&button), Button_getX(&button), pMenu->renderer);
    }

    Button_search(&pMenu->vecButton, "exit", &button);
    if(Button_isHover(&button) == true) {
        TextureManager_draw(&pMenu->vecTex, "bExitH", Button_getY(&button), Button_getX(&button), pMenu->renderer);
    }else {
        TextureManager_draw(&pMenu->vecTex, "bExit", Button_getY(&button), Button_getX(&button), pMenu->renderer);
    }

    SDL_RenderPresent(pMenu->renderer);
}

bool _Menu_createRanking(tMenu* pMenu) {
    char buffer[BUFFER_SIZE];
    char* pipe;
    char* player;
    char pRank[SIZE_PRANK];
    int id;
    char name[SIZE_NAME];
    int points;
    SDL_Color color = {255, 255, 255, 255};

    getRanking(&pMenu->socket, buffer);

    if(Vector_isEmpty(&pMenu->vecRank) == false) {
        TextureManager_clean(&pMenu->vecRank);
    }
    Vector_empty(&pMenu->vecRank);

    player = buffer;
    player++;
    pipe = strchr(player, '|');
    while (pipe) {
        *pipe = '\0';
        sscanf(player, "%d %10s %d", &id, name, &points);
        sprintf(pRank, "%-10s             %8d", name, points);
        if(!TextureManager_loadFontNotID(&pMenu->vecRank, pRank, pMenu->font, color, pMenu->renderer)) {
            puts("ERROR");
            return false;
        }
        player = pipe + 1;
        pipe = strchr(player, '|');
    }


    pMenu->createRank = false;
    return true;
}

void _Menu_rankingShow(tMenu* pMenu) {
    if(pMenu->createRank == true) {
        _Menu_createRanking(pMenu);
    }
    while (pMenu->showRanking == true) {
        _Menu_handleEventsRank(pMenu);

        _Menu_drawRank(pMenu);

        SDL_Delay(16);
    }
 }

void  _Menu_handleEventsRank(tMenu* pMenu) {
    int x,y;
    tButton bExit;
    Button_search(&pMenu->vecButton, "back", &bExit);
    while(SDL_PollEvent(&pMenu->event)) {
        switch (pMenu->event.type) {
            case SDL_QUIT:
                puts("Enter para salir");
                pMenu->running = false;
                pMenu->showRanking = false;
                break;
            case SDL_MOUSEMOTION:
                x = pMenu->event.motion.x;
                y = pMenu->event.motion.y;
                if (x >= Button_getX(&bExit) && x <= Button_getX(&bExit) + Button_getW(&bExit) && y >= Button_getY(&bExit) && y <= Button_getY(&bExit) + Button_getH(&bExit)) {
                    Button_trueHover(&bExit);
                    Vector_update(&pMenu->vecButton, &bExit, _Button_cmp, _Button_update);
                } else {
                    Button_falseHover(&bExit);
                    Vector_update(&pMenu->vecButton, &bExit, _Button_cmp, _Button_update);
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

    Button_search(&pMenu->vecButton, "back", &button);

    TextureManager_draw(&pMenu->vecTex, "rank", 0, 0, pMenu->renderer);
    if(Button_isHover(&button) == true) {
        TextureManager_draw(&pMenu->vecTex, "bBackH", Button_getY(&button), Button_getX(&button), pMenu->renderer);
    }else {
        TextureManager_draw(&pMenu->vecTex, "bBack", Button_getY(&button), Button_getX(&button), pMenu->renderer);
    }

    if(Vector_isEmpty(&pMenu->vecRank) == false) {
        TextureManager_drawVec(&pMenu->vecRank, Y_RANK, X_RANK, DISTANCE_RANK, pMenu->renderer);
    }


    SDL_RenderPresent(pMenu->renderer);
 }

 void _Menu_insertName(tMenu* pMenu) {
    SDL_StartTextInput();
    while (pMenu->runningName == true && pMenu->running == true) {
        _Menu_handleinsertName(pMenu);

        _Menu_insertNameDraw(pMenu);

        SDL_Delay(16);
    }
    SDL_StopTextInput();
 }

 void _Menu_handleinsertName(tMenu* pMenu) {
    char c;
        while(SDL_PollEvent(&pMenu->event)) {
        switch (pMenu->event.type) {
        case SDL_QUIT:
            puts("Enter para salir");
            pMenu->running = false;
            break;
        case SDL_TEXTINPUT:
                if (strlen(pMenu->name) + strlen(pMenu->event.text.text) < SIZE_NAME && (ISNUMBER(pMenu->event.text.text[0]) || ISLETTER(pMenu->event.text.text[0]))) {
                    c = toupper(pMenu->event.text.text[0]);
                    strcat(pMenu->name, &c);
                }
            break;
        case SDL_KEYDOWN:
            switch (pMenu->event.key.keysym.scancode) {
                case SDL_SCANCODE_RETURN:
                    if(strlen(pMenu->name) > 0) {
                        pMenu->runningName = false;
                    }
                    break;
                case SDL_SCANCODE_BACKSPACE:
                    if(strlen(pMenu->name) > 0) {
                        pMenu->name[strlen(pMenu->name) - 1] = '\0';
                    }
                    break;
                default:
                    break;
                }
        }
    }
}

void _Menu_insertNameDraw(tMenu* pMenu) {
    SDL_RenderClear(pMenu->renderer);

    TextureManager_draw(&pMenu->vecTex, "mName", 0, 0, pMenu->renderer);

    if(pMenu->insertName == 30) {
        pMenu->insertNameH = pMenu->insertNameH == true ? false : true;
        pMenu->insertName = 0;
    } else {
        pMenu->insertName ++;
    }

    if(pMenu->insertNameH == true) {
        TextureManager_draw(&pMenu->vecTex, "insertNameH", 205, 73, pMenu->renderer);
    }

    if(strlen(pMenu->name) > 0) {
        SDL_Color color = {255, 255, 255, 255};

        SDL_Surface* surface = TTF_RenderText_Solid(pMenu->fontName, pMenu->name, color);
        SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(pMenu->renderer, surface);
        SDL_Rect nameRect = {X_INSERTNAME, Y_INSERTNAME, surface->w, surface->h};
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
