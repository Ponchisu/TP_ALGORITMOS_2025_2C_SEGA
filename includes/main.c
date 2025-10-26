#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/game.h"

int main(void) {
    tGame* game;
    srand(time(NULL));

    Game_create(&game);
    if(!Game_init(game)) {
        Game_clean(&game);
        return 0;
    }

    Game_running(game);

    Game_clean(&game);
    return 0;
}
