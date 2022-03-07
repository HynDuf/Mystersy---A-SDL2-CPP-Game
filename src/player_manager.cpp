#include <player_manager.h>
#include <texture_manager.h>
PlayerManager::PlayerManager(int orig_x, int orig_y, const char *texture_file)
{
    transform = new TransformComponent(orig_x, orig_y, 2, 45, 50);
    sprite = new SpriteComponent(texture_file, transform, 17, 21, true);
    AddAnimations();
    sprite->ApplyAnimation("idle");
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
    Animation idle(0, 4, 100);
    Animation walk_right(1, 4, 100);
    Animation walk_left(2, 4, 100);
    Animation sword_right(3, 3, 100);
    Animation sword_left(4, 3, 100);
    sprite->animations_map.emplace("idle", idle);
    sprite->animations_map["walk_right"] = walk_right;
    sprite->animations_map["walk_left"] = walk_left;
    sprite->animations_map["sword_right"] = sword_right;
    sprite->animations_map["sword_left"] =sword_left;
}