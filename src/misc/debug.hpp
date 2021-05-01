#pragma once
#include "dependencies.hpp"

class debug_timer{
public:
    debug_timer(){
        start_timepoint = std::chrono::high_resolution_clock::now();
    }

    ~debug_timer(){

    }
    
    void stop(std::string function_name){
        auto end_timepoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

        auto duration = end - start;
        double ms = duration * 0.0001;

        std::cout << "\n'" << function_name << "':    ";
        std::cout << ms << "ms";
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint;
};
