//
// Created by Nader Khedr on 28/01/2024.
//

#ifndef VALUENOISE_H
#define VALUENOISE_H
#include "INoiseGenerator.h"
#include "Noise.h"


class ValueNoiseGenerator : INoiseGenerator{
public:
    Noise genNoise(uint seed, uint width, uint height, uint frequency) override;
};



#endif //VALUENOISE_H
