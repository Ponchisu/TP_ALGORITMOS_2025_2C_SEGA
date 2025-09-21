#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct{
    void* dato;
    unsigned tam;
}tNodoV;

typedef struct{
    tNodoV* vec;
    unsigned ce;
    unsigned tam;
}Vector;

typedef int (*Cmp)(const void* , const void*);
typedef void (*Accion)(const void*);

int Vector_create(Vector*v, unsigned tamVector);
void Vector_destroy(Vector*v);
int Vector_resize(Vector* v,size_t nuevoTamanio);
int Vector_insertInOrder(Vector* v,void*elemento,size_t tamDato,Cmp cmp);
int Vector_insertInOrderNoRepeat(Vector* v, void* elemento, size_t tamDato, Cmp cmp);
int Vector_getByPos(Vector* v, int pos, void * valor, size_t tamValor);
void* Vector_bsearch(Vector *v, void * valor, Cmp cmp);
int compararInt(const void* a, const void* b);
void Vector_map(Vector*v,Accion accion);
void* Vector_getRefByPos(Vector* v, int pos);
size_t Vector_count(Vector* v);

#endif // VECTOR_H_INCLUDED
