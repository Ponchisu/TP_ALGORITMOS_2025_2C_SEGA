#include "../headers/maze.h"

bool _Maze_checkWallCollision(tMaze* pMaze, int xPos, int yPos);
void _Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn);
void _Maze_drawElem(tVector* pVec, tVector* pVecTex, SDL_Renderer* pRender, const char* id, unsigned tamElem, Elem_isAlive _Elem_isAlive, Elem_getY _Elem_getY, Elem_getX _Elem_getX);
bool _Maze_ghostMovementIsValid(tMaze* pMaze, int newX, int newY);
void _Maze_ghostFollowPos(tMaze* pMaze, int posX, int posY, int ghostX, int ghostY, int dirX, int dirY, tMovement* move);

bool Maze_create(tMaze** pMaze, SDL_Renderer* renderer, int rows, int columns, int numLives, int numGhosts, int numAwards, int maxLives, bool rei) {
    *pMaze = (tMaze*)malloc(sizeof(tMaze));
    if(*pMaze == NULL) {
        fprintf(stderr, "Error al crear laberinto\n");
        return false;
    }

    Vector_init(&(*pMaze)->vecAwards);
    Vector_init(&(*pMaze)->vecChunk);
    Vector_init(&(*pMaze)->vecGhost);
    Vector_init(&(*pMaze)->vecKeys);
    Vector_init(&(*pMaze)->vecLives);
    Vector_init(&(*pMaze)->vecTex);

    (*pMaze)->renderer = renderer;
    (*pMaze)->rows = rows;
    (*pMaze)->columns = columns;
    (*pMaze)->numLives = numLives;
    (*pMaze)->numGhosts = numGhosts;
    (*pMaze)->numAwards = numAwards;
    (*pMaze)->maxLives = maxLives;
    (*pMaze)->points = 0;
    (*pMaze)->keys = SIZE_VECKEYS;


    (*pMaze)->maze = (char**)Matrix_create(rows, columns, sizeof(char));
    if((*pMaze)->maze == NULL) {
        fprintf(stderr, "Error al crear matriz de laberinto\n");
        return false;
    }

    if(!Margin_create(&(*pMaze)->margin, numLives, columns, SIZE_VECKEYS, renderer)) {
        fprintf(stderr, "Error al crear margin\n");
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

    if(!Vector_create(&(*pMaze)->vecChunk, sizeof(tChunk), SIZE_VECCHUNK)) {
        fprintf(stderr, "Error al crear vector de chunk\n");
        return false;
    }

    if(!Vector_create(&(*pMaze)->vecKeys, sizeof(tKeys), SIZE_VECKEYS)) {
        fprintf(stderr, "Error al crear vector de keys\n");
        return false;
    }

    if(!SoundManager_loadChunk(&(*pMaze)->vecChunk, "sound/points.wav", "points", 20)) {
        fprintf(stderr, "Error al cargar sonido points\n");
        return false;
    }

    if(!SoundManager_loadChunk(&(*pMaze)->vecChunk, "sound/hit.wav", "hit", 20)) {
        fprintf(stderr, "Error al cargar sonido hit\n");
        return false;
    }

    if(!SoundManager_loadChunk(&(*pMaze)->vecChunk, "sound/heart.wav", "heart", 20)) {
        fprintf(stderr, "Error al cargar sonido heart\n");
        return false;
    }

    if(!SoundManager_loadChunk(&(*pMaze)->vecChunk, "sound/turn.wav", "turn", 10)) {
        fprintf(stderr, "Error al cargar sonido turn\n");
        return false;
    }

    if(!SoundManager_loadChunk(&(*pMaze)->vecChunk, "sound/unluck.wav", "unluck", 15)) {
        fprintf(stderr, "Error al cargar sonido unluck\n");
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

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/key.png", "key", renderer)) {
        fprintf(stderr, "Error al cargar imagen Key\n");
        return false;
    }

    if(rei == false) {
        if(!TextureManager_load(&(*pMaze)->vecTex, "assets/ghost.png", "ghost", renderer)) {
            fprintf(stderr, "Error al cargar imagen Fantasma\n");
            return false;
        }
    } else {
        if(!TextureManager_load(&(*pMaze)->vecTex, "assets/rei.png", "ghost", renderer)) {
            fprintf(stderr, "Error al cargar imagen Fantasma\n");
            return false;
        }
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/heart.png", "heart", renderer)) {
        fprintf(stderr, "Error al cargar imagen corazon\n");
        return false;
    }

    if(!TextureManager_load(&(*pMaze)->vecTex, "assets/award.png", "award", renderer)) {
        fprintf(stderr, "Error al cargar imagen premio\n");
        return false;
    }

    return true;
}

bool Maze_createRun(tMaze* pMaze) {
    tGhost ghost;
    tAwards award;
    tLives live;
    tKeys key;
    int idGhost = 0;
    int idAwards = 0;
    int idLives = 0;
    int idKey = 0;
    if(!Matrix_randomCreate(pMaze->rows, pMaze->columns, 1, pMaze->numGhosts, pMaze->numAwards, SIZE_VECKEYS, pMaze->maxLives, FILE_NAME)) {
        fprintf(stderr, "Error al crear laberinto random\n");
        return false;
    }

    if(!Matrix_loadFromFileTxt((void**)pMaze->maze, pMaze->rows, pMaze->columns, FILE_NAME, MatrixAction_loadChar)) {
        fprintf(stderr, "Error al cargar matriz de laberinto\n");
        return false;
    }

    pMaze->keys = SIZE_VECKEYS;
    Margin_updateKey(&pMaze->margin, pMaze->keys);

    Vector_empty(&pMaze->vecAwards);
    Vector_empty(&pMaze->vecGhost);
    Vector_empty(&pMaze->vecKeys);
    Vector_empty(&pMaze->vecLives);

    for (int i = 0; i < pMaze->rows; i++) {
        for (int j = 0; j < pMaze->columns; j++) {
            if (pMaze->maze[i][j] == 'G') {
                Ghost_create(&ghost, i, j, "", idGhost);
                Ghost_numId(&ghost, idGhost);
                if(!Vector_insertInOrder(&pMaze->vecGhost, &ghost, Ghost_cmp, NULL)) {
                    return false;
                }
                idGhost++;
                pMaze->maze[i][j] = '.';
            } else if(pMaze->maze[i][j] == 'A') {
                Awards_create(&award, i, j, "");
                Awards_numIde(&award, idAwards);
                if(!Vector_insertInOrder(&pMaze->vecAwards, &award, Awards_cmp, NULL)) {
                    return false;
                }
                idAwards++;
                pMaze->maze[i][j] = '.';
            } else if(pMaze->maze[i][j] == 'H') {
                Lives_create(&live, i, j, "");
                Lives_numId(&live, idLives);
                if(!Vector_insertInOrder(&pMaze->vecLives, &live, Lives_cmp, NULL)) {
                    return false;
                }
                idLives++;
                pMaze->maze[i][j] = '.';
            } else if(pMaze->maze[i][j] == 'K') {
                Key_create(&key, i, j, "");
                Key_numIde(&key, idKey);
                if(!Vector_insertInOrder(&pMaze->vecKeys, &key, Key_cmp, NULL)) {
                    return false;
                }
                idKey++;
                pMaze->maze[i][j] = '.';
            } else if (pMaze->maze[i][j] == 'S') {
                playerCreate(&pMaze->player, i, j, pMaze->numLives);
            } else if(pMaze->maze[i][j] == 'E') {
            }
        }
    }

    return true;
}

void Maze_clean(tMaze** pMaze) {
    Matrix_clean((void**)(*pMaze)->maze, (*pMaze)->rows);

    if(Vector_isEmpty(&(*pMaze)->vecTex) == false) {
        TextureManager_clean(&(*pMaze)->vecTex);
    }
    Vector_clean(&(*pMaze)->vecTex);

    Vector_clean(&(*pMaze)->vecGhost);
    Vector_clean(&(*pMaze)->vecAwards);
    Vector_clean(&(*pMaze)->vecLives);

    if(Vector_isEmpty(&(*pMaze)->vecChunk) == false) {
        SoundManager_cleanChunk(&(*pMaze)->vecChunk);
    }
    Vector_clean(&(*pMaze)->vecChunk);

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
            TextureManager_draw(pVecTex, id, _Elem_getY(elem) * HEIGTH + MARGIN_TOP, _Elem_getX(elem) * WIDTH,  WIDTH, HEIGTH, pRender);
        }
        VectorIterator_next(&vecIter, elem);
    }
    free(elem);
}

