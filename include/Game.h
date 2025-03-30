#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Snake.h"
#include "Fruit.h"
#include "TextureManager.h"


class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void checkFruitCollision();
    void showEndScreen();
    void resetGame();
    void showMenu();
    void clean();
    bool running();

private:
    int screenWidth;
    int screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    bool isGameOver;
    SDL_Texture* menuTexture;
    bool inMenu = true;
    Snake* snake;
    Fruit* fruit;

};

#endif
