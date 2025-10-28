#include "../headers/game.h"

void _Game_handleEvents(tGame* game, bool isGame);
void _Game_draw(tGame* game, int marginDraw);
void _Game_update(tGame* game);

bool Game_create(tGame** game) {
    *game = (tGame*)malloc(sizeof(tGame));
    if(*game == NULL) {
        return false;
    }

    return true;
}

bool Game_init(tGame* game) {
    int rows, columns, numLive, numGhosts, numAwards, maxLives;
    bool rei;
    SDL_Surface* icon;

    game->maze = NULL;
    game->renderer = NULL;
    game->window = NULL;
    game->colaMovement = NULL;
    game->colaTurn = NULL;
    game->pMenu = NULL;
    strcpy(game->name, "");

    Vector_init(&game->vecMusic);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }

    if(!Config_getParametersFromFile(&rows, &columns, &numLive, &numGhosts, &numAwards, &maxLives, &rei)) {
        return false;
    }

    if(numGhosts < 1 || numGhosts > 20) {
        fprintf(stderr, "Numero de fantasmas invalido\n");
        return false;
    }

    if(columns < 15 || columns > 31) {
        fprintf(stderr, "Numero de columnas invalido\n");
        return false;
    }

    if(rows < 15 || rows > 31) {
        fprintf(stderr, "Numero de filas invalido\n");
        return false;
    }

    if(numLive < 0 || numLive > 10) {
        fprintf(stderr, "Numero de vidas invalido\n");
        return false;
    }

    if(numAwards < 1 || numLive > 20) {
        fprintf(stderr, "Numero de premios invalido\n");
        return false;
    }

    if(maxLives < 1 || MAX_LIVES > 15) {
        fprintf(stderr, "Numero de vidas extras invalido\n");
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        return false;
    }

    game->window = SDL_CreateWindow("Maze and Ghost", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, 0);
    if(!game->window) {
        fprintf(stderr, "Error al crear window: %s\n", SDL_GetError());
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if(!game->renderer) {
        game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    }

    if(!game->renderer) {
        fprintf(stderr, "Error al crear renderer: %s\n", SDL_GetError());
        return false;
    }

    if(!Maze_create(&game->maze, game->renderer, rows, columns, numLive, numGhosts, numAwards, maxLives, rei)) {
        return false;
    }
    if(!Menu_create(&game->pMenu, game->window, game->renderer)) {
        return false;
    }

    if(!Vector_create(&game->vecMusic, sizeof(tMusic), SIZE_VECMUSIC)) {
        return false;
    }

    if(!SoundManager_loadMusic(&game->vecMusic, "sound/musicGame.mp3", "musicGame")) {
        fprintf(stderr, "Error al cargar la cancion musicGame\n");
        return false;
    }

    if(!SoundManager_loadMusic(&game->vecMusic, "sound/musicVictory.mp3", "musicVictory")) {
        fprintf(stderr, "Error al cargar la cancion musicVictory\n");
        return false;
    }

    if(!SoundManager_loadMusic(&game->vecMusic, "sound/musicLost.mp3", "musicLost")) {
        fprintf(stderr, "Error al cargar la cancion musicLost\n");
        return false;
    }

    icon = IMG_Load("assets/icon.jpg");
    if(!icon) {
        fprintf(stderr, "Error al cargar icono: %s\n", SDL_GetError());
        return false;
    }

    Cola_create(&game->colaMovement);
    Cola_create(&game->colaTurn);

    SDL_SetWindowIcon(game->window, icon);
    SDL_FreeSurface(icon);
    icon = NULL;

    game->running = true;

    return true;
}

void Game_clean(tGame** game) {
    if ((*game)->maze != NULL) {
        Maze_clean(&(*game)->maze);
    }

    if((*game)->renderer != NULL) {
        SDL_DestroyRenderer((*game)->renderer);
        (*game)->renderer = NULL;
    }
    if((*game)->window != NULL) {
        SDL_DestroyWindow((*game)->window);
        (*game)->window = NULL;
    }

    if((*game)->colaMovement != NULL) {
        Cola_clean(&(*game)->colaMovement);
        (*game)->colaMovement = NULL;
    }

    if((*game)->colaTurn != NULL) {
        Cola_clean(&(*game)->colaTurn);
        (*game)->colaTurn = NULL;
    }

    if((*game)->pMenu != NULL) {
        Menu_clean(&(*game)->pMenu);
        (*game)->pMenu = NULL;
    }

    if(Vector_empty(&(*game)->vecMusic) == false) {
        SoundManager_cleanMusic(&(*game)->vecMusic);
    }
    Vector_clean(&(*game)->vecMusic);

    Mix_CloseAudio();
    SDL_Quit();
    TTF_Quit();

    free(*game);
    *game = NULL;
}

void _Game_draw(tGame* game, int marginDraw) {
    SDL_RenderClear(game->renderer);

    Maze_draw(game->maze, marginDraw);

    SDL_RenderPresent(game->renderer);
}

void _Game_update(tGame* game) {

}

 void Game_running(tGame* game) {
    int state = OK;
    bool turn = false;
    char ghostKill = 'X';
    game->running = Menu_running(game->pMenu, game->name);
    if(game->running == true) {
        SDL_SetWindowSize(game->window, Maze_getColumns(game->maze) * WIDTH, Maze_getRows(game->maze) * HEIGTH + MARGIN_TOP);
        SDL_SetWindowPosition(game->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SoundManager_playMusic(&game->vecMusic, "musicGame");
        Mix_VolumeMusic(5);
    }
    while (game->running && state != LOST && state != VICTORY) {
        state = OK;
        if(turn == false) {
            _Game_handleEvents(game, true);
        } else {
            state = Maze_check(game->maze);
        }

        if(state != OK) {
            Cola_clean(&game->colaTurn);
        }

        if(state == LOST_LIVE) {
            Cola_put(&game->colaMovement, &ghostKill, sizeof(char));
        }

        turn = Maze_update(game->maze, &game->colaTurn);

        _Game_draw(game, 0);

        SDL_Delay(16);
    }

    if(state == VICTORY) {
        puts("Ganaste papu esc para salir");
        Mix_HaltMusic();
        SoundManager_playMusic(&game->vecMusic, "musicVictory");
        SDL_Delay(800);
        Maze_resetPlayer(game->maze);
        while(game->running) {
            _Game_handleEvents(game, false);
            _Game_draw(game, VICTORY);
            Maze_recreateGame(game->maze, &game->colaMovement);
            SDL_Delay(216);
        }
    }

    if(state == LOST) {
        puts("Perdiste papu esc para salir");
        Mix_HaltMusic();
        Mix_VolumeMusic(15);
        SoundManager_playMusic(&game->vecMusic, "musicLost");
        SDL_Delay(800);
        Maze_resetPlayer(game->maze);
        while(game->running) {
            _Game_handleEvents(game, false);
            _Game_draw(game, LOST);
            Maze_recreateGame(game->maze, &game->colaMovement);
            SDL_Delay(216);
        }
    }
 }

 void _Game_handleEvents(tGame* game, bool isGame) {
    while(SDL_PollEvent(&game->event)) {
        switch (game->event.type) {
        case SDL_QUIT:
            puts("Enter para salir");
            game->running = false;
            break;
        case SDL_KEYDOWN:
            switch (game->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                puts("Enter para salir");
                game->running = false;
                break;
            default:
                break;
            }
        }
        if(game->running == true && isGame == true) {
            Maze_handleEvents(game->maze, &game->event, &game->colaTurn, &game->colaMovement);
        }
    }
}
