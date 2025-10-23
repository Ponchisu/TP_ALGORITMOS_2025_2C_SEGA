#include "../headers/soundManager.h"

int _SoundManager_cmpMusic(const void* elem1, const void* elem2);
int _SoundManager_cmpChunk(const void* elem1, const void* elem2);

bool SoundManager_loadMusic(tVector* pVec, const char* fileName, const char* id) {
    tMusic music;

    music.music = Mix_LoadMUS(fileName);
    if(music.music == NULL) {
        return false;
    }

    strncpy(music.id, id, SIZE_ID - 1);
    music.id[SIZE_ID - 1] = '\0';

    if(!Vector_insertInOrder(pVec, &music, _SoundManager_cmpMusic, NULL)) {
        return false;
    }

    return true;

}

bool SoundManager_loadChunk(tVector* pVec, const char* fileName, const char* id, int volume) {
    tChunk chunk;

    chunk.chunk = Mix_LoadWAV(fileName);
    if(chunk.chunk == NULL) {
        return false;
    }

    strncpy(chunk.id, id, SIZE_ID - 1);
    chunk.id[SIZE_ID - 1] = '\0';

    if(!Vector_insertInOrder(pVec, &chunk, _SoundManager_cmpChunk, NULL)) {
        return false;
    }
    Mix_VolumeChunk(chunk.chunk, volume);

    return true;
}

void SoundManager_cleanMusic(tVector* pVec) {
    tVectorIterator vecIter;
    tMusic music;
    VectorIterator_create(&vecIter, pVec);

    VectorIterator_first(&vecIter, &music);
    while (!VectorIterator_finished(&vecIter)) {
        Mix_FreeMusic(music.music);
        VectorIterator_next(&vecIter, &music);
    }
}

void SoundManager_cleanChunk(tVector* pVec) {
    tVectorIterator vecIter;
    tChunk chunk;
    VectorIterator_create(&vecIter, pVec);

    VectorIterator_first(&vecIter, &chunk);
    while (!VectorIterator_finished(&vecIter)) {
        Mix_FreeChunk(chunk.chunk);
        VectorIterator_next(&vecIter, &chunk);
    }
}

void SoundManager_playMusic(tVector* pVec, const char* id) {
    tMusic music;

    strcpy(music.id, id);

    if(Vector_bsearch(pVec, &music, _SoundManager_cmpMusic) == -1) {
        fprintf(stderr,"Error, la id '%s' no se encuentra.\n", id);
        return;
    }

    Mix_PlayMusic(music.music, -1);
}

void SoundManager_playChunk(tVector* pVec, const char* id) {
    tChunk chunk;

    strcpy(chunk.id, id);

    if(Vector_bsearch(pVec, &chunk, _SoundManager_cmpChunk) == -1) {
        fprintf(stderr,"Error, la id '%s' no se encuentra.\n", id);
        return;
    }

    Mix_PlayChannel(-1, chunk.chunk, 0);
}

int _SoundManager_cmpMusic(const void* elem1, const void* elem2) {
    const tMusic* music1 = elem1;
    const tMusic* music2 = elem2;
    return strcmp(music1->id, music2->id);
}

int _SoundManager_cmpChunk(const void* elem1, const void* elem2) {
    const tChunk* chunk1 = elem1;
    const tChunk* chunk2 = elem2;
    return strcmp(chunk1->id, chunk2->id);
}