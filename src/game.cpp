#include <game.h>
#include <player_manager.h>
#include <world_map.h>
#include <enemy_skeleton.h>
#include <texture_manager.h>
#include <enemy_generator.h>
#include <player_skill_q.h>
#include <player_skill_e.h>
#include <arrow_direction.h>
#include <shooter.h>
#include <level_manager.h>
#include <boss.h>
#include <boss_guider.h>

EnemySkeleton *enemy;
SDL_Renderer *Game::renderer = nullptr;
Game::Game() {}
Game::~Game() {}
const Uint8 *Game::keyboard_state = SDL_GetKeyboardState(NULL);
WorldMap *map;
PlayerManager *player;
PlayerSkillQ *player_skill_q;
PlayerSkillE *player_skill_e;
ArrowDirection *arrow_direction;
EnemyGenerator *enemy_generator;
LevelManager *level_manager;
Shooter *shooter;
Boss *boss;
BossGuider *boss_guider;
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

    if (TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        is_running = false;
        return;
    }
    window = SDL_CreateWindow(title, xpos, ypos, width, height, screen_mode);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    is_running = true;
    player = new PlayerManager("img/player/player.png", 365, 300);
    player_skill_q = new PlayerSkillQ();
    player_skill_e = new PlayerSkillE();
    arrow_direction = new ArrowDirection();
    enemy_generator = new EnemyGenerator();
    map = new WorldMap();
    shooter = new Shooter();
    level_manager = new LevelManager();
    boss = new Boss();
    boss_guider = new BossGuider();
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
    player_skill_e->Update();
    boss->Update();
    level_manager->Update();
    player->stats_bar->Update();
    shooter->Update();
    boss_guider->Update();
}
void Game::Render()
{
    SDL_RenderClear(renderer);
    // Render something here
    map->RenderMap();
    boss->RenderFire();
    player->Render();
    shooter->Render();
    enemy_generator->Render();
    boss->Render();
    player->stats_bar->Render();
    player_skill_q->Render();
    player_skill_e->Render();
    arrow_direction->Render();
    boss_guider->Render();

    if (Lost())
        RenderGameOver();
    if (Won())
        RenderGameWon();
    
    SDL_RenderPresent(renderer);
}
void Game::RenderGameOver()
{
    SDL_Texture *texture = TextureManager::LoadTexture("img/game/gameover.png");
    SDL_Rect dest_rect_tmp;
    dest_rect_tmp.x = 200;
    dest_rect_tmp.y = 170;
    dest_rect_tmp.w = 400;
    dest_rect_tmp.h = 240;
    TextureManager::Draw(texture, dest_rect_tmp);

    texture = TextureManager::LoadTexture("img/game/play_again_quit.png");
    dest_rect_tmp.x = 157;
    dest_rect_tmp.y = 420;
    dest_rect_tmp.w = 490;
    dest_rect_tmp.h = 35;
    TextureManager::Draw(texture, dest_rect_tmp);
}
void Game::RenderGameWon()
{
    SDL_Texture *texture = TextureManager::LoadTexture("img/game/gamewon.png");
    SDL_Rect dest_rect_tmp;
    dest_rect_tmp.x = 100;
    dest_rect_tmp.y = 100;
    dest_rect_tmp.w = 600;
    dest_rect_tmp.h = 340;
    TextureManager::Draw(texture, dest_rect_tmp);

    texture = TextureManager::LoadTexture("img/game/play_again_quit.png");
    dest_rect_tmp.x = 170;
    dest_rect_tmp.y = 355;
    dest_rect_tmp.w = 490;
    dest_rect_tmp.h = 35;
    TextureManager::Draw(texture, dest_rect_tmp);
}

bool Game::InsidePlayButton(int x, int y)
{
    return 320 <= x && x <= 480
        && 250 <= y && y <= 350;
}
bool Game::InsideHelpButton(int x, int y)
{
    return 320 <= x && x <= 480
        && 365 <= y && y <= 465;
}
bool Game::InsideExitButton(int x, int y)
{
    return 320 <= x && x <= 480
        && 480 <= y && y <= 580;
}

int Game::UpdateMouse() 
{
    int mousex, mousey;

    SDL_PumpEvents();

    Uint32 buttons = SDL_GetMouseState(&mousex, &mousey);

    bool changed = false;
    int play = InsidePlayButton(mousex, mousey);
    int help = InsideHelpButton(mousex, mousey);
    int exit = InsideExitButton(mousex, mousey);

    if (play != play_button_state || help != help_button_state || exit != exit_button_state)
        changed = true;
    play_button_state = play;
    help_button_state = help;
    exit_button_state = exit;

    if (help && (buttons & SDL_BUTTON_LMASK) != 0)
        return 1;
    if (exit && (buttons & SDL_BUTTON_LMASK) != 0)
        return 2;
    if (play && (buttons & SDL_BUTTON_LMASK) != 0)
        return 3;

    if (!changed) 
        return -1;
    return 0;
}

void Game::RenderMenu()
{
    SDL_RenderClear(renderer);
    map->RenderMap();
    SDL_Texture *title = TextureManager::LoadTexture("img/game/game_title.png");
    SDL_Rect dest, src;
    dest.x = 80;
    dest.y = 50;
    dest.w = 640;
    dest.h = 150;
    TextureManager::Draw(title, dest);

    title = TextureManager::LoadTexture("img/game/play_button.png");
    src.x = play_button_state * 150;
    src.y = 0;
    src.w = 150;
    src.h = 98;
    dest.x = 320;
    dest.y = 250;
    dest.w = 160;
    dest.h = 100;
    TextureManager::Draw(title, src, dest);

    title = TextureManager::LoadTexture("img/game/help_button.png");
    src.x = help_button_state * 150;
    src.y = 0;
    src.w = 150;
    src.h = 98;
    dest.x = 320;
    dest.y = 365;
    dest.w = 160;
    dest.h = 100;
    TextureManager::Draw(title, src, dest);

    title = TextureManager::LoadTexture("img/game/exit_button.png");
    src.x = exit_button_state * 150;
    src.y = 0;
    src.w = 150;
    src.h = 98;
    dest.x = 320;
    dest.y = 480;
    dest.w = 160;
    dest.h = 100;
    TextureManager::Draw(title, src, dest);

    SDL_RenderPresent(renderer);
}

void Game::RenderGuide()
{
    SDL_RenderClear(renderer);
    map->RenderMapFullGrass();
    SDL_Texture *title = TextureManager::LoadTexture("img/game/guide.png");
    SDL_Rect dest;
    dest.x = 80;
    dest.y = 110;
    dest.w = 660;
    dest.h = 680;
    TextureManager::Draw(title, dest);

    title = TextureManager::LoadTexture("img/game/instructions.png");
    dest.x = 300;
    dest.y = 35;
    dest.w = 500;
    dest.h = 550;
    TextureManager::Draw(title, dest);
    SDL_RenderPresent(renderer);
}

bool Game::Won()
{
    return !boss->IsAlive();
}
bool Game::Lost()
{
    return is_running == false;
}
void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    std::cout << "Game cleaned" << std::endl;
}

