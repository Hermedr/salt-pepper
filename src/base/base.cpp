#include "base.hpp"
#include "../shaders/shader_manager.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

namespace base{

bool init(base_init_config& config){
    if (!glfwInit()){return false;}

    window = glfwCreateWindow(config.width, config.height, config.title.c_str(), NULL, NULL);
    if(window == NULL){base::error("unable to create glfw window"); return false;}

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //glfwWindowHint(GLFW_SAMPLES, 4);

    glfwMakeContextCurrent(window);

    //glEnable(GL_MULTISAMPLE);  
    //glEnable(GL_DEPTH_TEST);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {base::error("unable to init glad"); return false;}

    if(!init_shaders()){base::error("unable to init shaders"); return false;}

    return true;
}

void cleanup(){
    if(window){
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

};