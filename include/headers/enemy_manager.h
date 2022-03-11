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
    void Render();

    bool IsInsideLivingZone();
    bool IsInsideMovingZone();
    bool CheckMoveCollide();
    bool TileCollideEnemy(int x0, int y0, int x1, int y1, int X, int Y);
    
    SpriteComponent *sprite;
    TransformComponent *transform;


private:
    int health;
    int attack;
    int move_duration;
    int dx, dy;
    // 1 is right, 0 is left
    bool direction;
};  
