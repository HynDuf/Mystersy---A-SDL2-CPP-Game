#include <boss.h>
#include <random>
#include <player_manager.h>
Boss::Boss()
{
    start_x = (rand() % 2 ? 1 : -1) * (rand() % 109);
    start_y = (rand() % 2 ? 1 : -1) * (rand() % 177);
    cur_skill = 0;
    skill_duration = 500;

    transform = new TransformComponent(start_x, start_y, 0, 90, 90);
    sprite = new SpriteComponent("img/enemy/boss.png", transform, true);
    AddAnimations();
    sprite->ApplyAnimation("walk_right");
}

Boss::~Boss() {}

void Boss::Update()
{
    transform->Update();
    sprite->Update();
}
void Boss::Render()
{
    sprite->Draw(-player->xdif, -player->ydif);
}
bool Boss::IsInsideStartingZone(int x, int y)
{
    return ((x + player->xdif) <= start_x + 400)
        && ((x + player->xdif) >= start_x - 400)
        && ((y + player->ydif) <= start_y + 400)
        && ((y + player->ydif) >= start_y - 400);
}

void Boss::AddAnimations()
{
    Animation walk_left(0, 45, 40, 2, 350);
    Animation walk_right(40, 45, 40, 2, 350);
    sprite->animations_map["walk_right"] = walk_right;
    sprite->animations_map["walk_left"] = walk_left;
}

void Boss::DecHealth(int v)
{
    health -= v;
}