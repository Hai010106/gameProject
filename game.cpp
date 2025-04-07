#include "game.h"
#include "music.h"

using namespace std;

Dino::Dino() {
    x = 100;
    y = GROUND_Y;
    vy = 0;
    isJumping = false;
}

void Dino::update() {
    y += vy;
    if (isJumping) {
        vy += GRAVITY;
    }
    if (y >= GROUND_Y) {
        y = GROUND_Y;
        vy = 0;
        isJumping = false;
    }
    frameCounter++;
    if (frameCounter >= 6) {
        sprite.tick();
        frameCounter = 0;
    }
}

Obstacle::Obstacle() {
    x = SCREEN_WIDTH;
    y = GROUND_Y;
}

Game::Game() {
    score = 0;
    obstacleSpeed = 8;
}

void Game::jump() {
    if (!dino.isJumping) {
        dino.vy = -JUMP_HEIGHT;
        dino.isJumping = true;
    }
}

bool Game::checkCollision() {
    SDL_Rect dinoRect = {dino.x, dino.y, 100, 100};
    SDL_Rect obstacleRect = {obstacle.x, obstacle.y, 50, 50};
    return SDL_HasIntersection(&dinoRect, &obstacleRect);
}

void Game::render(Graphics& graphics) {
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255);
    SDL_RenderClear(graphics.renderer);

    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(graphics.renderer, graphics.backgroundTexture, nullptr, &bgRect);

    SDL_Rect dinoRect = {dino.x, dino.y, 100, 100};
    SDL_RenderCopy(graphics.renderer, dino.sprite.texture, dino.sprite.getCurrentClip(), &dinoRect);

    SDL_Rect obstacleRect = {obstacle.x, obstacle.y, 100, 100};
    SDL_RenderCopy(graphics.renderer, graphics.obstacleTexture, nullptr, &obstacleRect);

    SDL_RenderPresent(graphics.renderer);
}

void Game::run(Graphics& graphics) {
    bool running = true;
    SDL_Event event;

    dino.sprite.init(graphics.dinoTexture, DINO_FRAMES, DINO_CLIPS);

    backgroundMusic = Music::loadMusic("music.mp3");
    Music::playMusic(backgroundMusic);

    jumpSound = Music::loadSound("jump.mp3");

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                jump();
                Music::playSound(jumpSound);
            }
        }

        dino.update();

        obstacle.x -= obstacleSpeed;
        if (obstacle.x < -50) {
            obstacle.x = SCREEN_WIDTH + rand() % 300;
            score++;
            cout << "Score: " << score << endl;
            if (score % 5 == 0 && obstacleSpeed <= 25) {
                obstacleSpeed += 1;
            }
        }

        if (checkCollision()) {
            cout << "Game Over! Your Score is: " << score << endl;
            running = false;
        }

        render(graphics);
        SDL_Delay(16);
    }
    if (backgroundMusic != nullptr) Mix_FreeMusic(backgroundMusic);
    if (jumpSound != nullptr) Mix_FreeChunk(jumpSound);
}


