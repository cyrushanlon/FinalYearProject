#ifndef L_WINDOW_H
#define L_WINDOW_H

#include <lua.hpp>
#include "Global.h"
#include <SFML/Graphics.hpp>

//functions required to use the class in lua

static int l_Window_GetSize(lua_State * l)
{
    //sf::RenderWindow* window = l_CheckWindow(1);

    sf::Vector2u pos = Window.getSize();
    //use the LuaState helper to push the vector onto the stack
    Lua.PushVector2u(pos);

    //we return a single variable to Lua
    return 1;
}

static int l_Window_Destructor(lua_State * l)
{
    return 0;
}

static void RegisterWindow()
{
    //defines the functions and their C counterparts
    luaL_Reg sDrawableRegs[] =
    {
        { "GetSize", l_Window_GetSize },
        { "__gc", l_Window_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_Window");

    //register the functions
    luaL_setfuncs(Lua.L(), sDrawableRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "Window");
}

#endif // L_WINDOW_H
