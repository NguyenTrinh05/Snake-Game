#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (tex == nullptr) {
        std::cerr << SDL_GetError();
    }
    return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Renderer* renderer, int x, int y, int width, int height) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, tex, nullptr, &destRect);
}
