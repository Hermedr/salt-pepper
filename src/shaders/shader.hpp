#pragma once
#include "../misc/dependencies.hpp"
#include "../misc/files.hpp"
#include "../base/base.hpp"

struct shader{
    unsigned int id = -1;
};

struct shader_compile_config{
    std::string vert = "", geom = "", frag = "";
};

bool is_shader_compile_config_valid(shader_compile_config& c);
bool compile_shader(shader& s, shader_compile_config& c);
bool is_shader_created(shader& s);

void s_set_float(shader& s, std::string var, double d);
void s_set_int(shader& s, std::string var, int i);
void s_set_vec2(shader& s, std::string var, double x, double y);
void s_set_vec3(shader& s, std::string var, double x, double y, double z);
