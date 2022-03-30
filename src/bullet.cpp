#include <bullet.h>
#include <point_2d.h>
#include <player_manager.h>
Bullet::Bullet(int x, int y)
{

    transform = new TransformComponent(x, y, 3.5, 20, 20);
    sprite = new SpriteComponent("img/game/shooting_ball.png", transform, false);

    damage = 10;
    active = true;
    duration = 300;
    // * Calculate vector direction
    int screenX = x - player->xdif, screenY = y - player->ydif;
    Point<double> vec(400 - screenX, 320 - screenY);
    double dist = vec.dist(); // ! 'dist' should be > 64
    vec = vec / dist;

    transform->SetDir(vec.x, vec.y);
}
Bullet::~Bullet() {}
void Bullet::Update()
{
    if (active == false)
        return;
    transform->Update();
    sprite->Update();

    if (CollidePlayer())
    {
        player->health -= damage;
        active = false;
    }
    if (--duration == 0)
        active = false;
}
void Bullet::Render()
{
    sprite->Draw(-player->xdif, -player->ydif);
}

bool Bullet::IsActive()
{
    return active;
}

bool Bullet::CollidePlayer()
{
    int x0 = transform->x - player->xdif;
    int y0 = transform->y - player->ydif;
    return std::max(x0, 390) <= std::min(x0 + 20, 410)
        && std::max(y0, 308) <= std::min(y0 + 20, 332);
}