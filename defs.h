#ifndef DEFS_H
#define DEFS_H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GROUND_Y = 450;
const int JUMP_HEIGHT = 21;
const int GRAVITY = 1;

const int DINO_CLIPS[][4] = {
    {  0, 0, 174, 178},
    {174, 0, 174, 178}
};
const int DINO_FRAMES = sizeof(DINO_CLIPS)/sizeof(int)/4;

#endif

