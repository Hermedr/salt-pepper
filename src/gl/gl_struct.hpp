#pragma once
#include "../misc/dependencies.hpp"

struct gl_struct{
    unsigned int VAO;
    unsigned int VBO;
    bool valid = false;
};

void create_gl_struct(gl_struct& g);
void delete_gl_struct(gl_struct& g);