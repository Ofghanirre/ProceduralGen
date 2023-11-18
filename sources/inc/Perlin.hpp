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
    static float **perlin_noise(uint width, uint height, uint grid_size);

private:
};