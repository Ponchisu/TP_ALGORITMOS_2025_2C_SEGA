#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../headers/bool.h"

#define TAM_LINEA 130

void** matrizCrear(int filas, int columnas, int temElem);
void matrizEliminar(void** mat, int filas);
bool matrizCargarDeArchTxt(char** mat, int columnas);

void matrizMostrar(char** mat, int filas, int columnas);

#endif // MATRIZ_H_INCLUDED
