#include "../headers/game.h"

void Game_handleEvents(tGame* game);
void Game_draw(tGame* game);
void Game_update(tGame* game);

bool Game_create(tGame** game) {
    *game = (tGame*)malloc(sizeof(tGame));
    if(*game == NULL) {
        return false;
    }

    return true;
}

bool Game_init(tGame* game, int rows, int columns) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return false;
    }

    game->window = SDL_CreateWindow("Maze and Ghost", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, columns * WIDTH, rows * HEIGTH + 50, 0);
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

    if(!Maze_create(&game->maze, rows, columns, game->renderer)) {
        return false;
    }

    SDL_Surface* icon = IMG_Load("assets/icon.jpg");
    if(!icon) {
        fprintf(stderr, "Error al cargar icono: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetWindowIcon(game->window, icon);
    SDL_FreeSurface(icon);
    icon = NULL;

    game->running = true;

    return true;
}

void Game_clean(tGame** game) {
    if ((*game)->maze)
        Maze_clean(&(*game)->maze, (*game)->maze->rows);

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

void Game_draw(tGame* game) {
    SDL_RenderClear(game->renderer);

    Maze_draw(game->maze);

    SDL_RenderPresent(game->renderer);
}

void Game_update(tGame* game) {

}

 void Game_running(tGame* game) {
    while (game->running) {
        Game_handleEvents(game);

        Game_draw(game);

        SDL_Delay(16);
    }
 }

 void Game_handleEvents(tGame* game) {
    if(!Maze_handleEvents(game->maze)) {
        game->running = false;
    }
 }
