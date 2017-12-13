#include <iostream>

#include "LuaState.h"

#include "Lua/L_Window.h"
#include "Lua/L_Drawable.h"
#include "Lua/L_Input.h"
#include "Lua/L_Sound.h"


LuaState::LuaState()
{
    this->state = luaL_newstate();
    luaL_openlibs(this->state);

    //register everything from C++ into lua
    RegisterWindow();
    RegisterDrawable();
    RegisterInput();
    RegisterSound();

    //run any engine related files
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

void LuaState::PushVector2i(sf::Vector2i vec)
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

void LuaState::PushVector2u(sf::Vector2u vec)
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

void LuaState::Think(sf::Time dt)
{
    //load the function from global
    lua_getglobal(this->L(),"Think");
    if(lua_isfunction(this->L(), -1) )
    {
        //push function argument onto stack
        lua_pushnumber(this->L(), dt.asSeconds());
        int err = lua_pcall(this->L(),1,0,0); // 1 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::Initialise(const char* initPath)
{
    //run the init script
    int err = luaL_dofile(this->state, initPath);
    if(err)
    {
        std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
    }

    //load the function from global
    lua_getglobal(this->L(),"Init");
    if(lua_isfunction(this->L(), -1) )
    {
        int err = lua_pcall(this->L(),0,0,0); // 0 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookGainedFocus()
{
    //load the function from global
    lua_getglobal(this->L(),"HookGainedFocus");
    if(lua_isfunction(this->L(), -1) )
    {
        int err = lua_pcall(this->L(),0,0,0); // 0 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookLostFocus()
{
    //load the function from global
    lua_getglobal(this->L(),"HookLostFocus");
    if(lua_isfunction(this->L(), -1) )
    {
        int err = lua_pcall(this->L(),0,0,0); // 0 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}
