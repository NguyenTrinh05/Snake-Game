#ifndef SNAKE_H
#define SNAKE_H


#include <vector>
#include <SDL.h>
#include "Vector2D.h"
#include "TextureManager.h"

class Snake {
public:
    Snake(int gridSize);
    void update();
    void render(SDL_Renderer* renderer);
    void setDirection(int dx, int dy);
    void increaseSpeed();
    bool checkCollision(int screenWidth, int screenHeight);
    std::vector<Vector2D> getBody();
    void grow();

private:
    int gridSize;
    int speed;
    std::vector<Vector2D> body;
    Vector2D direction;
    Uint32 lastUpdateTime;
    bool growing = false;
};

#endif // SNAKE_H
