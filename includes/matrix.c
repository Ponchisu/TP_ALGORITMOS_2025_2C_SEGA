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

void Matriz_show(char** mat, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            printf("%c", mat[i][j]);
        }

        putchar('\n');
    }
}

void MatrixAction_loadChar(void** mat, const void* elem, int rows, int columns) {
    char** matChar = (char**)mat;
    const char* elemChar = elem;
    matChar[rows][columns] = *elemChar;
}
