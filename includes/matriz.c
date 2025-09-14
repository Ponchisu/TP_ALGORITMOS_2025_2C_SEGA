#include "../headers/matriz.h"

void** matrizCrear(unsigned filas, unsigned columnas, unsigned tamElem)
{
    void** mat = malloc(sizeof(void*) * filas);

    if(!mat)
    {
        return NULL;
    }

    void** ult = mat + filas - 1;
    for(void** i = mat; i <= ult ; i++)
    {
        *i = malloc(tamElem  * columnas);

        if(!*i)
        {
            matrizEliminar(mat, i - mat);

            return NULL;
        }
    }

    return mat;

}

void matrizEliminar(void** mat, unsigned filas)
{
    void** ult = mat + filas - 1;
    for(void** i = mat; i <= ult ; i++)
    {
        free(*i);
    }
    free(mat);

}

bool matrizCargarDeArchTxt(char** mat, unsigned columnas) {
    int fila = 0;
    char linea[TAM_LINEA];
    char* act;

    FILE* pf = fopen("laberinto.txt", "rt");
    if(!pf) {
        fprintf(stderr, "Error al abrir archivo");
        return false;
    }


    while(fgets(linea, TAM_LINEA, pf)) {
        act = linea;
        for(int col = 0; col < columnas; col++, act++) {
            mat[fila][col] = *act;
        }
        fila++;
    }

    fclose(pf);
    return true;
}

void matrizMostrar(char** mat, int filas, int columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            printf("%c", mat[i][j]);
        }

        putchar('\n');
    }
}
