#ifndef L_SOUND_H
#define L_SOUND_H

#include "Global.h"
#include<SFML/Audio.hpp>

static sf::Sound* l_CheckSound(int i)
{
    // This checks that the argument is a userdata with the metatable "luaL_Sound"
    return *(sf::Sound **)luaL_checkudata(Lua.L(), i, "luaL_Sound");
}

//we should pass the lua state in here but instead we will use the global object instead
static int l_Sound_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 1 argument
    if (argc != 1)
    {
        return luaL_error(L, "incorrect argument count");
    }

    //create userdata
    sf::Sound ** udata = (sf::Sound **)lua_newuserdata(L, sizeof(sf::Sound *));

    const char * soundPath = luaL_checkstring(L, 1);
    auto buffer = *rscManager.LoadSoundBuffer(soundPath).get();

    *udata = new sf::Sound(buffer);

    //
    luaL_getmetatable(L, "luaL_Sound");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_Sound_Play(lua_State *L)
{
    sf::Sound* sound = l_CheckSound(1);

    sound->play();

    return 0;
}

static int l_Sound_Destructor(lua_State * l)
{
    sf::Sound* sound = l_CheckSound(1);
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
