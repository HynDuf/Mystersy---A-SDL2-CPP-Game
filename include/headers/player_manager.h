#pragma once
#include <transform_component.h>
#include <sprite_component.h>
#include <animation.h>
class PlayerManager
{
public:
    PlayerManager(const char *texture_file, int orig_x, int orig_y);
    ~PlayerManager();

    void AddAnimations();
    void Update();
    void Render();
    bool IsNearPlayer(int x0, int y0, int x1, int y1);
    bool CollidePlayer(int x0, int y0, int x1, int y1);
    bool CollideSwordRight(int x0, int y0, int x1, int y1);
    bool CollideSwordLeft(int x0, int y0, int x1, int y1);

    // How far player has moved?
    int xdif, ydif;

    int health;
    int attack;

    SpriteComponent *sprite;
    TransformComponent *transform;

    // 1 is right, 0 is left
    bool direction;
};
extern PlayerManager *player;