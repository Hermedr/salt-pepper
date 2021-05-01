#pragma once
#include "../misc/dependencies.hpp"

struct map{
    unsigned int* world = NULL;
    unsigned int w, h;

    unsigned int id(unsigned int x, unsigned int y){return ((y * w) + x);}

    map(unsigned int nw, unsigned int nh){
        w = nw; h = nh;

        world = new unsigned int [w * h];

        for(int i = 0; i < (w * h); i++){
            world[i] = i / 10;
        }
    }

    unsigned int get(unsigned int x, unsigned int y){
        return world[id(x, y)];
    }

    void set(unsigned int x, unsigned int y, unsigned int v){
        world[id(x, y)] = v;
    }
};

void print_map(map& m){
    printf("\n");
    printf("\n");

    for(int y = 0; y < m.h; y++){
        for(int x = 0; x < m.w; x++){
            printf("%i ", m.get(x, y));
        }
        printf("\n");
    }
}