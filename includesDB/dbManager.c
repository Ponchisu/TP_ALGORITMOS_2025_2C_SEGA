#include "../headersDB/dbManager.h"

int _PlayerIndex_cmpName(const void* elem1, const void* elem2);
int _PlayerIndex_cmpId(const void* elem1, const void* elem2);
void _PlayerIndex_update(void* elem1, const void* elem2);
void _PlayerIndex_load(void* elem1, void* elem2, void* elem3);
void _PlayerIndex_loadToFile(void* elem1, void* elem2, void* elem3);
int _PlayerRank_cmpId(const void* elem1, const void* elem2);
void _PlayerRank_update(void* elem1, const void* elem2);
int _PlayerRank_cmpPoints(const void* elem1, const void* elem2);

int _PlayerIndex_cmpName(const void* elem1, const void* elem2) {
    const tPlayerIndex* player1 = elem1;
    const tPlayerIndex* player2 = elem2;
    return strcmp(player1->name, player2->name);
}

int _PlayerIndex_cmpId(const void* elem1, const void* elem2) {
    const tPlayerIndex* player1 = elem1;
    const tPlayerIndex* player2 = elem2;
    return player1->idPlayer - player2->idPlayer;
}

void _PlayerIndex_update(void* elem1, const void* elem2) {
    tPlayerIndex* playerUpd = elem1;
    const tPlayerIndex* player2 = elem2;
    playerUpd->idPlayer = player2->idPlayer;
    playerUpd->offset = player2->offset;
    strcpy(playerUpd->name, player2->name);
}

void _PlayerIndex_load(void* elem1, void* elem2, void* elem3) {
    tPlayer* player = (tPlayer*) elem1;
    tPlayerIndex* playerIdx = (tPlayerIndex*) elem2;
    unsigned* offset = (unsigned*) elem3;

    playerIdx->idPlayer = player->idPlayer;
    strcpy(playerIdx->name, player->name);
    playerIdx->offset = *offset;
}

void _PlayerIndex_loadToFile(void* elem1, void* elem2, void* elem3) {
    FILE** fp = (FILE**) elem2;
    fwrite(elem1, sizeof(tPlayerIndex), 1, *fp);
}

int _PlayerRank_cmpId(const void* elem1, const void* elem2) {
    const tPlayerRank* pRank1 = elem1;
    const tPlayerRank* pRank2 = elem2;
    return pRank1->idPlayer - pRank2->idPlayer;
}

void _PlayerRank_update(void* elem1, const void* elem2) {
    tPlayerRank* pRank1 = elem1;
    const tPlayerRank* pRank2 = elem2;
    pRank1->pointsTotal += pRank2->pointsTotal;
}

int _PlayerRank_cmpPoints(const void* elem1, const void* elem2) {
    const tPlayerRank* pRank1 = elem1;
    const tPlayerRank* pRank2 = elem2;
    return pRank2->pointsTotal - pRank1->pointsTotal;
}

