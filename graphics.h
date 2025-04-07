#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include<vector>
#include <SDL_mixer.h>

using namespace std;

struct Sprite {
    SDL_Texture* texture;
    vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips[][4]);
    void tick();
    const SDL_Rect* getCurrentClip() const;
};

struct Graphics {
    Graphics();
    bool init();
    void quit();

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* dinoTexture;
    SDL_Texture* obstacleTexture;
    SDL_Texture* backgroundTexture;
    SDL_Texture* loadTexture(const char *filename);
};

#endif


