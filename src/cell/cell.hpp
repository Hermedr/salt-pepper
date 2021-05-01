#pragma once
#include "../misc/dependencies.hpp"
#include "../gl/gl_struct.hpp"
#include "../base/base.hpp"
#include "../shaders/shader_manager.hpp"

enum material{
    AIR = 0,
    DIRT = 1,
    ROCK = 2
};

bool is_material_rigid(material m);
bool is_material_solid(material m);

struct cell{
    material mat, next_mat;
};

struct cells{
    cell* buffer;
    unsigned int w, h;

    gl_struct* g;
};

void init_cells(cells& c, unsigned int w, unsigned int h, gl_struct& g);
void calculate_boring_shit(cells& c);
void update_cells(cells& c);
void draw_cells(cells& c);

cell read_buffer(cells& c, unsigned int x, unsigned int y);

unsigned int get_mouse_x_cells(cells& c);
unsigned int get_mouse_y_cells(cells& c);