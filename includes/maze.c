#include "../headers/maze.h"

bool _Maze_checkWallCollision(tMaze* pMaze, int xPos, int yPos);
void _Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn);

bool Maze_create(tMaze** pMaze, SDL_Renderer* render, int rows, int columns, int numLives, int numGhosts, int numAwards, int maxLives) {
    tGhost ghost;
    char idGhost[10];
    char idNum[10];
    int id = 0;

    *pMaze = (tMaze*)malloc(sizeof(tMaze));
    if(*pMaze == NULL) {
        fprintf(stderr, "Error al crear laberinto\n");
        return false;
    }

    (*pMaze)->rows = rows;
    (*pMaze)->columns = columns;
    (*pMaze)->render = render;
    (*pMaze)->numGhosts = numGhosts;

    (*pMaze)->maze = (char**)Matrix_create(rows, columns, sizeof(char));
    if((*pMaze)->maze == NULL) {
        fprintf(stderr, "Error al crear matriz de laberinto\n");
        return false;
    }

    if(!Matrix_loadFromFileTxt((void**)(*pMaze)->maze, rows, columns, FILE_NAME, MatrixAction_loadChar)) {
        fprintf(stderr, "Error al cargar matriz de laberinto\n");
        return false;
    }


    if(!Vector_create(&(*pMaze)->vecTex, sizeof(tTexture), SIZE_VECTEX)) {
        fprintf(stderr, "Error al crear vector\n");
        return false;
    }

    if(!Vector_create(&(*pMaze)->vecGhost, sizeof(tGhost), numGhosts)) {
        fprintf(stderr, "Error al crear vector de Fantasmas\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/entrada32x32.png", "entrada", render)) {
        fprintf(stderr, "Error al cargar imagen Entrada\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/salida32x32.png", "salida", render)) {
        fprintf(stderr, "Error al cargar imagen Salida\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/personaje32.png", "player", render)) {
        fprintf(stderr, "Error al cargar imagen Player\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/suelo32x32.png", "suelo", render)) {
        fprintf(stderr, "Error al cargar imagen Suelo\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/pared32x32.png", "pared", render)) {
        fprintf(stderr, "Error al cargar imagen Pared\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/fantasma32.png", "ghost", render)) {
        fprintf(stderr, "Error al cargar imagen Fantasma\n");
        return false;
    }

    for (int i = 0; i < (*pMaze)->rows; i++) {
        for (int j = 0; j < (*pMaze)->columns; j++) {
            if ((*pMaze)->maze[i][j] == 'F') {
                strcpy(idGhost, "ghost");
                sprintf(idNum, "%d", id);
                strcat(idGhost, idNum);
                Ghost_create(&ghost, i, j, idGhost);
                if(!Vector_insertInOrder(&(*pMaze)->vecGhost, &ghost, Ghost_cmp, NULL)){
                    return false;
                }
                id++;
                (*pMaze)->maze[i][j] = '.';
            }
            if ((*pMaze)->maze[i][j] == 'E') {
                playerCreate(&(*pMaze)->player, i, j, numLives);
            }
        }
    }

    Matriz_show((*pMaze)->maze, rows, columns);

    return true;
}

void Maze_clean(tMaze** pMaze) {
    Matrix_clean((void**)(*pMaze)->maze, (*pMaze)->rows);

    Vector_clean(&(*pMaze)->vecTex);
    Vector_clean(&(*pMaze)->vecGhost);

    free(*pMaze);
}

