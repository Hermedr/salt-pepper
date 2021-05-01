#include "base.hpp"

double mx, my;

namespace base{

double mouse_gl_x(){return mx;}
double mouse_gl_y(){return my;}

void tick_window(){
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    int w, h;
    glfwGetWindowSize(window, &w, &h);

    double endx, endy;

    endx = x / w;
    endy = y / h;

    endx = (endx - 0.5) * 2;
    endy = -(endy - 0.5) * 2;

    mx = endx;
    my = endy;
}

};