#ifndef L_SOUND_H
#define L_SOUND_H

#include "Global.h"
#include "Sound.h"

static Sound* l_CheckSound(int i)
{
    // This checks that the argument is a userdata with the metatable "luaL_Sound"
    return *(Sound **)luaL_checkudata(Lua.L(), i, "luaL_Sound");
}

//we should pass the lua state in here but instead we will use the global object instead
static int l_Sound_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 1 argument
    if (argc != 2) // need both id and path
    {
        return luaL_error(L, "incorrect argument count");
    }

    //gets the first argument of the constructor
    const char * newID = luaL_checkstring(L, 1);

    //create userdata
    Sound ** udata = (Sound **)lua_newuserdata(L, sizeof(Sound *));

    //create an instance using the correct number of arguments as required
    const char * soundPath = luaL_checkstring(L, 2);
    *udata = new Sound(newID, soundPath);

    //
    luaL_getmetatable(L, "luaL_Sound");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_Sound_Play(lua_State *L)
{
    Sound* sound = l_CheckSound(1);

    sound->Play();

    return 0;
}

static int l_Sound_Destructor(lua_State * l)
{
    Sound* sound = l_CheckSound(1);
    delete sound;

    return 0;
}

static void RegisterSound()
{
    //defines the functions and their C counterparts
    luaL_Reg sSoundRegs[] =
    {
        { "New", l_Sound_Constructor },
        { "Play", l_Sound_Play },
        { "__gc", l_Sound_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_Sound");

    //register the functions
    luaL_setfuncs(Lua.L(), sSoundRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "Sound");
}

#endif // L_SOUND_H
