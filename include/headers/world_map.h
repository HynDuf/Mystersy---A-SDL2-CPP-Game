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
    void RenderMapFullGrass();
    bool IsValidMove(const std::pair<int, int> &dir);

    /**
     * @brief When generating map the FIRST TIME, 
     * 'player' could be standing on water or tree (forbidden)
     * So if a tile is inside the 'player' starting zone,
     * just make it grass type.
    */
    bool InsideGrassZone(int x, int y);
    PerlinNoise *perlin_noise;
private:

    SDL_Rect tmp_src, tmp_dest;
    std::array<SDL_Texture*, 6> tile_type;

    
    /**
     * @brief Manager deep_water, water and tree so player can't walk through
     * {x, y, width/height}
     * TODO: Optimize this (interate through surrounding tiles without save to a vector)
    */
    std::vector<std::array<int, 3>> tiles_near_player;
};

extern WorldMap *map;