#include "graphics.h"
#include "music.h"

void Sprite::init(SDL_Texture* _texture, int frames, const int _clips[][4]) {
    texture = _texture;

    SDL_Rect clip;
    for (int i = 0; i < frames; i++) {
        clip.x = _clips[i][0];
        clip.y = _clips[i][1];
        clip.w = _clips[i][2];
        clip.h = _clips[i][3];
        clips.push_back(clip);
    }
}

void Sprite::tick() {
    currentFrame = (currentFrame + 1) % clips.size();
}

const SDL_Rect* Sprite::getCurrentClip() const {
    return &(clips[currentFrame]);
}

Graphics::Graphics() {
    window = nullptr;
    renderer = nullptr;
    dinoTexture = nullptr;
    obstacleTexture = nullptr;
    backgroundTexture = nullptr;
}

SDL_Texture* Graphics::loadTexture(const char *filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (!texture) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to load texture %s: %s", filename, IMG_GetError());
    }
    return texture;
}

bool Graphics::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    window = SDL_CreateWindow("Dino Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
    }
    dinoTexture = loadTexture("dino.png");
    obstacleTexture = loadTexture("obstacle.png");
    backgroundTexture = loadTexture("background.png");
    if (!dinoTexture || !obstacleTexture || !backgroundTexture) {
        return false;
    }

    return true;
}

void Graphics::quit() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(dinoTexture);
    SDL_DestroyTexture(obstacleTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
