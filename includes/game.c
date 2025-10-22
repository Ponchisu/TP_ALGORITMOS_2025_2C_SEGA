#include "../headers/game.h"

void _Game_handleEvents(tGame* game, bool isGame);
void _Game_draw(tGame* game);
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
    SDL_Surface* icon;

    game->maze = NULL;
    game->renderer = NULL;
    game->window = NULL;
    game->colaMovement = NULL;
    game->colaTurn = NULL;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return false;
    }

    if(!Config_getParametersFromFile(&rows, &columns, &numLive, &numGhosts, &numAwards, &maxLives)) {
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        return false;
    }

    game->window = SDL_CreateWindow("Maze and Ghost", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, columns * WIDTH, rows * HEIGTH + MARGIN_TOP, 0);
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

    if(!Maze_create(&game->maze, game->renderer, rows, columns, numLive, numGhosts, numAwards, maxLives)) {
        return false;
    }


    game->music = Mix_LoadMUS("sound/music.mp3");
    if(game->music == NULL) {
        fprintf(stderr, "Error al cargar cancion: %s\n", Mix_GetError());
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

    Mix_FreeMusic((*game)->music);

    Mix_CloseAudio();
    SDL_Quit();

    free(*game);
    *game = NULL;
}

void _Game_draw(tGame* game) {
    SDL_RenderClear(game->renderer);

    Maze_draw(game->maze);

    SDL_RenderPresent(game->renderer);
}

void _Game_update(tGame* game) {

}

 void Game_running(tGame* game) {
    int state = OK;
    bool turn = false;
    Mix_PlayMusic(game->music, -1);
    Mix_VolumeMusic(5); 
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

        turn = Maze_update(game->maze, &game->colaTurn);

        _Game_draw(game);

        SDL_Delay(16);
    }

    if(state == VICTORY) {
        puts("Ganaste papu esc para salir");
        Mix_HaltMusic(); 
        while(game->running) {
            _Game_handleEvents(game, false);
            _Game_draw(game);
            SDL_Delay(16);
        }
    }

    if(state == LOST) {
        puts("Perdiste papu esc para salir");
        Mix_HaltMusic(); 
        while(game->running) {
            _Game_handleEvents(game, false);
            _Game_draw(game);
            SDL_Delay(16);
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
