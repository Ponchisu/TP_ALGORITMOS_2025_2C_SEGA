#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include <stdlib.h>

#include "../headers/bool.h"
#include "../headers/matrix.h"
#include "../headers/textureManager.h"
#include "../headers/player.h"
#include "../headers/ghost.h"
#include "../headers/vector.h"
#include "../headers/cola.h"
#include "../headers/movement.h"
#include "../headers/awards.h"
#include "../headers/lives.h"
#include "../headers/margin.h"
#include "../headers/soundManager.h"
#include "../headers/key.h"

#define FILE_NAME "maze.txt"

#define OK 0
#define LOST_LIVE 1
#define ADD_LIVE 2
#define LOST 3
#define GET_AWARD 4
#define VICTORY 5

#define SIZE_VECTEX 9
#define SIZE_VECCHUNK 5

#define SIZE_VECKEYS 3

typedef struct
{
    SDL_Renderer* renderer;
    char** maze;
    int rows;
    int columns;
    int points;
    tPlayer player;
    tVector vecGhost;
    tVector vecTex;
    tVector vecLives;
    tVector vecAwards;
    tVector vecChunk;
    tVector vecKeys;
    int keys;
    tMargin margin;
}tMaze;

typedef bool (*Elem_isAlive)(const void* elem);
typedef bool (*Elem_getY)(const void* elem);
typedef bool (*Elem_getX)(const void* elem);

bool Maze_create(tMaze** pMaze, SDL_Renderer* renderer, int rows, int columns, int numLives, int numGhost, int numAwards, int maxLives, bool rei);
void Maze_clean(tMaze** pMaze);
void Maze_draw(tMaze* pMaze, int marginDraw);
void Maze_handleEvents(tMaze* pMaze, SDL_Event* event, tCola* colaTurn, tCola* colaMovement);
bool Maze_update(tMaze* pMaze, tCola* colaTurn);
int Maze_check(tMaze* pMaze);
int Maze_getColumns(tMaze* pMaze);
int Maze_getRows(tMaze* pMaze);
void Maze_resetPlayer(tMaze* pMaze);
void Maze_recreateGame(tMaze* pMaze, tCola* pColaMovement);

#endif // MAZE_H_INCLUDED
