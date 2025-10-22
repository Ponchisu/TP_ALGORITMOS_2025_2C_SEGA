#include "../headers/maze.h"

bool _Maze_checkWallCollision(tMaze* pMaze, int xPos, int yPos);
void _Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn);
void _Maze_drawElem(tVector* pVec, tVector* pVecTex, SDL_Renderer* pRender, const char* id, unsigned tamElem, Elem_isAlive _Elem_isAlive, Elem_getY _Elem_getY, Elem_getX _Elem_getX);

bool Maze_create(tMaze** pMaze, SDL_Renderer* renderer, int rows, int columns, int numLives, int numGhosts, int numAwards, int maxLives) {
    tGhost ghost;
    tAwards award;
    tLives live;
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
    (*pMaze)->renderer = renderer;
    (*pMaze)->points = 0;


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

    if(!Margin_create(&(*pMaze)->margin, numLives, columns, renderer)) {
        fprintf(stderr, "Error al crear margin\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/starter.png", "starter", renderer)) {
        fprintf(stderr, "Error al cargar imagen Entrada\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/exit.png", "exit", renderer)) {
        fprintf(stderr, "Error al cargar imagen Salida\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/player.png", "player", renderer)) {
        fprintf(stderr, "Error al cargar imagen Player\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/floor.png", "floor", renderer)) {
        fprintf(stderr, "Error al cargar imagen Suelo\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/wall.png", "wall", renderer)) {
        fprintf(stderr, "Error al cargar imagen Pared\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/ghost.png", "ghost", renderer)) {
        fprintf(stderr, "Error al cargar imagen Fantasma\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/heart.png", "heart", renderer)) {
        fprintf(stderr, "Error al cargar imagen Fantasma\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/award.png", "award", renderer)) {
        fprintf(stderr, "Error al cargar imagen Fantasma\n");
        return false;
    }

    for (int i = 0; i < (*pMaze)->rows; i++) {
        for (int j = 0; j < (*pMaze)->columns; j++) {
            if ((*pMaze)->maze[i][j] == 'G') {
                Ghost_create(&ghost, i, j, "");
                Ghost_numId(&ghost, idGhost);
                if(!Vector_insertInOrder(&(*pMaze)->vecGhost, &ghost, Ghost_cmp, NULL)) {
                    return false;
                }
                idGhost++;
                (*pMaze)->maze[i][j] = '.';
            } else if((*pMaze)->maze[i][j] == 'A') {
                Awards_create(&award, i, j, "");
                Awards_numIde(&award, idAwards);
                if(!Vector_insertInOrder(&(*pMaze)->vecAwards, &award, Awards_cmp, NULL)) {
                    return false;
                }
                idAwards++;
                (*pMaze)->maze[i][j] = '.';
            } else if((*pMaze)->maze[i][j] == 'H') {
                Lives_create(&live, i, j, "");
                Lives_numId(&live, idLives);
                if(!Vector_insertInOrder(&(*pMaze)->vecLives, &live, Lives_cmp, NULL)) {
                    return false;
                }
                idLives++;
                (*pMaze)->maze[i][j] = '.';
            } else if ((*pMaze)->maze[i][j] == 'S') {
                playerCreate(&(*pMaze)->player, i, j, numLives);
            } else if((*pMaze)->maze[i][j] == 'E') {
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
    Margin_clean(&(*pMaze)->margin);

    free(*pMaze);
}

void _Maze_drawElem(tVector* pVec, tVector* pVecTex, SDL_Renderer* pRender, const char* id, unsigned tamElem, Elem_isAlive _Elem_isAlive, Elem_getY _Elem_getY, Elem_getX _Elem_getX) {
    tVectorIterator vecIter;
    void* elem = malloc(tamElem);

    VectorIterator_create(&vecIter, pVec);

    VectorIterator_first(&vecIter, elem);
    while(!VectorIterator_finished(&vecIter)) {
        if(_Elem_isAlive(elem) == true) {
            TextureManager_Draw(pVecTex, id, _Elem_getY(elem) * HEIGTH + MARGIN_TOP, _Elem_getX(elem) * WIDTH,  WIDTH, HEIGTH, pRender);
        }
        VectorIterator_next(&vecIter, elem);
    }
    free(elem);
}

void Maze_draw(tMaze* pMaze) {
    Margin_draw(&pMaze->margin, pMaze->renderer);
    for (int rows = 0; rows < pMaze->rows; rows++) {
        for (int col = 0; col < pMaze->columns; col++) {
            if (pMaze->maze[rows][col] == '#') {
                TextureManager_Draw(&pMaze->vecTex, "wall", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
            if (pMaze->maze[rows][col] == '.') {
                TextureManager_Draw(&pMaze->vecTex, "floor", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
            if (pMaze->maze[rows][col] == 'S') {
                TextureManager_Draw(&pMaze->vecTex, "wall", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
                TextureManager_Draw(&pMaze->vecTex, "starter", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
            if (pMaze->maze[rows][col] == 'E') {
                TextureManager_Draw(&pMaze->vecTex, "floor", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
                TextureManager_Draw(&pMaze->vecTex, "exit", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
            if (pMaze->maze[rows][col] == 'F') {
                TextureManager_Draw(&pMaze->vecTex, "floor", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
        }
        TextureManager_Draw(&pMaze->vecTex, "player", Player_getY(&pMaze->player) * HEIGTH + 32,  Player_getX(&pMaze->player) * WIDTH, WIDTH, HEIGTH, pMaze->renderer);

        _Maze_drawElem(&pMaze->vecGhost, &pMaze->vecTex, pMaze->renderer, "ghost", sizeof(tGhost), Ghost_isAlive, Ghost_getY, Ghost_getX);
        _Maze_drawElem(&pMaze->vecAwards, &pMaze->vecTex, pMaze->renderer, "award", sizeof(tAwards), Awards_isAlive, Awards_getY, Awards_getX);
        _Maze_drawElem(&pMaze->vecLives, &pMaze->vecTex, pMaze->renderer, "heart", sizeof(tLives), Lives_isAlive, Lives_getY, Lives_getX);
    }
}

void Maze_handleEvents(tMaze* pMaze, SDL_Event* event, tCola* colaTurn, tCola* colaMovement) {
    tMovement move;
    strcpy(move.id, "player");
    char moveChar;

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_RIGHT:
        case SDLK_d:
            if(Cola_empty(colaTurn) == true && !_Maze_checkWallCollision(pMaze, pMaze->player.x + 1, pMaze->player.y)) {
                move.vecX = 1;
                move.vecY = 0;
                moveChar = 'R';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &moveChar, sizeof(char));
                _Maze_ghostMovement(pMaze, colaTurn);
            }
            break;
        case SDLK_LEFT:
        case SDLK_a:
            if(Cola_empty(colaTurn) == true && !_Maze_checkWallCollision(pMaze, pMaze->player.x - 1, pMaze->player.y)) {
                move.vecX = -1;
                move.vecY = 0;
                moveChar = 'L';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &moveChar, sizeof(char));
                _Maze_ghostMovement(pMaze, colaTurn);
            }
            break;
        case SDLK_DOWN:
        case SDLK_s:
            if(Cola_empty(colaTurn) == true && !_Maze_checkWallCollision(pMaze, pMaze->player.x, pMaze->player.y + 1)) {
                move.vecX = 0;
                move.vecY = 1;
                moveChar = 'D';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &moveChar, sizeof(char));
                _Maze_ghostMovement(pMaze, colaTurn);
            }
            break;
        case SDLK_UP:
        case SDLK_w:
            if(Cola_empty(colaTurn) == true && !_Maze_checkWallCollision(pMaze, pMaze->player.x, pMaze->player.y - 1)) {
                move.vecX = 0;
                move.vecY = -1;
                moveChar = 'U';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &moveChar, sizeof(char));
                _Maze_ghostMovement(pMaze, colaTurn);
            }
            break;
        default:
            break;
        }
    }
}

void _Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn) {
    tVectorIterator vecIter;
    char id[10];
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
    VectorIterator_create(&vecIter, &pMaze->vecGhost);

    VectorIterator_first(&vecIter, &ghost);
    while(!VectorIterator_finished(&vecIter)) {
        ghostX = Ghost_getX(&ghost);
        ghostY = Ghost_getY(&ghost);

        if(Ghost_isAlive(&ghost) == true) {
                Ghost_getId(&ghost, id);
                strcpy(move.id, id);

                xDist = abs(playerX - ghostX);
                yDist = abs(playerY - ghostY);

                if (xDist > yDist) {
                    if (playerX < ghostX) {
                        move.vecX = -1;
                        move.vecY = 0;
                    }
                    else {
                        move.vecX = 1;
                        move.vecY = 0;
                    }
                }
                else {
                    if (playerY < ghostY) {
                        move.vecX = 0;
                        move.vecY = -1;
                    }
                    else {
                        move.vecX = 0;
                        move.vecY = 1;
                    }
                }
                Cola_put(colaTurn, &move, sizeof(tMovement));
            }
        VectorIterator_next(&vecIter, &ghost);
    }
}

bool Maze_update(tMaze* pMaze, tCola* colaTurn) {
    tMovement move;
    tGhost ghost;

    if(Cola_takeOut(colaTurn, &move, sizeof(tMovement)) == false) {
        return false;
    }

    if(strcmp(move.id, "player") == 0) {
        Player_movement(&pMaze->player, move);
        return true;
    }

    Ghost_changeId(&ghost, move.id);

    Vector_bsearch(&pMaze->vecGhost, &ghost, Ghost_cmp);
    Ghost_movement(&ghost, move);

    Vector_Update(&pMaze->vecGhost, &ghost, Ghost_cmp, Ghost_Update);

    return true;
}

int Maze_check(tMaze* pMaze) {
    int playerX;
    int playerY;
    int elemX;
    int elemY;
    int lives;
    tGhost ghost;
    tLives live;
    tAwards award;
    tVectorIterator vecIter;
    int _return = OK;

    playerX = Player_getX(&pMaze->player);
    playerY = Player_getY(&pMaze->player);
    lives = Player_getLives(&pMaze->player);

    if(pMaze->maze[playerY][playerX] == 'E') {
        return VICTORY;
    }

    VectorIterator_create(&vecIter, &pMaze->vecLives);
    VectorIterator_first(&vecIter, &live);
    while(!VectorIterator_finished(&vecIter) && _return == OK) {
        if(Lives_isAlive(&live) == true) {
            elemX = Lives_getX(&live);
            elemY = Lives_getY(&live);

            if(elemX == playerX && elemY == playerY) {
                _return = ADD_LIVE;
                SDL_Delay(100);
                Player_addLives(&pMaze->player);
                Lives_delete(&live);
                Vector_Update(&pMaze->vecLives, &live, Lives_cmp, Lives_update);
                lives++;
                Margin_updateLives(&pMaze->margin, lives);
            }
        }
        VectorIterator_next(&vecIter, &live);
    }

    _return = OK;
    VectorIterator_create(&vecIter, &pMaze->vecAwards);
    VectorIterator_first(&vecIter, &award);
    while(!VectorIterator_finished(&vecIter) && _return == OK) {
        if(Awards_isAlive(&award) == true) {
            elemX = Awards_getX(&award);
            elemY = Awards_getY(&award);

            if(elemX == playerX && elemY == playerY) {
                _return = GET_AWARD;
                SDL_Delay(100);
                Awards_delete(&award);
                Vector_Update(&pMaze->vecAwards, &award, Awards_cmp, Awards_update);
                pMaze->points += GET_POINTS;
                Margin_updatePoints(&pMaze->margin, pMaze->points);
            }
        }
        VectorIterator_next(&vecIter, &award);
    }

    _return = OK;
    VectorIterator_create(&vecIter, &pMaze->vecGhost);
    VectorIterator_first(&vecIter, &ghost);
    while(!VectorIterator_finished(&vecIter) && _return == OK) {
        if(Ghost_isAlive(&ghost) == true) {
            elemX = Ghost_getX(&ghost);
            elemY = Ghost_getY(&ghost);

            if(elemX == playerX && elemY == playerY) {
                _return = LOST_LIVE;
            }
        }
        if(_return == OK) {
            VectorIterator_next(&vecIter, &ghost);
        }
    }

    if(_return == LOST_LIVE) {
        SDL_Delay(200);
        if(pMaze->points >= 150) {
            pMaze->points -= 150;
            Margin_updatePoints(&pMaze->margin, pMaze->points);
        }
        if(lives != 0) {
            Player_lostLives(&pMaze->player);
            Ghost_delete(&ghost);
            Vector_Update(&pMaze->vecGhost, &ghost, Ghost_cmp, Ghost_Update);
            Player_resetPos(&pMaze->player);
            lives--;
            Margin_updateLives(&pMaze->margin, lives);
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
