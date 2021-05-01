#include "cell.hpp"


cell read_buffer(cells& c, unsigned int x, unsigned int y){
    if(x < 0 || x > c.w || y < 0 || y > c.h){cell ce; ce.mat = AIR; ce.next_mat = AIR; return ce;}
    return c.buffer[(y * c.w) + x];
}

void init_cells(cells& c, unsigned int w, unsigned int h, gl_struct& g){
    if(w == 0 || h == 0){return;}
    c.w = w; c.h = h;

    if(g.valid){delete_gl_struct(g);}

    c.buffer = new cell [w * h];

    create_gl_struct(g);

    glBindVertexArray(g.VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, g.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * w * h, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    c.g = &g;

    for(int i = 0; i < c.w * c.h; i++){
        c.buffer[i].mat = AIR;
        c.buffer[i].next_mat = AIR;
    }

    base::use_shader("test_shader");
    base::set_shader_variable("test_shader", "sizex", s_float, 1.0f / float(w), 0, 0, 0);
    base::set_shader_variable("test_shader", "sizey", s_float, 1.0f / float(h), 0, 0, 0);
}

void update_cells(cells& c){
    for(int i = 0; i < c.w * c.h; i++){
        c.buffer[i].mat = c.buffer[i].next_mat;
    }
    
    for(int i = c.w; i < (c.w * (c.h - 1)); i++){
        if(c.buffer[i].mat == DIRT){
            bool down = false;

            for(int o = 0; o < (i / c.w); o++){
                if(c.buffer[i - (c.w * o)].mat == AIR){down = true;}
            }

            if(down){
                c.buffer[i].next_mat = AIR;
                c.buffer[i - c.w].next_mat = DIRT;
            }
        }
    }
}

void draw_cells(cells& c){
    std::vector<float> long_arr = {};

    for(int x = 0; x < c.w; x++){
        for(int y = 0; y < c.h; y++){
            float xp, yp;

            xp = -1 + (float(x) / float(c.w)) * 2;
            yp = -1 + (float(y) / float(c.h)) * 2;

            xp += (2.0f / float(c.w)) / 2.0f;
            yp += (2.0f / float(c.h)) / 2.0f;

            long_arr.push_back(xp);
            long_arr.push_back(yp);
            long_arr.push_back(c.buffer[(y * c.w) + x].mat);
        }
    }

    glBindVertexArray(c.g->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, c.g->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * c.w * c.h, long_arr.data());

    glDrawArrays(GL_POINTS, 0, c.w * c.h);
}



void calculate_boring_shit(cells& c){

}

unsigned int get_mouse_x_cells(cells& c){
    double mx = base::mouse_gl_x();
    if(mx < -1 || mx > 1){
        return 0;
    }
    return ((mx + 1) / 2) * c.w;
}

unsigned int get_mouse_y_cells(cells& c){
    double my = base::mouse_gl_y();
    if(my < -1 || my > 1){
        return 0;
    }
    return ((my + 1) / 2) * c.h;
}

