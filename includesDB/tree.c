#include "../headersDB/tree.h"

void* _Tree_searchNotKey(const tTree* pTree, const void* notKey, Cmp cmp);

void Tree_create(tTree* pTree) {
    *pTree = NULL;
}

void Tree_clean(tTree* pTree) {
    if(*pTree != NULL) {
        Tree_clean(&(*pTree)->lower);
        Tree_clean(&(*pTree)->higher);
        free((*pTree)->info);
        free(*pTree);
        *pTree = NULL;
    }
}

bool Tree_insertInOrder(tTree* pTree, const void* elem, unsigned sizeElem, Cmp cmp, Update update) {
    int compare;

    if(*pTree != NULL) {
        compare = cmp(elem, (*pTree)->info);
        if(compare < 0)
            return Tree_insertInOrder(&(*pTree)->lower, elem, sizeElem, cmp, update);
        if(compare > 0)
            return Tree_insertInOrder(&(*pTree)->higher, elem, sizeElem, cmp, update);
        else {
            if(update != NULL)
                update((*pTree)->info, elem);
            return true;
        }
    }

    *pTree = malloc(sizeof(tNodeTree));
    if(*pTree == NULL) {
        fprintf(stderr, "ERROR MEM\n");
        return false;
    }

    (*pTree)->info = malloc(sizeElem);
    if((*pTree)->info == NULL) {
        fprintf(stderr, "ERROR MEM\n");
        return false;
    }

    memcpy((*pTree)->info, elem, sizeElem);
    (*pTree)->sizeElem = sizeElem;
    (*pTree)->higher = NULL;
    (*pTree)->lower = NULL;

    return true;
}

void* _Tree_searchNotKey(const tTree* pTree, const void* notKey, Cmp cmp) {
    void* info;

    if (*pTree == NULL)
    return NULL;

    if(cmp(notKey, (*pTree)->info) == 0) {
        return (*pTree)->info;
    }

    info = _Tree_searchNotKey(&(*pTree)->lower, notKey, cmp);
    if (info != NULL)
        return info;
    return _Tree_searchNotKey(&(*pTree)->higher, notKey, cmp);
}

void Tree_searchNotKey(tTree* pTree, void* notKey, Cmp cmp, Update update) {
    void* info = _Tree_searchNotKey(pTree, notKey, cmp);
    if(info != NULL) {
        update(notKey, info);
    }
}

bool Tree_loadFromFileB(tTree* pTree, FILE** pf, unsigned sizeElemFile, unsigned sizeElemIdx, Cmp cmp, Action action) {
    int i = 0;
    void* infoIdx;
    void* infoFile = malloc(sizeElemFile);
    if(infoFile == NULL) {
        fprintf(stderr, "Error al cargar memoria\n");
        return false;
    }

    infoIdx = malloc(sizeElemIdx);
    if(infoFile == NULL) {
        fprintf(stderr, "Error al cargar memoria\n");
        return false;
    }

    while (fread(infoFile, sizeElemFile, 1, *pf) == 1) {
        action(infoFile, infoIdx, &i);
        Tree_insertInOrder(pTree, infoIdx, sizeElemIdx, cmp, NULL);
        i++;
    }

    free(infoIdx);
    free(infoFile);
    return true;
}

void Tree_uploadTreeToFileB(tTree* pTree, FILE** pf, Action action) {
    if(*pTree != NULL) {
        Tree_uploadTreeToFileB(&(*pTree)->lower, pf, action);
        action((*pTree)->info, pf, NULL);
        Tree_uploadTreeToFileB(&(*pTree)->higher, pf, action);
    }
}



bool Tree_loadBalancedFromFile(tTree* pTree, FILE** fp, unsigned sizeElem, Cmp cmp) {
    int end;
    void* info = malloc(sizeElem);

    if(info == NULL) {
        fprintf(stderr, "Error al cargar memoria\n");
        fclose(*fp);
        return false;
    }


    fseek(*fp, 0, SEEK_END);
    end = (ftell(*fp) / sizeElem) - 1;
    rewind(*fp);

    Tree_insertInBalanced(pTree, info, sizeElem, 0, end, fp);

    free(info);
    return true;
}

bool Tree_insertInBalanced(tTree* pTree, void* info, unsigned sizeElem, int start, int end, FILE** fp) {
    int mid;

    if(start <= end) {
        mid = (start + end) / 2;
        fseek(*fp, mid * sizeElem, SEEK_SET);
        fread(info, sizeElem, 1, *fp);

        *pTree = malloc(sizeof(tNodeTree));
        if (!*pTree) {
            return false;
        }
        (*pTree)->info = malloc(sizeElem);
        if((*pTree)->info == NULL) {
            free(*pTree);
            return false;
        }

        memcpy((*pTree)->info, info, sizeElem);
        (*pTree)->sizeElem = sizeElem;
        (*pTree)->higher = NULL;
        (*pTree)->lower = NULL;


        if (Tree_insertInBalanced(&(*pTree)->lower, info, sizeElem, start, mid - 1, fp) == false) {
            return false;
        }
        return Tree_insertInBalanced(&(*pTree)->higher, info, sizeElem, mid + 1, end, fp);
    }

    return true;
}

bool Tree_searchByKey(const tTree* pTree, void* elem, Cmp cmp, Update update) {
    int result;
    while (*pTree != NULL){
        result = cmp(elem, (*pTree)->info);

        if (result < 0)
            pTree = &((*pTree)->lower);
        else if (result > 0)
            pTree = &((*pTree)->higher);
        else {
            if(update != NULL)
                update(elem, (*pTree)->info);
            return true;
        }
    }
    return false;
}
