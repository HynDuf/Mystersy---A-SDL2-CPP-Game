#pragma once
#include <vector>
#include <bullet.h>
class Shooter
{
public:
    Shooter();
    ~Shooter();
    void AddNewBullet(int x, int y);
    void Update();
    void Render();
    std::vector<Bullet*> bullet_container;
private:
};

extern Shooter *shooter;