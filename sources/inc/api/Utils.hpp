//
// Created by VONG Jérémy on 27/01/24.
//

#ifndef PROCEDURALGEN_UTILS_HPP
#define PROCEDURALGEN_UTILS_HPP

#include <math.h>
template<typename T>
struct vec2 {
public :
    T x;
    T y;

    // Constructor
    vec2(T x_val, T y_val) : x(x_val), y(y_val) {}
} ;

template<typename T>
static float distance(vec2<T> v1, vec2<T> v2){
    return sqrt( pow(v2.x-v1.x,2) + pow(v2.y-v1.y,2));
}

#endif //PROCEDURALGEN_UTILS_HPP
