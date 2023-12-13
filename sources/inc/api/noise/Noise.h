//
// Created by Antonin Jean on 18/11/2023.
//

#pragma once

#include <iostream>
#include <vector>

using BitMap = std::vector<std::vector<float>>;

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
    Noise(BitMap bitmap, uint seed, uint width, uint height, uint frequency);


    [[nodiscard]] const BitMap &getBitmap() const;

    [[nodiscard]] uint getSeed() const;

    [[nodiscard]] uint getWidth() const;

    [[nodiscard]] uint getHeight() const;

    [[nodiscard]] uint getFrequency() const;
private:
    const BitMap _bitmap;
    const uint _seed;
    const uint _width;
    const uint _height;
    const uint _frequency;
};
