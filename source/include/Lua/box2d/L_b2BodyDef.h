#ifndef L_B2BODYDEF
#define L_B2BODYDEF

#include <lua.hpp>

#include "Global.h"
#include "Box2D/Box2D.h"

#include <iostream>

static b2BodyDef* l_Checkb2BodyDef(int i)
{
    return *(b2BodyDef **)luaL_checkudata(Lua.L(), i, "luaL_b2BodyDef");
}

static int l_b2BodyDef_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 1 argument
    if (argc != 1)
    {
        return luaL_error(L, "incorrect argument count");
    }

    //create userdata
    b2BodyDef ** udata = (b2BodyDef **)lua_newuserdata(L, sizeof(b2BodyDef *));
    *udata = new b2BodyDef();

    lua_pushvalue(L, 1);
    lua_pushnil(L);  /* first key */
    while (lua_next(L, -2))
    {
        lua_pushvalue(L, -2);
        std::string key = luaL_checkstring(L, -1);

        //std::cout << key;
        if (key == "active")
            (*udata)->active = lua_toboolean(L, -2);
        else if (key == "allowSleep")
            (*udata)->allowSleep = lua_toboolean(L, -2);
        else if (key == "angle")
            (*udata)->angle = lua_tonumber(L, -2);
        else if (key == "angularDamping")
            (*udata)->angularDamping = lua_tonumber(L, -2);
        else if (key == "angularVelocity")
            (*udata)->angularVelocity = lua_tonumber(L, -2);
        else if (key == "awake")
            (*udata)->awake = lua_toboolean(L, -2);
        else if (key == "bullet")
            (*udata)->bullet = lua_toboolean(L, -2);
        else if (key == "fixedRotation")
            (*udata)->fixedRotation = lua_toboolean(L, -2);
        else if (key == "gravityScale")
            (*udata)->gravityScale = lua_tonumber(L, -2);
        else if (key == "linearDamping")
            (*udata)->linearDamping = lua_tonumber(L, -2);
        //else if (key == "linearVelocity")
            //(*udata)->linearVelocity = lua_toboolean(L, -2);
        else if (key == "type")
        {
            std::string type = luaL_checkstring(L, -2);
            if (type == "static")
                (*udata)->type = b2_staticBody;
            else if (type == "dynamic")
                (*udata)->type = b2_dynamicBody;
            else if (type == "kinematic")
                (*udata)->type = b2_kinematicBody;
        }
        else
            //not sure what to do in the else case
            luaL_checkstring(L, -2);

        // removes 'value'; keeps 'key' for next iteration
        lua_pop(L, 2);
    }
    lua_pop(L, 1);

    //
    luaL_getmetatable(L, "luaL_b2BodyDef");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_b2BodyDef_Destructor(lua_State * l)
{
    b2BodyDef * def = l_Checkb2BodyDef(1);
    delete def;

    return 0;
}

static void Registerb2BodyDef()
{
    //defines the functions and their C counterparts
    luaL_Reg sb2BodyDefRegs[] =
    {
        { "New", l_b2BodyDef_Constructor },
        { "__gc", l_b2BodyDef_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_b2BodyDef");

    //register the functions
    luaL_setfuncs(Lua.L(), sb2BodyDefRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "b2BodyDef");
}

#endif // L_B2BODYDEF
