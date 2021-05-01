#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <string>
#include <map>
#include <vector>
#include <fstream>

#include <math.h>
#include <sys/stat.h>
#include <unistd.h>

//GLFW AND OPENGl
#include "../../external/glad/include/glad/glad.h"
#include "../../external/glfw/include/GLFW/glfw3.h"

//LUA
extern "C"{
    #include "../../external/lua/include/lua.h"
    #include "../../external/lua/include/lualib.h"
    #include "../../external/lua/include/lauxlib.h"
}

#pragma comment(lib, "external/lua/liblua54.a")