#include <player_manager.h>
#include <texture_manager.h>
PlayerManager::PlayerManager(int orig_x, int orig_y, const char *texture_file)
{
    transform = new TransformComponent(orig_x, orig_y, 2, 70, 45);
    sprite = new SpriteComponent(texture_file, transform);
    direction = 1;
    AddAnimations();
    sprite->ApplyAnimation("idle_right");
}
PlayerManager::~PlayerManager() {}
void PlayerManager::Update()
{
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
    sprite->animations_map["sword_left"] =sword_left;
}