bool DataBase_init(tDbManager* pDb) {
    FILE* fpPlayer;
    FILE* fpRuns;
    FILE* fpPlayerIdx;
    FILE* fpRanking;

    Tree_create(&pDb->treePlayerIdx);

    if(FileManager_initB(&fpRuns, FILE_NAME_RUNS) == false) {
        fprintf(stderr,"Error al abrir/crear archivo runs\n");
        return false;
    }

    if(FileManager_initB(&fpPlayer, FILE_NAME_PLAYER) == false) {
        fprintf(stderr,"Error al abrir/crear archivo users\n");
        fclose(fpRuns);
        return false;
    }

    if(FileManager_openB(&fpPlayerIdx, FILE_NAME_PLAYERIDX) == false) {
        if(FileManager_initB(&fpPlayerIdx, FILE_NAME_PLAYERIDX) == false) {
            fprintf(stderr,"Error al abrir/crear archivo indx\n");
            fclose(fpRuns);
            fclose(fpPlayer);
            return false;
        }
        if(!DataBase_createIndx(&fpPlayerIdx, &fpPlayer)) {
            fprintf(stderr,"Error al abrir/crear archivo indx\n");
            fclose(fpRuns);
            fclose(fpPlayer);
            return false;
        }
        rewind(fpPlayerIdx);
    }

    Tree_loadBalancedFromFile(&pDb->treePlayerIdx, &fpPlayerIdx, sizeof(tPlayerIndex), _PlayerIndex_cmpId);

    if(FileManager_initB(&fpRanking, FILE_NAME_RANKING) == false) {
        fprintf(stderr,"Error al abrir/crear archivo ranking\n");
        fclose(fpRuns);
        fclose(fpPlayer);
        fclose(fpPlayerIdx);
        return false;
    }
    if(!DataBase_createRanking(pDb, &fpRanking, &fpRuns)) {
        fprintf(stderr,"Error al abrir/crear archivo ranking\n");
        fclose(fpRuns);
        fclose(fpPlayer);
        fclose(fpPlayerIdx);
        return false;
    }

    fseek(fpPlayer, 0 , SEEK_END);
    pDb->lastPlayerID = ftell(fpPlayer) / sizeof(tPlayer) -1;
    fseek(fpRuns, 0, SEEK_END);
    pDb->lastRunID = ftell(fpRuns) / sizeof(tRuns) -1;


    fclose(fpRuns);
    fclose(fpPlayer);
    fclose(fpPlayerIdx);
    fclose(fpRanking);
    return true;
}

bool DataBase_createRanking(tDbManager* pDb, FILE** fpRanking, FILE**  fpRuns) {
    tList list;
    tPlayerIndex playerIdx;
    tPlayerRank playerRank;
    tRuns run;
    int i = 0;

    rewind(*fpRuns);
    List_create(&list);

    while(fread(&run, sizeof(tRuns), 1, *fpRuns) == 1){
        playerIdx.idPlayer = run.idPlayer;
        strcpy(playerIdx.name, "");
        playerIdx.offset = -1;

        Tree_searchByKey(&pDb->treePlayerIdx, &playerIdx, _PlayerIndex_cmpId, _PlayerIndex_update);
        strcpy(playerRank.name, playerIdx.name);
        playerRank.pointsTotal = run.points;
        playerRank.idPlayer = playerIdx.idPlayer;

        List_insertInOrder(&list, &playerRank, sizeof(tPlayerRank), _PlayerRank_cmpId, _PlayerRank_update);
    }

    List_sort(&list, _PlayerRank_cmpPoints);

    while(!List_isEmpty(&list) && i < TOP_RANKING){
        List_getFirst(&list, &playerRank, sizeof(tPlayerRank));
        fwrite(&playerRank, sizeof(tPlayerRank), 1, *fpRanking);
        i++;
    }
    List_clean(&list);
    return true;
}

bool DataBase_createIndx(FILE** fpIdx, FILE** fp) {
    tTree treeAux;

    Tree_create(&treeAux);

    if(!Tree_loadFromFileB(&treeAux, fp, sizeof(tPlayer), sizeof(tPlayerIndex), _PlayerIndex_cmpId, _PlayerIndex_load)) {
        return false;
    }
    Tree_uploadTreeToFileB(&treeAux, fpIdx, _PlayerIndex_loadToFile);

    Tree_clean(&treeAux);
    return true;
}

bool DataBase_updateIndx(tDbManager* pDb) {
    FILE* fpIndx = fopen(FILE_NAME_PLAYERIDX, "wb");
    if(fpIndx == NULL) {
        fprintf(stderr, "Error al actualizar idx\n");
        return false;
    }

    Tree_uploadTreeToFileB(&pDb->treePlayerIdx, &fpIndx, _PlayerIndex_loadToFile);

    Tree_clean(&pDb->treePlayerIdx);
    fclose(fpIndx);
    return true;
}

