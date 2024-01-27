#pragma once

#ifndef PROCEDURALGEN_WORLEY_NOISE_H
#define PROCEDURALGEN_WORLEY_NOISE_H

#include <iostream>
#include <random>
#include <algorithm>
#include "api/noise/BitMap.h"


class Worley_noise {
public:
    static BitMap<int> generate(uint seed, uint width, uint height, uint gridSize);

    static void test(int width, int height, int seed, int gridSize);
};

#endif // PROCEDURALGEN_WORLEY_NOISE_H