#pragma once
#include "../misc/dependencies.hpp"

struct base_init_config{
    bool vsync;
    int width, height;
    std::string title;
};

//vars
namespace base{

extern GLFWwindow* window;

};

//funcs
namespace base{

bool init(base_init_config& config);
void cleanup();

bool should_run();
void exit();

void warning(std::string warning);
void error(std::string error);

bool thrown_error();

double mouse_gl_x();
double mouse_gl_y();

////////
//TICK//
////////

void tick();
void tick_window();

};
