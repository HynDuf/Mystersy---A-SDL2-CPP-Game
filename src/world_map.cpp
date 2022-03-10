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
        return 0; // deep_water
    if (val < 0.25) 
        return 1; // water
    if (val < 0.70) 
        return 2; // grass
    if (val < 0.75) 
        return 3; // grass mushroom 0
    if (val < 0.80)  
        return 4; // grass mushroom 1
    return 5; // tree
}

void WorldMap::UpdateMap()
{
    std::pair<int, int> dir = {0, 0};
    if (Game::keyboard_state[SDL_SCANCODE_SPACE])
    {
        if (player_tmp->direction)
            player_tmp->sprite->ApplyAnimation("sword_right");
        else 
            player_tmp->sprite->ApplyAnimation("sword_left");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_A] && Game::keyboard_state[SDL_SCANCODE_W])
    {
        dir = {-1, -1};
        player_tmp->direction = 0;
        player_tmp->sprite->ApplyAnimation("walk_left");
        player_tmp->xdif -= player_tmp->transform->speed;
        player_tmp->ydif -= player_tmp->transform->speed;
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D] && Game::keyboard_state[SDL_SCANCODE_W])
    {
        dir = {1, -1};
        player_tmp->direction = 1;
        player_tmp->sprite->ApplyAnimation("walk_right");
        player_tmp->xdif += player_tmp->transform->speed;
        player_tmp->ydif -= player_tmp->transform->speed;
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_A] && Game::keyboard_state[SDL_SCANCODE_S])
    {
        dir = {-1, 1};
        player_tmp->direction = 0;
        player_tmp->sprite->ApplyAnimation("walk_left");
        player_tmp->xdif -= player_tmp->transform->speed;
        player_tmp->ydif += player_tmp->transform->speed;
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D] && Game::keyboard_state[SDL_SCANCODE_S])
    {
        dir = {1, 1};
        player_tmp->direction = 1;
        player_tmp->sprite->ApplyAnimation("walk_right");
        player_tmp->xdif += player_tmp->transform->speed;
        player_tmp->ydif += player_tmp->transform->speed;
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_W])
    {
        dir = {0, -1};
        player_tmp->ydif -= player_tmp->transform->speed;
        goto Next;
    }
    if (Game::keyboard_state[SDL_SCANCODE_S])
    {
        dir = {0, 1};
        player_tmp->ydif += player_tmp->transform->speed;
        goto Next;
    }
    if (Game::keyboard_state[SDL_SCANCODE_A])
    {
        dir = {-1, 0};
        player_tmp->direction = 0;
        player_tmp->sprite->ApplyAnimation("walk_left");
        player_tmp->xdif -= player_tmp->transform->speed;
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_D])
    {
        dir = {1, 0};
        player_tmp->direction = 1;
        player_tmp->sprite->ApplyAnimation("walk_right");
        player_tmp->xdif += player_tmp->transform->speed;
        goto Finished;
    }
    Next:;
    if (player_tmp->direction)
        player_tmp->sprite->ApplyAnimation("idle_right");
    else 
        player_tmp->sprite->ApplyAnimation("idle_left");
    Finished:;
    bool valid_move = true;
    for (std::array<int, 3> &tile : tiles_near_player)
    {
        int x0 = tile[0] - dir.first * player_tmp->transform->speed + (tile[2] == 64 ? 8: 2);
        int y0 = tile[1] - dir.second * player_tmp->transform->speed + (tile[2] == 64 ? 10 : 3);
        int x1 = x0 + tile[2] - (tile[2] == 64 ? 8 : 4);
        int y1 = y0 + tile[2] - (tile[2] == 64 ? 30 : 20);
        if (player_tmp->TileCollidePlayer(x0, y0, x1, y1))
        {
            valid_move = false;
            break;
        }
    }
    if (valid_move == false)
    {
        player_tmp->xdif -= dir.first * player_tmp->transform->speed;
        player_tmp->ydif -= dir.second * player_tmp->transform->speed;
        if (player_tmp->direction)
            player_tmp->sprite->ApplyAnimation("idle_right");
        else 
            player_tmp->sprite->ApplyAnimation("idle_left");
    }
}

void WorldMap::RenderMap()
{
    int x_left = -((player_tmp->xdif % 32 + 32) % 32);
    int y_left = -((player_tmp->ydif % 32 + 32) % 32);
    int X_tile = (player_tmp->xdif / 32) + ((x_left != 0 && player_tmp->xdif < 0) ? -1 : 0);
    int Y_tile = (player_tmp->ydif / 32) + ((y_left != 0 && player_tmp->ydif < 0) ? -1 : 0);

    tmp_dest.h = tmp_dest.w = 32;

    std::vector<std::array<int, 2>> vec_tree;
    
    tiles_near_player.clear();

    for (int x = x_left - 32, x_tile = X_tile; x < 800; x += 32, x_tile++)
        for (int y = y_left - 32, y_tile = Y_tile; y < 640; y += 32, y_tile++)
    {
        int tile = GetTileType(x_tile, y_tile);
        if (InsidePlayerStartingZone(x, y))
            tile = 2;
        tmp_dest.x = x;
        tmp_dest.y = y;
        if (tile == 5)
        {
            TextureManager::Draw(tile_type[4], tmp_src, tmp_dest);
            vec_tree.push_back({x, y});
        } else 
            TextureManager::Draw(tile_type[tile], tmp_src, tmp_dest);
        bool tile_forbidden = (tile <= 1 || tile == 5);
        int sz = (tile == 5 ? 64 : 32);
        // May collide with player
        if (tile_forbidden == true && player_tmp->IsNearPlayer(x, y, x + sz, y + sz)) 
        {
            tiles_near_player.push_back({x, y, sz});
        }
    }
    tmp_dest.h = tmp_dest.w = 64;
    for (auto &i : vec_tree)
    {
        tmp_dest.x = i[0];
        tmp_dest.y = i[1];
        TextureManager::Draw(tile_type[5], tmp_src, tmp_dest);
    }
    
}

bool WorldMap::InsidePlayerStartingZone(int x, int y)
{
    return ((x + player_tmp->xdif) <= 450)
        && ((x + player_tmp->xdif) >= 200)
        && ((y + player_tmp->ydif) <= 400)
        && ((y + player_tmp->ydif) >= 150);
}