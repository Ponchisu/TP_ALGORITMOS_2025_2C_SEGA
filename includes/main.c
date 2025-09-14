#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../headers/game.h"

int main(int argc, char* argv[]) {
    Game* game;

    gameCreate(&game);
    if(!gameInit(game, 10, 10)) {
        gameClean(&game);
        return 0;
    }

    gameRunning(game);

    gameClean(&game);
    return 0;
}
