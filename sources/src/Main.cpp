//
// Created by Antonin Jean on 25/01/2024.
//

#include <api/noise/BitMap.h>
#include <iostream>
#include <api/Terrain.h>


int main(void) {
    Terrain terrain("test", 0);
    // terrain.addTerrainNode(Noise::PerlinNoise(0.5, 0.5, 0.5, 0.5, 0.5, 0.5), NoisePunderationFunction::IDENTITY);
    // terrain.addTerrainNode(Noise::PerlinNoise(1.5, 0.5, 0.5, 0.5, 0.5, 1.5), NoisePunderationFunction::SQUARE);
    // terrain.addTerrainNode(Noise::WorleyNoise(0.5, 0.5, 0.5, 0.5, 0.5, 0.5), NoisePunderationFunction::INVERSE);
    // terrain.addTerrainNode(Noise::ValueNoise(0.5, 0.5, 0.5, 0.5, 0.5, 0.5), NoisePunderationFunction::ABS);
    Noise result = terrain.getTerrain(256, 256, 42);
    return 0;
}
