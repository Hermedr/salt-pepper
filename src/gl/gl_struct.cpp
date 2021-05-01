#include "gl_struct.hpp"

void create_gl_struct(gl_struct& g){
    glGenVertexArrays(1, &g.VAO);
    glGenBuffers(1, &g.VBO);
    g.valid = true;
}

void delete_gl_struct(gl_struct& g){
    glDeleteBuffers(1, &g.VAO);
    glDeleteBuffers(1, &g.VBO);
    g.valid = false;
}