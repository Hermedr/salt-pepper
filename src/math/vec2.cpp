#include "vec2.hpp"

dvec2 vec2(double x, double y){
    dvec2 v;
    v.x = x;
    v.y = y;
    return v;
}

ivec2 vec2(int x, int y){
    ivec2 v;
    v.x = x;
    v.y = y;
    return v;
}

uivec2 vec2(unsigned int x, unsigned int y){
    uivec2 v;
    v.x = x;
    v.y = y;
    return v;
}

double length(dvec2 v){
    return sqrt(v.x * v.x + v.y * v.y);
}

double length(ivec2 v){
    return sqrt(v.x * v.x + v.y * v.y);
}

double length(uivec2 v){
    return sqrt(v.x * v.x + v.y * v.y);
}