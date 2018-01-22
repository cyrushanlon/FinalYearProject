#ifndef L_ANIMATABLE_H
#define L_ANIMATABLE_H

#include <lua.hpp>
#include "Animatable.h"
#include "Global.h"
#include <iostream>

//functions required to use the class in lua
//initial example found here: https://gist.github.com/kizzx2/1594905

static Animatable* l_CheckAnimatable(int i)
{
    // This checks that the argument is a userdata with the metatable "luaL_Animation"
    return *(Animatable **)luaL_checkudata(Lua.L(), i, "luaL_Animatable");
}

//we should pass the lua state in here but instead we will use the global object instead
static int l_Animatable_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //create userdata
    Animatable ** udata = (Animatable **)lua_newuserdata(L, sizeof(Animatable *));
    //there should be 1 arguments
    //std::string id and viewtarget
    if (argc == 1)
    {
        //gets the 1 argument
        const char * id = luaL_checkstring(L, 1);

        *udata = new Animatable(id);
    }
    else if (argc == 2)
    {
        //gets the 1 argument
        const char * id = luaL_checkstring(L, 1);
        const char * view = luaL_checkstring(L, 2);

        *udata = new Animatable(id, view);
    }
    else
    {
        return luaL_error(L, "incorrect argument count");
    }

    //
    luaL_getmetatable(L, "luaL_Animatable");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_Animatable_SetAnimation(lua_State * l)
{
    Animatable* anim = l_CheckAnimatable(1);

    const char * name = luaL_checkstring(l, 2);

    anim->SetAnimation(name);

    return 0;
}
static int l_Animatable_AddAnimation(lua_State * l)
{
    Animatable* anim = l_CheckAnimatable(1);

    const char * name = luaL_checkstring(l, 2);
    Animation* newAnim = l_CheckAnimation(3);

    anim->AddAnimation(name, *newAnim);

    return 0;
}

static int l_Animatable_Destructor(lua_State * l)
{
    Animatable * anim = l_CheckAnimatable(1);
    delete anim;

    return 0;
}

static void RegisterAnimatable()
{
    //defines the functions and their C counterparts
    luaL_Reg sAnimatableRegs[] =
    {
        { "New", l_Animatable_Constructor },
        { "SetAnimation", l_Animatable_SetAnimation },
        { "AddAnimation", l_Animatable_AddAnimation },
        { "__gc", l_Animatable_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_Animatable");

    //register the functions
    luaL_setfuncs(Lua.L(), sAnimatableRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "Animatable");
}

#endif //L_ANIMATABLE_H