bool DataBase_registerPlayer(tDbManager* pDb,const char* buffer, char* response) {
    tPlayerIndex playerIndx;
    tPlayer player;
    FILE* fpPlayer;

    if(FileManager_initB(&fpPlayer, FILE_NAME_PLAYER) == false) {
        fprintf(stderr,"Error al abrir/crear archivo users\n");
        return false;
    }

    strcpy(playerIndx.name, buffer);
    playerIndx.idPlayer = -1;

    puts(playerIndx.name);

    Tree_searchNotKey(&pDb->treePlayerIdx, &playerIndx, _PlayerIndex_cmpName, _PlayerIndex_update);

    if (playerIndx.idPlayer != -1) {
        if(response != NULL){
            strcpy(response, "Player ya existente\n");
        }
        return false;
    }

    pDb->lastPlayerID ++;
    strcpy(player.name, buffer);
    player.idPlayer = pDb->lastPlayerID;
    player.movesTotal = 0;
    player.pointsTotal = 0;
    player.runsTotal = 0;

    playerIndx.idPlayer = pDb->lastPlayerID;
    strcpy(playerIndx.name, buffer);
    playerIndx.offset = pDb->lastPlayerID;
    Tree_insertInOrder(&pDb->treePlayerIdx, &playerIndx, sizeof(tPlayerIndex), _PlayerIndex_cmpId, NULL);


    fseek(fpPlayer, 0, SEEK_END);
    fwrite(&player, sizeof(tPlayer), 1, fpPlayer);
    if(response != NULL) {
        strcpy(response, "Player registrado\n");
    }


    fclose(fpPlayer);
    return true;
}


bool Database_registerNewRun(tDbManager* pDb, const char* buffer, char* response) {
    char name[SIZE_NAME];
    FILE* fpRuns;
    FILE* fpPlayer;
    FILE* fpRanking;
    tRuns run;
    tPlayerIndex playerIndx;
    tPlayer player;

    if(FileManager_initB(&fpRuns, FILE_NAME_RUNS) == false) {
        fprintf(stderr,"Error al abrir/crear archivo runs\n");
        return false;
    }

    if(FileManager_initB(&fpPlayer, FILE_NAME_PLAYER) == false) {
        fprintf(stderr,"Error al abrir/crear archivo player\n");
        fclose(fpRuns);
        return false;
    }

    if(FileManager_initB(&fpRanking, FILE_NAME_RANKING) == false) {
        fprintf(stderr,"Error al abrir/crear archivo ranking\n");
        fclose(fpRuns);
        fclose(fpPlayer);
        return false;
    }

    sscanf(buffer,"%[^|]|%d|%d", name, &run.points, &run.moves);

    strcpy(playerIndx.name, name);
    Tree_searchNotKey(&pDb->treePlayerIdx, &playerIndx, _PlayerIndex_cmpName, _PlayerIndex_update);

    pDb->lastRunID ++;
    run.idPlayer = playerIndx.idPlayer;
    run.idRun = pDb->lastRunID;

    fseek(fpRuns, 0, SEEK_END);
    fwrite(&run, sizeof(tRuns), 1, fpRuns);
    if(response != NULL) {
        strcpy(response, "Run registrada\n");
    }


    fseek(fpPlayer, playerIndx.offset * sizeof(tPlayer), SEEK_SET);
    fread(&player, sizeof(tPlayer), 1, fpPlayer);

    player.movesTotal  += run.moves;
    player.pointsTotal += run.points;
    player.runsTotal ++;

    fseek(fpPlayer, playerIndx.offset * sizeof(tPlayer), SEEK_SET);
    fwrite(&player, sizeof(tPlayer), 1, fpPlayer);

    DataBase_createRanking(pDb, &fpRanking, &fpRuns);

    fclose(fpPlayer);
    fclose(fpRuns);
    fclose(fpRanking);
    return true;
}

bool Database_getRanking(tDbManager* pDb, char* response) {
    FILE* fpRanking;
    tPlayerRank player;
    char buffer[200];

    strcpy(response, "|");

    if(FileManager_initB(&fpRanking, FILE_NAME_RANKING) == false) {
        fprintf(stderr,"Error al abrir/crear archivo ranking\n");
        return false;
    }
    while(fread(&player, sizeof(tPlayerRank), 1, fpRanking) == 1) {
        sprintf(buffer, "%d %s %d|", player.idPlayer, player.name, player.pointsTotal);
        strcat(response, buffer);
    }

    return true;
}
