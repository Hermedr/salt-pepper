#include "cell.hpp"

bool is_material_rigid(material m){
    switch (m)
    {
    case AIR:
        return false;
        break;
    case DIRT:
        return false;
        break;
    case ROCK:
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool is_material_solid(material m){
    switch (m)
    {
    case AIR:
        return false;
        break;
    case DIRT:
        return true;
        break;
    case ROCK:
        return true;
        break;
    default:
        return true;
        break;
    }
}