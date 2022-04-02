#include <boss.h>
#include <random>
#include <player_manager.h>
#include <shooter.h>
#include <enemy_generator.h>
Boss::Boss()
{
    start_x = (rand() % 2 ? 1 : -1) * (rand() % 109);
    start_y = (rand() % 2 ? 1 : -1) * (rand() % 177);
    cur_skill = 0;
    skill_duration = 1000;

    transform = new TransformComponent(start_x, start_y, 0, 90, 90);
    sprite = new SpriteComponent("img/enemy/boss.png", transform, true);
    health = 10000;
    health_bar = new EnemyHealthBar(transform, health);
    health_bar->SetDestSize(80, 7);
    AddAnimations();
    sprite->ApplyAnimation("walk_right");

    skill_fire.fire_tiles.assign(skill_fire.number, NULL);
    for (int i = 0; i < skill_fire.number; i++)
        skill_fire.fire_tiles[i] = new FireTile(skill_fire.damage, 0);
}

Boss::~Boss() {}

void Boss::Update()
{
    if (!IsInsideActiveZone()) 
        return;
    transform->Update();
    sprite->Update();
    if (--skill_duration == 0)
    {
        ExecuteSkill();
        skill_duration = 1000;
        (cur_skill += 1) %= 4;
    }

    for (FireTile *&f : skill_fire.fire_tiles)
        f->Update();
    UpdateShoot();
    health_bar->Update(-5, -20);
}
void Boss::Render()
{
    if (!IsInsideActiveZone()) 
        return;
    sprite->Draw(-player->xdif, -player->ydif);
    health_bar->Draw(-player->xdif, -player->ydif);
}
void Boss::RenderFire()
{
    for (FireTile *&f : skill_fire.fire_tiles)
        f->Render();
}
bool Boss::IsInsideStartingZone(int x, int y)
{
    int X = (x + player->xdif) - start_x;
    int Y = (y + player->ydif) - start_y;
    return X * X + Y * Y <= 450 * 450;
}

bool Boss::IsInsideActiveZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-100 < x && x < 900 && -100 < y && y < 700);
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
    health_bar->Reset(health);
}

void Boss::UpdateShoot()
{
    if (skill_shoot.duration == 0)
        return;
    skill_shoot.duration--;
    if (--skill_shoot.interval == 0)
    {
        skill_shoot.interval = 20;
        shooter->AddNewBullet(transform->x + 40, transform->y + 40);
    }
}
void Boss::ExecuteSkill()
{
    switch (cur_skill)
    {
        case TELEPORT:
            ExecuteTeleport();
            break;
        case FIREWALL:
            ExecuteFirewall();
            break;
        case SHOOT_FIRE_BALL:
            ExecuteShootFireBall();
            break;
        case SPAWN_MONSTER:
            ExecuteSpawnMonster();
            break;
    }
}

void Boss::ExecuteTeleport()
{
    transform->x = (rand() % 400) - 200 + start_x;
    transform->y = (rand() % 400) - 200 + start_y;
}
void Boss::ExecuteFirewall()
{
    for (FireTile *&f : skill_fire.fire_tiles)
        f->Reset(skill_fire.damage, skill_fire.duration);
}
void Boss::ExecuteShootFireBall()
{
    skill_shoot.duration = 800;
}
void Boss::ExecuteSpawnMonster()
{
    for (int i = 0; i < skill_spawn.number; i++)
    {
        enemy_generator->AddNewBat(transform->x + 40, transform->y + 40);
        enemy_generator->AddNewSkeleton(transform->x + 40, transform->y + 40);
    }
}

bool Boss::IsAlive()
{
    return health > 0;
}