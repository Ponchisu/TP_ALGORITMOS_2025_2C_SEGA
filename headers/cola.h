#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include "../headers/bool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct sNodo {
    void* info;
    unsigned sizeElem;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tCola;

void Cola_create(tCola* cola);
void Cola_clean(tCola* cola);
bool Cola_full(const tCola* cola, unsigned sizeElem);
bool Cola_empty(const tCola* cola);
bool Cola_put(tCola* cola, const void* elem, unsigned sizeElem);
bool Cola_takeOut(tCola* cola, void* elem, unsigned sizeElem);
bool Cola_showFirst(tCola* cola, void* elem, unsigned sizeElem);

#endif // COLA_H_INCLUDED
