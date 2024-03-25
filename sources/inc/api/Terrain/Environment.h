//
// Created by Antonin Jean on 23/03/2024
//

#pragma once
#include "../Terrain/Terrain.h"

class Environment {
private:
    Terrain heightTerrain;
    Terrain biomeTerrain;
    std::string name;
public:
    Environment(std::string name, Terrain heightTerrain, Terrain biomeTerrain): 
        name(name), 
        heightTerrain(heightTerrain), 
        biomeTerrain(biomeTerrain) {};

    Terrain getHeightTerrain() const {
        return heightTerrain;
    }

    Terrain getBiomeTerrain() const {
        return biomeTerrain;
    }

    std::string getName() const {
        return name;
    }

    static Environment newEnvironment(std::string name, Terrain heightTerrain) {
        return Environment(name, heightTerrain, Terrain(name + "_biome", heightTerrain.getSeed()));
    }
};