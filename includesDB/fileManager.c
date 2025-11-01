#include "../headersDB/fileManager.h"

bool FileManager_initB(FILE** pFile, const char* fileName) {
    *pFile = fopen(fileName, "r+b");
    if (*pFile == NULL) {
        *pFile = fopen(fileName, "w+b");
        if (*pFile == NULL) {
            printf("Error creando %s\n", fileName);
            return false;
        }
    }

    return true;
}

bool FileManager_openB(FILE** pFile, const char* fileName) {
    *pFile = fopen(fileName, "r+b");
    if (*pFile == NULL) {
        return false;
    }

    return true;
}