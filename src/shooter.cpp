#include <shooter.h>

Shooter::Shooter() {}
Shooter::~Shooter() {}
void Shooter::AddNewBullet(int x, int y, bool advanced)
{
    Bullet *bullet = new Bullet(x, y, advanced);
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