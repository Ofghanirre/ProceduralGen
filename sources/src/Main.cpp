//
// Created by Antonin Jean on 25/01/2024.
//

#include "inc/api/noise/BitMap.h"
#include <iostream>

int main(void) {
    BitMap<int> bitmap(16,16, 0);
    bitmap[0] = 1;

    std::cout << bitmap[0] << std::endl;
    return 0;
}
