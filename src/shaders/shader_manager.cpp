#include "shader_manager.hpp"

std::string current_vert = "", current_frag = "", current_geom = "";

int lua_vert(lua_State* L){
    if(current_vert != ""){base::warning("redifining vertex path");}
    if(lua_isstring(L, 1)){current_vert = lua_tostring(L, 1);}
    return 0;
}

int lua_frag(lua_State* L){
    if(current_frag != ""){base::warning("redifining fragment path");}
    if(lua_isstring(L, 1)){current_frag = lua_tostring(L, 1);}
    return 0;
}

int lua_geom(lua_State* L){
    if(current_geom != ""){base::warning("redifining geometry path");}
    if(lua_isstring(L, 1)){current_geom = lua_tostring(L, 1);}
    return 0;
}

int lua_push(lua_State* L){
    if(lua_isstring(L, 1)){if(lua_tostring(L, 1) == ""){base::error("no name defined for shader"); return 0;}}

    if(base::is_shader_defined(lua_tostring(L, 1))){base::error("shader already defined");}

    shader_compile_config c;
    
    c.vert = current_vert;
    c.frag = current_frag;
    c.geom = current_geom;

    shader s;
    if(compile_shader(s, c)){
        base::loaded_shaders.insert(std::make_pair(lua_tostring(L, 1), s));
    }else{
        base::error("unable to compile shader");
    }

    current_vert = current_frag = current_geom = "";
    return 0;
}

namespace base{

bool init_shaders(){
    debug_timer d;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "vertex", lua_vert);
    lua_register(L, "fragment", lua_frag);
    lua_register(L, "geometry", lua_geom);
    lua_register(L, "push", lua_push);

    if(!check_lua(L, luaL_dofile(L, "res/shader_init.lua"))){
        base::error("cant init luaL_dofile");
        return false;
    }

    printf("\nshader count: %i", loaded_shaders.size());

    d.stop("shader initialization");

    return true;
}

bool is_shader_defined(std::string shader){
    return (loaded_shaders.find(shader) != loaded_shaders.end());
}

void use_shader(std::string shader){
    if(!is_shader_defined(shader)){
        std::string err = "cant use shader " + shader + " because it is not defined";
        base::warning(err); return;
    }
    glUseProgram(loaded_shaders[shader].id);
}

void set_shader_variable(std::string shader, std::string var, shader_variable_type type, double a, double b, double c, double d){
    if(!is_shader_defined(shader)){base::warning("cant set shader variable, shader is not defined"); return;}
    
    switch(type){
        case s_float:
            s_set_float(loaded_shaders[shader], var, a);
            break;
        case s_int:
            s_set_int(loaded_shaders[shader], var, a);
            break;
        case s_vec2:
            s_set_vec2(loaded_shaders[shader], var, a, b);
            break;
        case s_vec3:
            s_set_vec3(loaded_shaders[shader], var, a, b, c);
            break;
    }
}

};