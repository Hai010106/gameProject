#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer.h>
#include <SDL_log.h>

struct Music {
    static Mix_Music* loadMusic(const char* path);
    static void playMusic(Mix_Music* gMusic);
    static Mix_Chunk* loadSound(const char* path);
    static void playSound(Mix_Chunk* gChunk);
};

#endif


