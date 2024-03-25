//
// Created by Antonin Jean on 25/01/2024.
//

#include <iostream>
#include <memory>
#include <api/noise/BitMap.h>
#include <api/Terrain/Terrain.h>
#include <api/noise/generators/Perlin.hpp>
#include <api/noise/generators/Worley_noise.hpp>
#include <time.h>
#include <chrono>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;


void testPerlin() {
    Terrain terrain1("test", 0);
    Perlin p = Perlin(0, 255, 30, 1);
    terrain1.addTerrainNode(p, NoisePunderationFunction::IDENTITY);
    Noise result1 = terrain1.getTerrain(256, 256, 42);
    result1.toPGM("./perlin.pgm");
}

void testPerlin2(){
    fs::create_directory("./PerlinTest");

    Terrain terrain("test", 0);

    Perlin p = Perlin(0, 255, 200, 1);
    terrain.addTerrainNode(p, NoisePunderationFunction::IDENTITY);
    Noise result1 = terrain.getTerrain(800, 800, 42);
    result1.toPGM("./PerlinTest/Result1.pgm");
    Terrain terrain1("test", 0);
    terrain1.addTerrainNode(p, NoisePunderationFunction::IDENTITY);
    Noise res1 = terrain1.getTerrain(800, 800, 42);
    res1.toPGM("./PerlinTest/perlin1.pgm");

    Perlin p2 = Perlin(0, 255, 100, 1.f/2.f);
    terrain.addTerrainNode(p2, NoisePunderationFunction::IDENTITY);
    Noise result2 = terrain.getTerrain(800, 800, 42);
    result2.toPGM("./PerlinTest/Result2.pgm");
    Terrain terrain2("test", 0);
    terrain2.addTerrainNode(p2, NoisePunderationFunction::IDENTITY);
    Noise res2 = terrain2.getTerrain(800, 800, 42);
    res2.toPGM("./PerlinTest/perlin2.pgm");

    Perlin p3 = Perlin(0, 255, 50, 1.f/4.f);
    terrain.addTerrainNode(p3, NoisePunderationFunction::IDENTITY);
    Noise result3 = terrain.getTerrain(800, 800, 42);
    result3.toPGM("./PerlinTest/Result3.pgm");
    Terrain terrain3("test", 0);
    terrain3.addTerrainNode(p3, NoisePunderationFunction::IDENTITY);
    Noise res3 = terrain3.getTerrain(800, 800, 42);
    res3.toPGM("./PerlinTest/perlin3.pgm");

    Perlin p4 = Perlin(0, 255, 25, 1.f/8.f);
    terrain.addTerrainNode(p4, NoisePunderationFunction::IDENTITY);
    Noise result4 = terrain.getTerrain(800, 800, 42);
    result4.toPGM("./PerlinTest/Result4.pgm");
    Terrain terrain4("test", 0);
    terrain4.addTerrainNode(p4, NoisePunderationFunction::IDENTITY);
    Noise res4 = terrain4.getTerrain(800, 800, 42);
    res4.toPGM("./PerlinTest/perlin4.pgm");

    Perlin p5 = Perlin(0, 255, 15, 1.f/16.f);
    terrain.addTerrainNode(p5, NoisePunderationFunction::IDENTITY);
    Noise result5 = terrain.getTerrain(800, 800, 42);
    result5.toPGM("./PerlinTest/Result5.pgm");
    Terrain terrain5("test", 0);
    terrain5.addTerrainNode(p5, NoisePunderationFunction::IDENTITY);
    Noise res5 = terrain5.getTerrain(800, 800, 42);
    res5.toPGM("./PerlinTest/perlin5.pgm");

    Perlin p6 = Perlin(0, 255, 10, 1.f/32.f);
    terrain.addTerrainNode(p6, NoisePunderationFunction::IDENTITY);
    Noise result6 = terrain.getTerrain(800, 800, 42);
    result6.toPGM("./PerlinTest/Result6.pgm");
    Terrain terrain6("test", 0);
    terrain6.addTerrainNode(p6, NoisePunderationFunction::IDENTITY);
    Noise res6 = terrain6.getTerrain(800, 800, 42);
    res6.toPGM("./PerlinTest/perlin6.pgm");
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
    Worley_noise w = Worley_noise(0, 255, 120);
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


void testStainPattern(int size) {
    std::cout << "Initialising Terrain..." << std::endl;
    Terrain terrain("Test Terrain 2", time(NULL));
    int width = size;
    int height = width;
    std::cout.precision(2);
    int scale = width;
    Perlin detailShape = Perlin(0, 255, scale/10);
    Perlin microShape = Perlin(0, 255, scale/34);
    Worley_noise w_a = Worley_noise(0, 256, size/1.9);
    Worley_noise w_b = Worley_noise(0, 256, size/1.5);
    auto secnPunderation = FilterPunderationFunction([](int value) { return value < 126; }, std::make_shared<ProductPunderationFunction<double>>(0.1));

    auto detailPunderation = ProductPunderationFunction<double>(0.3);
    auto id = IdentityPunderationFunction();

    terrain.addTerrainNode(w_a, id);
    terrain.addTerrainNode(detailShape, detailPunderation);
    terrain.addTerrainNode(microShape, secnPunderation);
    terrain.addTerrainNode(w_b, detailPunderation);

    std::cout << "Generating Terrain..." << std::endl;
    Noise result = terrain.getTerrain(width, height, size/0.9);
    std::cout << "Exporting..." << std::endl;
    result.toPGM("./stains.pgm", 255);
    //result.toPPM("./stains_heatmap.ppm", HEATMAP);
    result.toPPM("./stains.ppm", TERRAIN, 255);
    std::cout << "Done." << std::endl;
}



void testMinerals(int size) {
    std::cout << "Initialising Terrain..." << std::endl;
    Terrain terrain("Test Terrain 2", time(NULL));
    int width = size;
    int height = width;
    std::cout.precision(2);
    int scale = width;
    Perlin canyonShape = Perlin(0, 255, scale/2);
    Worley_noise w_a = Worley_noise(0, 256, size/1.9);
    Worley_noise w_b = Worley_noise(0, 256, size/9.5, true);
    Worley_noise w_c = Worley_noise(0, 700, size/16, true);
    Worley_noise w_d = Worley_noise(0, 256, size/30, true);
    auto canyonPunderation = FilterPunderationFunction([](int value) { return value > 0; }, std::make_shared<ProductPunderationFunction<double>>(0.7));

    auto microPunderation = ProductPunderationFunction<double>(0.05);
    auto globalFunction = InversePunderationFunction(255);
    auto id = IdentityPunderationFunction();

    terrain.addTerrainNode(w_a, id);
    terrain.addTerrainNode(canyonShape, canyonPunderation, [](int value) { return value > 0; });
    terrain.addTerrainNode(w_b, microPunderation);
    terrain.addTerrainNode(w_c, globalFunction);
    terrain.addTerrainNode(w_d, globalFunction);


    std::cout << "Generating Terrain..." << std::endl;
    Noise result = terrain.getTerrain(width, height, size/0.9);
    std::cout << "Exporting..." << std::endl;
    result.toPGM("./minerals.pgm", 255);
    // result.toPPM("./heatmap2.ppm", HEATMAP);
    result.toPPM("./minerals.ppm", TERRAIN, 255);
    std::cout << "Done." << std::endl;
}
void testSeaRiver(int size) {
    std::cout << "Initialising Terrain..." << std::endl;
    Terrain terrain("Test Terrain 2", time(NULL));
    int width = size;
    int height = width;
    std::cout.precision(2);
    int scale = width;
    Perlin canyonShape = Perlin(0, 256, scale/1.5);
    Perlin detailShape = Perlin(0, 255, scale/10);
    Perlin terrainShape = Perlin(0, 255, scale/6);
    Worley_noise w_a = Worley_noise(10, 24, size/26, true);
    Worley_noise w_d = Worley_noise(0, 50, size/30);

    auto detailPunderation = ProductPunderationFunction<double>(-0.05);
    auto productPunderation =  ProductPunderationFunction<double>(0.2);
    auto subPunderation =  SumPunderationFunction(-450);

    auto globalFunction = InversePunderationFunction(300);
    auto id = IdentityPunderationFunction();

    terrain.addTerrainNode(w_a, id);
    terrain.addTerrainNode(detailShape, detailPunderation);
    terrain.addTerrainNode(terrainShape, productPunderation);
    Noise result_inter1 = terrain.getTerrain(width, height, 666);
    result_inter1.toPGM("./NearSea_step1.pgm");

    terrain.addTerrainNode(canyonShape, globalFunction);
    Noise result_inter2 = terrain.getTerrain(width, height, 666);
    result_inter2.toPGM("./NearSea_step2.pgm");

    terrain.addTerrainNode(detailShape, subPunderation, [](int value) { return value > 200;} );
    Noise result_inter3 = terrain.getTerrain(width, height, 666);
    result_inter3.toPGM("./NearSea_step3.pgm");
    terrain.addTerrainNode(w_d, productPunderation);

    std::cout << "Generating Terrain..." << std::endl;
    Noise result = terrain.getTerrain(width, height, size/0.9);
    std::cout << "Exporting..." << std::endl;
    result.toPGM("./NearSea_step4.pgm", 255);
    // result.toPPM("./heatmap2.ppm", HEATMAP);
    result.toPPM("./NearSea_step4.ppm", TERRAIN, 255);
    std::cout << "Done." << std::endl;
}
int main(void) {
    // ---------------------- Test ---------------------------
    int size = 512;
    std::cout << "--- Test Perlin ---" << std::endl;
    testPerlin2();
    std::cout << "--- Terrain 1 ---" << std::endl;
    testTerrain1(size);
    std::cout << "--- Terrain 2 ---" << std::endl;
    testTerrain2(size);
    std::cout << "--- Archipellago ---" << std::endl;
    testArchipellago(size);

    std::cout << "--- Stain pattern ---" << std::endl;
    testStainPattern(size);
    std::cout << "--- Minerals ---" << std::endl;
    testMinerals(size);
    std::cout << "--- Sea River ---" << std::endl;
    testSeaRiver(size);
    return 0;
}


