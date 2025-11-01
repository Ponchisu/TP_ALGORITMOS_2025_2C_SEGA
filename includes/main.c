#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/menu.h"

int main(void) {
    tMenu* menu;
    srand(time(NULL));

    system("mkdir files");
    system("start ./bin/Debug/DataBase.exe");
    SDL_Delay(1000);

    if(!Menu_create(&menu)) {
        Menu_clean(&menu);
        return 0;
    }

    Menu_running(menu);

    Menu_clean(&menu);
    return 0;
}
