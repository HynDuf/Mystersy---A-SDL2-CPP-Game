#include <game.h>
#include <player_manager.h>
#include <world_map.h>
#include <enemy_manager.h>
#include <texture_manager.h>
#include <enemy_generator.h>
#include <player_skill_q.h>
#include <arrow_direction.h>

EnemyManager *enemy;
SDL_Renderer *Game::renderer = nullptr;
Game::Game() {}
Game::~Game() {}
const Uint8 *Game::keyboard_state = SDL_GetKeyboardState(NULL);
WorldMap *map;
PlayerManager *player;
PlayerSkillQ *player_skill_q;
ArrowDirection *arrow_direction;
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
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        is_running = false;
        return;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        is_running = false;
        return;
    }
    window = SDL_CreateWindow(title, xpos, ypos, width, height, screen_mode);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    is_running = true;
    player = new PlayerManager("img/player/player.png", 365, 300);
    player_skill_q = new PlayerSkillQ();
    arrow_direction = new ArrowDirection();
    enemy_generator = new EnemyGenerator("img/enemy/enemy_skeleton.png");
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
    enemy_generator->Update();
    player->Update();
    map->UpdateMap();
    if (player->IsAlive() == false)
        is_running = false;
    player_skill_q->Update();
}
void Game::Render()
{
    SDL_RenderClear(renderer);
    // Render something here
    map->RenderMap();
    player->Render();
    enemy_generator->Render();
    player->health_box->Render();
    player_skill_q->Render();
    arrow_direction->Render();
    if (is_running == false)
        RenderGameOver();
    
    SDL_RenderPresent(renderer);
}
void Game::RenderGameOver()
{
    SDL_Texture *texture = TextureManager::LoadTexture("img/game/gameover.png");
    SDL_Rect dest_rect_tmp;
    dest_rect_tmp.x = 200;
    dest_rect_tmp.y = 200;
    dest_rect_tmp.w = 400;
    dest_rect_tmp.h = 240;
    TextureManager::Draw(texture, dest_rect_tmp);
}
void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}