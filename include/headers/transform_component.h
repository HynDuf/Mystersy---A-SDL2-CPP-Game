#pragma once

class TransformComponent
{
public:
    int x, y;
    int speed;

    // Velocity (Direction) of x and y
    int vx, vy;

    int h, w;
    TransformComponent(int _x, int _y, int _speed, int _w, int _h);
    ~TransformComponent();
    void Update();
    void SetDir(int _vx, int _vy);
    void SetPosition(int _x, int _y);
    void SetSpeed(int _speed);
    void AddSpeed(int v);
};