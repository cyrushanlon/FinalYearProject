#ifndef L_PHYSICSCOMPONENT
#define L_PHYSICSCOMPONENT

#include <lua.hpp>
#include "Box2D/Box2D.h"

#include "Components/PhysicsComponent.h"
#include "Global.h"
#include <iostream>

static b2BodyDef* l_Checkb2BodyDef(int i);
static b2FixtureDef* l_Checkb2FixtureDef(int i);

static PhysicsComponent* l_CheckPhysicsComponent(int i)
{
    return *(PhysicsComponent **)luaL_checkudata(Lua.L(), i, "luaL_PhysicsComponent");
}

static int l_PhysicsComponent_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 0 argument
    if (argc != 4)
    {
        return luaL_error(L, "incorrect argument count");
    }

    b2BodyDef* bodyDef = l_Checkb2BodyDef(1);
    b2FixtureDef* fixtureDef =  l_Checkb2FixtureDef(2);
    float x = luaL_checknumber(L, 3);
    float y = luaL_checknumber(L, 4);

    //create userdata
    PhysicsComponent ** udata = (PhysicsComponent **)lua_newuserdata(L, sizeof(PhysicsComponent *));
    *udata = new PhysicsComponent(*bodyDef, *fixtureDef, x, y);

    //
    luaL_getmetatable(L, "luaL_PhysicsComponent");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_PhysicsComponent_Destructor(lua_State * l)
{
    PhysicsComponent * pc = l_CheckPhysicsComponent(1);
    //delete pc;

    return 0;
}

static int l_PhysicsComponent_GetAng(lua_State * l)
{
    PhysicsComponent * pc = l_CheckPhysicsComponent(1);

    float ang = pc->GetAngle();
    //use the LuaState helper to push the angle onto the stack
    lua_pushnumber(l, ang);

    //we return a single variable to Lua
    return 1;
}

static int l_PhysicsComponent_GetPos(lua_State * l)
{
    PhysicsComponent * pc = l_CheckPhysicsComponent(1);

    b2Vec2 pos = pc->GetPosition();
    //use the LuaState helper to push the angle onto the stack
    Lua.Pushb2Vec2(pos);

    //we return a single variable to Lua
    return 1;
}

static int l_PhysicsComponent_GetVel(lua_State * l)
{
    PhysicsComponent * pc = l_CheckPhysicsComponent(1);

    b2Vec2 pos = pc->GetLinearVelocity();
    //use the LuaState helper to push the angle onto the stack
    Lua.Pushb2Vec2(pos);

    //we return a single variable to Lua
    return 1;
}

static int l_PhysicsComponent_SetPos(lua_State * l)
{
    PhysicsComponent* pc = l_CheckPhysicsComponent(1);
    float x = luaL_checknumber(l, 2);
    float y = luaL_checknumber(l, 3);

    pc->SetBodyTransform(b2Vec2(x,y));

    return 0;
}

static int l_PhysicsComponent_SetAng(lua_State * l)
{
    PhysicsComponent* pc = l_CheckPhysicsComponent(1);
    float ang = luaL_checknumber(l, 2);

    pc->SetBodyTransform(ang);

    return 0;
}

static int l_PhysicsComponent_ApplyForce(lua_State * l)
{
    PhysicsComponent* pc = l_CheckPhysicsComponent(1);

    //first we check how many arguments we are dealing with
    int argc = lua_gettop(l) - 1;

    if (argc != 3 && argc != 5)
    {
        std:: cout << argc << std::endl;
        return luaL_error(l, "incorrect argument count");
    }

    float x = luaL_checknumber(l, 2);
    float y = luaL_checknumber(l, 3);
    b2Vec2 force = b2Vec2(x, y);

    if (argc == 5)
    {
        float x2 = luaL_checknumber(l, 4);
        float y2 = luaL_checknumber(l, 5);
        b2Vec2 pos = b2Vec2(x2, y2);

        bool wake = lua_toboolean(l, 6);

        pc->ApplyForce(force, pos, wake);
    }
    else
    {
        bool wake = lua_toboolean(l, 4);

        pc->ApplyForceToCenter(force, wake);
    }

    return 0;
}

static int l_PhysicsComponent_ApplyImpulse(lua_State * l)
{
    PhysicsComponent* pc = l_CheckPhysicsComponent(1);

    //first we check how many arguments we are dealing with
    int argc = lua_gettop(l) - 1;

    if (argc != 3 && argc != 5)
    {
        std:: cout << argc << std::endl;
        return luaL_error(l, "incorrect argument count");
    }

    float x = luaL_checknumber(l, 2);
    float y = luaL_checknumber(l, 3);
    b2Vec2 force = b2Vec2(x, y);

    if (argc == 5)
    {
        float x2 = luaL_checknumber(l, 4);
        float y2 = luaL_checknumber(l, 5);
        b2Vec2 pos = b2Vec2(x2, y2);

        bool wake = lua_toboolean(l, 6);

        pc->ApplyImpulse(force, pos, wake);
    }
    else
    {
        bool wake = lua_toboolean(l, 4);

        pc->ApplyImpulseToCenter(force, wake);
    }

    return 0;
}

static int l_PhysicsComponent_ApplyTorque(lua_State * l)
{
    PhysicsComponent* pc = l_CheckPhysicsComponent(1);

    //first we check how many arguments we are dealing with
    int argc = lua_gettop(l) - 1;

    if (argc != 3 && argc != 5)
    {
        std:: cout << argc << std::endl;
        return luaL_error(l, "incorrect argument count");
    }

    float torque = luaL_checknumber(l, 2);
    bool wake = lua_toboolean(l, 4);

    pc->ApplyTorque(torque, wake);

    return 0;
}

static int l_PhysicsComponent_ApplyAngularImpulse(lua_State * l)
{
    PhysicsComponent* pc = l_CheckPhysicsComponent(1);

    //first we check how many arguments we are dealing with
    int argc = lua_gettop(l) - 1;

    if (argc != 3 && argc != 5)
    {
        std:: cout << argc << std::endl;
        return luaL_error(l, "incorrect argument count");
    }

    float torque = luaL_checknumber(l, 2);
    bool wake = lua_toboolean(l, 4);

    pc->ApplyAngularImpulse(torque, wake);

    return 0;
}

/*
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
*/

static void RegisterPhysicsComponent()
{
    //defines the functions and their C counterparts
    luaL_Reg sPhysicsComponentRegs[] =
    {
        { "New", l_PhysicsComponent_Constructor },
        { "SetPos", l_PhysicsComponent_SetPos },
        { "SetAng", l_PhysicsComponent_SetAng },
        { "GetPos", l_PhysicsComponent_GetPos },
        { "GetAng", l_PhysicsComponent_GetAng },
        { "GetVel", l_PhysicsComponent_GetVel },
        { "ApplyForce", l_PhysicsComponent_ApplyForce},
        { "ApplyImpulse" ,l_PhysicsComponent_ApplyImpulse},
        { "ApplyTorque", l_PhysicsComponent_ApplyTorque},
        { "ApplyAngularImpulse" ,l_PhysicsComponent_ApplyAngularImpulse},
        { "__gc", l_PhysicsComponent_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_PhysicsComponent");

    //register the functions
    luaL_setfuncs(Lua.L(), sPhysicsComponentRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "PhysicsComponent");
}

#endif // L_PHYSICSCOMPONENT
