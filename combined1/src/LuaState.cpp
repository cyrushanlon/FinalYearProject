#include "LuaState.h"

LuaState::LuaState()
{
    this->L = luaL_newstate();
    luaL_openlibs(this->L);

    /*
    //run the script
    int err = luaL_dofile(L,"init.lua");
    if(err)
    {
        std::cout << "lua error: " << luaL_checkstring(L, -1) << std::endl;
    }
    */
}

LuaState::~LuaState()
{
    //dtor
}
