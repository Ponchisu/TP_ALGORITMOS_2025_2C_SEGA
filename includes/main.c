#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../headers/game.h"

int main(void) {
    tGame* game;

    Game_create(&game);
    if(!Game_init(game, 10, 10)) {
        Game_clean(&game);
        return 0;
    }

    Game_running(game);

    Game_clean(&game);
    return 0;
}
