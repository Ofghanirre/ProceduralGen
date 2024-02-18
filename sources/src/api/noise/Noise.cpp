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
/*
void Noise::toPPM(const char* filename) const {
 // Looking for the maximum value in the noise
    int max = 0;
    for (size_t x = 0; x < m_width; x++){
        for (size_t y = 0; y < m_height; y++){
            if (max < m_bitmap.get(x, y)){
                max = m_bitmap.get(x, y);
            }
        }
    }
    int max_2 = max / 3;
    int max_3 = max_2 * 2;

    FILE * image;
    unsigned char* format;
    image = fopen(filename, "wb");
    fprintf(image, "P3\n");
    fprintf(image, "%lu %lu\n", m_width, m_height);
    fprintf(image, "%d\n", max);
    
    for (size_t x = 0; x < m_width; x++){
        for (size_t y = 0; y < m_height; y++){
            int value = m_bitmap.get(x, y);
            int red = std::min(max, value * 3);
            int green = std::min(max, std::max(0, (value - max_2) * 3));
            int blue = std::min(max, std::max(0, (value - max_3) * 3));
            fprintf(image,"%d %d %d ", red, green, blue);
        }
        fprintf(image, "\n");
    }

    fclose(image);
}
*/
void _heatMap(int value, int max, int& red, int &green, int &blue) {
    int max_2 = max / 3;
    int max_3 = max_2 * 2;
    red = std::min(max, value * 3);
    green = std::min(max, std::max(0, (value - max_2) * 3));
    blue = std::min(max, std::max(0, (value - max_3) * 3));
}

void _interpolateColor(int value, int max, float midThreshold, int minR, int minG, int minB, int maxR, int maxG, int maxB, int& R, int& G, int& B) {
    // Calculer le facteur d'interpolation
    double factor = static_cast<double>(value) / max;
    if (factor < midThreshold) {
        factor = factor * (1. - midThreshold);
    } else {
        factor = (factor - midThreshold) / (1. - midThreshold);
    }
    // Interpoler chaque composante de couleur
    R = minR + static_cast<int>(factor * (maxR - minR));
    G = minG + static_cast<int>(factor * (maxG - minG));
    B = minB + static_cast<int>(factor * (maxB - minB));
}

void _groupColor(int value, int max, int amountOfGroup, int minR, int minG, int minB, int maxR, int maxG, int maxB, int& R, int& G, int& B) {
    // Calculer la taille de chaque groupe
    int groupSize = max / amountOfGroup;

    // Déterminer le groupe auquel appartient la valeur
    int groupIndex = value / groupSize;

    // Interpoler la couleur en fonction du groupe
    _interpolateColor(groupIndex, amountOfGroup - 1, 0.8, minR, minG, minB, maxR, maxG, maxB, R, G, B);
}

void oceanColor(int value, int max, int& red, int& green, int& blue) {
    _interpolateColor(value, max, 0.8, 8, 23, 116, 119, 167, 179, red, green, blue);
}

void beachColor(int value, int max, int& red, int& green, int& blue) {
    _interpolateColor(value, max, 0.8, 99, 94, 72, 224, 214, 169, red, green, blue);
}

void plainColor(int value, int max, int& red, int& green, int& blue) {
    _groupColor(value, max, 22, 141, 199, 97, 48, 86, 30, red, green, blue);
}

void mountainColor(int value, int max, int& red, int& green, int& blue) {
    _interpolateColor(value, max, 0.6, 16, 35, 16, 159, 198, 198, red, green, blue);
}

void snowColor(int value, int max, int& red, int& green, int& blue) {
    _interpolateColor(value, max, 0.8, 159, 198, 198, 255, 255, 255, red, green, blue);
}
void _terrainTexture(int value, int max, int& red, int& green, int& blue) {
    int step = max / 32;
    int quota = value / step;
    if (quota < 4) { // DEEP OCEAN LEVEL
        red = 8;
        green = 23;
        blue = 116;
    } else if (quota < 9) {  // SHORES LEVEL
        oceanColor(value, step * 9, red, green, blue);
    } else if (quota < 11) { // BEACH LEVEL
        beachColor(value, step * 11, red, green, blue);
    } else if (quota < 28) { // PLAIN LEVEL
        plainColor(value, step * 28, red, green, blue);
    } else if (quota < 32) { // MOUNTAIN LEVEL
        mountainColor(value, step * 32, red, green, blue);
    } else { // SNOW LEVEL
        snowColor(value, step * 32, red, green, blue);
    }
}


void _saveterrainTexture(int value, int max, int& red, int& green, int& blue) {
    int step = max / 16;
    int sea_level = step*4;
    int beach_level = step * 6;
    int plain_level = step * 12;
    int mountain_level = max * 15;

    if (value < sea_level) {
        blue = 255;
        green = std::min(max, value * 5 / sea_level);
        red  = 0;
    } else if (value < beach_level) {
        blue = 0;
        green = std::min(max, (value - sea_level) * 10 / ( beach_level - sea_level));
        red = std::min(max, (value - sea_level) * 10 / ( beach_level - sea_level));
    } else if (value < plain_level) {
        blue = 0;
        green = std::min(max, (value - beach_level) * 3 / ( plain_level - beach_level));
        red = 0;
    } else if (value < mountain_level) {
        blue = green = red = std::min(max, (value - plain_level) * 3 / ( plain_level - mountain_level));
    } else {
        blue = red = green = max;
    }
}

void Noise::toPPM(const char* filename, void (*colorFunction)(int, int, int&, int&, int&)) const {
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
    fprintf(image, "P3\n");
    fprintf(image, "%lu %lu\n", m_width, m_height);
    fprintf(image, "%d\n", max);
    int red, blue, green;
    for (size_t x = 0; x < m_width; x++){
        for (size_t y = 0; y < m_height; y++){
            int value = m_bitmap.get(x, y);
            colorFunction(value, max, red, green, blue);
            fprintf(image,"%d %d %d ", red, green, blue);
        }
        fprintf(image, "\n");
    }

    fclose(image);
}

void Noise::toPPM(const char* filename, ENoiseColorFunction function) const {
    switch (function) {
        case HEATMAP: toPPM(filename, &_heatMap); break;
        case TERRAIN: toPPM(filename, &_terrainTexture); break;
    }
}
