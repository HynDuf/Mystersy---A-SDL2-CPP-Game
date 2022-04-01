#pragma once
#include <transform_component.h>
#include <sprite_component.h>
class Boss
{
public:

    Boss();
    ~Boss();
    bool IsInsideStartingZone(int x, int y);
    void Update();
    void Render();
    void AddAnimations();
    void DecHealth(int v);
private:
    // Skill types
    static const int TELEPORT = 0;
    static const int FIREWALL = 1;
    static const int SHOOT_FIRE_BALL = 2;
    static const int SPAWN_MONSTER = 3;   
    //

    int health;

    // Duration for using next skill
    int skill_duration;

    // Current skill : [0, 3]
    int cur_skill;

    struct 
    {
        int cooldown;
        int dx, dy;
        int vx, vy;
    } skill_tele;

    struct 
    {
        int cooldown;   
    } skill_fire;

    struct 
    {
        int cooldown;
    } skill_shoot;

    struct 
    {
        int cooldown;
    } skill_spawn;

    SpriteComponent *sprite;
    TransformComponent *transform;
    int start_x, start_y;
};  

extern Boss *boss;