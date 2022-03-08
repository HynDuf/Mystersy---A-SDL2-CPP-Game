#pragma once

#include <cmath>
#include <random>

using vector2 = std::pair<double, double>;
class PerlinNoise
{
public:
    PerlinNoise();
    PerlinNoise(unsigned _seed); 
    ~PerlinNoise();
    double GetPerlinNoise2D(double x, double y); // With fractal brownian motion
private:
    double DotProduct(const vector2 &V1, const vector2 &V2);
    vector2 RandomGradient(int ix, int iy);
    double Interpolate(double t, double a1, double a2);
    double GetRawPerlinNoise2D(double x, double y);
    unsigned seed;
};  