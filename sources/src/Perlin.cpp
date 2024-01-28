// Perlin Noise implementation
/*
 * This Noise is often use to terrain-like patterns
 * due to the slow algorithms, this noise is pre-generated before usages
 *
 */

// Some of those functions have been taken from https://pastebin.com/gXEYsmw8

#include "../inc/Perlin.hpp"

vec2 generate_random_vect()
{
    vec2 v;
    v.x = sin(rand());
    v.y = cos(rand());
    return v;
}

// Generate a random gradient vector
vec2 randomGradient(int ix, int iy, int seed = 0)
{
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    vec2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

// Compute the dot product of the distance and gradient vectors
float dotGridGradient(int grid_x, int grid_y, float x, float y)
{
    vec2 gradiant = randomGradient(grid_x, grid_y);

    // Compute distance from grid point to our pixel
    float dx = x - (float)grid_x;
    float dy = y - (float)grid_y;

    // Compute dot product
    return gradiant.x * dx + gradiant.y * dy;
}

float interpolation(float a0, float a1, float weight)
{
    // Cubic interpolation
    return (a1 - a0) * (3.0 - weight * 2.0) * weight * weight + a0;
}

std::vector<std::vector<float>> Perlin::perlin_noise(uint width, uint height, uint grid_size)
{
    std::vector<std::vector<float>> pixels;

    // Initiating value table
    //float **pixels = new float *[height];

    /*for (int y = 0; y < height; y++)
    {
        pixels[y] = new float[width];
    }*/

    for (int y = 0; y < height; y++)
    {
        std::vector<float> line;  // The values of the pixel of line y
        for (int x = 0; x < width; x++)
        {
            // Point coordinate on the grid
            float px = (float)x / (float)grid_size;
            float py = (float)y / (float)grid_size;

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
            float grad1 = dotGridGradient(x0, y0, px, py);
            float grad2 = dotGridGradient(x1, y0, px, py);
            float top_interpol_val = interpolation(grad1, grad2, sx);

            // Compute interpolation for the bottom two corner
            grad1 = dotGridGradient(x0, y1, px, py);
            grad2 = dotGridGradient(x1, y1, px, py);
            float bot_interpol_val = interpolation(grad1, grad2, sx);

            line.push_back(interpolation(top_interpol_val, bot_interpol_val, sy));
        }
        pixels.push_back(line);
    }
    return pixels;
}

int main()
{
    // ---------------------- Test ---------------------------
    int width = 50;
    int height = 50;
    int grid_size = 10;
    // float **noise = Perlin::perlin_noise(width, height, grid_size);
    std::cout.precision(2);

    std::vector<std::vector<float>> pixels = Perlin::perlin_noise(width, height, grid_size);
    float min = 0;
    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < height; x++)
        {
            std::cout << pixels[y][x] << "\t";
            if (min > pixels[y][x]){
                min = pixels[y][x];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Min is : " << min <<std::endl;
    return 1;
}