#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <memory>
// #include "glm/vec2.hpp"
#include "./api/noise/INoiseGenerator.h"

using namespace std;
// using namespace glm;

struct Vector2 {
    float x;
    float y;
};

class Perlin : public INoiseGenerator
{
public:

    ~Perlin() = default;

    /**
     * @brief Constructor of the class
    */
    Perlin(int minRange, int maxRange, size_t gridSize);

    /**
     * @brief The generator of perlin noise.
     * It will generate a vector of vector of int of size width * height
     * whose values are between min_range and max_range
     * @param width the width of the resulting noise
     * @param height the height of the resulting noise
     * @param min_range the minimum value of the range
     * @param max_range the maximum value of the range
    */
    std::vector<std::vector<int>> perlin_noise(size_t width, size_t height, int min_range, int max_range, size_t seed) const; 

    Noise genNoise(size_t seed, size_t width, size_t height, size_t frequency) const override;

private:

    static Vector2 generate_random_vect();

    static Vector2 randomGradient(int ix, int iy, int seed);

    static float dotGridGradient(int grid_x, int grid_y, float x, float y, int seed);

    static float interpolation(float a0, float a1, float weight);

    /**
     * @brief A function that normalizes a vector of vector of float to a range of int between min and max
     * @param min the minimum int value of the normalized range
     * @param max the maximum int value of the normalized range
    */ 
    static std::vector<std::vector<int>> normalize_noise(int min, int max, std::vector<std::vector<float>> & pixels);

    int _minRange;  // The minimum value of the range of number generated.
    int _maxRange;  // The maximum value of the range of number generated.
    size_t _gridSize; // The size of the grid used to generate the Perlin noise.
};