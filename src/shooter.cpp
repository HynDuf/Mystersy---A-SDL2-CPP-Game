#include <shooter.h>

Shooter::Shooter() {}
Shooter::~Shooter() {}
void Shooter::AddNewBullet(int x, int y)
{
    Bullet *bullet = new Bullet(x, y);
    bullet_container.push_back(bullet);
}
void Shooter::Update()
{
    std::vector<Bullet*> tmp;
    for (Bullet *&b : bullet_container)
    {
        b->Update();
        if (b->IsActive())
            tmp.push_back(b);
    }
    bullet_container = std::move(tmp);
}
void Shooter::Render()
{
    for (Bullet *&b : bullet_container)
        b->Render();
}