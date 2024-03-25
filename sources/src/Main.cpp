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
    Perlin p = Perlin(0, 255, 30, 1);
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
    Perlin globalShape = Perlin(0, 255, scale, 1);
    Perlin canyonShape = Perlin(0, 255, scale/2, 1);
    Perlin detailShape = Perlin(0, 255, scale/20, 1);
    Perlin microShape = Perlin(0, 255, scale/200, 1); 
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
    Perlin globalShape = Perlin(0, 255, scale, 1);
    Perlin canyonShape = Perlin(0, 255, scale/2, 1);
    Perlin detailShape = Perlin(0, 255, scale/10, 1);
    Perlin microShape = Perlin(0, 255, scale/34, 1); 
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

void testArchipellago(int size) {
    std::cout << "Initialising Terrain..." << std::endl;
    Terrain terrain("Test Terrain 3", time(NULL));
    int width = size;
    int height = width;
    std::cout.precision(2);
    int scale = width;
    // Perlin globalShape = Perlin(0, 255, scale);
    Worley_noise w = Worley_noise(0, 255);
    Perlin perlin1 = Perlin(0, 255, scale/2);
    Perlin perlin2 = Perlin(0, 255, scale/10);
    Perlin perlin3 = Perlin(0, 255, scale/10);
    // Perlin microShape = Perlin(0, 255, scale/34); 
    auto punderation1 = FilterPunderationFunction([](int value) { return value > 0; }, std::make_shared<ProductPunderationFunction<double>>(0.7));
    auto punderation2 = ProductPunderationFunction<double>(0.15);
    auto punderation3 = ProductPunderationFunction<double>(0.05);
    auto globalFunction = InversePunderationFunction(255);
    // terrain.addTerrainNode(globalShape, globalFunction);
    terrain.addTerrainNode(w, NoisePunderationFunction::IDENTITY);

    Noise result_inter1 = terrain.getTerrain(width, height, 83);
    result_inter1.toPGM("./Archipellago_step1.pgm");

    terrain.addTerrainNode(perlin1, punderation1, [](int value) { return value > 0; });

    Noise result_inter2 = terrain.getTerrain(width, height, 83);
    result_inter2.toPGM("./Archipellago_step2.pgm");

    terrain.addTerrainNode(perlin2, NoisePunderationFunction::INVERSE);

    Noise result_inter3 = terrain.getTerrain(width, height, 83);
    result_inter3.toPGM("./Archipellago_step3.pgm");

    terrain.addTerrainNode(perlin3, NoisePunderationFunction::INVERSE);
    // terrain.addTerrainNode(microShape, microPunderation);

    std::cout << "Generating Terrain..." << std::endl;
    Noise result = terrain.getTerrain(width, height, 83);

    std::cout << "Exporting..." << std::endl;
    result.toPGM("./Archipellago_step4.pgm");
    // result.toPPM("./heatmap2.ppm", HEATMAP);
    result.toPPM("./Archipellago.ppm", TERRAIN, 255);
    std::cout << "Done." << std::endl;
}

int main(void) {
    // ---------------------- Test ---------------------------
    int size = 512;
    std::cout << "--- Terrain 1 ---" << std::endl;
    testTerrain1(size);
    std::cout << "--- Terrain 2 ---" << std::endl;
    testTerrain2(size);
    std::cout << "--- Archipellago ---" << std::endl;
    testArchipellago(size);

    Terrain terrain("test", 0);

    Perlin p = Perlin(0, 255, 200, 1);
    terrain.addTerrainNode(p, NoisePunderationFunction::IDENTITY);
    Noise result1 = terrain.getTerrain(800, 800, 42);
    result1.toPGM("./PerlinTest/perlinTEST1.pgm");
    Terrain terrain1("test", 0);
    terrain1.addTerrainNode(p, NoisePunderationFunction::IDENTITY);
    Noise res1 = terrain1.getTerrain(800, 800, 42);
    res1.toPGM("./PerlinTest/map1.pgm");

    Perlin p2 = Perlin(0, 255, 100, 1.f/2.f);
    terrain.addTerrainNode(p2, NoisePunderationFunction::IDENTITY);
    Noise result2 = terrain.getTerrain(800, 800, 42);
    result2.toPGM("./PerlinTest/perlinTEST2.pgm");
    Terrain terrain2("test", 0);
    terrain2.addTerrainNode(p2, NoisePunderationFunction::IDENTITY);
    Noise res2 = terrain2.getTerrain(800, 800, 42);
    res2.toPGM("./PerlinTest/map2.pgm");

    Perlin p3 = Perlin(0, 255, 50, 1.f/4.f);
    terrain.addTerrainNode(p3, NoisePunderationFunction::IDENTITY);
    Noise result3 = terrain.getTerrain(800, 800, 42);
    result3.toPGM("./PerlinTest/perlinTEST3.pgm");
    Terrain terrain3("test", 0);
    terrain3.addTerrainNode(p3, NoisePunderationFunction::IDENTITY);
    Noise res3 = terrain3.getTerrain(800, 800, 42);
    res3.toPGM("./PerlinTest/map3.pgm");

    Perlin p4 = Perlin(0, 255, 25, 1.f/8.f);
    terrain.addTerrainNode(p4, NoisePunderationFunction::IDENTITY);
    Noise result4 = terrain.getTerrain(800, 800, 42);
    result4.toPGM("./PerlinTest/perlinTEST4.pgm");
    Terrain terrain4("test", 0);
    terrain4.addTerrainNode(p4, NoisePunderationFunction::IDENTITY);
    Noise res4 = terrain4.getTerrain(800, 800, 42);
    res4.toPGM("./PerlinTest/map4.pgm");

    Perlin p5 = Perlin(0, 255, 15, 1.f/16.f);
    terrain.addTerrainNode(p5, NoisePunderationFunction::IDENTITY);
    Noise result5 = terrain.getTerrain(800, 800, 42);
    result5.toPGM("./PerlinTest/perlinTEST5.pgm");
    Terrain terrain5("test", 0);
    terrain5.addTerrainNode(p5, NoisePunderationFunction::IDENTITY);
    Noise res5 = terrain5.getTerrain(800, 800, 42);
    res5.toPGM("./PerlinTest/map5.pgm");

    Perlin p6 = Perlin(0, 255, 10, 1.f/32.f);
    terrain.addTerrainNode(p6, NoisePunderationFunction::IDENTITY);
    Noise result6 = terrain.getTerrain(800, 800, 42);
    result6.toPGM("./PerlinTest/perlinTEST6.pgm");
    Terrain terrain6("test", 0);
    terrain6.addTerrainNode(p6, NoisePunderationFunction::IDENTITY);
    Noise res6 = terrain6.getTerrain(800, 800, 42);
    res6.toPGM("./PerlinTest/map6.pgm");

    Noise result = terrain.getTerrain(800, 800, 42);
    result.toPGM("./PerlinTest/perlinTESTRES.pgm");

    return 0;
}


