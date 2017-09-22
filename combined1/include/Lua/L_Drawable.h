#ifndef L_DRAWABLE_H
#define L_DRAWABLE_H

#include <lua.hpp>
#include "Drawable.h"
#include "Global.h"
#include <iostream>

//functions required to use the class in lua
//initial example found here: https://gist.github.com/kizzx2/1594905

//we should pass the lua state in here but instead we will use the global object instead
static int l_Drawable_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be either 1 or 2 arguments
    if (argc != 1 && argc != 2)
    {
        return luaL_error(L, "incorrect argument count");
    }

    //gets the first argument of the constructor
    const char * newID = luaL_checkstring(L, 1);

    //create userdata
    Drawable ** udata = (Drawable **)lua_newuserdata(L, sizeof(Drawable *));

    //create an instance using the correct number of arguments as required
    if(argc == 2)
    {
        const char * texturePath = luaL_checkstring(L, 2);
        *udata = new Drawable(newID, texturePath);
    }
    else
    {
        *udata = new Drawable(newID);
    }

    //
    luaL_getmetatable(L, "luaL_Drawable");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

Drawable* l_CheckDrawable(int i)
{
    // This checks that the argument is a userdata with the metatable "luaL_Drawable"
    return *(Drawable **)luaL_checkudata(Lua.L(), i, "luaL_Drawable");
}

int l_Drawable_GetPos(lua_State * l)
{
    Drawable* drawable = l_CheckDrawable(1);

    sf::Vector2f pos = drawable->GetPos();
    //use the LuaState helper to push the vector onto the stack
    Lua.PushVector2f(pos);

    //we return a single variable to Lua
    return 1;
}

int l_Drawable_SetPos(lua_State * l)
{
    Drawable* drawable = l_CheckDrawable(1);
    double x = luaL_checknumber(Lua.L(), 2);
    double y = luaL_checknumber(Lua.L(), 3);

    drawable->SetPos(sf::Vector2f(x, y));

    return 0;
}

int l_Drawable_Destructor(lua_State * l)
{
    Drawable * drawable = l_CheckDrawable(1);
    delete drawable;

    return 0;
}

void RegisterDrawable()
{
    //defines the functions and their C counterparts
    luaL_Reg sDrawableRegs[] =
    {
        { "New", l_Drawable_Constructor },
        { "GetPos", l_Drawable_GetPos },
        { "SetPos", l_Drawable_SetPos },
        { "__gc", l_Drawable_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_Drawable");

    //register the functions
    luaL_setfuncs(Lua.L(), sDrawableRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "Drawable");
}

#endif // L_DRAWABLE_H
