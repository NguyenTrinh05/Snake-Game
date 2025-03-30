#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL.h>
#include <string>

class TextureManager {
public:
    static SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    static void draw(SDL_Texture* tex, SDL_Renderer* renderer, int x, int y, int width, int height);
};

#endif // TEXTUREMANAGER_H
