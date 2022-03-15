#include <enemy_generator.h>
#include <world_map.h>
#include <player_manager.h>
#include <algorithm>
EnemyGenerator::EnemyGenerator(const char *texture_file)
{
    generator_interval = 200;
    texture = texture_file;
}
EnemyGenerator::~EnemyGenerator() {}

void EnemyGenerator::AddNewEnemy(int x, int y)
{
    // Ensure that tile at (x, y) is not deep_water, water or tree
    EnemyManager *enemy = new EnemyManager(texture, x, y);
    enemy_container.push_back(enemy);
}
void EnemyGenerator::Update()
{   
    
    if (enemy_container.size() < MAX_ENEMY)
    {
        if (--generator_interval == 0) // Generate 1 new enemy
        {
            generator_interval = 200;
            int x_left = -((player->xdif % 32 + 32) % 32);
            int y_left = -((player->ydif % 32 + 32) % 32);
            int X_tile = (player->xdif / 32) + ((x_left != 0 && player->xdif < 0) ? -1 : 0);
            int Y_tile = (player->ydif / 32) + ((y_left != 0 && player->ydif < 0) ? -1 : 0);

            std::vector<std::pair<int, int> > grass;
            // Iterate through the outer "Moving Zone" to generate new enemy
            for (int x = x_left - 160, x_tile = X_tile - 5; x < 928; x += 32, x_tile++)
                for (int y = y_left - 160, y_tile = Y_tile - 5; y < 768; y += 32, y_tile++)
                    if (x < x_left - 32 || x >= 832 || y < y_left - 32 || y >= 672)
                    {
                        int tile0 = map->GetTileType(x_tile, y_tile);
                        int tile1 = map->GetTileType(x_tile - 1, y_tile);
                        int tile2 = map->GetTileType(x_tile, y_tile - 1);
                        int tile3 = map->GetTileType(x_tile - 1, y_tile - 1);
                        if (map->InsidePlayerStartingZone(x, y))
                            tile0 = 2; // set to grass
                        if (map->InsidePlayerStartingZone(x - 32, y))
                            tile1 = 2; // set to grass
                        if (map->InsidePlayerStartingZone(x, y - 32))
                            tile2 = 2; // set to grass
                        if (map->InsidePlayerStartingZone(x - 32, y - 32))
                            tile3 = 2; // set to grass
                        int mx = std::max({tile0, tile1, tile2, tile3});
                        int mn = std::min({tile0, tile1, tile2, tile3});
                        if (2 <= mn && mx <= 4)
                            grass.push_back({x - 20, y - 15}); 
                    }
            if (!grass.empty())
            {
                int index = rand() % ((int) grass.size());
                AddNewEnemy(grass[index].first + player->xdif, grass[index].second + player->ydif);
            } 
            
        }
    }

    std::vector<EnemyManager*> tmp;
    for (EnemyManager *e : enemy_container)
    {
        if (e->IsAlive() && e->IsInsideLivingZone())
        {
            e->Update();
            tmp.push_back(e);
        }
    }
    enemy_container = std::move(tmp);
}
void EnemyGenerator::Render()
{
    for (EnemyManager *&e : enemy_container)
        e->Render();
}