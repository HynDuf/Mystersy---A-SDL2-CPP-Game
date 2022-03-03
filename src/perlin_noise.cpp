#include <perlin_noise.h>
std::mt19937 rng(std::random_device{}());

PerlinNoise::PerlinNoise()
{
    PerlinNoise::MakePermutation();
}
PerlinNoise::~PerlinNoise() {}

double PerlinNoise::DotProduct(const std::pair<double, double> &V1, const std::pair<double, double> &V2)
{
    return V1.first * V2.first + V1.second * V2.second;
}

void PerlinNoise::MakePermutation()
{
    for (int i = 0; i < (1 << 18); i++) 
        p.push_back(i);
    shuffle(p.begin(), p.end(), rng);
    for (int i = 0; i < (1 << 18); i++) 
        p.push_back(p[i]);
}

std::pair<double, double> PerlinNoise::GetConstantVector(int v)
{
    int rem = v & 3;
    if (rem == 0)
        return {1.0, 1.0};
    else if (rem == 1)
        return {-1.0, 1.0};
    else if (rem == 2)
        return {-1.0, -1.0};
    else
        return {1.0, -1.0};
}

double PerlinNoise::Fade(double t)
{
    return ((6 * t - 15) * t + 10) * t * t * t;
}

double PerlinNoise::Interpolate(double t, double a1, double a2)
{
    return a1 + (a2 - a1) * t;
}

double PerlinNoise::GetRawPerlinNoise2D(double x, double y)
{
    int X = ((int) floor(x)) & ((1 << 18) - 1);
    int Y = ((int) floor(y)) & ((1 << 18) - 1);

    double xf = x - ((int) floor(x));
    double yf = y - ((int) floor(y));

    std::pair<double, double> topRight = std::make_pair(xf - 1.0, yf - 1.0);
    std::pair<double, double> topLeft = std::make_pair(xf, yf - 1.0);
    std::pair<double, double> bottomRight = std::make_pair(xf - 1.0, yf);
    std::pair<double, double> bottomLeft = std::make_pair(xf, yf);

    int valueTopRight = p[p[X + 1] + Y + 1];
    int valueTopLeft = p[p[X] + Y + 1];
    int valueBottomRight = p[p[X + 1] + Y];
    int valueBottomLeft = p[p[X] + Y];

    double dotTopRight = DotProduct(topRight, GetConstantVector(valueTopRight));
    double dotTopLeft = DotProduct(topLeft, GetConstantVector(valueTopLeft));
    double dotBottomRight = DotProduct(bottomRight, GetConstantVector(valueBottomRight));
    double dotBottomLeft = DotProduct(bottomLeft, GetConstantVector(valueBottomLeft));

    double u = Fade(xf);
    double v = Fade(yf);

    return Interpolate(u, Interpolate(v, dotBottomLeft, dotTopLeft), Interpolate(v, dotBottomRight, dotTopRight));
    // return value in [-1.0, 1.0]
}

double PerlinNoise::GetPerlinNoise2D(double x, double y)
{
    double ret = 0;
    double magnitude = 2;
    double frequency = 0.001;

    for (int o = 0; o < 8; o++)
    {
        double tmp = magnitude * GetRawPerlinNoise2D(x * frequency, y * frequency);
        ret += tmp;
        magnitude *= 0.5;
        frequency *= 2.0;
    }

    // scale from [-1, 1] to [0, 1]
    ret += 1.0;
    ret *= 0.5;

    return ret;
}