#include <enemy_manager.h>
#include <player_manager.h>
#include <world_map.h>
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
    srand(time(NULL));
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
    // Already checked IsInsideLivingZone(player->xdif, player->ydif) == false
    
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
        transform->x += dx;
        transform->y += dy;

    }
    sprite->Update();
}
void EnemyManager::Render(int deltax, int deltay)
{
    sprite->Draw(deltax, deltay);
}

bool EnemyManager::IsInsideLivingZone()
{
    return 1;
}
bool EnemyManager::IsInsideMovingZone()
{

    return 1;
}

/*
@brief Try moving and check if it'll collide with anything.
       Only check if enemy is inside moving zone, i.e., IsInsideMovingZone(...) is true.
@return 1 if enemy moves and it collides with deep_water, water, tree; 0 otherwise.
*/
bool EnemyManager::CheckMoveCollide()
{
    // If don't move, return 1
    if (move_duration % 2 == 0)
        return 1;
    if (dx == 0 && dy == 0) 
        return 1;
    
    // Try moving
    int curx = transform->x - player->xdif + dx;
    int cury = transform->y - player->ydif + dy;
    // Iterate the tiles around and check for collision

    return 1;
}