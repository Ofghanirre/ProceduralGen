// Worley Noise implementation
/*
 * This Noise is often use to generate clouds or cell-like patterns
 * due to the slow algorithms, this noise is pre-generated before usages
 *
 */

#include "../inc/Worley_noise.h"

BitMap Worley_noise::generate(uint seed, uint width, uint height, uint nbPoints) {

    // Init a 2D Vector with zeros
    std::vector<std::vector<float>> pixels(height, std::vector<float>(width, 0));

    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distrib_width(0, width);
    std::uniform_int_distribution<int> distrib_height(0, height);

    // random points
    vec2 points[nbPoints];
    for (int i = 0; i < nbPoints; i++) {
        int x = distrib_width(generator);
        int y = distrib_height(generator);
        pixels[y][x] = 255;
        points[i] = vec2{x, y};
    }

    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {

            // Find closest point
            double distances[nbPoints];
            for (int i = 0; i < nbPoints; i++) {
                distances[i] = distance(points[i], {x, y});
            }

            std::sort(distances, distances + nbPoints);

            pixels[y][x] = distances[0]; // need to normalize
        }
    }

    return pixels;
}

void Worley_noise::test() {

    int width = 20, height = 20;
    int seed = 5;
    uint nbPoints = 2;
    BitMap img = Worley_noise::generate(seed, width, height, nbPoints);


    std::cout << std::fixed;
    std::cout.precision(2);
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {
            std::cout << img[y][x] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    Worley_noise::test();
}