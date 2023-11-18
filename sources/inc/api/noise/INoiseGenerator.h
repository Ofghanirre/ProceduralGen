//
// Created by Antonin Jean on 18/11/2023.
//

#pragma once

#include <iostream>


template<typename T>
class INoiseGenerator{
public:
    /**
     * @brief Generator for a Noise, those can be statically loaded for usage and contains the all-usable parameters
     * known for generating a noise.
     *
     * This factory shall be implemented by each and every noise there is, but the required common parameters are stored
     * here
     *
     * @param seed the seed used to generate the noise
     * @param width the width of the windowed bitmap created
     * @param height the height of the windowed bitmap created
     * @param frequency the frequency used to create the noise
     * @return
     */
    virtual T genNoise(uint seed, uint width, uint height, uint frequency) = 0;
};
