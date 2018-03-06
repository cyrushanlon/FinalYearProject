#ifndef L_DRAWABLECOMPONENT
#define L_DRAWABLECOMPONENT

#include <lua.hpp>
#include "Components/Entity.h"
#include "Global.h"
#include <iostream>

static DrawableComponent* l_CheckDrawableComponent(int i)
{
    return *(DrawableComponent **)luaL_checkudata(Lua.L(), i, "luaL_DrawableComponent");
}

static int l_DrawableComponent_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 0 argument
    if (argc != 0)
    {
        return luaL_error(L, "incorrect argument count");
    }

    //create userdata
    DrawableComponent ** udata = (DrawableComponent **)lua_newuserdata(L, sizeof(DrawableComponent *));
    *udata = new DrawableComponent();

    //
    luaL_getmetatable(L, "luaL_DrawableComponent");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_DrawableComponent_Destructor(lua_State * l)
{
    DrawableComponent * dc = l_CheckDrawableComponent(1);
    //delete dc;

    return 0;
}

static int l_DrawableComponent_GetPos(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);

    sf::Vector2f pos = dc->GetPos();
    //use the LuaState helper to push the vector onto the stack
    Lua.PushVector2f(pos);

    //we return a single variable to Lua
    return 1;
}

static int l_DrawableComponent_SetPos(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);
    double x = luaL_checknumber(l, 2);
    double y = luaL_checknumber(l, 3);

    dc->SetPos(sf::Vector2f(x, y));

    return 0;
}

static int l_DrawableComponent_GetAng(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);

    float ang = dc->GetAng();
    //use the LuaState helper to push the angle onto the stack
    lua_pushnumber(l, ang);

    //we return a single variable to Lua
    return 1;
}

static int l_DrawableComponent_SetAng(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);
    float ang = luaL_checknumber(l, 2);

    dc->SetAng(ang);

    return 0;
}

static int l_DrawableComponent_GetOrigin(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);

    sf::Vector2f origin = dc->GetOrigin();
    //use the LuaState helper to push the vector onto the stack
    Lua.PushVector2f(origin);

    //we return a single variable to Lua
    return 1;
}

static int l_DrawableComponent_SetOrigin(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);
    double x = luaL_checknumber(l, 2);
    double y = luaL_checknumber(l, 3);

    dc->SetOrigin(sf::Vector2f(x, y));

    return 0;
}

static int l_DrawableComponent_GetSize(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);

    auto bounds = dc->sprite.getGlobalBounds();

    sf::Vector2f size = sf::Vector2f(bounds.width, bounds.height);
    //use the LuaState helper to push the vector onto the stack
    Lua.PushVector2f(size);

    //we return a single variable to Lua
    return 1;
}

static int l_DrawableComponent_SetSize(lua_State * l)
{
    //DrawableComponent* dc = l_CheckDrawableComponent(1);

    //double x = luaL_checknumber(l, 2);
    //double y = luaL_checknumber(l, 3);

    //dc->GetSprite()(sf::Vector2f(x, y));

    return 0;
}

static int l_DrawableComponent_SetTexture(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);
    std::string uri = luaL_checkstring(l, 2);

    dc->SetTexture(uri);

    return 0;
}

static int l_Animatable_SetAnimates(lua_State * l)
{
    DrawableComponent* anim = l_CheckDrawableComponent(1);

    bool n = lua_toboolean(l, 2);

    anim->Animates(n);

    return 0;
}

static int l_Animatable_GetAnimates(lua_State * l)
{
    DrawableComponent* dc = l_CheckDrawableComponent(1);

    bool n = dc->Animates();
    //use the LuaState helper to push the angle onto the stack
    lua_pushboolean(l, n);

    //we return a single variable to Lua
    return 1;
}

static int l_Animatable_SetAnimation(lua_State * l)
{
    DrawableComponent* anim = l_CheckDrawableComponent(1);

    const char * name = luaL_checkstring(l, 2);

    anim->SetAnimation(name);

    return 0;
}
static int l_Animatable_AddAnimation(lua_State * l)
{
    DrawableComponent* anim = l_CheckDrawableComponent(1);

    Animation* newAnim = l_CheckAnimation(2);

    anim->AddAnimation(*newAnim);

    return 0;
}

static void RegisterDrawableComponent()
{
    //defines the functions and their C counterparts
    luaL_Reg sDrawableComponentRegs[] =
    {
        { "New", l_DrawableComponent_Constructor },
        { "GetPos", l_DrawableComponent_GetPos },
        { "SetPos", l_DrawableComponent_SetPos },
        { "GetAng", l_DrawableComponent_GetAng },
        { "SetAng", l_DrawableComponent_SetAng },
        { "GetSize", l_DrawableComponent_GetSize },
        { "SetSize", l_DrawableComponent_SetSize },
        { "GetOrigin", l_DrawableComponent_GetOrigin },
        { "SetOrigin", l_DrawableComponent_SetOrigin },
        { "SetTexture", l_DrawableComponent_SetTexture },
        { "SetAnimates", l_Animatable_SetAnimates},
        { "GetAnimates", l_Animatable_GetAnimates},
        { "SetAnimation", l_Animatable_SetAnimation },
        { "AddAnimation", l_Animatable_AddAnimation },
        { "__gc", l_DrawableComponent_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_DrawableComponent");

    //register the functions
    luaL_setfuncs(Lua.L(), sDrawableComponentRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "DrawableComponent");
}


#endif // L_DRAWABLECOMPONENT
