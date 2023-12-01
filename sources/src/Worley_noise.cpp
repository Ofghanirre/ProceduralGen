// Worley Noise implementation
/*
 * This Noise is often use to generate clouds or cell-like patterns
 * due to the slow algorithms, this noise is pre-generated before usages
 *
 */

#include "../inc/Worley_noise.h"

BitMap Worley_noise::generate(uint seed, uint width, uint height, uint gridSize) {

    // Init a 2D Vector with zeros
    std::vector<std::vector<float>> pixels(height, std::vector<float>(width, 0));

    // Init random generators
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distrib_width(0, gridSize);
    std::uniform_int_distribution<int> distrib_height(0, gridSize);

    // Generate random points in grid
    std::vector<vec2> points;

    for (int gridY = 0; gridY < width - gridSize+1; gridY+= gridSize) {
        for (int gridX = 0; gridX < height - gridSize+1; gridX+= gridSize) {
            int x = distrib_width(generator);
            int y = distrib_height(generator);
            points.emplace_back(vec2{x+gridX,y+gridY});
            std::cout << x+gridX << " hey " << y+gridY << std::endl;
        }
    }
    std::cout << points.size() << std::endl;
    // Calculate distance
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {

            // Find closest point
            double distances[points.size()];
            for (int i = 0; i < points.size(); i++) {
                distances[i] = distance(points[i], {x, y});
            }

            std::sort(distances, distances + points.size());

            pixels[y][x] = distances[0]; // need to normalize
        }
    }
    for (int i = 0; i < points.size(); i++) {
        pixels[points[i].x][points[i].y] = 255;
    }

    return pixels;
}

void Worley_noise::test() {

    int width = 10, height = 10;
    int seed = 5;
    uint gridSize = 4;
    BitMap img = Worley_noise::generate(seed, width, height, gridSize);


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