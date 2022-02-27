#include <game.h>
#include <iostream>
#include <SDL_image.h>
#include <texture_manager.h>
#include <game_object.h>
SDL_Texture *player_tex;
GameObject *player;
SDL_Renderer *Game::renderer = nullptr;
Game::Game() {}
Game::~Game() {}
void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int screen_mode = (fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL Failed Initializing..." << std::endl;
        is_running = false;
        return;
    }
    window = SDL_CreateWindow(title, xpos, ypos, width, height, screen_mode);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    is_running = true;
    player_tex = TextureManager::LoadTexture("res/player.png");
    player = new GameObject("res/player.png", 0, 0);
}
void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) 
    {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}
void Game::Update()
{
    player->Update();
}
void Game::Render()
{
    SDL_RenderClear(renderer);
    // Render something here
    player->Render();
    SDL_RenderPresent(renderer);
}
void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}