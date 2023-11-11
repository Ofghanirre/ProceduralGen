//
// Created by Antonin Jean on 11/11/2023.
//

#include "../inc/Test.h"
#include <iostream>

int Test::getX() const {
    return x;
}

void Test::setX(int x) {
    Test::x = x;
}

int Test::getY() const {
    return y;
}

void Test::setY(int y) {
    Test::y = y;
}

Test::Test(int x, int y) : x(x), y(y) {}

Test::~Test() {
    std::cout << "Test Destroyed" << std::endl;
}
