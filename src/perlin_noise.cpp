#include <perlin_noise.h>

PerlinNoise::PerlinNoise() 
{
    srand(time(NULL));
    // seed = rand();
    seed = 123;
}
PerlinNoise::PerlinNoise(unsigned _seed) 
{
    seed = _seed;
}
PerlinNoise::~PerlinNoise() {}

double PerlinNoise::DotProduct(const vector2 &V1, const vector2 &V2)
{
    return V1.first * V2.first + V1.second * V2.second;
}

// Get this from wiki
vector2 PerlinNoise::RandomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix * seed, b = iy * seed;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    vector2 v;
    v.first = cos(random); 
    v.second = sin(random);
    return v;
}


double PerlinNoise::Interpolate(double w, double a0, double a1)
{
    // return a0 + (a1 - a0) * w;

    // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
    // return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;

    // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}

double PerlinNoise::GetRawPerlinNoise2D(double x, double y)
{
    int X = ((int) floor(x));
    int Y = ((int) floor(y));

    double xf = x - (double) X;
    double yf = y - (double) Y;

    vector2 topRight = std::make_pair(xf - 1.0, yf - 1.0);
    vector2 topLeft = std::make_pair(xf, yf - 1.0);
    vector2 bottomRight = std::make_pair(xf - 1.0, yf);
    vector2 bottomLeft = std::make_pair(xf, yf);

    double dotTopRight = DotProduct(topRight, RandomGradient(X + 1, Y + 1));
    double dotTopLeft = DotProduct(topLeft, RandomGradient(X, Y + 1));
    double dotBottomRight = DotProduct(bottomRight, RandomGradient(X, Y + 1));
    double dotBottomLeft = DotProduct(bottomLeft, RandomGradient(X, Y));

    double u = xf;
    double v = yf;

    return Interpolate(u, 
                        Interpolate(v, dotBottomLeft, dotTopLeft), 
                        Interpolate(v, dotBottomRight, dotTopRight));
    // return value approximately in [-1.0, 1.0]
    // due to double imprecision
}

double PerlinNoise::GetPerlinNoise2D(double x, double y)
{
    double ret = 0;
    double magnitude = 2;
    double frequency = 0.08;
    // With fractal brownian motion - only 2 here - increase for terrain complexity
    for (int o = 0; o < 2; o++)
    {
        double tmp = magnitude * GetRawPerlinNoise2D(x * frequency, y * frequency);
        ret += tmp;
        magnitude /= 2;
        frequency += frequency;
    }

    // scale from [-1, 1] to [0, 1]
    // Just approximately in that range (due to double imprecision)
    ret += 1.0;
    ret /= 2;

    return ret;
}