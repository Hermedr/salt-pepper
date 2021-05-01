cmake_minimum_required(VERSION 3.2.0)

project(out VERSION 1.2.3)

file(GLOB SOURCE
    src/*.cpp
    src/*.hpp

    src/**/*.cpp 
    src/**/*.hpp

    external/glad/include/glad/glad.h
    external/glad/include/KHR/khrplatform.h
    external/glad/src/glad.c
    
    external/lua/include/lua.h
    external/lua/include/lualib.h
    external/lua/include/lauxlib.h
)

set(CMAKE_CXX_FLAGS "-std=c++17 -static-libgcc -static-libstdc++")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
set(DCMAKE_GENERATOR_PLATFORM x64)

#windows
add_executable(out ${HEADERS} ${SOURCE})

target_link_libraries(out ${CMAKE_DL_LIBS})
target_link_libraries(out glfw)
target_link_libraries(out ${CMAKE_SOURCE_DIR}/external/lua/liblua54.a)