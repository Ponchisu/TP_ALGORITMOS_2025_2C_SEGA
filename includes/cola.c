#include "../headers/cola.h"

void Cola_create(tCola* cola) {
    *cola = NULL;
}

void Cola_clean(tCola* cola) {
    tNodo* aux;
    tNodo* current;

    if(*cola == NULL) {
        return;
    }
    
    current = (*cola)->sig;
    while(current != *cola) {
        aux = current;
        current = current->sig;
        free(aux->info);
        free(aux);
    }

    free(current->info);
    free(current);
    *cola = NULL;
}

bool Cola_full(const tCola* cola, unsigned sizeElem) {
    tNodo* new;

    new = (tNodo*)malloc(sizeof(tNodo));
    if(new == NULL) {
        fprintf(stderr, "Error de memoria\n");
        return true;
    }

    new->info = malloc(sizeElem);
    if(new->info == NULL) {
        fprintf(stderr, "Error de memoria\n");
        free(new);
        return true;
    }
    
    free(new->info);
    free(new);

    return false;
}

bool Cola_empty(const tCola* cola) {
    return *cola == NULL ? true : false;
}

bool Cola_put(tCola* cola, const void* elem, unsigned sizeElem) {
    tNodo* new;

    new = (tNodo*)malloc(sizeof(tNodo));
    if(new == NULL) {
        fprintf(stderr, "Error de memoria\n");
        return false;
    }

    new->info = malloc(sizeElem);
    if(new->info == NULL) {
        fprintf(stderr, "Error de memoria\n");
        free(new);
        return false;
    }

    new->sizeElem = sizeElem;
    memcpy(new->info, elem, sizeElem);

    if(*cola == NULL) {
        new->sig = new;
        *cola = new;
        return true;
    }

    new->sig = (*cola)->sig;
    (*cola)->sig = new;
    *cola = new;

    return true;
}

bool Cola_takeOut(tCola* cola, void* elem, unsigned sizeElem) {
    tNodo* aux;

    if(*cola == NULL) {
        return false;
    }

    aux = (*cola)->sig;
    memcpy(elem, aux->info, MIN(aux->sizeElem, sizeElem));
    
    if(*cola == aux) {
        *cola = NULL;
    } else {
        (*cola)->sig = aux->sig;
    }

    free(aux->info);
    free(aux);

    return true;
}

bool Cola_showFirst(tCola* cola, void* elem, unsigned sizeElem) {
    tNodo* first;

    if(*cola == NULL) {
        return false;
    }

    first = (*cola)->sig;
    memcpy(elem, first->info, MIN(first->sizeElem, sizeElem));
    
    return true;
}