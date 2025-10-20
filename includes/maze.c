#include "../headers/maze.h"

bool _Maze_checkWallCollision(tMaze* pMaze, int xPos, int yPos);
void _Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn);

bool Maze_create(tMaze** pMaze, SDL_Renderer* render, int rows, int columns, int numLives, int numGhosts, int numAwards, int maxLives) {
    tGhost ghost;
    tAwards award;
    tLives live;
    char id[10];
    char idNum[10];
    int idGhost = 0;
    int idAwards = 0;
    int idLives = 0;

    *pMaze = (tMaze*)malloc(sizeof(tMaze));
    if(*pMaze == NULL) {
        fprintf(stderr, "Error al crear laberinto\n");
        return false;
    }

    (*pMaze)->rows = rows;
    (*pMaze)->columns = columns;
    (*pMaze)->render = render;
    (*pMaze)->numGhosts = numGhosts;
    (*pMaze)->numAwards = numAwards;
    (*pMaze)->numLives = maxLives;

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

    if(!Vector_create(&(*pMaze)->vecAwards, sizeof(tAwards), numAwards)) {
        fprintf(stderr, "Error al crear vector de Fantasmas\n");
        return false;
    }

    if(!Vector_create(&(*pMaze)->vecLives, sizeof(tLives), maxLives)) {
        fprintf(stderr, "Error al crear vector de Fantasmas\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/starter.png", "starter", render)) {
        fprintf(stderr, "Error al cargar imagen Entrada\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/exit.png", "exit", render)) {
        fprintf(stderr, "Error al cargar imagen Salida\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/player.png", "player", render)) {
        fprintf(stderr, "Error al cargar imagen Player\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/floor.png", "floor", render)) {
        fprintf(stderr, "Error al cargar imagen Suelo\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/wall.png", "wall", render)) {
        fprintf(stderr, "Error al cargar imagen Pared\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/ghost.png", "ghost", render)) {
        fprintf(stderr, "Error al cargar imagen Fantasma\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/heart.png", "heart", render)) {
        fprintf(stderr, "Error al cargar imagen Fantasma\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/award.png", "award", render)) {
        fprintf(stderr, "Error al cargar imagen Fantasma\n");
        return false;
    }

    for (int i = 0; i < (*pMaze)->rows; i++) {
        for (int j = 0; j < (*pMaze)->columns; j++) {
            if ((*pMaze)->maze[i][j] == 'G') {
                strcpy(id, "ghost");
                sprintf(idNum, "%d", idGhost);
                strcat(id, idNum);
                Ghost_create(&ghost, i, j, id);
                if(!Vector_insertInOrder(&(*pMaze)->vecGhost, &ghost, Ghost_cmp, NULL)) {
                    return false;
                }
                idGhost++;
                (*pMaze)->maze[i][j] = '.';
            } else if((*pMaze)->maze[i][j] == 'A') {
                strcpy(id, "award");
                sprintf(idNum, "%d", idAwards);
                strcat(id, idNum);
                Awards_create(&award, i, j, id);
                if(!Vector_insertInOrder(&(*pMaze)->vecAwards, &award, Awards_cmp, NULL)) {
                    return false;
                }
                idAwards++;
                (*pMaze)->maze[i][j] = '.';
            } else if((*pMaze)->maze[i][j] == 'H') {
                strcpy(id, "live");
                sprintf(idNum, "%d", idLives);
                strcat(id, idNum);
                Lives_create(&live, i, j, id);
                if(!Vector_insertInOrder(&(*pMaze)->vecLives, &live, Lives_cmp, NULL)) {
                    puts("a");
                    return false;
                }
                idLives++;
                (*pMaze)->maze[i][j] = '.';
            } else if ((*pMaze)->maze[i][j] == 'E') {
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
    Vector_clean(&(*pMaze)->vecAwards);
    Vector_clean(&(*pMaze)->vecLives);

    free(*pMaze);
}

void Maze_draw(tMaze* pMaze) {
    char idNum[25];
    tGhost ghost;
    tAwards award;
    tLives live;

    for (int rows = 0; rows < pMaze->rows; rows++) {
        for (int col = 0; col < pMaze->columns; col++) {
            if (pMaze->maze[rows][col] == '#') {
                TextureManager_Draw(&pMaze->vecTex, "wall", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == '.') {
                TextureManager_Draw(&pMaze->vecTex, "floor", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == 'E') {
                TextureManager_Draw(&pMaze->vecTex, "wall", rows * HEIGTH, col * WIDTH, pMaze->render);
                TextureManager_Draw(&pMaze->vecTex, "starter", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == 'S') {
                TextureManager_Draw(&pMaze->vecTex, "floor", rows * HEIGTH, col * WIDTH, pMaze->render);
                TextureManager_Draw(&pMaze->vecTex, "exit", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == 'F') {
                TextureManager_Draw(&pMaze->vecTex, "floor", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == 'P') {
                TextureManager_Draw(&pMaze->vecTex, "floor", rows * HEIGTH, col * WIDTH, pMaze->render);
                TextureManager_Draw(&pMaze->vecTex, "award", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
            if (pMaze->maze[rows][col] == 'H') {
                TextureManager_Draw(&pMaze->vecTex, "floor", rows * HEIGTH, col * WIDTH, pMaze->render);
                TextureManager_Draw(&pMaze->vecTex, "heart", rows * HEIGTH, col * WIDTH, pMaze->render);
            }
        }
        TextureManager_Draw(&pMaze->vecTex, "player", Player_getY(&pMaze->player) * HEIGTH,  Player_getX(&pMaze->player) * WIDTH, pMaze->render);
        for(int i = 0; i < pMaze->numGhosts; i++) {
            strcpy(ghost.id, "ghost");
            sprintf(idNum, "%d", i);
            strcat(ghost.id, idNum);
            Vector_bsearch(&pMaze->vecGhost, &ghost, Ghost_cmp);

            if(Ghost_isAlive(&ghost) == true) {
                TextureManager_Draw(&pMaze->vecTex, "ghost", Ghost_getY(&ghost) * HEIGTH, Ghost_getX(&ghost) * WIDTH, pMaze->render);
            }
        }
        for(int i = 0; i < pMaze->numAwards; i++) {
            strcpy(award.id, "award");
            sprintf(idNum, "%d", i);
            strcat(award.id, idNum);
            Vector_bsearch(&pMaze->vecAwards, &award, Awards_cmp);
            TextureManager_Draw(&pMaze->vecTex, "award", Awards_getY(&award) * HEIGTH, Awards_getX(&award) * WIDTH, pMaze->render);
        }
        for(int i = 0; i < pMaze->numLives; i++) {
            strcpy(live.id, "live");
            sprintf(idNum, "%d", i);
            strcat(live.id, idNum);
            Vector_bsearch(&pMaze->vecLives, &live, Lives_cmp);
            TextureManager_Draw(&pMaze->vecTex, "heart", Lives_getY(&live) * HEIGTH, Lives_getX(&live) * WIDTH, pMaze->render);
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
    int playerX;
    int playerY;
    int ghostX;
    int ghostY;

    playerX = Player_getX(&pMaze->player);
    playerY = Player_getY(&pMaze->player);

    for(int i = 0; i < cant; i++) {
            strcpy(ghost.id, "ghost");
            sprintf(idNum, "%d", i);
            strcat(ghost.id, idNum);
            Vector_bsearch(&pMaze->vecGhost, &ghost, Ghost_cmp);

            ghostX = Ghost_getX(&ghost);
            ghostY = Ghost_getY(&ghost);

            if(Ghost_isAlive(&ghost) == true) {
                strcpy(move.id, ghost.id);

                xDist = abs(playerX - ghostX);
                yDist = abs(playerY - ghostY);

                if (xDist > yDist) {
                    if (playerX < ghostX) {
                        move.movement = 'L';
                    }
                    else {
                        move.movement = 'R';
                    }
                }
                else {
                    if (playerY < ghostY) {
                        move.movement = 'U';
                    }
                    else {
                        move.movement = 'D';
                    }
                }
                Cola_put(colaTurn, &move, sizeof(tMovement));
            }
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

    return true;
}

int Maze_check(tMaze* pMaze) {
    int playerX;
    int playerY;
    int ghostX;
    int ghostY;
    int lives;
    tGhost ghost;
    char idNum[25];
    int _return = OK;
    int i = 0;

    playerX = Player_getX(&pMaze->player);
    playerY = Player_getY(&pMaze->player);
    lives = Player_getLives(&pMaze->player);

    while(i <=  pMaze->numGhosts && _return == OK) {
        strcpy(ghost.id, "ghost");
        sprintf(idNum, "%d", i);
        strcat(ghost.id, idNum);
        Vector_bsearch(&pMaze->vecGhost, &ghost, Ghost_cmp);
        if(Ghost_isAlive(&ghost) == true) {
            ghostX = Ghost_getX(&ghost);
            ghostY = Ghost_getY(&ghost);

            if(ghostX == playerX && ghostY == playerY) {
                _return = LOST_LIVE;
            }
        }

        i++;
    }

    if(_return == LOST_LIVE) {
        SDL_Delay(200);
        if(lives != 0) {
            Player_lostLives(&pMaze->player);
            Ghost_delete(&ghost);
            Vector_Update(&pMaze->vecGhost, &ghost, Ghost_cmp, Ghost_Update);
            Player_resetPos(&pMaze->player);
        } else 
            _return = LOST;
    }

    return _return;
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
