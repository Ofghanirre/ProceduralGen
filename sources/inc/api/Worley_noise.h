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
    Worley_noise(int minRnage, int maxRange);
    Worley_noise();

    Noise genNoise(size_t seed, size_t width, size_t height, size_t frequency);
    static void test(size_t width, size_t height, size_t seed, size_t gridSize);
private :
    int _minRange = 0;
    int _maxRange = 255;
};

#endif // PROCEDURALGEN_WORLEY_NOISE_H