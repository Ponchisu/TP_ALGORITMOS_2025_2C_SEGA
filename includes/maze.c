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

void Maze_clean(tMaze** pMaze, int rows) {
    Matrix_clean((void**)(*pMaze)->maze, rows);

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

bool Maze_handleEvents(tMaze* pMaze) {
    bool isGameRunning = true;
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            isGameRunning = false;
            puts("ENTER para salir");
            return isGameRunning;
        }
        if (event.key.keysym.sym == SDLK_RIGHT) {
            if(pMaze->maze[pMaze->player.y][pMaze->player.x + 1] != '#') {
                pMaze->player.x += 1;
            }
            return isGameRunning;
        }
        if (event.key.keysym.sym == SDLK_LEFT) {
            if(pMaze->maze[pMaze->player.y][pMaze->player.x - 1] != '#') {
                pMaze->player.x -= 1;
            }
            return isGameRunning;
        }
        if (event.key.keysym.sym == SDLK_DOWN && pMaze->player.y < pMaze->rows - 1) {
            if(pMaze->maze[pMaze->player.y + 1][pMaze->player.x] != '#') {
                pMaze->player.y += 1;
            }
            return isGameRunning;
        }
        if (event.key.keysym.sym == SDLK_UP && pMaze->player.y > 0) {
            if(pMaze->maze[pMaze->player.y - 1][pMaze->player.x] != '#') {
                pMaze->player.y -= 1;
            }
            return isGameRunning;
        }
    }
    return isGameRunning;
}
