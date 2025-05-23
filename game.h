#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "music.h"

using namespace std;

struct Dino {
    int x, y;
    int vy;
    bool isJumping;
    Sprite sprite;
    int frameCounter;
    void update();
    Dino();
};

struct Obstacle {
    int x, y;
    Obstacle();
};

struct Game {
    void run(Graphics& graphics);
    Game();

private:
    Dino dino;
    Obstacle obstacle;
    int score;
    int obstacleSpeed;
    Music music;
    Mix_Music* backgroundMusic;
    Mix_Chunk* jumpSound;
    bool checkCollision();
    void render(Graphics& graphics);
    void jump();
};

#endif

