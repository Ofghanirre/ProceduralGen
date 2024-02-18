//
// Created by Antonin Jean on 25/01/2024.
//

#include <iostream>
#include <memory>
#include <api/noise/BitMap.h>
#include <api/Terrain.h>
#include <Perlin.hpp>
#include <Worley_noise.hpp>
#include <time.h>

void testPerlin() {
    Terrain terrain1("test", 0);
    Perlin p = Perlin(0, 255, 30);
    terrain1.addTerrainNode(p, NoisePunderationFunction::IDENTITY);
    Noise result1 = terrain1.getTerrain(256, 256, 42);
    result1.toPGM("./perlin.pgm");
}

void testWorley() {
    Terrain terrain2("test2", 0);
    Worley_noise w = Worley_noise();
    terrain2.addTerrainNode(w, NoisePunderationFunction::IDENTITY);
    Noise result2 = terrain2.getTerrain(1024, 1024, 42);
    result2.toPGM("./worley.pgm");
}

int main(void) {
    // testWorley();
    // ---------------------- Test ---------------------------
    Terrain terrain("test", time(NULL));
    int width = 516;
    int height = width;
    std::cout.precision(2);
    int scale = 200;
    Perlin globalShape = Perlin(0, 255, scale);
    Perlin canyonShape = Perlin(0, 255, scale/2);
    Perlin detailShape = Perlin(0, 255, scale/20);
    Perlin microShape = Perlin(0, 255, scale/200); 
    auto canyonPunderation = FilterPunderationFunction([](int value) { return value > 20; }, std::make_shared<ProductPunderationFunction<double>>(0.7));
    auto detailPunderation = FilterPunderationFunction([](int value) { return value > 20; }, std::make_shared<ProductPunderationFunction<double>>(0.15));
    auto microPunderation = FilterPunderationFunction([](int value) { return value > 20; }, std::make_shared<ProductPunderationFunction<double>>(0.05));
    terrain.addTerrainNode(globalShape, NoisePunderationFunction::IDENTITY);
    terrain.addTerrainNode(canyonShape, canyonPunderation);
    terrain.addTerrainNode(detailShape, detailPunderation);
    terrain.addTerrainNode(microShape, microPunderation);


    Noise result = terrain.getTerrain(width, height, 2);
    std::cout << "Result: " << std::endl;
    result.toPGM("./values.pgm");
    result.toPPM("./heatmap.ppm", HEATMAP);
    result.toPPM("./terrain.ppm", TERRAIN);
    return 0;
}


