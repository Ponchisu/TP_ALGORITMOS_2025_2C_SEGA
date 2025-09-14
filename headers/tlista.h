#ifndef TLISTA_H_INCLUDED
#define TLISTA_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/bool.h"

#define DUPLICADO 1
#define NO_DUPLICADO 2

typedef struct sNodo {
    void* info;
    unsigned tamElem;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tlista;
typedef void (*MostrarElem)(const void* elem);
typedef int (*Cmp)(const void* elem1, const void* elem2);

void listaCrear(tlista* lista);
void listaVaciar(tlista* lista);
bool listaPonerAlFinal(tlista* lista, const void* elem, unsigned tamElem);
bool listaInsertarEnOrden(tlista* lista, const void* elem, unsigned tamElem, unsigned duplicado, Cmp cmp);
bool listaMostrar(tlista* lista, unsigned tamElem, MostrarElem mostrarElem);

#endif // TLISTA_H_INCLUDED