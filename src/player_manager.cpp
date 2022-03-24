#include <player_manager.h>
#include <texture_manager.h>
PlayerManager::PlayerManager(const char *texture_file, int orig_x, int orig_y)
{
    xdif = ydif = 0;
    transform = new TransformComponent(orig_x, orig_y, 3, 70, 45);
    sprite = new SpriteComponent(texture_file, transform, true);
    health_box = new PlayerHealthBox(100);
    direction = 1;
    health = 100;
    attack = 2;
    AddAnimations();
    sprite->ApplyAnimation("idle_right");
}
PlayerManager::~PlayerManager() {}
void PlayerManager::Update()
{
    health = std::max(health, 0);
    health_box->Update(player->health);
    sprite->Update();
}

void PlayerManager::Render()
{
    sprite->Draw();
}

void PlayerManager::AddAnimations()
{
    Animation walk_right(0, 33, 21, 4, 200);
    Animation walk_left(21, 33, 21, 4, 200);
    Animation sword_right(42, 33, 21, 3, 100);
    Animation sword_left(63, 33, 21, 3, 100);
    sprite->animations_map["idle_right"] = walk_right;
    sprite->animations_map["idle_left"] = walk_left;
    sprite->animations_map["walk_right"] = walk_right;
    sprite->animations_map["walk_left"] = walk_left;
    sprite->animations_map["sword_right"] = sword_right;
    sprite->animations_map["sword_left"] = sword_left;
}

bool PlayerManager::IsNearPlayer(int x0, int y0, int x1, int y1)
{
    return (std::max(x0, 385) <= std::min(x1, 415))
        && (std::max(y0, 305) <= std::min(y1, 355));

    // Assume player's speed always <= 5
}

bool PlayerManager::CollidePlayer(int x0, int y0, int x1, int y1)
{
    return (std::max(x0, 390) <= std::min(x1, 410))
        && (std::max(y0, 305) <= std::min(y1, 350));
}

bool PlayerManager::CollideSwordRight(int x0, int y0, int x1, int y1)
{
    return (std::max(x0, 415) <= std::min(x1, 420))
        && (std::max(y0, 305) <= std::min(y1, 350));
}
bool PlayerManager::CollideSwordLeft(int x0, int y0, int x1, int y1)
{
    return (std::max(x0, 380) <= std::min(x1, 385))
        && (std::max(y0, 305) <= std::min(y1, 350));
}

bool PlayerManager::IsAlive()
{
    return health > 0;
}