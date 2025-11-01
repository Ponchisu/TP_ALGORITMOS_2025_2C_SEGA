#include "../headersDB/list.h"

void List_create(tList* pList) {
    *pList = NULL;
}

void List_clean(tList* pList) {
    tNodeList* aux;

    while(*pList != NULL) {

        aux = *pList;
        *pList = aux->sig;
        free(aux->info);
        free(aux);
    }
}

bool List_isEmpty(tList* pList) {
    return *pList == NULL;
}

bool List_insertInOrder(tList* pList, const void* elem, unsigned sizeElem, Cmp cmp, Update update) {
    tNodeList* new;

    while(*pList != NULL && cmp(elem, (*pList)->info) > 0) {
        pList = &(*pList)->sig;
    }

    if(*pList != NULL && cmp(elem, (*pList)->info) == 0) {
        update((*pList)->info, elem);
        return true;
    }

    new = (tNodeList*) malloc(sizeof(tNodeList));

    if (NULL == new) {
        return false;
    }

    new->info = malloc(sizeElem);
    if(NULL == new->info) {
        free(new);
        return false;
    }

    memcpy(new->info, elem, sizeElem);
    new->sizeElem = sizeElem;
    new->sig = *pList;
    *pList = new;

    return true;
}

bool List_sort(tList* pList, Cmp cmp) {
    tList *first = pList;
    tList *current;
    tNodeList *aux;

    if (*pList == NULL) {
        return false;
    }

    while ((*pList)->sig) {
        if (cmp((*pList)->info, (*pList)->sig->info) > 0) {
            current = first;
            aux = (*pList)->sig;

            (*pList)->sig = aux->sig;
            while (cmp(aux->info, (*current)->info) > 0) {
                current = &(*current)->sig;
            }
            aux->sig = *current;
            *current = aux;
        }
        else {
            pList = &(*pList)->sig;
        }
    }
    return true;
}

bool List_getFirst(tList* pList, void* elem, unsigned sizeElem) {
    tNodeList* aux = *pList;

    if(*pList == NULL) {
        return false;
    }
    *pList = aux->sig;

    memcpy(elem, aux->info, MIN(aux->sizeElem, sizeElem));
    
    free(aux->info);
    free(aux);

    return true;
}

bool listaMostrar(tList* lista, unsigned tamElem, ShowElem mostrarElem) {
    void* elem;
    if(*lista == NULL) {
        return false;
    }

    elem = malloc(tamElem);
    if(elem == NULL) {
        return false;
    }

    while (*lista != NULL) {
        memcpy(elem, (*lista)->info, tamElem);
        mostrarElem(elem);
        lista = &(*lista)->sig;
    }

    return true;
}