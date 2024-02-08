#pragma once

#ifndef PROCEDURALGEN_WORLEY_NOISE_H
#define PROCEDURALGEN_WORLEY_NOISE_H

#include <iostream>
#include <random>
#include <algorithm>
#include <memory>
#include "noise/BitMap.h"
#include "noise/INoiseGenerator.h"


class Worley_noise : public INoiseGenerator {
public:
    Worley_noise(int minRange, int maxRange);
    Worley_noise();

    std::vector<std::vector<int>> worley_noise(size_t seed, size_t width, size_t height, size_t gridSize) const;

    Noise genNoise(size_t seed, size_t width, size_t height, size_t frequency) const;

    static void test(size_t width, size_t height, size_t seed, size_t gridSize, size_t minRange, size_t maxRange);
private :
    int _minRange = 0;
    int _maxRange = 255;
};

#endif // PROCEDURALGEN_WORLEY_NOISE_H