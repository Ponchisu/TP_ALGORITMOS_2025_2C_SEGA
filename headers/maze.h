#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../headers/bool.h"
#include "../headers/matrix.h"
#include "../headers/textureManager.h"
#include "../headers/player.h"
#include "../headers/ghost.h"
#include "../headers/vector.h"

#define FILE_NAME "maze.txt"

typedef struct
{
    SDL_Renderer* render;
    char** maze;
    int rows;
    int columns;
    tPlayer player;
    Vector vecTex;
}tMaze;

bool Maze_create(tMaze** pMaze, int rows, int columns, SDL_Renderer* render);
void Maze_clean(tMaze** pMaze, int rows);
void Maze_draw(tMaze* pMaze);
bool Maze_handleEvents(tMaze* pMaze, SDL_Event* event);

#endif // MAZE_H_INCLUDED
