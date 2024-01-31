//
// Created by Antonin Jean on 18/11/2023.
//

#pragma once

#include <iostream>
#include <vector>
#include "BitMap.h"

class Noise {
public:
    /**
     * @brief Noise Object, describing its content, with parameters such as
     * @param bitmap The content of the noise described as a bitmap
     * @param seed the seed used to generate the noise
     * @param width the width of the windowed bitmap created
     * @param height the height of the windowed bitmap created
     * @param frequency the frequency used to create the noise
     */
    Noise(BitMap<int> bitmap, const size_t seed, const size_t width, const size_t height, const size_t frequency);

    const BitMap<int> &getBitmap() const;

    size_t getSeed() const;

    size_t getWidth() const;

    size_t getHeight() const;

    size_t getFrequency() const;
private:
    const BitMap<int> m_bitmap;
    const size_t m_seed;
    const size_t m_width;
    const size_t m_height;
    const size_t m_frequency;
};
