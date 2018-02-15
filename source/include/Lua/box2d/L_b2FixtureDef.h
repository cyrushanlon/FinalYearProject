#ifndef L_B2FIXTUREDEF
#define L_B2FIXTUREDEF

#include <lua.hpp>

#include "Global.h"
#include "Box2D/Box2D.h"

#include <iostream>

static b2FixtureDef* l_Checkb2FixtureDef(int i)
{
    return *(b2FixtureDef **)luaL_checkudata(Lua.L(), i, "luaL_b2FixtureDef");
}

static int l_b2FixtureDef_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 1 argument
    if (argc != 1)
    {
        return luaL_error(L, "incorrect argument count");
    }

    //create userdata
    b2FixtureDef ** udata = (b2FixtureDef **)lua_newuserdata(L, sizeof(b2FixtureDef *));
    *udata = new b2FixtureDef();

    lua_pushvalue(L, 1);
    lua_pushnil(L);  /* first key */
    while (lua_next(L, -2))
    {
        lua_pushvalue(L, -2);
        std::string key = luaL_checkstring(L, -1);

        std::cout << key;
        if (key == "density")
            (*udata)->density = lua_tonumber(L, -2);
        //else if (key == "filter")
        //    (*udata)->filter = lua_toboolean(L, -2);
        else if (key == "friction")
            (*udata)->friction = lua_tonumber(L, -2);
        else if (key == "isSensor")
            (*udata)->isSensor = lua_toboolean(L, -2);
        else if (key == "restitution")
            (*udata)->restitution = lua_tonumber(L, -2);
        else
            //not sure what to do in the else case
            luaL_checkstring(L, -2);

        // removes 'value'; keeps 'key' for next iteration
        lua_pop(L, 2);
    }
    lua_pop(L, 1);

    //
    luaL_getmetatable(L, "luaL_b2FixtureDef");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_b2FixtureDef_Destructor(lua_State * l)
{
    b2FixtureDef * def = l_Checkb2FixtureDef(1);
    delete def;

    return 0;
}

static void Registerb2FixtureDef()
{
    //defines the functions and their C counterparts
    luaL_Reg sb2FixtureDefRegs[] =
    {
        { "New", l_b2FixtureDef_Constructor },
        { "__gc", l_b2FixtureDef_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_b2FixtureDef");

    //register the functions
    luaL_setfuncs(Lua.L(), sb2BodyDefRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "b2FixtureDef");
}

#endif // L_B2FIXTUREDEF
