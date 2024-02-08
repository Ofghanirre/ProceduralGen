//
// Created by Antonin Jean on 18/11/2023.
//

#include <api/noise/Noise.h>

#include <utility>

Noise::Noise(BitMap<int> bitmap, const size_t seed, const size_t width, const size_t height, const size_t frequency)
        : m_bitmap(std::move(bitmap)), m_seed(seed), m_width(width), m_height(height), m_frequency(frequency) {}


const BitMap<int>& Noise::getBitmap() const {

    return m_bitmap;
}

size_t Noise::getSeed() const {
    return m_seed;
}

size_t Noise::getWidth() const {
    return m_width;
}

size_t Noise::getHeight() const {
    return m_height;
}

size_t Noise::getFrequency() const {
    return m_frequency;
}
