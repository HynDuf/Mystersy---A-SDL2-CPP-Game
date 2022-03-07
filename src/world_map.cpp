#include <world_map.h>
#include <game.h>
#include <perlin_noise.h>

PerlinNoise *perlin_noise = new PerlinNoise();
WorldMap::WorldMap(PlayerManager *_player)
{
    player_tmp = _player;
    grass[0] = TextureManager::LoadTexture("res/deep_water_0.png");
    grass[1] = TextureManager::LoadTexture("res/water_0.png");
    grass[2] = TextureManager::LoadTexture("res/grass_10.png");
    grass[3] = TextureManager::LoadTexture("res/grass_21.png");
    grass[4] = TextureManager::LoadTexture("res/grass_20.png");
    grass[5] = TextureManager::LoadTexture("res/rock_0.png");
    xdif = ydif = 0;
    tmp_src.x = tmp_src.y = 0;
    tmp_src.h = tmp_src.w = 32;
}

WorldMap::~WorldMap()
{
    for (int i = 0; i < 6; i++) SDL_DestroyTexture(grass[i]);
}

int WorldMap::GetTileType(int x, int y)
{
    double val = perlin_noise->GetPerlinNoise2D(x, y);
    if (val < 0.09) 
        return 0;
    if (val < 0.27) 
        return 1;
    if (val < 0.75) 
        return 2;
    if (val < 0.92) 
        return (x & 1) ? 3 : 4;
    return 5;
}

void WorldMap::UpdateMap()
{
    
    player_tmp->sprite->ApplyAnimation("idle");
    if (Game::keyboard_state[SDL_SCANCODE_A] && Game::keyboard_state[SDL_SCANCODE_W])
    {
        xdif -= player_tmp->transform->speed;
        ydif -= player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D] && Game::keyboard_state[SDL_SCANCODE_W])
    {
        xdif += player_tmp->transform->speed;
        ydif -= player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_A] && Game::keyboard_state[SDL_SCANCODE_S])
    {
        xdif -= player_tmp->transform->speed;
        ydif += player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D] && Game::keyboard_state[SDL_SCANCODE_S])
    {
        xdif += player_tmp->transform->speed;
        ydif += player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_W])
    {
        ydif -= player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_S])
    {
        ydif += player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_A])
    {
        xdif -= player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D])
    {
        xdif += player_tmp->transform->speed;
        return;
    }
}

void WorldMap::RenderMap()
{
    int x_left = -((xdif % 32 + 32) % 32);

    int y_left = -((ydif % 32 + 32) % 32);
    int X_tile = (xdif / 32) + ((x_left != 0 && xdif < 0) ? -1 : 0);
    int Y_tile = (ydif / 32) + ((y_left != 0 && ydif < 0) ? -1 : 0);
    for (int x = x_left, x_tile = X_tile; x < 800; x += 32, x_tile++)
        for (int y = y_left, y_tile = Y_tile; y < 640; y += 32, y_tile++)
    {
        int tile_type = GetTileType(x_tile, y_tile);
        tmp_dest.h = tmp_dest.w = 32;
        tmp_dest.x = x;
        tmp_dest.y = y;
        if (tile_type == 5)
            TextureManager::Draw(grass[4], tmp_src, tmp_dest);
        TextureManager::Draw(grass[tile_type], tmp_src, tmp_dest);
    }
}

