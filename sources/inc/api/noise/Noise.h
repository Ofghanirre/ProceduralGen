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
    Noise(BitMap<int> bitmap, uint seed, uint width, uint height, uint frequency);


    [[nodiscard]] const BitMap<int> &getBitmap() const;

    [[nodiscard]] uint getSeed() const;

    [[nodiscard]] uint getWidth() const;

    [[nodiscard]] uint getHeight() const;

    [[nodiscard]] uint getFrequency() const;
private:
    const BitMap<int> m_bitmap;
    const uint m_seed;
    const uint m_width;
    const uint m_height;
    const uint m_frequency;
};
