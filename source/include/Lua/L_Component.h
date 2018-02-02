#ifndef L_COMPONENT
#define L_COMPONENT

#include <lua.hpp>
#include "Components/Component.h"
#include "Global.h"
#include <iostream>

static Component* l_CheckComponent(int i)
{
    return *(Component **)luaL_checkudata(Lua.L(), i, "luaL_Component");
}

static int l_Component_Destructor(lua_State * l)
{
    Component * c = l_CheckComponent(1);
    delete c;

    return 0;
}

static int l_Component_GetName(lua_State * l)
{
    Component * c = l_CheckComponent(1);

    lua_pushstring(l, c->Name().c_str());

    return 1;
}

static int l_Component_SetParent(lua_State * l)
{
    Component * c = l_CheckComponent(1);

    std::string id = luaL_checkstring(l, 1);

    c->SetParent(id);

    return 0;
}

static int l_Component_GetParent(lua_State * l)
{
    Component * c = l_CheckComponent(1);

    lua_pushstring(l, c->GetParent().c_str());

    return 1;
}

static void RegisterComponent()
{
    //defines the functions and their C counterparts
    luaL_Reg sDrawableComponentRegs[] =
    {
        { "GetName", l_Component_GetName },
        { "SetParent", l_Component_SetParent },
        { "GetParent", l_Component_GetParent },
        { "__gc", l_Component_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_Component");

    //register the functions
    luaL_setfuncs(Lua.L(), sDrawableComponentRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "Component");
}


#endif // L_DRAWABLECOMPONENT
