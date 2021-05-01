#include "files.hpp"

bool file_exists(std::string file_path){ //idfk this is the only one that works
    struct stat buffer;   
    return (stat (file_path.c_str(), &buffer) == 0); 
}