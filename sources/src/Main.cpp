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
#include <chrono>

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

void testTerrain1(int size) {
    std::cout << "Initialising Terrain..." << std::endl;
    Terrain terrain("Test Terrain 1", time(NULL));
    int width = size;
    int height = width;
    std::cout.precision(2);
    int scale = width;
    Perlin globalShape = Perlin(0, 255, scale);
    Perlin canyonShape = Perlin(0, 255, scale/2);
    Perlin detailShape = Perlin(0, 255, scale/20);
    Perlin microShape = Perlin(0, 255, scale/200); 
    auto canyonPunderation = FilterPunderationFunction([](int value) { return value > 0; }, std::make_shared<ProductPunderationFunction<double>>(0.7));
    auto detailPunderation = ProductPunderationFunction<double>(0.15);
    auto microPunderation = ProductPunderationFunction<double>(0.05);
    terrain.addTerrainNode(globalShape);
    terrain.addTerrainNode(canyonShape, canyonPunderation, [](int value) { return value > 0; });
    terrain.addTerrainNode(detailShape, detailPunderation);
    terrain.addTerrainNode(microShape, microPunderation);

    std::cout << "Generating Terrain..." << std::endl;
    Noise result = terrain.getTerrain(width, height, 2);
    std::cout << "Exporting..." << std::endl;
    // result.toPGM("./values1.pgm", 255);
    // result.toPPM("./heatmap1.ppm", HEATMAP);
    result.toPPM("./terrain1.ppm", TERRAIN, 255);
    std::cout << "Done." << std::endl;
}

void testTerrain2(int size) {
    std::cout << "Initialising Terrain..." << std::endl;
    Terrain terrain("Test Terrain 2", time(NULL));
    int width = size;
    int height = width;
    std::cout.precision(2);
    int scale = width;
    Perlin globalShape = Perlin(0, 255, scale);
    Perlin canyonShape = Perlin(0, 255, scale/2);
    Perlin detailShape = Perlin(0, 255, scale/10);
    Perlin microShape = Perlin(0, 255, scale/34); 
    auto canyonPunderation = FilterPunderationFunction([](int value) { return value > 0; }, std::make_shared<ProductPunderationFunction<double>>(0.7));
    auto detailPunderation = ProductPunderationFunction<double>(0.15);
    auto microPunderation = ProductPunderationFunction<double>(0.05);
    auto globalFunction = InversePunderationFunction(255);
    terrain.addTerrainNode(globalShape, globalFunction);
    terrain.addTerrainNode(canyonShape, canyonPunderation, [](int value) { return value > 0; });
    terrain.addTerrainNode(detailShape, detailPunderation);
    terrain.addTerrainNode(microShape, microPunderation);

    std::cout << "Generating Terrain..." << std::endl;
    Noise result = terrain.getTerrain(width, height, 2);
    std::cout << "Exporting..." << std::endl;
    // result.toPGM("./values2.pgm", 255);
    // result.toPPM("./heatmap2.ppm", HEATMAP);
    result.toPPM("./terrain2.ppm", TERRAIN, 255);
    std::cout << "Done." << std::endl;
}
int main(void) {
    // ---------------------- Test ---------------------------
    int size = 512;
    std::cout << "--- Terrain 1 ---" << std::endl;
    testTerrain1(size);
    std::cout << "--- Terrain 2 ---" << std::endl;
    testTerrain2(size);
    return 0;
}