void Maze_draw(tMaze* pMaze) {
    int cant = pMaze->numGhosts;
    char idNum[25];
    tGhost ghost;

    for (int rows = 0; rows < pMaze->rows; rows++) {
        for (int col = 0; col < pMaze->columns; col++) {
            if (pMaze->maze[rows][col] == '#') {
                TextureManager_Draw(&pMaze->vecTex, "pared", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == '.') {
                TextureManager_Draw(&pMaze->vecTex, "suelo", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == 'E') {
                TextureManager_Draw(&pMaze->vecTex, "entrada", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == 'S') {
                TextureManager_Draw(&pMaze->vecTex, "salida", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == 'F') {
                TextureManager_Draw(&pMaze->vecTex, "suelo", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
        }
        TextureManager_Draw(&pMaze->vecTex, "player", pMaze->player.y * HEIGTH,  pMaze->player.x * WIDTH, pMaze->render);
        for(int i = 0; i < cant; i++) {
            strcpy(ghost.id, "ghost");
            sprintf(idNum, "%d", i);
            strcat(ghost.id, idNum);
            Vector_bsearch(&pMaze->vecGhost, &ghost, Ghost_cmp);
            TextureManager_Draw(&pMaze->vecTex, "ghost", ghost.y * HEIGTH, ghost.x * WIDTH, pMaze->render);
        }
    }
}

void Maze_handleEvents(tMaze* pMaze, SDL_Event* event, tCola* colaTurn, tCola* colaMovement) {
    tMovement move;
    strcpy(move.id, "player");

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_RIGHT:
        case SDLK_d:
            if(Cola_empty(colaTurn) == true && !_Maze_checkWallCollision(pMaze, pMaze->player.x + 1, pMaze->player.y)) {
                move.movement = 'R';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &move.movement, sizeof(char));
                _Maze_ghostMovement(pMaze, colaTurn);
            }
            break;
        case SDLK_LEFT:
        case SDLK_a:
            if(Cola_empty(colaTurn) == true && !_Maze_checkWallCollision(pMaze, pMaze->player.x - 1, pMaze->player.y)) {
                move.movement = 'L';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &move.movement, sizeof(char));
                _Maze_ghostMovement(pMaze, colaTurn);
            }
            break;
        case SDLK_DOWN:
        case SDLK_s:
            if(Cola_empty(colaTurn) == true && !_Maze_checkWallCollision(pMaze, pMaze->player.x, pMaze->player.y + 1)) {
                move.movement = 'D';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &move.movement, sizeof(char));
                _Maze_ghostMovement(pMaze, colaTurn);
            }
            break;
        case SDLK_UP:
        case SDLK_w:
            if(Cola_empty(colaTurn) == true && !_Maze_checkWallCollision(pMaze, pMaze->player.x, pMaze->player.y - 1)) {
                move.movement = 'U';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &move.movement, sizeof(char));
                _Maze_ghostMovement(pMaze, colaTurn);
            }
            break;
        default:
            break;
        }
    }
}

void _Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn) {
    int cant = pMaze->numGhosts;
    char idNum[25];
    tGhost ghost;
    tMovement move;
    int xDist;
    int yDist;
    
    for(int i = 0; i < cant; i++) {
            strcpy(ghost.id, "ghost");
            sprintf(idNum, "%d", i);
            strcat(ghost.id, idNum);
            Vector_bsearch(&pMaze->vecGhost, &ghost, Ghost_cmp);

            strcpy(move.id, ghost.id);

            xDist = abs(pMaze->player.x - ghost.x);
            yDist = abs(pMaze->player.y - ghost.y);

            if (xDist > yDist) {
                if (pMaze->player.x < ghost.x) {
                    move.movement = 'L';
                }
                else {
                    move.movement = 'R';
                }
            }
            else {
                if (pMaze->player.y < ghost.y) {
                    move.movement = 'U';
                }
                else {
                    move.movement = 'D';
                }
            }
        Cola_put(colaTurn, &move, sizeof(tMovement));
    }
}

bool Maze_update(tMaze* pMaze, tCola* colaTurn) {
    tMovement move;
    tGhost ghost;

    if(Cola_takeOut(colaTurn, &move, sizeof(tMovement)) == false) {
        return false;
    }

    if(strcmp(move.id, "player") == 0) {
        Player_movement(&pMaze->player, move.movement);
        return true;
    }

    strcpy(ghost.id, move.id);

    Vector_bsearch(&pMaze->vecGhost, &ghost, Ghost_cmp);

    Ghost_movement(&ghost, move.movement);

    Vector_Update(&pMaze->vecGhost, &ghost, Ghost_cmp, Ghost_Update);

    return false;
}

int Maze_check(tMaze* pMaze) {

    // chequear si el player toco un fantasma, OK si no toco
    // si se toca un fantasma, el player volvera a la posIni, se restara una vida, se "matara" al fantasma tocado y se devolvera LOST_LIVE
    // si el player es tocado y tiene 0 vidas se devuelve LOST y se da por perdido
    // for (int i = 0; i <= pMaze->vecGhost.lotElem; i++){
    //     if (g)
    // }
    
    return OK;
}


bool _Maze_checkWallCollision(tMaze* pMaze, int xPos, int yPos) {
    if (yPos < 0) {
        return true;
    }
    if (yPos > pMaze->rows - 1) {
        return true;
    }
    if (pMaze->maze[yPos][xPos] == '#') {
        return true;
    }
    return false;
}