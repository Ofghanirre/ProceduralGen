//
// Created by Nader Khedr on 03/03/2024.
//


#include "../inc/ValueNoise.hpp"

#include <cstdio>
#include <random>
#include <functional>
#include <iostream>
#include <fstream>
#include <cmath>

template<typename T>
class Vec2
{
public:
    Vec2() : x(T(0)), y(T(0)) {}
    Vec2(T xx, T yy) : x(xx), y(yy) {}
    Vec2 operator * (const T &r) const { return Vec2(x * r, y * r); }
    Vec2& operator *= (const T &r) { x *= r, y *= r; return *this; }
    T x, y;
};

typedef Vec2<float> Vec2f;

template<typename T = float>
inline T lerp(const T &lo, const T &hi, const T &t)
{
    return lo * (1 - t) + hi * t;
}

inline
float smoothstep(const float &t)
{
    return t * t * (3 - 2 * t);
}

class Value_Noise
{
public:
    Value_Noise(unsigned seed = 2016)
    {
        std::mt19937 gen(seed);
        std::uniform_real_distribution<float> distrFloat;
        auto randFloat = std::bind(distrFloat, gen);

        // create an array of random values and initialize permutation table
        for (unsigned k = 0; k < kMaxTableSize; ++k) {
            r[k] = randFloat();
            permutationTable[k] = k;
        }

        // shuffle values of the permutation table
        std::uniform_int_distribution<unsigned> distrUInt;
        auto randUInt = std::bind(distrUInt, gen);
        for (unsigned k = 0; k < kMaxTableSize; ++k) {
            unsigned i = randUInt() & kMaxTableSizeMask;
            std::swap(permutationTable[k], permutationTable[i]);
            permutationTable[k + kMaxTableSize] = permutationTable[k];
        }
    }

    float eval(Vec2f p) const
    {
        int xi = std::floor(p.x);
        int yi = std::floor(p.y);

        float tx = p.x - xi;
        float ty = p.y - yi;

        int rx0 = xi & kMaxTableSizeMask;
        int rx1 = (rx0 + 1) & kMaxTableSizeMask;
        int ry0 = yi & kMaxTableSizeMask;
        int ry1 = (ry0 + 1) & kMaxTableSizeMask;

        // random values at the corners of the cell using permutation table
        const float & c00 = r[permutationTable[permutationTable[rx0] + ry0]];
        const float & c10 = r[permutationTable[permutationTable[rx1] + ry0]];
        const float & c01 = r[permutationTable[permutationTable[rx0] + ry1]];
        const float & c11 = r[permutationTable[permutationTable[rx1] + ry1]];

        // remapping of tx and ty using the Smoothstep function
        float sx = smoothstep(tx);
        float sy = smoothstep(ty);

        // linearly interpolate values along the x axis
        float nx0 = lerp(c00, c10, sx);
        float nx1 = lerp(c01, c11, sx);

        // linearly interpolate the nx0/nx1 along they y axis
        return lerp(nx0, nx1, sy);
    }


    static const unsigned kMaxTableSize = 256;
    static const unsigned kMaxTableSizeMask = kMaxTableSize - 1;
    float r[kMaxTableSize];
    unsigned permutationTable[kMaxTableSize * 2];
};


ValueNoise::ValueNoise() = default;



Noise ValueNoise::genNoise(size_t seed, size_t width, size_t height, size_t frequency) const {
    // generate value noise
    BitMap<int> noiseMap = BitMap<int>(width,height,0);
    Value_Noise noise(seed);
    float freq = 0.05f;
    for (unsigned j = 0; j < height; ++j) {
        for (unsigned i = 0; i < width; ++i) {
            // generate a float in the range [0:1]
            const Vec2f v2f = Vec2f(i, j);
            float g = noise.eval(v2f * freq)*255;
            noiseMap.put(j,i, static_cast<int>(g));
        }
    }
    return Noise(noiseMap,seed,width,height,frequency);

}
