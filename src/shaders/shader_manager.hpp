#pragma once
#include "../misc/dependencies.hpp"
#include "../misc/files.hpp"
#include "../misc/debug.hpp"
#include "../misc/lua.hpp"
#include "shader.hpp"

//vars
namespace base{

extern std::map<std::string, shader> loaded_shaders;

};

enum class shader_variable_type{
    shader_variable_float,
    shader_variable_int,
    shader_variable_vec2,
    shader_variable_vec3,
};

#define s_float shader_variable_type::shader_variable_float
#define s_int shader_variable_type::shader_variable_int
#define s_vec2 shader_variable_type::shader_variable_vec2
#define s_vec3 shader_variable_type::shader_variable_vec3

//funcs
namespace base{

bool init_shaders();
bool is_shader_defined(std::string shader);

void use_shader(std::string shader);
void set_shader_variable(std::string shader, std::string var, shader_variable_type type, double a, double b, double c, double d);

};