void Maze_draw(tMaze* pMaze, int marginDraw) {
    if(marginDraw == VICTORY) {
        Margin_drawWin(&pMaze->margin, pMaze->renderer);
    } else if(marginDraw == LOST){
        Margin_drawLost(&pMaze->margin, pMaze->renderer);
    } else {
        Margin_draw(&pMaze->margin, pMaze->renderer);
    }
    for (int rows = 0; rows < pMaze->rows; rows++) {
        for (int col = 0; col < pMaze->columns; col++) {
            if (pMaze->maze[rows][col] == '#') {
                TextureManager_draw(&pMaze->vecTex, "wall", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
            if (pMaze->maze[rows][col] == '.') {
                TextureManager_draw(&pMaze->vecTex, "floor", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
            if (pMaze->maze[rows][col] == 'S') {
                TextureManager_draw(&pMaze->vecTex, "wall", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
                TextureManager_draw(&pMaze->vecTex, "starter", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
            if (pMaze->maze[rows][col] == 'E') {
                TextureManager_draw(&pMaze->vecTex, "floor", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
                TextureManager_draw(&pMaze->vecTex, "exit", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
            if (pMaze->maze[rows][col] == 'F') {
                TextureManager_draw(&pMaze->vecTex, "floor", rows * HEIGTH + MARGIN_TOP, col * WIDTH, WIDTH, HEIGTH, pMaze->renderer);
            }
        }
        TextureManager_draw(&pMaze->vecTex, "player", Player_getY(&pMaze->player) * HEIGTH + 32,  Player_getX(&pMaze->player) * WIDTH, WIDTH, HEIGTH, pMaze->renderer);

        if(marginDraw != VICTORY && marginDraw != LOST) {
            _Maze_drawElem(&pMaze->vecGhost, &pMaze->vecTex, pMaze->renderer, "ghost", sizeof(tGhost), Ghost_isAlive, Ghost_getY, Ghost_getX);
            _Maze_drawElem(&pMaze->vecAwards, &pMaze->vecTex, pMaze->renderer, "award", sizeof(tAwards), Awards_isAlive, Awards_getY, Awards_getX);
            _Maze_drawElem(&pMaze->vecLives, &pMaze->vecTex, pMaze->renderer, "heart", sizeof(tLives), Lives_isAlive, Lives_getY, Lives_getX);
            _Maze_drawElem(&pMaze->vecKeys, &pMaze->vecTex, pMaze->renderer, "key", sizeof(tKeys), Key_isAlive, Key_getY, Key_getX);
        }
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

bool _Maze_ghostMovementIsValid(tMaze* pMaze, int newX, int newY) {
    if(pMaze->maze[newY][newX] == '.') {
        return true;
    } else {
        return false;
    }
}

void _Maze_ghostMovementInvertDir(int* dirX, int* dirY) {
    *dirX = - *dirX;
    *dirY = - *dirY;
}

bool _Maze_ghostMovementIsIntersection(tMaze* pMaze, int posX, int posY, int dirX, int dirY) {
    int count = 0;

    if (pMaze->maze[posY - 1][posX] == '.')
        count++;
    if (pMaze->maze[posY + 1][posX] == '.')
        count++;
    if (pMaze->maze[posY][posX - 1] == '.')
        count++;
    if (pMaze->maze[posY][posX + 1] == '.')
        count++;

    if (dirX > 0 && pMaze->maze[posY][posX - 1] == '.')
        count--;
    else if (dirX < 0 && pMaze->maze[posY][posX + 1] == '.')
        count--;
    else if (dirY > 0 && pMaze->maze[posY - 1][posX] == '.')
        count--;
    else if (dirY < 0 && pMaze->maze[posY + 1][posX] == '.')
        count--;

    return count > 1;
}

void _Maze_ghostFollowPos(tMaze* pMaze, int posX, int posY, int ghostX, int ghostY, int dirGhostX, int dirGhostY, tMovement* move) {
    int xDist = abs(posX - ghostX);
    int yDist = abs(posY - ghostY);
    if (xDist > yDist) {
        if (posX < ghostX && dirGhostX != 1 && _Maze_ghostMovementIsValid(pMaze, ghostX - 1, ghostY)) {
            move->vecX = -1;
            move->vecY = 0;
        } else if (posX > ghostX && dirGhostX != -1 && _Maze_ghostMovementIsValid(pMaze, ghostX + 1, ghostY)) {
            move->vecX = 1;
            move->vecY = 0;
        } else if (dirGhostY != 1 && _Maze_ghostMovementIsValid(pMaze, ghostX, ghostY - 1)) {
            move->vecX = 0;
            move->vecY = -1;
        } else if (dirGhostY != -1 && _Maze_ghostMovementIsValid(pMaze, ghostX, ghostY + 1)) {
            move->vecX = 0;
            move->vecY = 1;
        }
    } else {
        if (posY < ghostY && _Maze_ghostMovementIsValid(pMaze, ghostX, ghostY - 1) && dirGhostY != 1) {
            move->vecX = 0;
            move->vecY = -1;
        } else if (posY > ghostY && _Maze_ghostMovementIsValid(pMaze, ghostX, ghostY + 1) && dirGhostY != -1) {
            move->vecX = 0;
            move->vecY = 1;
        } else if (_Maze_ghostMovementIsValid(pMaze, ghostX - 1, ghostY) && dirGhostX != 1) {
            move->vecX = -1;
            move->vecY = 0;
        } else if (_Maze_ghostMovementIsValid(pMaze, ghostX + 1, ghostY) && dirGhostX != -1) {
            move->vecX = 1;
            move->vecY = 0;
        }
    }
}

void _Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn) {
    tVectorIterator vecIter;
    char id[10];
    tGhost ghost;
    tMovement move;
    int playerX, playerY;
    int ghostX, ghostY;
    int dirGhostX, dirGhostY;
    int tipeMove;

    playerX = Player_getX(&pMaze->player);
    playerY = Player_getY(&pMaze->player);

    VectorIterator_create(&vecIter, &pMaze->vecGhost);
    VectorIterator_first(&vecIter, &ghost);
    while(!VectorIterator_finished(&vecIter)) {
        if(Ghost_isAlive(&ghost) == true) {
            ghostX = Ghost_getX(&ghost);
            ghostY = Ghost_getY(&ghost);
            dirGhostX = Ghost_getDirX(&ghost);
            dirGhostY = Ghost_getDirY(&ghost);
            tipeMove = Ghost_getTipeMove(&ghost);

            move.vecX = dirGhostX;
            move.vecY = dirGhostY;

            if(_Maze_ghostMovementIsIntersection(pMaze, ghostX, ghostY, dirGhostX, dirGhostY) == true) {
                switch(tipeMove) {
                    case FOLLOW:
                        _Maze_ghostFollowPos(pMaze, playerX, playerY, ghostX, ghostY, dirGhostX, dirGhostY, &move);
                    break;
                    case SEMI_RANDOM:
                    _Maze_ghostFollowPos(pMaze, playerY, playerX, ghostX, ghostY, dirGhostX, dirGhostY, &move);
                    break;
                    case RANDOM:
                    _Maze_ghostFollowPos(pMaze, rand() %(pMaze->columns - 2) + 1, rand() % (pMaze->rows - 2) + 1, ghostX, ghostY, dirGhostX, dirGhostY, &move);
                    break;
                    case TOP_LEFT:
                        _Maze_ghostFollowPos(pMaze, 0, 0, ghostX, ghostY, dirGhostX, dirGhostY, &move);
                        break;
                    case TOP_RIGHT:
                        _Maze_ghostFollowPos(pMaze, pMaze->columns, 0, ghostX, ghostY, dirGhostX, dirGhostY, &move);
                        break;
                    case BOT_LEFT:
                        _Maze_ghostFollowPos(pMaze, 0, pMaze->rows, ghostX, ghostY, dirGhostX, dirGhostY, &move);
                        break;
                    case BOT_RIGHT:
                        _Maze_ghostFollowPos(pMaze, pMaze->columns, pMaze->rows, ghostX, ghostY, dirGhostX, dirGhostY, &move);
                        break;
                }
            } else if(!_Maze_ghostMovementIsValid(pMaze, ghostX + dirGhostX, ghostY + dirGhostY)) {
                if (dirGhostX == 0 && _Maze_ghostMovementIsValid(pMaze, ghostX - 1, ghostY)) {
                    move.vecX = -1;
                    move.vecY = 0;
                }
                else if (dirGhostX == 0 && _Maze_ghostMovementIsValid(pMaze, ghostX + 1, ghostY)) {
                    move.vecX = 1;
                    move.vecY = 0;
                }
                else if (dirGhostY == 0 && _Maze_ghostMovementIsValid(pMaze, ghostX, ghostY + 1)) {
                    move.vecX = 0;
                    move.vecY = 1;
                }
                else if (dirGhostY == 0 && _Maze_ghostMovementIsValid(pMaze, ghostX, ghostY - 1)) {
                    move.vecX = 0;
                    move.vecY = -1;
                } else {
                    _Maze_ghostMovementInvertDir(&dirGhostX, &dirGhostY);
                    move.vecX = dirGhostX;
                    move.vecY = dirGhostY;
                }
            }
            Ghost_getId(&ghost, id);
            strcpy(move.id, id);
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
        SoundManager_playChunk(&pMaze->vecChunk, "turn");
        Player_movement(&pMaze->player, move);
        return true;
    }

    Ghost_changeId(&ghost, move.id);

    Vector_bsearch(&pMaze->vecGhost, &ghost, Ghost_cmp);
    Ghost_movement(&ghost, move);

    Vector_update(&pMaze->vecGhost, &ghost, Ghost_cmp, Ghost_update);

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
    tKeys key;
    tVectorIterator vecIter;
    int _return = OK;

    playerX = Player_getX(&pMaze->player);
    playerY = Player_getY(&pMaze->player);
    lives = Player_getLives(&pMaze->player);

    if(pMaze->maze[playerY][playerX] == 'E') {
        pMaze->points += 2000;
        Margin_updatePoints(&pMaze->margin, pMaze->points);
        return VICTORY;
    }

    VectorIterator_create(&vecIter, &pMaze->vecKeys);
    VectorIterator_first(&vecIter, &key);
    while(!VectorIterator_finished(&vecIter)) {
        if(Key_isAlive(&key) == true) {
            elemX = Key_getX(&key);
            elemY = Key_getY(&key);

            if(elemX == playerX && elemY == playerY) {
                SDL_Delay(100);
                Key_delete(&key);
                Vector_update(&pMaze->vecKeys, &key, Key_cmp, Key_update);
                pMaze->keys --;
                Margin_updateKey(&pMaze->margin, pMaze->keys);
                if(pMaze->keys == 0) {
                    SoundManager_playChunk(&pMaze->vecChunk, "unluck");
                    pMaze->maze[pMaze->rows -1][rand() % (pMaze->columns - 2) + 1] = 'E';
                } else {
                    SoundManager_playChunk(&pMaze->vecChunk, "points");
                }
            }
        }
        VectorIterator_next(&vecIter, &key);
    }

    VectorIterator_create(&vecIter, &pMaze->vecLives);
    VectorIterator_first(&vecIter, &live);
    while(!VectorIterator_finished(&vecIter) && _return == OK) {
        if(Lives_isAlive(&live) == true) {
            elemX = Lives_getX(&live);
            elemY = Lives_getY(&live);

            if(elemX == playerX && elemY == playerY) {
                _return = ADD_LIVE;
                SoundManager_playChunk(&pMaze->vecChunk, "heart");
                SDL_Delay(100);
                Player_addLives(&pMaze->player);
                Lives_delete(&live);
                Vector_update(&pMaze->vecLives, &live, Lives_cmp, Lives_update);
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
                SoundManager_playChunk(&pMaze->vecChunk, "points");
                Awards_delete(&award);
                Vector_update(&pMaze->vecAwards, &award, Awards_cmp, Awards_update);
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
        SoundManager_playChunk(&pMaze->vecChunk, "hit");
        if(pMaze->points >= 150) {
            pMaze->points -= 150;
            Margin_updatePoints(&pMaze->margin, pMaze->points);
        }
        if(lives != 0) {
            Player_lostLives(&pMaze->player);
            Ghost_delete(&ghost);
            Vector_update(&pMaze->vecGhost, &ghost, Ghost_cmp, Ghost_update);
            Player_resetPos(&pMaze->player);
            lives--;
            Margin_updateLives(&pMaze->margin, lives);
        } else {
            _return = LOST;
            pMaze->points = 0;
            Margin_updatePoints(&pMaze->margin, pMaze->points);
        }

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


int Maze_getColumns(tMaze* pMaze) {
    return pMaze->columns;
}

int Maze_getRows(tMaze* pMaze) {
    return pMaze->rows;
}

void Maze_resetPlayer(tMaze* pMaze) {
    Player_resetPos(&pMaze->player);
}

void Maze_recreateGame(tMaze* pMaze, tCola* pColaMovement) {
    char charMove;
    tMovement move;

    if(!Cola_takeOut(pColaMovement, &charMove, sizeof(char))) {
        return;
    }

    move.vecX = 0;
    move.vecY = 0;

    if(charMove == 'R') {
        move.vecX = 1;
        move.vecY = 0;
        SoundManager_playChunk(&pMaze->vecChunk, "turn");
    } else if(charMove == 'L') {
        move.vecX = -1;
        move.vecY = 0;
        SoundManager_playChunk(&pMaze->vecChunk, "turn");
    } else if(charMove == 'D') {
        move.vecX = 0;
        move.vecY = 1;
        SoundManager_playChunk(&pMaze->vecChunk, "turn");
    } else if(charMove == 'U') {
        move.vecX = 0;
        move.vecY = -1;
        SoundManager_playChunk(&pMaze->vecChunk, "turn");
    } else if(charMove == 'X') {
        move.vecX = 0;
        move.vecY = 0;
        Player_resetPos(&pMaze->player);
        SoundManager_playChunk(&pMaze->vecChunk, "hit");
    }

    Player_movement(&pMaze->player, move);
}
