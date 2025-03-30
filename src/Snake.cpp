#include "Snake.h"
#include <iostream>

Snake::Snake(int gridSize) {
    this->gridSize = gridSize;
    body.push_back({5, 5});
    direction = {1, 0};
    speed = 200;
    lastUpdateTime = SDL_GetTicks();
}

void Snake::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastUpdateTime < static_cast<Uint32>(speed)) {
        return;
    }
    lastUpdateTime = currentTime;
    for (int i = body.size() - 1; i > 0; i--) {
        body[i] = body[i - 1];
    }
    body[0].x += direction.x;
    body[0].y += direction.y;

}

void Snake::render(SDL_Renderer* renderer) {
    for (size_t i = 0; i < body.size(); i++) {
        if (i == 0) {
            SDL_SetRenderDrawColor(renderer, 135, 206, 255, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        SDL_Rect rect = {body[i].x * gridSize, body[i].y * gridSize, gridSize, gridSize};
        SDL_RenderFillRect(renderer, &rect);
    }
}


void Snake::setDirection(int dx, int dy) {
    if ((dx != -direction.x || dy != -direction.y) && (dx != direction.x || dy != direction.y)) {
        direction = {dx, dy};
    }
}

void Snake::increaseSpeed() {
    if (speed > 50) {
        speed -= 10;
    }
}

bool Snake::checkCollision(int screenWidth, int screenHeight) {
    Vector2D head = body[0];
    if (head.x < 0 || head.y < 0 || head.x >= screenWidth / gridSize || head.y >= screenHeight / gridSize) {
        return true;
    }
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i].x == body[0].x && body[i].y == body[0].y) {
            return true;
        }
    }
    return false;
}

void Snake::grow() {
    Vector2D tail = body.back();
    tail.x -= direction.x;
    tail.y -= direction.y;
    body.push_back(tail);
}

std::vector<Vector2D> Snake::getBody() {
    return body;
}


