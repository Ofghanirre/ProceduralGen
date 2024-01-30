//
// Created by Antonin Jean on 18/11/2023.
//

#include "inc/api/noise/Noise.h"
#include <utility>

Noise::Noise(BitMap<int> bitmap, const uint seed, const uint width, const uint height, const uint frequency)
        : m_bitmap(std::move(bitmap)), m_seed(seed), m_width(width), m_height(height), m_frequency(frequency) {}

const BitMap<int>& Noise::getBitmap() const {
    return m_bitmap;
}

uint Noise::getSeed() const {
    return m_seed;
}

uint Noise::getWidth() const {
    return m_width;
}

uint Noise::getHeight() const {
    return m_height;
}

uint Noise::getFrequency() const {
    return m_frequency;
}
