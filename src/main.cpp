#include "misc/dependencies.hpp"
#include "misc/debug.hpp"

#include "base/base.hpp"
#include "shaders/shader.hpp"

#include "shaders/shader_manager.hpp"
#include "gl/gl_struct.hpp"

#include "map/map.hpp"
#include "math/vec2.hpp"

#include "cell/cell.hpp"

const double TICK_RATE = 0.1;

int main(){
    debug_timer d;

    base_init_config i;
    i.width = 640;
    i.height = 480;
    i.title = "salt & pepper";
    i.vsync = false;

    if(!base::init(i)){
        return 1;
    }

    d.stop("base initialization");

    gl_struct g;

    cells c;
    init_cells(c, 100, 100, g);
   
    double last, dt;

    double last_tick = 0;

    while(base::should_run()){
        last = glfwGetTime();

        base::tick();

        //main loop

        glfwPollEvents();

        if(glfwGetKey(base::window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            base::exit();
        }

        glClearColor(0.6, 0.6, 0.6, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        base::use_shader("test_shader");

        if(glfwGetMouseButton(base::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
            unsigned int x, y;
            x = get_mouse_x_cells(c);
            y = get_mouse_y_cells(c);
            c.buffer[(y * c.w) + x].mat = DIRT; //REMEMBER TO SET BOTH BUFFERS RETARD
            c.buffer[(y * c.w) + x].next_mat = DIRT; //REMEMBER TO SET BOTH BUFFERS RETARD
        }

        if(glfwGetTime() - last_tick > TICK_RATE){
            last_tick = glfwGetTime();
            update_cells(c);
        }
        draw_cells(c);

        glfwSwapBuffers(base::window);

        dt = glfwGetTime() - last;
    }

    delete_gl_struct(g);

    base::cleanup();

    while(base::thrown_error()){}
    
    return 0;
}