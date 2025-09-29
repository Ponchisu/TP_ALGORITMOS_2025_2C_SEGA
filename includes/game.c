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

bool Game_init(tGame* game) {
    int rows, columns, numLive, numGhost, numAwards, maxLives;
    SDL_Surface* icon;

    game->maze = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return false;
    }

    if(!Config_getParametersFromFile(&rows, &columns, &numLive, &numGhost, &numAwards, &maxLives)) {
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
    if ((*game)->maze) {
        Maze_clean(&(*game)->maze);
    }

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
    int state = OK;
    while (game->running && state != LOST) {
        Game_handleEvents(game);

        Maze_ghostMovement(game->maze, &game->colaTurn); // verifica si el primer movimiento de la cola es del player, si lo es, mueve a los fantasmas

        if(Maze_update(game->maze, &game->colaTurn) == true) { // desencola el movimiento y lo ejecura
            state = Maze_check(game->maze); // comprueba si el player toco a un fantasma
        }

        if(state != OK) { // si el player toco a un fantasma se vacia la cola
            Cola_clean(&game->colaTurn); 
        }

        Game_draw(game);

        SDL_Delay(16);
    }
 }

 void Game_handleEvents(tGame* game) {
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
        if(game->running == true) {
            Maze_handleEvents(game->maze, &game->event, &game->colaTurn, &game->colaMovement);
        }
    }
}
