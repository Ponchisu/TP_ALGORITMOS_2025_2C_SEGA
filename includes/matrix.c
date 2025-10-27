#include "../headers/matrix.h"

void** Matrix_create(int rows, int columns, int sizeElem) {
    void** mat = malloc(sizeof(void*) * rows);
    void** last;

    if(!mat) {
        return NULL;
    }

    last = mat + rows - 1;
    for(void** i = mat; i <= last ; i++) {
        *i = malloc(sizeElem  * columns);

        if(!*i) {
            Matrix_clean(mat, i - mat);

            return NULL;
        }
    }

    return mat;
}

void Matrix_clean(void** mat, int rows) {
    void** last = mat + rows - 1;
    for(void** i = mat; i <= last ; i++) {
        free(*i);
    }
    free(mat);
}

bool Matrix_loadFromFileTxt(void** mat, int rows, int columns, char* fileName, Action action) {
    int currentRow = 0;
    char line[SIZE_LINE];
    char* current;
    FILE* pf;

    if(mat == NULL) {
        fprintf(stderr, "Error al abrir archivo\n");
        return false;
    }

    if(action == NULL) {
        fprintf(stderr, "Error al abrir archivo\n");
        return false;
    }

    pf = fopen(fileName, "rt");
    if(!pf) {
        fprintf(stderr, "Error al abrir archivo\n");
        return false;
    }


    while(fgets(line, SIZE_LINE, pf) && currentRow < rows) {
        current = line;
        for(int col = 0; col < columns; col++, current++) {
            action(mat, current, currentRow, col);
        }
        currentRow++;
    }

    fclose(pf);
    return true;
}

bool Matrix_randomCreate(int rows, int columns, int density, int numGhosts, int numAwards, int numKeys, int numHeart, const char* fileName) {
    int x, y, wallDensity, r, my[4], mx[4], midX, midY;
    char** maze = (char**)Matrix_create(rows, columns, sizeof(char));
    if(maze == NULL) {
        return false;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == 0 || j == 0 || i == rows - 1 || j == columns - 1) {
                maze[i][j] = '#';
            } else {
                maze[i][j] = '.';
            }
        }
    }

    wallDensity = density * 8;
    density = rows * columns * density / 4;

    for (int i = 0; i < density; i++) {
        x = rand() % (columns - 4) + 2;
        x = (x / 2) * 2;
        y = rand() % (rows - 4) + 2;
        y = (y / 2) * 2;

        maze[y][x] = '#';

        for (int j = 0; j < wallDensity; j++) {
            mx[0] = x;
            my[0] = y + 2;
            mx[1] = x;
            my[1] = y - 2;
            mx[2] = x + 2;
            my[2] = y;
            mx[3] = x - 2;
            my[3] = y;

            r = rand() % 4;

            if (my[r] > 0 && my[r] < rows - 1 && mx[r] > 0 && mx[r] < columns - 1) {
                if (maze[my[r]][mx[r]] == '.') {
                    maze[my[r]][mx[r]] = '#';

                    midY = my[r] + (y - my[r]) / 2;
                    midX = mx[r] + (x - mx[r]) / 2;
                    maze[midY][midX] = '#';
                }
            }
        }
    }

    r = rand() % (columns - 2) + 1;
    maze[0][r] = 'S';

    while(numGhosts != 0) {
        x = rand() % (columns - 4) + 2;
        y = rand() % (rows - 4) + 2;
        if(maze[y][x] == '.') {
            maze[y][x] = 'G';
            numGhosts--;
        }
    }

    while(numKeys != 0) {
        x = rand() % (columns - 4) + 2;
        y = rand() % (rows - 4) + 2;
        if(maze[y][x] == '.') {
            maze[y][x] = 'K';
            numKeys--;
        }
    }

    while(numHeart != 0) {
        x = rand() % (columns - 2) + 1;
        y = rand() % (rows - 2) + 1;
        if(maze[y][x] == '.') {
            maze[y][x] = 'H';
            numHeart--;
        }
    }

    while(numAwards != 0) {
        x = rand() % (columns - 4) + 2;
        y = rand() % (rows - 4) + 2;
        if(maze[y][x] == '.') {
            maze[y][x] = 'A';
            numAwards--;
        }
    }

    if(Matrix_uploadFileTxt((void**)maze, (char*)fileName, rows, columns, MatrixUploadFileTxt_uploadChar) == false) {
        Matrix_clean((void**)maze, rows);
        return false;
    }

    Matrix_clean((void**)maze, rows);
    return true;
}

bool Matrix_uploadFileTxt(void** mat, const char* fileName, int rows, int columns, UploadFileTxt uploadFileTxt) {
    FILE* pFile;

    pFile = fopen(fileName, "wt");
    if(pFile == NULL) {
        return false;
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            uploadFileTxt(mat, pFile, i, j);
        }
        fprintf(pFile, "\n");
    }

    fclose(pFile);
    return true;
}

void MatrixAction_loadChar(void** mat, const void* elem, int rows, int columns) {
    char** matChar = (char**)mat;
    const char* elemChar = elem;
    matChar[rows][columns] = *elemChar;
}

void MatrixUploadFileTxt_uploadChar(void** mat, FILE* pFile, int rows, int columns) {
    char** matChar = (char**)mat;
    fprintf(pFile, "%c", matChar[rows][columns]);
}


