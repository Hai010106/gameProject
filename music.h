#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer.h>
#include <SDL_log.h>

struct Music {
    Mix_Music* loadMusic(const char* path);
    void playMusic(Mix_Music* gMusic);
    Mix_Chunk* loadSound(const char* path);
    void playSound(Mix_Chunk* gChunk);
};

#endif


