#include "Fruit.h"
#include "TextureManager.h"

Fruit::Fruit(int gridSize, int screenWidth, int screenHeight, SDL_Renderer* renderer) {
    this->gridSize = gridSize;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    std::srand(std::time(nullptr));
    fruitTexture = TextureManager::loadTexture("Image/apple.png", renderer);
    respawn();
}

void Fruit::respawn() {
    position.x = (std::rand() % (screenWidth / gridSize));
    position.y = (std::rand() % (screenHeight / gridSize));
}

void Fruit::render(SDL_Renderer* renderer) {
    SDL_Rect destRect = { position.x * gridSize, position.y * gridSize, gridSize, gridSize };
    TextureManager::draw(fruitTexture, renderer, destRect.x, destRect.y, destRect.w, destRect.h);
}


Vector2D Fruit::getPosition() {
    return position;
}

