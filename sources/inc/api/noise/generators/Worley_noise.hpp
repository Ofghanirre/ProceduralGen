#pragma once

#ifndef PROCEDURALGEN_WORLEY_NOISE_HPP
#define PROCEDURALGEN_WORLEY_NOISE_HPP

#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
#include <memory>
#include <set>
#include <map>
#include <api/noise/BitMap.h>
#include <api/noise/INoiseGenerator.h>
#include <limits>

class Worley_noise : public INoiseGenerator {
public:
    Worley_noise(int minRange, int maxRange, size_t gridSize);
    Worley_noise(int minRange, int maxRange, size_t gridSize, bool isVoronoi);
    Worley_noise();

    std::vector<std::vector<int>> worley_noise(size_t seed, size_t width, size_t height) const;

    Noise genNoise(size_t seed, size_t width, size_t height, size_t frequency) const;

    static void test(size_t width, size_t height, size_t seed, size_t gridSize, size_t minRange, size_t maxRange);
private :
    int _minRange = 0;
    int _maxRange = 255;
    int _gridSize = 1;
    bool _isVoronoi = false;
};

#endif // PROCEDURALGEN_WORLEY_NOISE_HPP