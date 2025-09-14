#include "../headers/game.h"

void gameEvent(Game* game);
void gameDraw(Game* game);
void gameUpdate(Game* game);

bool gameCreate(Game** game) {
    *game = (Game*)malloc(sizeof(Game));
    if(*game == NULL) {
        return false;
    }

    return true;
}

bool gameInit(Game* game, int filas, int columnas) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return false;
    }

    game->window = SDL_CreateWindow("Laberinto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, columnas * ANCHO, filas * ALTO + 50, 0);
    if(!game->window) {
        fprintf(stderr, "Error al crear window: %s\n", SDL_GetError());
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if(!game->renderer) {
        fprintf(stderr, "Error al crear renderer: %s\n", SDL_GetError());
        return false;
    }

    if(!laberintoCreate(&game->laberinto, filas, columnas, game->renderer)) {
        return false;
    }

    SDL_Surface* icon = IMG_Load("assets/icon.jpg");
    if(icon == NULL) {
        fprintf(stderr, "Error al cargar icono: %s", SDL_GetError());
        return false;
    }

    SDL_SetWindowIcon(game->window, icon);
    SDL_FreeSurface(icon);
    icon = NULL;

    game->running = true;

    return true;
}

void gameClean(Game** game) {
    laberintoClean(&(*game)->laberinto, (*game)->laberinto->filas);

    if((*game)->renderer) {
        SDL_DestroyRenderer((*game)->renderer);
        (*game)->renderer = NULL;
    }
    if((*game)->window) {
        SDL_DestroyWindow((*game)->window);
        (*game)->window = NULL;
    }

    SDL_Quit();

    free(*game);
    *game = NULL;
}

void gameEvent(Game* game) {
    while(SDL_PollEvent(&game->event)) {
        switch (game->event.type) {
        case SDL_QUIT:
            game->running = false;
            break;
        case SDL_KEYDOWN:
            switch (game->event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                game->running = false;
                break;
            default:
                break;
            }
            break;
        }
    }
}

void gameDraw(Game* game) {
    SDL_RenderClear(game->renderer);

    laberintoDraw(game->laberinto);

    SDL_RenderPresent(game->renderer);
}

void gameUpdate(Game* game) {
    
}

 void gameRunning(Game* game) {
    while (game->running) {
        gameEvent(game);

        gameDraw(game);

        SDL_Delay(16);
    }
 }
