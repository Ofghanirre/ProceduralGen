// Worley Noise implementation
/*
 * This Noise is often use to generate clouds or cell-like patterns
 * due to the slow algorithms, this noise is pre-generated before usages
 *
 */

#include "../inc/Worley_noise.hpp"


Worley_noise::Worley_noise(int minRange, int maxRange) : _minRange(minRange), _maxRange(maxRange){};
Worley_noise::Worley_noise(){};



std::vector<std::vector<int>> Worley_noise::worley_noise(size_t seed, size_t width, size_t height, size_t gridSize) const{

    // Init a 2D Vector with zeros
    std::vector<std::vector<float>> pixels(height, std::vector<float>(width, 0));
    std::vector<std::vector<int>> pixels_int(height, std::vector<int>(width, 0));

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
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {

            // Find closest point
            float distances[points.size()];
            for (int i = 0; i < points.size(); i++) {
                distances[i] = distance(points[i], {static_cast<float>(x), static_cast<float>(y)});
            }

            std::sort(distances, distances + points.size());

            pixels[x][y] = distances[0]; // need to normalize
            if (max < distances[0]) {
                max = distances[0];
            }
        }
    }

    // Normalization scale
    float new_range = _maxRange - _minRange;

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            // Fill the new BitMap object
            //bitmap[x*width+y]
            pixels_int[x][y] = (pixels[x][y] / max * new_range + _minRange );
        }
    }
    return pixels_int;


}

Noise Worley_noise::genNoise(size_t seed, size_t width, size_t height, size_t gridSize) const {
    BitMap<int> bitmap(width,height, worley_noise(seed, width, height, gridSize));

    return Noise(bitmap, seed, width, height, gridSize);
}

void Worley_noise::test(size_t width, size_t height, size_t seed, size_t gridSize, size_t minRange, size_t maxRange) {
    //Worley_noise::test(24,8,5,7,5,10);
    std::cout << "Worley noise test" << std::endl;
    Worley_noise worleyNoiseGenerator = Worley_noise(minRange,maxRange);
    Noise worleyNoise = worleyNoiseGenerator.genNoise(seed, width, height, gridSize);
    BitMap img = worleyNoise.getBitmap();

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            std::cout << img.get(y,x)<< "\t";
        }
        std::cout << std::endl;
    }
    std::vector<std::unique_ptr<INoiseGenerator>> genVector;
    genVector.emplace_back(std::make_unique<Worley_noise>(minRange,maxRange));

    for (const auto &noise_gen: genVector) {
        Noise testNoise = noise_gen->genNoise(seed, width, height, gridSize);
        std::cout << "Height " << testNoise.getHeight() << std::endl;
        std::cout << "Width " << testNoise.getWidth() << std::endl;
    }
}
