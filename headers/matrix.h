#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../headers/bool.h"

#define SIZE_LINE 130

typedef void (*Action)(void** mat, const void* elem, int rows, int columns);
typedef void (*UploadFileTxt)(void** mat, FILE* pFile, int rows, int columns);

void** Matrix_create(int rows, int columns, int sizeElem);
void Matrix_clean(void** mat, int rows);
bool Matrix_loadFromFileTxt(void** mat, int rows, int columns, char* fileName, Action action);
bool Matrix_uploadFileTxt(void** mat, const char* fileName, int rows, int columns, UploadFileTxt uploadFileTxt);
bool Matrix_randomCreate(int rows, int columns, int density, int numGhosts, int numAwards, int numKeys, int numCross, int numHeart, const char* fileName);
void MatrixAction_loadChar(void** mat, const void* elem, int rows, int columns);
void MatrixUploadFileTxt_uploadChar(void** mat, FILE* pFile, int rows, int columns);

#endif // MATRIX_H_INCLUDED
