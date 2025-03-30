#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init("Snake Game", SCREEN_WIDTH, SCREEN_HEIGHT)) {        return -1;
    }

    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
        SDL_Delay(400);
    }

    return 0;
}
