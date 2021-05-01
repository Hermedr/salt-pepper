#include "shader.hpp"



void s_set_float(shader& s, std::string var, double d){
    //if(!is_shader_created(s)){return;}
    unsigned int mem_id = glGetUniformLocation(s.id, var.c_str());
    glUniform1f(mem_id, d);
}

void s_set_int(shader& s, std::string var, int i){
    //if(!is_shader_created(s)){return;}
    unsigned int mem_id = glGetUniformLocation(s.id, var.c_str());
    glUniform1i(mem_id, i);
}

void s_set_vec2(shader& s, std::string var, double x, double y){
    //if(!is_shader_created(s)){return;} //ERROR ?? 
    unsigned int mem_id = glGetUniformLocation(s.id, var.c_str());
    glUniform2f(mem_id, x, y);
}

void s_set_vec3(shader& s, std::string var, double x, double y, double z){
    //if(!is_shader_created(s)){return;}
    unsigned int mem_id = glGetUniformLocation(s.id, var.c_str());
    glUniform3f(mem_id, x, y, z);
}



/////////////
//COMPILING//
/////////////

bool checkCompileErrors(unsigned int shader, const char* type);

struct StringHelper {
	const char* p;
	StringHelper(const std::string& s) : p(s.c_str()) {}
	operator const char** () { return &p; }
};

bool is_shader_compile_config_valid(shader_compile_config& c){
    if(c.vert == ""){base::warning("vertex is not defined"); return false;}
    if(c.frag == ""){base::warning("fragment is not defined"); return false;}

    if(!file_exists(c.vert)){base::warning("vertex file does not exist"); return false;}
    if(!file_exists(c.frag)){base::warning("fragment file does not exist"); return false;}

    if(c.geom != "" && !file_exists(c.geom)){base::warning("geometry file does not exist"); return false;}

    return true;
}

bool compile_shader(shader& s, shader_compile_config& c){
    if(is_shader_created(s)){base::warning("shader id is already used"); return false;}
    s.id = glCreateProgram();

    if(!is_shader_compile_config_valid(c)){return false;}

    unsigned int vert_id, frag_id, geom_id;

    //VERTEX
    vert_id = glCreateShader(GL_VERTEX_SHADER);
    std::fstream f(c.vert);
    
    std::string str((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());

    glShaderSource(vert_id, 1, StringHelper(str), NULL);
    glCompileShader(vert_id);

    if(!checkCompileErrors(vert_id, "VERTEX")){return false;}

    f.close();

    //FRAGMENT
    frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    f.open(c.frag);
    
    str = std::string((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());

    glShaderSource(frag_id, 1, StringHelper(str), NULL);
    glCompileShader(frag_id);

    if(!checkCompileErrors(frag_id, "FRAGMENT")){return false;}

    f.close();

    //GEOMETRY
    if(c.geom != ""){
        geom_id = glCreateShader(GL_GEOMETRY_SHADER);
        f.open(c.geom);
        
        str = std::string((std::istreambuf_iterator<char>(f)),
                        std::istreambuf_iterator<char>());

        glShaderSource(geom_id, 1, StringHelper(str), NULL);
        glCompileShader(geom_id);

        if(!checkCompileErrors(geom_id, "GEOMETRY")){return false;}

        glAttachShader(s.id, geom_id);
    }

    glAttachShader(s.id, vert_id);
    glAttachShader(s.id, frag_id);
    
    glLinkProgram(s.id);
    if(!checkCompileErrors(s.id, "PROGRAM")){return false;}

    glDeleteShader(vert_id);
    glDeleteShader(frag_id);

    if(c.geom != ""){glDeleteShader(geom_id);}

    return true;
}

bool is_shader_created(shader& s){
    return (s.id > -1);
}

bool checkCompileErrors(unsigned int shader, const char* type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			printf("ERROR::SHADER_COMPILATION_ERROR of type: ");
			printf(type);
			printf("\n");
			printf(infoLog);
            return false;
		}
	} else{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			printf("ERROR::PROGRAM_LINKING_ERROR of type: ");
			printf(type);
			printf("\n");
			printf(infoLog);
            return false;
		}
	}

    return true;
}
