#ifndef L_ENTITY
#define L_ENTITY

#include <lua.hpp>
#include "Components/Entity.h"
#include "Components/DrawableComponent.h"
#include "Global.h"
#include <iostream>

static DrawableComponent* l_CheckDrawableComponent(int i);

static Entity* l_CheckEntity(int i)
{
    return *(Entity **)luaL_checkudata(Lua.L(), i, "luaL_Entity");
}

static int l_Entity_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 1 argument
    if (argc != 1)
    {
        return luaL_error(L, "incorrect argument count");
    }

    //gets the first argument of the constructor
    const char * newID = luaL_checkstring(L, 1);

    //create userdata
    Entity ** udata = (Entity **)lua_newuserdata(L, sizeof(Entity *));
    *udata = new Entity(newID);

    //
    luaL_getmetatable(L, "luaL_Entity");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_Entity_AddComponent(lua_State * l)
{
    Entity* entity = l_CheckEntity(1);

    //get component from argument
    DrawableComponent* dc = l_CheckDrawableComponent(2);
    auto dcPointer = std::shared_ptr<DrawableComponent>(dc);

    bool succ = !entity->AddComponent(dcPointer);

    lua_pushboolean(l, succ);

    return 1;
}

static int l_Entity_GetID(lua_State * l)
{
    Entity* entity = l_CheckEntity(1);

    std::string id = entity->GetID();
    //use the LuaState helper to push the angle onto the stack
    lua_pushstring(l, id.c_str());

    //we return a single variable to Lua
    return 1;
}

static int l_Entity_Destructor(lua_State * l)
{
    Entity * entity = l_CheckEntity(1);
    delete entity;

    return 0;
}
/*
static int l_Entity_Index( lua_State* L )
{
    std::cout << "a";
    //object, key
    //first check the environment
    lua_getuservalue( L, -2 );
    lua_pushvalue( L, -2 );
    lua_rawget( L, -2 );
    if( lua_isnoneornil( L, -1 ) == 0 )
    {
        return 1;
    }

    lua_pop( L, 2 );

    //second check the metatable
    lua_getmetatable( L, -2 );
    lua_pushvalue( L, -2 );
    lua_rawget( L, -2 );

    //nil or otherwise, we return here
    return 1;
}

static int l_Entity_NewIndex( lua_State* L )
{
std::cout << "b";
    //object, key, value
std::cout << 1;
    lua_getuservalue( L, -3 );
std::cout << 2;
    lua_pushvalue( L, -3 );
std::cout << 3;
    lua_pushvalue( L, -3 );
std::cout << 4;
    lua_rawset( L, -3 );
std::cout << 5;

    return 0;
}
*/

static void RegisterEntity()
{
    //defines the functions and their C counterparts
    luaL_Reg sEntityRegs[] =
    {
        { "New", l_Entity_Constructor },
        { "AddComponent", l_Entity_AddComponent },
        //{ "GetComponent", l_Entity_GetComponent },
        { "GetID", l_Entity_GetID },
        { "__gc", l_Entity_Destructor },
        //{"__index",l_Entity_Index},
        //{"__newindex",l_Entity_NewIndex},
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_Entity");

    //register the functions
    luaL_setfuncs(Lua.L(), sEntityRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "Entity");
}


#endif // L_ENTITY
