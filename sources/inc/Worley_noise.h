#pragma once

#ifndef PROCEDURALGEN_WORLEY_NOISE_H
#define PROCEDURALGEN_WORLEY_NOISE_H

#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include <iostream>
#include <random>
#include <algorithm>

using namespace glm;
using BitMap = std::vector<std::vector<float>>;

class Worley_noise {
public:
    static BitMap generate(uint seed, uint width, uint height, uint nbPoints);

    static void hello();
    static void test();
};

#endif // PROCEDURALGEN_WORLEY_NOISE_H