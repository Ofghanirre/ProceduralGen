//
// Created by Antonin Jean on 23/03/2024
//

#pragma once

class IBiomeGenerator {
public:
    virtual ~IBiomeGenerator() = default;

    virtual void generateBiome() = 0;
};