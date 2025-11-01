#include "../headers/vector.h"

bool _Vector_resize(tVector* pVec, unsigned newCapacity);

void Vector_init(tVector* pVec) {
    pVec->vec = NULL;
    pVec->capacity = 0;
    pVec->lotElem = 0;
    pVec->sizeElem = 0;
}

bool Vector_create(tVector* pVec, unsigned sizeElem, unsigned capacity) {
    pVec->vec = malloc(sizeElem * capacity);

    if(pVec->vec == NULL) {
        pVec->capacity = 0;
        pVec->lotElem = 0;
        pVec->sizeElem = 0;
        pVec->vec = NULL;
        return false;
    }

    pVec->capacity = capacity;
    pVec->lotElem = 0;
    pVec->sizeElem = sizeElem;
    return true;
}

void Vector_clean(tVector* pVec) {

        free(pVec->vec);
        pVec->capacity = 0;
        pVec->lotElem = 0;
        pVec->sizeElem = 0;
        pVec->vec = NULL;
}

bool _Vector_resize(tVector* pVec, unsigned newCapacity) {
    void* newVec = realloc(pVec->vec, newCapacity * pVec->sizeElem);
    if(newVec == NULL) {
        return false;
    }

    pVec->vec = newVec;
    pVec->capacity = newCapacity;
    return true;
}

bool Vector_insertInOrder(tVector* pVec, const void* elem, Cmp cmp, Update update) {
    void* posIns;
    void* last;

    if (pVec->vec == NULL) {
        return false;
    }

    if(pVec->capacity == pVec->lotElem) {
        if(!_Vector_resize(pVec, pVec->capacity * 1.5)) {
            return false;
        }
        return false;
    }
    posIns = pVec->vec;
    last = pVec->vec + (int)((pVec->lotElem - 1) * pVec->sizeElem);
    while (posIns <= last && cmp(elem, posIns) > 0) {
        posIns += pVec->sizeElem;
    }

    if(posIns <= last && cmp(elem, posIns) == 0) {
        if(update != NULL) {
            update(posIns, elem);
        }
        return false;
    }

    for(void* i = last; i >= posIns; i -= pVec->sizeElem) {
        memcpy(i + pVec->sizeElem, i, pVec->sizeElem);
    }

    memcpy(posIns, elem, pVec->sizeElem);
    pVec->lotElem ++;
    return true;
}

int Vector_bsearch(tVector* pVec, void* elem, Cmp cmp) {
    void* li = pVec->vec;
    void* ls = pVec->vec + (int)((pVec->lotElem - 1) * pVec->sizeElem);
    void* mid = li + ((ls - li) / pVec->sizeElem / 2) * pVec->sizeElem;
    int cmpCurent;

    if(pVec->lotElem == 0) {
        return -1;
    }

    while(li <= ls && (cmpCurent = cmp(elem, mid)) != 0) {
        if(cmpCurent < 0) {
            ls = mid - pVec->sizeElem;
        }
        else {
            li = mid + pVec->sizeElem;
        }
        mid = li + ((ls - li) / pVec->sizeElem / 2) * pVec->sizeElem;
    }

    if(li > ls) {
        return -1;
    }

    memcpy(elem, mid, pVec->sizeElem);
    return (mid - pVec->vec) / pVec->sizeElem;
}

bool Vector_update(tVector* pVec, const void* elem, Cmp cmp, Update update) {
    void* posUpd;
    void* last;

    if(pVec->lotElem == 0) {
        return false;
    }

    posUpd = pVec->vec;
    last = pVec->vec + (int)((pVec->lotElem - 1) * pVec->sizeElem);
    while (posUpd <= last && cmp(elem, posUpd) > 0) {
        posUpd += pVec->sizeElem;
    }

    if(posUpd <= last && cmp(elem, posUpd) == 0) {
        update(posUpd, elem);
        return true;
    }

    return false;
}

bool Vector_isEmpty(tVector* pVec) {
    return pVec->lotElem == 0;
}

void Vector_empty(tVector* pVec) {
    pVec->lotElem = 0;
}

bool Vector_insert(tVector* pVec, const void* elem)
{
    void* ult;
    if(pVec->lotElem == pVec->capacity)
    {
        if(!_Vector_resize(pVec, (unsigned) (pVec->capacity * 1.5)))
        {
            return false;
        }
    }
    ult = pVec->vec + pVec->lotElem * pVec->sizeElem;

    memcpy(ult, elem, pVec->sizeElem);
    pVec->lotElem++;

    return true;
}

void VectorIterator_create(tVectorIterator* pVecIter, tVector* pVec) {
    pVecIter->first = pVec->vec;
    pVecIter->last = pVec->vec + (int)((pVec->lotElem - 1) * pVec->sizeElem);
    pVecIter->current = NULL;
    pVecIter->sizeElem = pVec->sizeElem;
    pVecIter->finishIter = true;
}

void VectorIterator_first(tVectorIterator* pVecIter, void* elem) {
    if(pVecIter->first > pVecIter->last) {
        return;
    }

    pVecIter->current = pVecIter->first;
    pVecIter->finishIter = false;

    memcpy(elem, pVecIter->current, pVecIter->sizeElem);
}

void VectorIterator_next(tVectorIterator* pVecIter, void* elem) {
    if(pVecIter->current == pVecIter->last) {
        pVecIter->finishIter = true;
        return;
    }

    pVecIter->current += pVecIter->sizeElem;
    memcpy(elem, pVecIter->current, pVecIter->sizeElem);
}

bool VectorIterator_finished(tVectorIterator* pVecIter) {
    return pVecIter->finishIter;
}