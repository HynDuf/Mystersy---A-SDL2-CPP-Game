#include <transform_component.h>

TransformComponent::TransformComponent(int _x, int _y, int _speed, int _h, int _w)
{
    x = _x;
    y = _y;
    speed = _speed;

    // Doesn't move
    vx = vy = 0;

    h = _h;
    w = _w;
} 

TransformComponent::~TransformComponent() {}

void TransformComponent::Update()
{
    x += speed * vx;
    y += speed * vy;
}
void TransformComponent::SetDir(int _vx, int _vy)
{
    vx = _vx;
    vy = _vy;
}
void TransformComponent::SetPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}
void TransformComponent::SetSpeed(int _speed)
{
    speed = _speed;
}
void TransformComponent::AddSpeed(int v)
{
    speed += v;
}