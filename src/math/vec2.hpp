#pragma once
#include "../misc/dependencies.hpp"

struct dvec2{
    double x, y;
};

struct ivec2{
    int x, y;
};

struct uivec2{
    unsigned int x, y;
};

dvec2 vec2(double x, double y);
ivec2 vec2(int x, int y);
uivec2 vec2(unsigned int x, unsigned int y);

double length(dvec2 v);
double length(ivec2 v);
double length(uivec2 v);