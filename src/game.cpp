#include <game.h>
#include <player_manager.h>
#include <world_map.h>
#include <enemy_manager.h>
#include <texture_manager.h>
#include <enemy_generator.h>
EnemyManager *enemy;
SDL_Renderer *Game::renderer = nullptr;
Game::Game() {}
Game::~Game() {}
const Uint8 *Game::keyboard_state = SDL_GetKeyboardState(NULL);
WorldMap *map;
PlayerManager *player;
EnemyGenerator *enemy_generator;
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
    player = new PlayerManager("res/player.png", 365, 300);
    enemy_generator = new EnemyGenerator("res/enemy_skeleton.png");
    map = new WorldMap();
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
    SDL_PumpEvents();

}
void Game::Update()
{
    player->Update();
    map->UpdateMap();
    enemy_generator->Update();
}
void Game::Render()
{
    SDL_RenderClear(renderer);
    // Render something here
    map->RenderMap();
    player->Render();
    enemy_generator->Render();
    SDL_RenderPresent(renderer);
}
void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}