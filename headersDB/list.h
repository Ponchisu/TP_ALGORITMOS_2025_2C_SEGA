#ifndef TLISTA_H_INCLUDED
#define TLISTA_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headersDB/bool.h"

#define DUPLICADO 1
#define NO_DUPLICADO 2

typedef struct sNodeList {
    void* info;
    unsigned sizeElem;
    struct sNodeList* sig;
}tNodeList;

typedef tNodeList* tList;
typedef int (*Cmp)(const void* elem1, const void* elem2);
typedef void (*Update)(void* elem1, const void* elem2);
typedef void (*ShowElem)(const void* elem);

#define MIN(a,b) ((a)<(b)?(a):(b))

void List_create(tList* pList);
void List_clean(tList* pList);
bool List_isEmpty(tList* pList);
bool List_insertInOrder(tList* pList, const void* elem, unsigned sizeElem, Cmp cmp, Update uptdate);
bool List_sort(tList* pList, Cmp cmp);
bool List_getFirst(tList* pList, void* elem, unsigned sizeElem);

bool listaMostrar(tList* lista, unsigned tamElem, ShowElem show);

#endif // TLISTA_H_INCLUDED