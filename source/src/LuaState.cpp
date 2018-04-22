#include <iostream>

#include "LuaState.h"


#include "Lua/L_Input.h"
#include "Lua/L_Window.h"
#include "Lua/L_SF_View.h"
#include "Lua/L_Animation.h"
#include "Lua/L_Gamestate.h"
#include "Lua/L_Sound.h"
#include "Lua/L_Text.h"

#include "Lua/box2d/L_b2BodyDef.h"
#include "Lua/box2d/L_b2FixtureDef.h"

#include "Lua/L_Entity.h"
#include "Lua/L_Component.h"
#include "Lua/L_DrawableComponent.h"
#include "Lua/L_PhysicsComponent.h"

#include "Global.h"


LuaState::LuaState()
{
    this->state = luaL_newstate();
    luaL_openlibs(this->state);

    //register everything from C++ into lua

    RegisterWindow();
    RegisterView();
    RegisterInput();
    RegisterAnimation();
    RegisterGamestate();
    RegisterSound();
    RegisterText();

    Registerb2BodyDef();
    Registerb2FixtureDef();

    RegisterEntity();
    RegisterComponent();
    RegisterDrawableComponent();
    RegisterPhysicsComponent();

    //run any engine related files
    /* component funcs arent required and this didnt work anyway
    std::string luaCode =
    "DrawableComponent.__index = function(table,key)"
    "print(\"trying to get component function\")"
    "  return Component[key]"
    "end";
    luaL_dostring(this->state, luaCode.c_str());
    */
}

LuaState::~LuaState()
{
    //dtor
    lua_close(this->state);
}

lua_State* LuaState::L()
{
    return this->state;
}


void LuaState::PushVector2f(sf::Vector2f vec)
{
    //create a new table at the top of the stack
    lua_newtable(this->state);

    //push key
    lua_pushstring(this->state, "x");
    //push value
    lua_pushnumber(this->state, vec.x);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);

    //push key
    lua_pushstring(this->state, "y");
    //push value
    lua_pushnumber(this->state, vec.y);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);
}

void LuaState::PushVector2i(sf::Vector2i vec)
{
    //create a new table at the top of the stack
    lua_newtable(this->state);

    //push key
    lua_pushstring(this->state, "x");
    //push value
    lua_pushnumber(this->state, vec.x);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);

    //push key
    lua_pushstring(this->state, "y");
    //push value
    lua_pushnumber(this->state, vec.y);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);
}

void LuaState::PushVector2u(sf::Vector2u vec)
{
    //create a new table at the top of the stack
    lua_newtable(this->state);

    //push key
    lua_pushstring(this->state, "x");
    //push value
    lua_pushnumber(this->state, vec.x);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);

    //push key
    lua_pushstring(this->state, "y");
    //push value
    lua_pushnumber(this->state, vec.y);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);
}

void LuaState::Pushb2Vec2(b2Vec2 vec)
{
    //create a new table at the top of the stack
    lua_newtable(this->state);

    //push key
    lua_pushstring(this->state, "x");
    //push value
    lua_pushnumber(this->state, vec.x);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);

    //push key
    lua_pushstring(this->state, "y");
    //push value
    lua_pushnumber(this->state, vec.y);
    //add the key/value pair to the table at the top of the stack
    lua_settable(this->state,-3);
}

