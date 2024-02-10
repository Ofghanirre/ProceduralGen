//
// Created by Antonin Jean on 25/01/2024.
//

#include <iostream>
#include <memory>
#include <api/noise/BitMap.h>
#include <api/Terrain.h>
#include <Perlin.hpp>
#include <Worley_noise.hpp>


int main(void) {
    Terrain terrain("test", 0);
    Perlin p = Perlin(0, 255, 30);
    terrain.addTerrainNode(p, NoisePunderationFunction::IDENTITY);
    Noise result = terrain.getTerrain(256, 256, 42);
    result.toPGM("./perlin.pgm");

    Terrain terrain2("test2", 0);
    Worley_noise w = Worley_noise();
    terrain2.addTerrainNode(w, NoisePunderationFunction::IDENTITY);
    Noise result2 = terrain2.getTerrain(256, 256, 42);
    result2.toPGM("./worley.pgm");


    // ---------------------- Test ---------------------------
    int width = 10;
    int height = 10;
    int grid_size = 5;
    std::cout.precision(2);
    Perlin perlin = Perlin(0, 255, grid_size);
    Worley_noise worley = Worley_noise(0, 255);

    auto identityFunction = IdentityPunderationFunction();
    auto sumFunction = SumPunderationFunction(10);
    terrain.addTerrainNode(perlin, identityFunction);
    terrain.addTerrainNode(worley, sumFunction);

    Noise result = terrain.getTerrain(width, height, 2);
    
    BitMap<int> bitmap = result.getBitmap();
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++){
            std::cout << bitmap.get(x, y) << "\t";
        }

        std::cout << std::endl;
    }
    return 0;
}
