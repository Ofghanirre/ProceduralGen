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