void LuaState::Think(sf::Time dt)
{
    //load the function from global
    lua_getglobal(this->L(),"Think");
    if(lua_isfunction(this->L(), -1) )
    {
        //push function argument onto stack
        lua_pushnumber(this->L(), dt.asSeconds());
        int err = lua_pcall(this->L(),1,0,0); // 1 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::Initialise(const char* initPath)
{
    //run the init script
    int err = luaL_dofile(this->state, initPath);
    if(err)
    {
        std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
    }

    //setup the world variables from the settings table
    lua_getglobal(this->L(), "settings");
    if (lua_istable(this->L(), -1))
    {
        lua_pushvalue(this->L(), 1);
        lua_pushnil(this->L());

        float x = 0;
        float y = 0;
        sf::Color newbgColor = sf::Color::Magenta;

        while (lua_next(this->L(), -2))
        {
            lua_pushvalue(this->L(), -2);
            std::string key = luaL_checkstring(this->L(), -1);

            //std::cout << key;
            if (key == "gravityX")
            {
                x = lua_tonumber(this->L(), -2);
            }
            else if (key == "gravityY")
            {
                y = lua_tonumber(this->L(), -2);
            }
            else if (key == "bgColor")
            {
                uint32 color = lua_tonumber(this->L(), -2);
                newbgColor = sf::Color(color);
            }
            else
                luaL_checkstring(this->L(), -2);

            // removes 'value'; keeps 'key' for next iteration
            lua_pop(this->L(), 2);
        }
        lua_pop(this->L(), 1);

        world.SetGravity(b2Vec2(x, y));
        bgColor = newbgColor;
    }

    //load the function from global
    lua_getglobal(this->L(),"Init");
    if(lua_isfunction(this->L(), -1) )
    {
        int err = lua_pcall(this->L(),0,0,0); // 0 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookGainedFocus()
{
    //load the function from global
    lua_getglobal(this->L(),"HookGainedFocus");
    if(lua_isfunction(this->L(), -1) )
    {
        int err = lua_pcall(this->L(),0,0,0); // 0 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookLostFocus()
{
    //load the function from global
    lua_getglobal(this->L(),"HookLostFocus");
    if(lua_isfunction(this->L(), -1) )
    {
        int err = lua_pcall(this->L(),0,0,0); // 0 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookKeyPressed(sf::Keyboard::Key& key)
{
    //load the function from global
    lua_getglobal(this->L(),"HookKeyPressed");
    if(lua_isfunction(this->L(), -1))
    {
        lua_pushstring(this->L(), MapKey.at(key).c_str());
        int err = lua_pcall(this->L(),1,0,0); // 0 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookKeyReleased(sf::Keyboard::Key& key)
{
    //load the function from global
    lua_getglobal(this->L(),"HookKeyReleased");
    if(lua_isfunction(this->L(), -1) )
    {
        lua_pushstring(this->L(), MapKey.at(key).c_str());
        int err = lua_pcall(this->L(),1,0,0); // 0 args, 0 returns
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookMousePressed(bool isLeft)
{
    //load the function from global
    lua_getglobal(this->L(),"HookMousePressed");
    if(lua_isfunction(this->L(), -1))
    {
        lua_pushboolean (this->L(), isLeft);
        int err = lua_pcall(this->L(),1,0,0);
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookMouseReleased(bool isLeft)
{
    //load the function from global
    lua_getglobal(this->L(),"HookMouseReleased");
    if(lua_isfunction(this->L(), -1) )
    {
        lua_pushboolean (this->L(), isLeft);
        int err = lua_pcall(this->L(),1,0,0);
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookBeginContact(std::string ID1, std::string ID2)
{
    //load the function from global
    lua_getglobal(this->L(),"HookBeginContact");
    if(lua_isfunction(this->L(), -1) )
    {
        lua_pushstring(this->L(), ID1.c_str());
        lua_pushstring(this->L(), ID2.c_str());
        int err = lua_pcall(this->L(),2,0,0);
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}

void LuaState::HookEndContact(std::string ID1, std::string ID2)
{
    //load the function from global
    lua_getglobal(this->L(),"HookEndContact");
    if(lua_isfunction(this->L(), -1) )
    {
        lua_pushstring(this->L(), ID1.c_str());
        lua_pushstring(this->L(), ID2.c_str());
        int err = lua_pcall(this->L(),2,0,0);
        if(err)
        {
            std::cout << "lua error: " << luaL_checkstring(this->state, -1) << std::endl;
        }
    }
}
