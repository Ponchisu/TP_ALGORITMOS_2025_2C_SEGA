#ifndef DBMANAGER_H_INCLUDED
#define DBMANAGER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include "../headersDB/fileManager.h"
#include "../headersDB/tree.h"
#include "../headersDB/list.h"

#define SIZE_NAME 11
#define BUFFER_SIZE 1024
#define TOP_RANKING 10

#define FILE_NAME_RUNS "files/runs.dat"
#define FILE_NAME_PLAYER "files/player.dat"
#define FILE_NAME_PLAYERIDX "files/player.idx"
#define FILE_NAME_RANKING "files/ranking.dat"

typedef struct {
    tTree treePlayerIdx;
    unsigned lastPlayerID;
    unsigned lastRunID;
}tDbManager;

typedef struct {
    unsigned idPlayer;
    char name[SIZE_NAME];
    unsigned runsTotal;
    unsigned pointsTotal;
    unsigned movesTotal;
}tPlayer;

typedef struct {
    unsigned idRun;
    unsigned idPlayer;
    unsigned moves;
    unsigned points;
}tRuns;

typedef struct {
    unsigned idPlayer;
    char name[SIZE_NAME];
    unsigned offset;
}tPlayerIndex;

typedef struct {
    unsigned idPlayer;
    char name[SIZE_NAME];
    unsigned pointsTotal;
}tPlayerRank;


bool DataBase_init(tDbManager* pDb);
bool DataBase_createRanking(tDbManager* pDb, FILE** fpRanking, FILE**  fpRuns);
bool DataBase_createIndx(FILE** pfIdx, FILE** pf);
bool DataBase_updateIndx(tDbManager* pDb);
bool DataBase_registerPlayer(tDbManager* pDb,const char* buffer, char* response);
bool Database_registerNewRun(tDbManager* pDb,const char* buffer, char* response);
bool Database_getRanking(tDbManager* pDb, char* response);


#endif // DBMANAGER_H_INCLUDED
