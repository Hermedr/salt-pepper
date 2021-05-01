#include "base.hpp"

bool run = true;

//vars
namespace base{

GLFWwindow* window = NULL;

};

//funcs - hardcoded ew
namespace base{

bool should_run(){return run;}
void exit(){run = false; glfwSetWindowShouldClose(window, true);}

void tick(){
    tick_window();

    if(glfwWindowShouldClose(window)){
        run = false;
    }
}

};