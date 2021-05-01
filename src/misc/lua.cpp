#include "lua.hpp"

bool check_lua(lua_State* L, int r){
    lua_State* eL = luaL_newstate();

    if(r != LUA_OK){
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}