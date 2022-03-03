#pragma once

#include <cmath>
#include <random>
#include <algorithm>
class PerlinNoise
{
public:
    PerlinNoise();
    ~PerlinNoise();
    double DotProduct(const std::pair<double, double> &V1, const std::pair<double, double> &V2);
    void MakePermutation();
    std::pair<double, double> GetConstantVector(int v);
    double Fade(double t);
    double Interpolate(double t, double a1, double a2);
    double GetRawPerlinNoise2D(double x, double y);
    double GetPerlinNoise2D(double x, double y); // With fractal brownian motion
private:
    
    std::vector<int> p;
};  