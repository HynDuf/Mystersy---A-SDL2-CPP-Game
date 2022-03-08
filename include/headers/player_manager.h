#pragma once
#include <game.h>
#include <transform_component.h>
#include <sprite_component.h>
#include <animation.h>
class PlayerManager
{
public:
    PlayerManager(int orig_x, int orig_y, const char *texture_file);
    ~PlayerManager();

    void AddAnimations();
    void Update();
    void Render();
    bool IsNearPlayer(int x0, int y0, int x1, int y1);
    bool TileCollidePlayer(int x0, int y0, int x1, int y1);
    SpriteComponent *sprite;
    TransformComponent *transform;

    // 1 is right, 0 is left
    bool direction;
};