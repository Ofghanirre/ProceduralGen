// Worley Noise implementation
/*
 * This Noise is often use to generate clouds or cell-like patterns
 * due to the slow algorithms, this noise is pre-generated before usages
 *
 */

#include "../inc/Worley_noise.h"

BitMap<int> Worley_noise::generate(uint seed, uint width, uint height, uint gridSize) {

    // Init a 2D Vector with zeros
    std::vector<std::vector<float>> pixels(height, std::vector<float>(width, 0));

    // Init random generators
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distrib_width(0, gridSize);
    std::uniform_int_distribution<int> distrib_height(0, gridSize);

    // Generate random points in grid
    std::vector<vec2<float>> points;

    for (int gridY = 0; gridY < width - gridSize+1; gridY+= gridSize) {
        for (int gridX = 0; gridX < height - gridSize+1; gridX+= gridSize) {
            int x = distrib_width(generator);
            int y = distrib_height(generator);
            points.emplace_back(static_cast<float>(x+gridX),static_cast<float>(y+gridY));
        }
    }

    // Calculate distance
    float max = 0;
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {

            // Find closest point
            float distances[points.size()];
            for (int i = 0; i < points.size(); i++) {
                distances[i] = distance(points[i], {static_cast<float>(x), static_cast<float>(y)});
            }

            std::sort(distances, distances + points.size());

            pixels[y][x] = distances[0]; // need to normalize
            if (max < distances[0]) {
                max = distances[0];
            }
        }
    }
    // Normalization scale
    float scale = 255 / max;

    // After calculation in float, create a BitMap Object in int
    BitMap<int> bitmap(width,height, 0);

    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {
            // Fill the new BitMap object
            bitmap[y*width+x]= (int)  (pixels[y][x] * scale);
        }
    }
    return bitmap;
}

void Worley_noise::test(int width, int height, int seed, int gridSize) {
    std::cout << "Worley noise test" << std::endl;
    BitMap img = Worley_noise::generate(seed, width, height, gridSize);

    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {
            std::cout << img[y*img.getWidth()+x] << "\t";
        }
        std::cout << std::endl;
    }
}