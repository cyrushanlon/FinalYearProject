#ifndef L_GAMESTATE
#define L_GAMESTATE

#include "Global.h"

#include <iostream>

//functions required for Lua to create and set gamestates

static int l_State_Create(lua_State *L)
{
    //if there is 1 argument
    if (lua_gettop(L) == 1)
    {
        //get the string passed in from the top of the stack
        std::string id = luaL_checkstring(L, 1);

        //create new gamestate
        gsManager.CreateState(id);
    }

    return 0;
}

static int l_State_Set(lua_State *L)
{
    //if there is 1 argument
    if (lua_gettop(L) == 1)
    {
        //get the string passed in from the top of the stack
        std::string id = luaL_checkstring(L, 1);

        //set gamestate
        gsManager.SetState(id);
    }

    return 0;
}

static int l_State_Remove(lua_State *L)
{
    //if there is 1 argument
    if (lua_gettop(L) == 1)
    {
        //get the string passed in from the top of the stack
        std::string id = luaL_checkstring(L, 1);

        //set gamestate
        gsManager.RemoveState(id);
    }

    return 0;
}

static void RegisterGamestate()
{
    lua_register(Lua.L(), "CreateState", l_State_Create);
    lua_register(Lua.L(), "SetState", l_State_Set);
    lua_register(Lua.L(), "RemoveState", l_State_Remove);
}

#endif // L_GAMESTATE

