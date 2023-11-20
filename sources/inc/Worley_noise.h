#pragma once

#ifndef PROCEDURALGEN_WORLEY_NOISE_H
#define PROCEDURALGEN_WORLEY_NOISE_H


#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include <iostream>
#include <random>
#include <algorithm>

using namespace glm;


class Worley_noise {
public:
    static uint **generate(uint width, uint height, uint nbPoints, int seed);

    static void hello();
    static void test();
};

#endif //PROCEDURALGEN_WORLEY_NOISE_H