// Worley Noise implementation
/*
 * This Noise is often use to generate clouds or cell-like patterns
 * due to the slow algorithms, this noise is pre-generated before usages
 *
 */

#include <iostream>
#include <random>
#include <algorithm>

struct Point {
    int x; // width
    int y; // height
};

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

uint **worley_noise(uint width, uint height, uint nbPoints, int seed = 0) {

    uint **pixels = new uint *[height];
    std::default_random_engine generator(seed); // Default seed is 0
    std::uniform_int_distribution<int> distrib_width(0, width);
    std::uniform_int_distribution<int> distrib_height(0, height);


    for (int y = 0; y < height; y++) {
        pixels[y] = new uint[width];
        for (int x = 0; x < width; x++) {
            //std::cout << "hey " << x << " " << y << std::endl;
            uint index = y * width + x;
            pixels[y][x] = 0;
        }
    }

    // random points
    Point points[nbPoints];
    for (int i = 0; i < nbPoints; i++) {
        int x = distrib_width(generator);
        int y = distrib_height(generator);
        //std::cout << "hey " << x << " " << y << std::endl;
        pixels[y][x] = 255;
        points[i] = Point{x, y};
    }

    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {

            //Find closest point
            double distances[nbPoints];
            for (int i = 0; i < nbPoints; i++) {
                distances[i]= distance(points[i], {x, y});
                //std::cout << distances[i] << std::endl;
            }

            std::sort(distances, distances+ nbPoints);
            for (int i = 0; i < nbPoints; i++) {
                //std::cout << distances[i] << std::endl;
            }

            pixels[y][x] = distances[0]; // need to normalize
        }
    }


    return pixels;
}

int main() {
    std::cout << "hey" << std::endl;
    int width = 20, height = 20;
    uint **img = worley_noise(width, height, 2, 5);

    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {
            std::cout << img[y][x] << "\t";
        }
        std::cout << std::endl;
    }
}