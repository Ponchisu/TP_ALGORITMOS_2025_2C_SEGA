#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../headers/bool.h"

#define SIZE_LINE 130

typedef void (*Action)(void** mat, const void* elem, int rows, int columns);

void** Matrix_create(int rows, int columns, int sizeElem);
void Matrix_clean(void** mat, int rows);
bool Matrix_loadFromFileTxt(void** mat, int rows, int columns, char* fileName, Action action);

void MatrixAction_loadChar(void** mat, const void* elem, int rows, int columns);
void Matriz_show(char** mat, int rows, int columns); // provicional eliminar antes de la finalicacion del tp

#endif // MATRIX_H_INCLUDED
