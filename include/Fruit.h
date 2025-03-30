#ifndef FRUIT_H
#define FRUIT_H
#include <SDL.h>
#include <cstdlib>
#include <ctime>
#include "Vector2D.h"
#include "TextureManager.h"


class Fruit {
public:
    Fruit (int gridSize, int screenWidth, int screenHeight, SDL_Renderer* renderer);
    void respawn();
    void render(SDL_Renderer* renderer);
    Vector2D getPosition();

private:
    Vector2D position;
    int gridSize;
    int screenWidth, screenHeight;
    SDL_Renderer* renderer;
    SDL_Texture* fruitTexture;
};

#endif // FRUIT_H
