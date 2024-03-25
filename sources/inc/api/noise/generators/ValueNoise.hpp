//
// Created by Nader Khedr on 03/03/2024.
//

#ifndef VALUENOISE_HPP
#define VALUENOISE_HPP

#include <iostream>
#include <random>
#include <algorithm>
#include <memory>
#include <api/noise/BitMap.h>
#include <api/noise/INoiseGenerator.h>


class ValueNoise : public INoiseGenerator {
public:
    ValueNoise(int minRange, int maxRange);
    ValueNoise();

    std::vector<std::vector<int>> valueNoise(size_t seed, size_t width, size_t height, size_t gridSize) const;

    Noise genNoise(size_t seed, size_t width, size_t height, size_t frequency) const override;

private :
    int _minRange = 0;
    int _maxRange = 255;
};

#endif //VALUENOISE_HPP
