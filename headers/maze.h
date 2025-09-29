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
#include "../headers/cola.h"
#include "../headers/movement.h"

#define FILE_NAME "maze.txt"

#define OK 0
#define LOST_LIVE 1
#define LOST 2

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
void Maze_clean(tMaze** pMaze);
void Maze_draw(tMaze* pMaze);
void Maze_handleEvents(tMaze* pMaze, SDL_Event* event, tCola* colaTurn, tCola* colaMovement);
void Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn);
bool Maze_update(tMaze* pMaze, tCola* colaTurn);
int Maze_check(tMaze* pMaze);

#endif // MAZE_H_INCLUDED
