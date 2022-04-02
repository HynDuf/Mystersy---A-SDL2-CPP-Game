#pragma once
#include <transform_component.h>
#include <sprite_component.h>
#include <fire_tile.h>
#include <vector>
class Boss
{
public:

    Boss();
    ~Boss();
    bool IsInsideStartingZone(int x, int y);
    void Update();
    void Render();
    void RenderFire();
    void DecHealth(int v);
    int start_x, start_y;

private:
    bool IsInsideActiveZone();
    void ExecuteSkill();
    void AddAnimations();
    void ExecuteTeleport();
    void ExecuteFirewall();
    void ExecuteShootFireBall();
    void ExecuteSpawnMonster();
    void UpdateShoot();
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

    } skill_tele;

    struct 
    {
        int damage = 3;
        int duration = 1000;   
        int number = 30;
        std::vector<FireTile*> fire_tiles;
    } skill_fire;

    struct 
    {
        int duration = 0;
        int interval = 15;
    } skill_shoot;

    struct 
    {
        int number = 5;
    } skill_spawn;

    SpriteComponent *sprite;
    TransformComponent *transform;
};  

extern Boss *boss;