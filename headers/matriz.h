#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM_LINEA 130

void** matrizCrear(unsigned filas, unsigned columnas, unsigned temElem);
void matrizEliminar(void** mat, unsigned filas);
bool matrizCargarDeArchTxt(char** mat, unsigned columnas);

void matrizMostrar(char** mat, int filas, int columnas);

#endif // MATRIZ_H_INCLUDED
