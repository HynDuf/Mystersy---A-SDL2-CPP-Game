#pragma once 

#include <game.h>
#include <texture_manager.h>
#include <random>
#include <array>
#include <player_manager.h>
class WorldMap 
{
public:
    WorldMap(PlayerManager *_player);
    ~WorldMap();

    int GetTileType(int x, int y);
    void UpdateMap();
    void RenderMap();
    PlayerManager *player_tmp;
private:
    int xdif, ydif;
    SDL_Rect tmp_src, tmp_dest;
    std::array<SDL_Texture*, 6> tile_type;
};