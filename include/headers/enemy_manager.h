#pragma once
#include <sprite_component.h>
#include <transform_component.h>
#include <random>
class EnemyManager
{
public:
    EnemyManager(const char *texture_file, int x, int y);
    ~EnemyManager();

    void AddAnimations();
    void Update();

    // When player moves, everything gets shifted
    void Render(int deltax, int deltay);

    int health;
    int attack;
    SpriteComponent *sprite;
    TransformComponent *transform;

    int move_duration;
    int dx, dy;

    // 1 is right, 0 is left
    bool direction;
private:
};  