//
// Created by Antonin Jean on 23/03/2024
//

#pragma once
#include "../Terrain/Terrain.h"

class Environment {
private:
    Terrain m_heightTerrain;
    Terrain m_biomeTerrain;
    std::string name;
public:
    Environment(std::string name, Terrain heightTerrain, Terrain biomeTerrain): 
        name(name), 
        m_heightTerrain(heightTerrain), 
        m_biomeTerrain(biomeTerrain) {};

    Terrain getHeightTerrain() const {
        return m_heightTerrain;
    }

    Terrain getBiomeTerrain() const {
        return m_biomeTerrain;
    }

    std::string getName() const {
        return name;
    }

    static Environment newEnvironment(std::string name, Terrain heightTerrain) {
        return Environment(name, heightTerrain, Terrain(name + "_biome", heightTerrain.getSeed()));
    }

    void toPEM(const char* filename, int maxHeight = 0) const;
};