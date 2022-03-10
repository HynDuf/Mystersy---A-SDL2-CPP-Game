#pragma once 

#include <texture_manager.h>
#include <random>
#include <array>
#include <perlin_noise.h>


class WorldMap 
{
public:
    WorldMap();
    ~WorldMap();

    int GetTileType(int x, int y);
    void UpdateMap();
    void RenderMap();
    PerlinNoise *perlin_noise;
private:

    SDL_Rect tmp_src, tmp_dest;
    std::array<SDL_Texture*, 6> tile_type;

    /*
    @brief When generating map the FIRST TIME, 
           'player' could be standing on water or tree (forbidden)
           So if a tile is inside the 'player' starting zone,
           just make it grass type.
    */
    bool InsidePlayerStartingZone(int x, int y);

    
    /*
    @brief Manager deep_water, water and tree so player can't walk through
           {x, y, width/height}
    */
    std::vector<std::array<int, 3>> tiles_near_player;
};

extern WorldMap *map;