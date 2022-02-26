#include <game.h>
#include <iostream>
#include <assert.h>
#include <SDL_image.h>
#include <textureManager.h>
SDL_Texture *playerTex;
SDL_Rect srcR, destR;
Game::Game() {}
Game::~Game() {}
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int screen_mode = (fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL Failed Initializing..." << std::endl;
        isRunning = false;
        return;
    }
    window = SDL_CreateWindow(title, xpos, ypos, width, height, screen_mode);
    assert(window != nullptr);
    renderer = SDL_CreateRenderer(window, -1, 0);
    assert(renderer != nullptr);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    isRunning = true;
    playerTex = textureManager::loadTexture("res/player.png", renderer);
}
void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) 
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}
void Game::update()
{
    destR.h = 100;
    destR.w = 100;
    if (destR.x < 500) destR.x++;
    else destR.x--;
}
void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTex, NULL, &destR);
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}