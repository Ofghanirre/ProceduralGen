// Perlin Noise implementation
/*
 * This Noise is often use to terrain-like patterns
 * due to the slow algorithms, this noise is pre-generated before usages
 *
 */

// Some of those functions have been taken from https://pastebin.com/gXEYsmw8

#include "../inc/Perlin.hpp"

Perlin::Perlin(int minRange, int maxRange, size_t gridSize, float amp)
    : _minRange {minRange}
    , _maxRange {maxRange}
    , _gridSize {gridSize}
    , _amp {amp}
    {}

Vector2 Perlin::generate_random_vect()
{
    Vector2 v;
    v.x = sin(rand());
    v.y = cos(rand());
    return v;
}

// Generate a random gradient vector
Vector2 Perlin::randomGradient(int ix, int iy, int seed)
{
    // No precomputed gradients mean this works for any number of grid coordinates
    // Init random generators
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distrib_x(0, 3284157443);
    std::uniform_int_distribution<int> distrib_y(0, 1911520717);

    std::uniform_int_distribution<int> distrib_z(0, 2048419325);


    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    //a *= 3284157443;
    a *= distrib_x(generator);

    b ^= a << s | a >> w - s;
    //b *= 1911520717;
    b *= distrib_y(generator);

    a ^= b << s | b >> w - s;
    //a *= 2048419325;
    a *= distrib_z(generator);
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    Vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

// Compute the dot product of the distance and gradient vectors
float Perlin::dotGridGradient(int grid_x, int grid_y, float x, float y, int seed)
{
    Vector2 gradiant = randomGradient(grid_x, grid_y, seed);

    // Compute distance from grid point to our pixel
    float dx = x - (float)grid_x;
    float dy = y - (float)grid_y;

    // Compute dot product
    return gradiant.x * dx + gradiant.y * dy;
}

float Perlin::interpolation(float a0, float a1, float weight)
{
    // Cubic interpolation
    return (a1 - a0) * (3.0 - weight * 2.0) * weight * weight + a0;
}

/**
 * @brief A function that normalizes a vector of vector of float to a range of int between min and max
 * @param min the minimum int value of the normalized range
 * @param max the maximum int value of the normalized range
*/ 
std::vector<std::vector<int>> Perlin::normalize_noise(int min, int max, std::vector<std::vector<float>> & pixels, float amp){

    std::vector<std::vector<int>> normalized_pixels;

    float min_value = pixels[0][0];
    float max_value = pixels[0][0];

    for (const vector<float> vec : pixels){
        for (float val : vec){
            if (val < min_value){
                min_value = val;
            }
            if (val > max_value){
                max_value = val;
            }
        }
    }

    float span = max_value - min_value; // The range span of the noise
    float new_span = max - min;
    float convertion_factor = new_span / span;

    for (size_t i = 0; i < pixels.size(); i++){
        vector<int> line;
        for (size_t j = 0; j < pixels[i].size(); j++){
            line.push_back(((pixels[i][j] - min_value) * convertion_factor) * amp);
        }
        normalized_pixels.push_back(line);
    }

    return normalized_pixels;
}

/**
 * @brief The generator of perlin noise.
 * It will generate a vector of vector of int of size width * height
 * whose values are between min_range and max_range
 * @param width the width of the resulting noise
 * @param height the height of the resulting noise
 * @param min_range the minimum value of the range
 * @param max_range the maximum value of the range
 * @param seed the seed used to generate random numbers
 * @param amp the amplitude of the noise
*/
std::vector<std::vector<int>> Perlin::perlin_noise(size_t width, size_t height, int min_range, int max_range, size_t seed, float amp) const
{
    std::vector<std::vector<float>> pixels;

    for (int y = 0; y < height; y++)
    {
        std::vector<float> line;  // The values of the pixel of line y
        for (int x = 0; x < width; x++)
        {
            // Point coordinate on the grid
            float px = (float)x / (float)_gridSize;
            float py = (float)y / (float)_gridSize;

            // Grid cell corner coordinates
            // Coordinates of the first corner (top left)
            int x0 = (int)px;
            int y0 = (int)py;

            // Coordinates of the last corner (bottom right)
            int x1 = x0 + 1;
            int y1 = y0 + 1;

            // Interpolation Weight
            float sx = px - (float)x0;
            float sy = py - (float)y0;

            // Compute interpolation for top two corners
            float grad1 = dotGridGradient(x0, y0, px, py, seed);
            float grad2 = dotGridGradient(x1, y0, px, py, seed);
            float top_interpol_val = interpolation(grad1, grad2, sx);

            // Compute interpolation for the bottom two corner
            grad1 = dotGridGradient(x0, y1, px, py, seed);
            grad2 = dotGridGradient(x1, y1, px, py, seed);
            float bot_interpol_val = interpolation(grad1, grad2, sx);

            line.push_back(interpolation(top_interpol_val, bot_interpol_val, sy));
        }
        pixels.push_back(line);
    }
    return normalize_noise(_minRange, _maxRange, pixels, _amp);
}

Noise Perlin::genNoise(size_t seed, size_t width, size_t height, size_t frequency) const {

    // Creates a BitMap of size width * height filled with the generated values
    BitMap bitmap = BitMap(width, height, perlin_noise(width, height, _minRange, _maxRange, seed, _amp));

    return Noise(bitmap, seed, width, height, frequency);
}

// int main()
// {
//     // ---------------------- Test ---------------------------
//     int width = 10;
//     int height = 10;
//     int grid_size = 5;
//     // float **noise = Perlin::perlin_noise(width, height, grid_size);
//     std::cout.precision(2);

//     Perlin perlin = Perlin(0, 255, grid_size);
//     std::vector<std::vector<int>> pixels = perlin.perlin_noise(width, height, 0, 255, 54);
//     int max = 0;
//     int min = 50;
//     for (int y = 0; y < height; y++)
//     {
//         for (int x = 0; x < width; x++)
//         {
//             std::cout << pixels[y][x] << "\t";
//             if (max < pixels[y][x]){
//                 max = pixels[y][x];
//             }
//             if (min > pixels[y][x]){
//                 min = pixels[y][x];
//             }
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "Max is : " << max <<std::endl;
//     std::cout << "Min is : " << min <<std::endl;


//     /*--------------------Testing with INoiseGenerator container--------------------*/

//     std::vector<std::unique_ptr<INoiseGenerator>> gen;
//     gen.emplace_back(std::make_unique<Perlin>(0, 255, grid_size));


//     for (const auto& iter_gen: gen) {
//         Noise testNoise = iter_gen->genNoise(54, width, height, 0);

//         std::cout << "Height " << testNoise.getHeight() <<std::endl;
//         std::cout << "Width " <<testNoise.getWidth() <<std::endl;

        
//         BitMap<int> testBitmap = testNoise.getBitmap();

//         for (int y = 0; y < height; y++)
//         {
//             for (int x = 0; x < width; x++){
//                 std::cout << testBitmap.get(x, y) << "\t";
//             }

//             std::cout << std::endl;
//         }
//         std::cout << "Height " << testBitmap.getHeight() <<std::endl;
//         std::cout << "Width " <<testBitmap.getWidth() <<std::endl;
//         std::cout << "Size " << testBitmap.getSize() <<std::endl;
//     }



//     return 1;
// }