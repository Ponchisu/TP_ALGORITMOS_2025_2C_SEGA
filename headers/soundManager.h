#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../headers/bool.h"
#include "../headers/vector.h"


#define SIZE_ID 20

typedef struct 
{
    char id[SIZE_ID];
    Mix_Music* music;
}tMusic;

typedef struct 
{
    char id[SIZE_ID];
    Mix_Chunk* chunk;
}tChunk;

bool SoundManager_loadMusic(tVector* pVec, const char* fileName, const char* id);
bool SoundManager_loadChunk(tVector* pVec, const char* fileName, const char* id, int volume);
void SoundManager_cleanMusic(tVector* pVec);
void SoundManager_cleanChunk(tVector* pVec);
void SoundManager_playMusic(tVector* pVec, const char* id);
void SoundManager_playChunk(tVector* pVec, const char* id);



#endif // SOUNDMANAGER_H_INCLUDED
