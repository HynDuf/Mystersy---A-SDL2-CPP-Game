#include <enemy_manager.h>

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