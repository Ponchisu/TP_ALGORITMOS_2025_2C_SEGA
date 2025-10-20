#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../headers/bool.h"

typedef struct
{
    void* vec;
    unsigned sizeElem;
    unsigned capacity;
    unsigned lotElem;
}tVector;

typedef struct {
    void* first;
    void* last;
    void* current;
    bool finishIter;
    size_t sizeElem;
}VectorIterator;

typedef int (*Cmp)(const void* elem1, const void* elem2);
typedef void (*Update)(void* elem1, const void* elem2);

bool Vector_create(tVector* pVec, unsigned sizeElem, unsigned capacity);
void Vector_clean(tVector* pVec);
bool Vector_insertInOrder(tVector* pVec, const void* elem, Cmp cmp, Update update);
int Vector_bsearch(tVector* pVec, void* elem, Cmp cmp);
bool Vector_Update(tVector* pVec, const void* elem, Cmp cmp, Update update);


#endif // VECTOR_H_INCLUDED
