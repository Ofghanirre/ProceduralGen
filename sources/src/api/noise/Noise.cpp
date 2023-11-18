//
// Created by Antonin Jean on 18/11/2023.
//

#include "api/noise/Noise.h"
#include <utility>

Noise::Noise(BitMap bitmap, const uint seed, const uint width, const uint height, const uint frequency)
        : _bitmap(std::move(bitmap)), _seed(seed), _width(width), _height(height), _frequency(frequency) {}

const BitMap &Noise::getBitmap() const {
    return _bitmap;
}

uint Noise::getSeed() const {
    return _seed;
}

uint Noise::getWidth() const {
    return _width;
}

uint Noise::getHeight() const {
    return _height;
}

uint Noise::getFrequency() const {
    return _frequency;
}
