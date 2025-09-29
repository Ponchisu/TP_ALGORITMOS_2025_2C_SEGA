#include "../headers/maze.h"

bool Maze_create(tMaze** pMaze, int rows, int columns, SDL_Renderer* render) {
    //tGhost ghost;

    *pMaze = (tMaze*)malloc(sizeof(tMaze));
    if(*pMaze == NULL) {
        fprintf(stderr, "Error al crear laberinto\n");
        return false;
    }

    (*pMaze)->rows = rows;
    (*pMaze)->columns = columns;
    (*pMaze)->render = render;

    (*pMaze)->maze = (char**)Matrix_create(rows, columns, sizeof(char));
    if((*pMaze)->maze == NULL) {
        fprintf(stderr, "Error al crear matriz de laberinto\n");
        return false;
    }

    if(!Matrix_loadFromFileTxt((void**)(*pMaze)->maze, rows, columns, FILE_NAME, MatrixAction_loadChar)) {
        fprintf(stderr, "Error al cargar matriz de laberinto\n");
        return false;
    }


    if(!Vector_create(&(*pMaze)->vecTex, sizeof(tTexture))) {
        fprintf(stderr, "Error al crear vector\n");
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
            // if ((*pMaze)->pMaze[i][j] == 'F') {
            //     Ghost_create(&ghost, i, j, "ghost");
            //     listaPonerAlFinal(&(*pMaze)->lista, &ghost, sizeof(tGhost));
            // }
            if ((*pMaze)->maze[i][j] == 'E') {
                playerCreate(&(*pMaze)->player, i, j);
            }
        }
    }

    Matriz_show((*pMaze)->maze, rows, columns);

    return true;
}

void Maze_clean(tMaze** pMaze) {
    Matrix_clean((void**)(*pMaze)->maze, (*pMaze)->rows);

    Vector_destroy(&(*pMaze)->vecTex);

    free(*pMaze);
}

void Maze_draw(tMaze* pMaze) {
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
                TextureManager_Draw(&pMaze->vecTex, "ghost", rows * HEIGTH, col * WIDTH, pMaze->render);
            }

            TextureManager_Draw(&pMaze->vecTex, "player", pMaze->player.y * HEIGTH,  pMaze->player.x * WIDTH, pMaze->render);
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
            if(Cola_empty(colaTurn) == true && pMaze->maze[pMaze->player.y][pMaze->player.x + 1] != '#') {
                move.movement = 'R';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &move.movement, sizeof(char));
            }
            break;
        case SDLK_LEFT:
        case SDLK_a:
            if(Cola_empty(colaTurn) == true && pMaze->maze[pMaze->player.y][pMaze->player.x - 1] != '#') {
                move.movement = 'L';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &move.movement, sizeof(char));
            }
            break;
        case SDLK_DOWN:
        case SDLK_s:
            if(Cola_empty(colaTurn) == true && pMaze->player.y < pMaze->rows - 1 && pMaze->maze[pMaze->player.y + 1][pMaze->player.x] != '#') {
                move.movement = 'D';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &move.movement, sizeof(char));
            }
            break;
        case SDLK_UP:
        case SDLK_w:
            if(Cola_empty(colaTurn) == true && pMaze->player.y > 0 && pMaze->maze[pMaze->player.y - 1][pMaze->player.x] != '#') {
                move.movement = 'A';
                Cola_put(colaTurn, &move, sizeof(tMovement));
                Cola_put(colaMovement, &move.movement, sizeof(char));
            }
            break;
        default:
            break;
        }
    }
}

void Maze_ghostMovement(tMaze* pMaze, tCola* colaTurn) {
    tMovement move;

    Cola_showFirst(colaTurn, &move, sizeof(tMovement));

    if(strcmp(move.id, "player") == 0) {
        // Realizar movimiento de todos los fantasmas y encolar ese movimiento
    }
}

bool Maze_update(tMaze* pMaze, tCola* colaTurn) {
    tMovement move;

    if(Cola_takeOut(colaTurn, &move, sizeof(tMovement)) == false) {
        return false;
    }

    if(strcmp(move.id, "player") == 0) {
        Player_movement(&pMaze->player, move.movement);
        return true;
    }

    // Buscar id de fantasma y mover al fantasma

    return false;
}

int Maze_check(tMaze* pMaze) {
    
    // chequear si el player toco un fantasma, OK si no toco
    // si se toca un fantasma, el player volvera a la posIni, se restara una vida, se "matara" al fantasma tocado y se devolvera LOST_LIVE
    // si el player es tocado y tiene 0 vidas se devuelve LOST y se da por perdido 

    return OK;
}
