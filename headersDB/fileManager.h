#ifndef FILEMANAGER_H_INCLUDED
#define FILEMANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../headersDB/bool.h"

typedef int (*ActionFile)(const char* fileName, FILE* pf, void* data);
bool FileManager_initB(FILE** pFile, const char* fileName);
bool FileManager_openB(FILE** pFile, const char* fileName);

#endif // FILEMANAGER_H_INCLUDED
