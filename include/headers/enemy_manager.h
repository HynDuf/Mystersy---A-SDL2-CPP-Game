#pragma once
#include <sprite_component.h>
#include <transform_component.h>
#include <random>
#include <enemy_health_bar.h>

class EnemyManager
{
public:
    EnemyManager(const char *texture_file, int x, int y);
    ~EnemyManager();

    void AddAnimations();
    void Update();

    // When player moves, everything gets shifted
    void Render();

    bool IsInsideLivingZone();
    bool IsInsideMovingZone();
    bool CheckMoveCollide();
    bool TileCollideEnemy(int x0, int y0, int x1, int y1, int X, int Y);
    bool IsAlive();
    bool IsNearPlayer();
    bool IsNextToPlayer();
    
    SpriteComponent *sprite;
    TransformComponent *transform;
    EnemyHealthBar *health_bar;

    int health;
    int attack;
    int attack_interval;

private:
    int move_duration;
    int dx, dy;
    // 1 is right, 0 is left
    bool direction;
};  
