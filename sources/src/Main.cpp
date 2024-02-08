//
// Created by Antonin Jean on 25/01/2024.
//

#include <api/noise/BitMap.h>
#include <iostream>
#include <api/Terrain.h>
#include <Perlin.hpp>
#include <Worley_noise.hpp>


int main(void) {
    Terrain terrain("test", 0);
    Perlin p = Perlin(0, 255, 5);
    terrain.addTerrainNode(p, NoisePunderationFunction::IDENTITY);
    // // terrain.addTerrainNode(Noise::PerlinNoise(1.5, 0.5, 0.5, 0.5, 0.5, 1.5), NoisePunderationFunction::SQUARE);
    // // terrain.addTerrainNode(Noise::WorleyNoise(0.5, 0.5, 0.5, 0.5, 0.5, 0.5), NoisePunderationFunction::INVERSE);
    // // terrain.addTerrainNode(Noise::ValueNoise(0.5, 0.5, 0.5, 0.5, 0.5, 0.5), NoisePunderationFunction::ABS);
    Noise result = terrain.getTerrain(256, 256, 42);
    result.toPGM("./noise.pgm");

    // ---------------------- Test ---------------------------
    int width = 10;
    int height = 10;
    int grid_size = 5;
    // float **noise = Perlin::perlin_noise(width, height, grid_size);
    std::cout.precision(2);

    Perlin perlin = Perlin(0, 255, grid_size);
    std::vector<std::vector<int>> pixels = perlin.perlin_noise(width, height, 0, 255, 54);
    int max = 0;
    int min = 50;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            std::cout << pixels[y][x] << "\t";
            if (max < pixels[y][x]){
                max = pixels[y][x];
            }
            if (min > pixels[y][x]){
                min = pixels[y][x];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Max is : " << max <<std::endl;
    std::cout << "Min is : " << min <<std::endl;


    /*--------------------Testing with INoiseGenerator container--------------------*/
    /*
    std::vector<std::unique_ptr<INoiseGenerator>> gen;
    gen.emplace_back(std::make_unique<Perlin>(0, 255, grid_size));


    for (const auto& iter_gen: gen) {
        Noise testNoise = iter_gen->genNoise(54, width, height, 0);

        std::cout << "Height " << testNoise.getHeight() <<std::endl;
        std::cout << "Width " <<testNoise.getWidth() <<std::endl;

        
        BitMap<int> testBitmap = testNoise.getBitmap();

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++){
                std::cout << testBitmap.get(x, y) << "\t";
            }

            std::cout << std::endl;
        }
        std::cout << "Height " << testBitmap.getHeight() <<std::endl;
        std::cout << "Width " <<testBitmap.getWidth() <<std::endl;
        std::cout << "Size " << testBitmap.getSize() <<std::endl;
    }

    */

    return 1;
}
