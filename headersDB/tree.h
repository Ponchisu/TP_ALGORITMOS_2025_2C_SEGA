#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headersDB/bool.h"

typedef struct sNodeTree {
    void* info;
    unsigned sizeElem;
    struct sNodeTree* lower;
    struct sNodeTree* higher;
}tNodeTree;

typedef tNodeTree* tTree;
typedef int (*Cmp)(const void* elem1, const void* elem2);
typedef void (*Update)(void* elem1, const void* elem2);
typedef void (*Action)(void* elem1, void* elem2, void* elem3);

void Tree_create(tTree* pTree);
void Tree_clean(tTree* pTree);
bool Tree_insertInOrder(tTree* pTree, const void* elem, unsigned sizeElem, Cmp cmp, Update update);

void Tree_searchNotKey(tTree* pTree, void* notKey, Cmp cmp, Update update);
bool Tree_loadFromFileB(tTree* pTree, FILE** fp, unsigned sizeElemFile, unsigned sizeElemIdx, Cmp cmp, Action action);
void Tree_uploadTreeToFileB(tTree* pTree, FILE** pf, Action action);

bool Tree_loadBalancedFromFile(tTree* pTree, FILE** fp, unsigned sizeElem, Cmp cmp);
bool Tree_insertInBalanced(tTree* pTree, void* info, unsigned sizeElem, int start, int end, FILE** fp);
bool Tree_searchByKey(const tTree* pTree, void* elem, Cmp cmp, Update update);


#endif // TREE_H_INCLUDED
