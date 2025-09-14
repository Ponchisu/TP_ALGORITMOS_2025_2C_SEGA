#include "../headers/tlista.h"

void listaCrear(tlista* lista) {
    *lista = NULL;
}

void listaVaciar(tlista* lista) {
    tNodo* aux;

    while(*lista != NULL) {

        aux = *lista;
        *lista = aux->sig;
        free(aux->info);
        free(aux);
    }
}

bool listaPonerAlFinal(tlista* lista, const void* elem, unsigned tamElem) {
    tNodo* nue;

    nue = (tNodo*)malloc(sizeof(tNodo));
    if(nue == NULL) {
        return false;
    }

    nue->info = malloc(tamElem);
    if(nue->info == NULL) {
        free(nue);
        return false;
    }

    nue->tamElem = tamElem;
    memcpy(nue->info, elem, tamElem);
    nue->sig = NULL;

    while (*lista != NULL) {
        lista = &(*lista)->sig;
    }
    *lista = nue;
    return true;

}

bool listaMostrar(tlista* lista, unsigned tamElem, MostrarElem mostrarElem) {
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

bool listaInsertarEnOrden(tlista* lista, const void* elem, unsigned tamElem, unsigned permitirDup, Cmp cmp)
{
    tNodo* nue;

    while(*lista != NULL && cmp(elem, (*lista)->info) > 0) {
        lista = &(*lista)->sig;
    }

    if(*lista != NULL && cmp(elem, (*lista)->info) == 0 && permitirDup == NO_DUPLICADO) {
        return false;
    }

    nue = (tNodo*) malloc(sizeof(tNodo));

    if (NULL == nue) {
        return false;
    }

    nue->info = malloc(tamElem);
    if(NULL == nue->info) {
        free(nue);
        return false;
    }

    memcpy(nue->info, elem, tamElem);
    nue->tamElem = tamElem;
    nue->sig = *lista;
    *lista = nue;

    return true;
}
