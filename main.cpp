#include "game.h"
#include "graphics.h"

int main(int argc, char* argv[]) {
    Graphics graphics;
    if (!graphics.init()) return -1;

    Game game;
    game.run(graphics);

    graphics.quit();
    return 0;
}
