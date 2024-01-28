#pragma once
#include <iostream>
#include <random>
#include <vector>
#include "glm/vec2.hpp"

using namespace std;
using namespace glm;

class Perlin
{
public:

    /**
     * @brief The generator of perlin noise.
     * It will generate a vector of vector of int of size width * height
     * whose values are between min_range and max_range
     * @param width the width of the resulting noise
     * @param height the height of the resulting noise
     * @param min_range the minimum value of the range
     * @param max_range the maximum value of the range
    */
    static std::vector<std::vector<int>>  perlin_noise(uint width, uint height, int min_range, int max_range, uint grid_size); 

private:
};