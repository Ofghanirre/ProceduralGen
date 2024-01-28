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
    static std::vector<std::vector<int>>  perlin_noise(uint width, uint height, int min_range, int max_range, uint grid_size, int seed); 

private:

    static vec2 generate_random_vect();

    static vec2 randomGradient(int ix, int iy, int seed);

    static float dotGridGradient(int grid_x, int grid_y, float x, float y, int seed);

    static float interpolation(float a0, float a1, float weight);

    /**
     * @brief A function that normalizes a vector of vector of float to a range of int between min and max
     * @param min the minimum int value of the normalized range
     * @param max the maximum int value of the normalized range
    */ 
    static std::vector<std::vector<int>> normalize_noise(int min, int max, std::vector<std::vector<float>> & pixels);
};