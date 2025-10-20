#ifndef AWARDS_H_INCLUDED
#define AWARDS_H_INCLUDED

#include <string.h>

typedef struct 
{
    char id[10];
    int x;
    int y;
}tAwards;

void Awards_create(tAwards* pAwards, int y, int x, const char* id);
int Awards_cmp(const void* elem1, const void* elem2);
int Awards_getX(tAwards* pAwards);
int Awards_getY(tAwards* pAwards);

#endif // AWARDS_H_INCLUDED
