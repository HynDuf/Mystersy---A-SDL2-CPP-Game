#include <world_map.h>
#include <game.h>
#include <perlin_noise.h>

PerlinNoise *perlin_noise = new PerlinNoise();
WorldMap::WorldMap(PlayerManager *_player)
{
    player_tmp = _player;
    tile_type[0] = TextureManager::LoadTexture("res/deep_water.png");
    tile_type[1] = TextureManager::LoadTexture("res/water.png");
    tile_type[2] = TextureManager::LoadTexture("res/grass.png");
    tile_type[3] = TextureManager::LoadTexture("res/grass_mushroom_0.png");
    tile_type[4] = TextureManager::LoadTexture("res/grass_mushroom_1.png");
    tile_type[5] = TextureManager::LoadTexture("res/tree.png");
    xdif = ydif = 0;
    tmp_src.x = tmp_src.y = 0;
    tmp_src.h = tmp_src.w = 32;
}

WorldMap::~WorldMap()
{
    for (int i = 0; i < 6; i++) SDL_DestroyTexture(tile_type[i]);
}

int WorldMap::GetTileType(int x, int y)
{
    double val = perlin_noise->GetPerlinNoise2D(x, y);
    if (val < 0.09) 
        return 0;
    if (val < 0.25) 
        return 1;
    if (val < 0.70) 
        return 2;
    if (val < 0.80) 
        return (x & 1) ? 3 : 4;
    return 5;
}

void WorldMap::UpdateMap()
{
    
    if (Game::keyboard_state[SDL_SCANCODE_SPACE])
    {
        if (player_tmp->direction)
            player_tmp->sprite->ApplyAnimation("sword_right");
        else 
            player_tmp->sprite->ApplyAnimation("sword_left");
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_A] && Game::keyboard_state[SDL_SCANCODE_W])
    {
        player_tmp->direction = 0;
        player_tmp->sprite->ApplyAnimation("walk_left");
        xdif -= player_tmp->transform->speed;
        ydif -= player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D] && Game::keyboard_state[SDL_SCANCODE_W])
    {
        player_tmp->direction = 1;
        player_tmp->sprite->ApplyAnimation("walk_right");
        xdif += player_tmp->transform->speed;
        ydif -= player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_A] && Game::keyboard_state[SDL_SCANCODE_S])
    {
        player_tmp->direction = 0;
        player_tmp->sprite->ApplyAnimation("walk_left");
        xdif -= player_tmp->transform->speed;
        ydif += player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D] && Game::keyboard_state[SDL_SCANCODE_S])
    {
        player_tmp->direction = 1;
        player_tmp->sprite->ApplyAnimation("walk_right");
        xdif += player_tmp->transform->speed;
        ydif += player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_W])
    {
        ydif -= player_tmp->transform->speed;
        goto Next;
    }
    if (Game::keyboard_state[SDL_SCANCODE_S])
    {
        ydif += player_tmp->transform->speed;
        goto Next;
    }
    if (Game::keyboard_state[SDL_SCANCODE_A])
    {
        player_tmp->direction = 0;
        player_tmp->sprite->ApplyAnimation("walk_left");
        xdif -= player_tmp->transform->speed;
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D])
    {
        player_tmp->direction = 1;
        player_tmp->sprite->ApplyAnimation("walk_right");
        xdif += player_tmp->transform->speed;
        return;
    }
    Next:;
    if (player_tmp->direction)
        player_tmp->sprite->ApplyAnimation("idle_right");
    else 
        player_tmp->sprite->ApplyAnimation("idle_left");
}

void WorldMap::RenderMap()
{
    int x_left = -((xdif % 32 + 32) % 32);

    int y_left = -((ydif % 32 + 32) % 32);
    int X_tile = (xdif / 32) + ((x_left != 0 && xdif < 0) ? -1 : 0);
    int Y_tile = (ydif / 32) + ((y_left != 0 && ydif < 0) ? -1 : 0);

    tmp_dest.h = tmp_dest.w = 32;
    std::vector<std::array<int, 2>> vec_tree;
    for (int x = x_left - 32, x_tile = X_tile; x < 800; x += 32, x_tile++)
        for (int y = y_left - 32, y_tile = Y_tile; y < 640; y += 32, y_tile++)
    {
        int tile = GetTileType(x_tile, y_tile);
        tmp_dest.x = x;
        tmp_dest.y = y;
        if (tile == 5)
        {
            TextureManager::Draw(tile_type[4], tmp_src, tmp_dest);
            vec_tree.push_back({x, y});
        } else 
            TextureManager::Draw(tile_type[tile], tmp_src, tmp_dest);
    }
    tmp_dest.h = tmp_dest.w = 64;
    for (auto &i : vec_tree)
    {
        tmp_dest.x = i[0];
        tmp_dest.y = i[1];
        TextureManager::Draw(tile_type[5], tmp_src, tmp_dest);
    }
    
}

