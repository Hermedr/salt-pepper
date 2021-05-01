#include "base.hpp"

bool hit_err = false;

namespace base{

void warning(std::string warning){
    printf("\nWARNING: ");
    printf(warning.c_str());
}

void error(std::string error){
    printf("\nERROR: ");
    printf(error.c_str());
    printf(", aborting");
    hit_err = true;
    exit();
}

bool thrown_error(){return hit_err;}

};