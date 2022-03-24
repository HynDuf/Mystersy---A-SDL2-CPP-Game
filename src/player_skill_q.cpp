#include <player_skill_q.h>
#include <player_manager.h>
PlayerSkillQ::PlayerSkillQ()
{
    skill_used = false;
    cooldown = 0;
    duration = 0;

    circle_on = TextureManager::LoadTexture("img/player/q_circle_on.png");
    circle_off = TextureManager::LoadTexture("img/player/q_circle_off.png");
    circle.x = 580, circle.y = 530;
    circle.w = circle.h = 80;

    transform = new TransformComponent(0, 0, 6, 0, 0);
    sprite = new SpriteComponent("img/player/q_animation.png", transform, false);

}

PlayerSkillQ::~PlayerSkillQ() {}

void PlayerSkillQ::Update()
{
    if (duration > 0)
    {
        transform->Update();
        sprite->Update();
    }
}
void PlayerSkillQ::Render()
{
    if (cooldown == 0)
        TextureManager::Draw(circle_on, circle);
    else
    {
        cooldown--;
        TextureManager::Draw(circle_off, circle);
    }
    if (duration > 0)
    {
        duration--;
        sprite->Draw(-player->xdif, -player->ydif);
    }
}
void PlayerSkillQ::ExecuteSkill(int dx, int dy)
{
    if (cooldown > 0)
        return;
    skill_used = true;
    duration = 40;
    cooldown = 50;
    transform->vx = dx;
    transform->vy = dy;
    if (dx == 1 && dy == 0) // E
    {
        sprite->src_rect.x = 0;
        sprite->src_rect.y = 45;
        sprite->src_rect.w = 16;
        sprite->src_rect.h = 32;

        transform->w = 20;
        transform->h = 70;

        transform->x = 365 + player->xdif + 50;
        transform->y = 300 + player->ydif - 10;
    } else if (dx == 0 && dy == 1) // S
    {
        sprite->src_rect.x = 0;
        sprite->src_rect.y = 29;
        sprite->src_rect.w = 32;
        sprite->src_rect.h = 16;

        transform->w = 70;
        transform->h = 20;

        transform->x = 365 + player->xdif;
        transform->y = 300 + player->ydif + 40;
    } else if (dx == -1 && dy == 0) // W
    {
        sprite->src_rect.x = 16;
        sprite->src_rect.y = 45;
        sprite->src_rect.w = 16;
        sprite->src_rect.h = 32;

        transform->w = 20;
        transform->h = 70;

        transform->x = 365 + player->xdif;
        transform->y = 300 + player->ydif - 10;
    } else if (dx == 0 && dy == -1) // N
    {
        sprite->src_rect.x = 32;
        sprite->src_rect.y = 29;
        sprite->src_rect.w = 32;
        sprite->src_rect.h = 16;

        transform->w = 70;
        transform->h = 20;

        transform->x = 365 + player->xdif;
        transform->y = 300 + player->ydif - 30;

    } else if (dx == -1 && dy == -1) // NW
    {
        sprite->src_rect.x = 29;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 29;
        sprite->src_rect.h = 29;

        transform->w = 60;
        transform->h = 60;

        transform->x = 365 + player->xdif - 30;
        transform->y = 300 + player->ydif - 30;
    } else if (dx == -1 && dy == 1) // SW
    {
        sprite->src_rect.x = 87;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 29;
        sprite->src_rect.h = 29;

        transform->w = 60;
        transform->h = 60;
        
        transform->x = 365 + player->xdif - 30;
        transform->y = 300 + player->ydif + 30;
    } else if (dx == 1 && dy == -1) // NE
    {
        sprite->src_rect.x = 0;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 29;
        sprite->src_rect.h = 29;

        transform->w = 60;
        transform->h = 60;

        transform->x = 365 + player->xdif + 30;
        transform->y = 300 + player->ydif - 30;
    } else if (dx == 1 && dy == 1) // SE
    {
        sprite->src_rect.x = 58;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 29;
        sprite->src_rect.h = 29;

        transform->w = 60;
        transform->h = 60;

        transform->x = 365 + player->xdif + 30;
        transform->y = 300 + player->ydif + 30;
    }
}
bool PlayerSkillQ::CollideEnemy()
{
    return 1;
}
