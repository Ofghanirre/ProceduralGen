//
// Created by Antonin Jean on 23/03/2024
//

#include <api/Terrain/Environment.hpp>

class DefaultGenerator : public ITerrainGenerator {
private:
    const Terrain m_heightTerrain;
public:
    DefaultGenerator(const Terrain heightTerrain) : m_heightTerrain{heightTerrain}: = default;

    void generateBiome() override {
        // Generate the height map
        m_heightGenerator.generate();
        // Generate the biome map
        m_biomeGenerator.generate();
    }

    Environment getEnvironment() const {
        return Environment::newEnvironment("default", m_heightGenerator.getTerrain());
    }

    void setHeightGenerator(ITerrainGenerator& heightGenerator) {
        m_heightGenerator = heightGenerator;
    }

    void setBiomeGenerator(IBiomeGenerator& biomeGenerator) {
        m_biomeGenerator = biomeGenerator;
    }    
}
