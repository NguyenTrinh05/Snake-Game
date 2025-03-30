#include "Game.h"
#include "TextureManager.h"

Game::Game() {
    window = nullptr;
    renderer = nullptr;
    isRunning = false;
}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << SDL_GetError();
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << SDL_GetError();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << SDL_GetError();
        return false;
    }

    snake = new Snake(20);
    fruit = new Fruit(20, width, height, renderer );
    showMenu();
    isRunning = true;
    isGameOver = false;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: snake->setDirection(0, -1); break;
                case SDLK_DOWN: snake->setDirection(0, 1); break;
                case SDLK_LEFT: snake->setDirection(-1, 0); break;
                case SDLK_RIGHT: snake->setDirection(1, 0); break;
            }
        }
    }
}

void Game::update() {

    if (!isGameOver) {
        snake->update();
        checkFruitCollision();
        if (snake->checkCollision(screenWidth, screenHeight)) {
            isGameOver = true;
            showEndScreen();
        }
    }
}


void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    fruit->render(renderer);
    snake->render(renderer);
    SDL_RenderPresent(renderer);
}

void Game::checkFruitCollision() {
   if (snake->getBody()[0].x == fruit->getPosition().x &&
        snake->getBody()[0].y == fruit->getPosition().y) {
        fruit->respawn();
        snake->grow();
        snake->increaseSpeed();
    }
}

void Game::showEndScreen() {
    SDL_Texture* endScreenTexture = TextureManager::loadTexture("Image/game.png", renderer);

    if (!endScreenTexture) {
        return;
    }

    SDL_Rect destRect = {screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2};
    SDL_RenderCopy(renderer, endScreenTexture, NULL, &destRect);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool waitForKey = true;
    while (waitForKey) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                waitForKey = false;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                waitForKey = false;
                resetGame();
            }
        }
    }

    SDL_DestroyTexture(endScreenTexture);
}

void Game::resetGame() {
    delete snake;
    delete fruit;

    snake = new Snake(20);
    fruit = new Fruit(20, screenWidth, screenHeight, renderer);

    isGameOver = false;
}

void Game::showMenu() {
    menuTexture = TextureManager::loadTexture("Image/play.png", renderer);
    if (!menuTexture) {
        return;
    }

    SDL_Event event;
    while (inMenu) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                inMenu = false;
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                inMenu = false;
            }
        }

        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(menuTexture);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::running() {
    return isRunning;
}


