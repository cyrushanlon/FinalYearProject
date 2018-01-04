#ifndef L_ANIMATION_H
#define L_ANIMATION_H

#include <lua.hpp>
#include "Animation.h"
#include "Global.h"
#include <iostream>

//functions required to use the class in lua
//initial example found here: https://gist.github.com/kizzx2/1594905

static Animation* l_CheckAnimation(int i)
{
    // This checks that the argument is a userdata with the metatable "luaL_Animation"
    return *(Animation **)luaL_checkudata(Lua.L(), i, "luaL_Animation");
}

//we should pass the lua state in here but instead we will use the global object instead
static int l_Animation_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 6 arguments
    //std::string name, std::string pathToSheet, sf::Vector2i frameSize, int framerate, int framecount
    if (argc != 6)
    {
        return luaL_error(L, "incorrect argument count");
    }

    //gets the 1 argument
    const char * name = luaL_checkstring(L, 1);
    //gets the 2 argument
    const char * path = luaL_checkstring(L, 2);
    //gets the 3 argument
    double sizeX = luaL_checknumber(L, 3);
    //gets the 4 argument
    double sizeY = luaL_checknumber(L, 4);
    //gets the 5 argument
    double framerate = luaL_checknumber(L, 5);
    //gets the 6 argument
    double framecount = luaL_checknumber(L, 6);

    //create userdata
    Animation ** udata = (Animation **)lua_newuserdata(L, sizeof(Animation *));
    *udata = new Animation(name, path, sf::Vector2i(sizeX, sizeY), framerate, framecount);

    //
    luaL_getmetatable(L, "luaL_Animation");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_Animation_GetFrameRate(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);

    float fr = anim->GetFrameRate();

    lua_pushnumber(l, fr);

    //we return a single variable to Lua
    return 1;
}
static int l_Animation_SetFrameRate(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);
    float fr = luaL_checknumber(l, 2);

    anim->SetFrameRate(fr);

    return 0;
}

static int l_Animation_GetFrameCount(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);

    float fr = anim->GetFrameCount();

    lua_pushnumber(l, fr);

    //we return a single variable to Lua
    return 1;
}
static int l_Animation_SetFrameCount(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);
    float fc = luaL_checknumber(l, 2);

    anim->SetFrameCount(fc);

    return 0;
}

/*
static int l_Animation_GetBackgroundColor(lua_State * l)
static int l_Animation_SetBackgroundColor(lua_State * l)

static int l_Animation_GetFrameSize(lua_State * l)
static int l_Animation_SetFrameSize(lua_State * l)

static int l_Animation_GetSpriteSheetPath(lua_State * l)
static int l_Animation_SetSpriteSheetPath(lua_State * l)
*/

static int l_Animation_GetFirstFrameTopLeft(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);

    sf::Vector2i topleft = anim->getFirstFrameTopLeft();
    //use the LuaState helper to push the vector onto the stack
    Lua.PushVector2i(topleft);

    //we return a single variable to Lua
    return 1;
}
static int l_Animation_SetFirstFrameTopLeft(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);

    double x = luaL_checknumber(l, 2);
    double y = luaL_checknumber(l, 3);

    anim->SetFirstFrameTopLeft(sf::Vector2i(x, y));

    return 0;
}

static int l_Animation_GetForwards(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);

    bool forwards = anim->isForwards();

    lua_pushboolean(l, forwards);

    //we return a single variable to Lua
    return 1;
}
static int l_Animation_SetForwards(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);
    bool forwards = lua_toboolean(l, 2);

    anim->SetForwards(forwards);

    return 0;
}

static int l_Animation_GetReversing(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);

    bool reversing = anim->isReversing();

    lua_pushboolean(l, reversing);

    //we return a single variable to Lua
    return 1;
}
static int l_Animation_SetReversing(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);
    bool reversing = lua_toboolean(l, 2);

    anim->SetReversing(reversing);

    return 0;
}

static int l_Animation_GetLooping(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);

    bool looping = anim->isLooping();

    lua_pushboolean(l, looping);

    //we return a single variable to Lua
    return 1;
}
static int l_Animation_SetLooping(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);
    bool looping = lua_toboolean(l, 2);

    anim->SetLooping(looping);

    return 0;
}

static int l_Animation_Regenerate(lua_State * l)
{
    Animation* anim = l_CheckAnimation(1);

    anim->Regenerate();
}

static int l_Animation_Destructor(lua_State * l)
{
    Animation * anim = l_CheckAnimation(1);
    delete anim;

    return 0;
}

static void RegisterAnimation()
{
    //defines the functions and their C counterparts
    luaL_Reg sAnimationRegs[] =
    {
        { "New", l_Animation_Constructor },
        { "GetFrameRate", l_Animation_GetFrameRate },
        { "SetFrameRate", l_Animation_SetFrameRate },
        { "GetFrameCount", l_Animation_GetFrameCount },
        { "SetFrameCount", l_Animation_SetFrameCount },
        { "GetFirstFrameTopLeft", l_Animation_GetFirstFrameTopLeft },
        { "SetFirstFrameTopLeft", l_Animation_SetFirstFrameTopLeft },
        { "GetForwards", l_Animation_GetForwards },
        { "SetForwards", l_Animation_SetForwards },
        { "GetReversing", l_Animation_GetReversing },
        { "SetReversing", l_Animation_SetReversing },
        { "GetLooping", l_Animation_GetLooping },
        { "SetLooping", l_Animation_SetLooping },
        { "Regenerate", l_Animation_Regenerate },
        { "__gc", l_Animation_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_Animation");

    //register the functions
    luaL_setfuncs(Lua.L(), sAnimationRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "Animation");
}

#endif //L_ANIMATION_H
