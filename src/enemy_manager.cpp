#include <enemy_manager.h>
#include <player_manager.h>
#include <world_map.h>
#include <assert.h>
EnemyManager::EnemyManager(const char *texture_file, int x, int y)
{
    transform = new TransformComponent(x, y, 1, 70, 40);
    sprite = new SpriteComponent(texture_file, transform);
    health = 10;
    attack = 2;
    move_duration = 50;
    dx = dy = 0;
    AddAnimations();
    sprite->ApplyAnimation("idle_right");
    direction = 1;
    
}
EnemyManager::~EnemyManager() {}

void EnemyManager::AddAnimations()
{
    Animation walk_right(0, 31, 17, 4, 200);
    Animation walk_left(17, 31, 17, 4, 200);
    Animation sword_right(34, 31, 17, 4, 200);
    Animation sword_left(51, 31, 17, 4, 200);
    sprite->animations_map["idle_right"] = walk_right;
    sprite->animations_map["idle_left"] = walk_left;
    sprite->animations_map["walk_right"] = walk_right;
    sprite->animations_map["walk_left"] = walk_left;
    sprite->animations_map["sword_right"] = sword_right;
    sprite->animations_map["sword_left"] =sword_left;
}
void EnemyManager::Update()
{
    // Already checked IsInsideMovingZone() == true
    if (IsInsideMovingZone())
    {
        if (--move_duration == 0)
        {
            move_duration = 50;
            dx = (rand() % 3) - 1; // [-1, 0, 1]
            dy = (rand() % 3) - 1; // [-1, 0, 1]
            if (dx == 1)
            {
                sprite->ApplyAnimation("walk_right");
                direction = 1;
            } else if (dx == -1)
            {
                sprite->ApplyAnimation("walk_left");
                direction = 0;
            } 
        } else if (move_duration == 10) 
            dx = dy = 0;
        
        
        if (move_duration & 1)
        {
            if (CheckMoveCollide())
            {
                transform->x += dx;
                transform->y += dy;
            }
        }
    }
    
    sprite->Update();
}
void EnemyManager::Render()
{
    sprite->Draw(-player->xdif, -player->ydif);
}

bool EnemyManager::IsInsideLivingZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-1000 < x && x < 2000 && -1000 < y && y < 2000);
}
bool EnemyManager::IsInsideMovingZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-160 < x && x < 928 && -160 < y && y < 768);
}

/*
@brief Try moving and check if it'll collide with anything.
       Only check if enemy is inside moving zone, i.e., IsInsideMovingZone(...) is true.
@return 1 if enemy moves and it collides with deep_water, water, tree; 0 otherwise.
*/
bool EnemyManager::CheckMoveCollide()
{
    // If don't move, return 1
    if (dx == 0 && dy == 0) 
        return 1;
    
    // Try moving
    int curx = transform->x - player->xdif + dx;
    int cury = transform->y - player->ydif + dy;
    
    // Iterate the surrounding tiles and check for collision
    bool valid_move = 1;
    int x_left = -((player->xdif % 32 + 32) % 32);
    int y_left = -((player->ydif % 32 + 32) % 32);
    int X_tile = (player->xdif / 32) + ((x_left != 0 && player->xdif < 0) ? -1 : 0);
    int Y_tile = (player->ydif / 32) + ((y_left != 0 && player->ydif < 0) ? -1 : 0);

    while (x_left + 32 <= curx - 96) x_left += 32, X_tile++;
    while (x_left > curx - 96) x_left -= 32, X_tile--;
    while (y_left + 32 <= cury - 96) y_left += 32, Y_tile++;
    while (y_left > cury - 96) y_left -= 32, Y_tile--;
    for (int x = x_left, x_tile = X_tile; x_tile < X_tile + 8; x += 32, x_tile++)
        for (int y = y_left, y_tile = Y_tile; y_tile < Y_tile + 8; y += 32, y_tile++)
    {
        int tile = map->GetTileType(x_tile, y_tile);
        if (map->InsidePlayerStartingZone(x, y))
            continue; // tile = 2; // set to grass
        int sz = (tile == 5 ? 64 : 32);
        int x0 = x + (sz == 64 ? 4: 0);
        int y0 = y + (sz == 64 ? 4 : 0);
        int x1 = x + sz - (sz == 64 ? 4 : 0);
        int y1 = y + sz - (sz == 64 ? 25 : 15);
        if ((tile <= 1 || tile == 5) && TileCollideEnemy(x0, y0, x1, y1, curx, cury))
        {
            valid_move = false;
            goto Next;
        }
        
    }
    Next:;
    return valid_move;
}

bool EnemyManager::TileCollideEnemy(int x0, int y0, int x1, int y1, int X, int Y)
{
    return (std::max(x0, X + 22) <= std::min(x1, X + 43))
        && (std::max(y0, Y - 3) <= std::min(y1, Y + 40));
}