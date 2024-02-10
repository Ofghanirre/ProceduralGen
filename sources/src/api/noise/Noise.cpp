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

/**
 * @brief Generate a PGM file using the values contained in the noise
 * @param filename A string describing the name of the PGM file
*/
void Noise::toPGM(const char* filename) const {
    // Looking for the maximum value in the noise
    int max = 0;
    for (size_t x = 0; x < m_width; x++){
        for (size_t y = 0; y < m_height; y++){
            if (max < m_bitmap.get(x, y)){
                max = m_bitmap.get(x, y);
            }
        }
    }

    FILE * image;
    unsigned char* format;
    image = fopen(filename, "wb");
    fprintf(image, "P2\n");
    fprintf(image, "%lu %lu\n", m_width, m_height);
    fprintf(image, "%d\n", max);
    
    for (size_t x = 0; x < m_width; x++){
        for (size_t y = 0; y < m_height; y++){
            fprintf(image,"%d ", m_bitmap.get(x, y));
        }
        fprintf(image, "\n");
    }

    fclose(image);
}