#pragma once 

#include <game.h>
#include <texture_manager.h>
#include <random>
#include <array>
class WorldMap 
{
public:
    WorldMap();
    ~WorldMap();

    int GetTileType(int x, int y);
    void UpdateMap();
    void RenderMap();
private:
    int xdif, ydif;
    SDL_Rect tmp_src, tmp_dest;
    std::array<SDL_Texture*, 6> grass;
};