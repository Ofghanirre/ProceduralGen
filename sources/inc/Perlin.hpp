#pragma once
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Perlin
{
public:
    static float **perlin_noise(uint width, uint height, uint grid_size);

private:
};