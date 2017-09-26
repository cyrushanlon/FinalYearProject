#include "LuaState.h"

#include "Lua/L_Drawable.h"
#include <iostream>

LuaState::LuaState()
{
    this->state = luaL_newstate();
    luaL_openlibs(this->state);

    //register the drawable C++ class for use in Lua
    RegisterDrawable();

    //run the init script
    int err = luaL_dofile(this->state,"init.lua");
    if(err)
    {
        std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
    }
}

LuaState::~LuaState()
{
    //dtor
    lua_close(this->state);
}

lua_State* LuaState::L()
{
    return this->state;
}


void LuaState::PushVector2f(sf::Vector2f vec)
{
    //create a new table at the top of the stack
    lua_newtable(this->state);

    //push key
    lua_pushstring(this->state, "x");
    //push value
    lua_pushnumber(this->state, vec.x);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);

    //push key
    lua_pushstring(this->state, "y");
    //push value
    lua_pushnumber(this->state, vec.y);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);
}

void LuaState::CallLuaThink(sf::Time dt)
{
    //load the function from global
    lua_getglobal(this->L(),"Think");
    if(lua_isfunction(this->L(), -1) )
    {
        //push function argument onto stack
        lua_pushnumber(this->L(), dt.asSeconds());
        lua_pcall(this->L(),1,0,0);
    }
}
