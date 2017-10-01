#ifndef L_INPUT
#define L_INPUT

#include "Global.h"

#include <iostream>

//functions required for Lua to receive input from SFML

static int l_Input_IsKeyPressed(lua_State *L)
{
    //if there is 1 argument
    if (lua_gettop(L) == 1)
    {
        //get the string passed in from the top of the stack
        std::string KeyString = luaL_checkstring(L, 1);

        //check that the key is real
        auto iter = KeyMap.find(KeyString);
        if (iter != KeyMap.end())
        {
            //push back true or false whether the key is pressed or not
            lua_pushboolean(L, sf::Keyboard::isKeyPressed(iter->second));
            //we return a single variable to Lua
            return 1;
        }
    }
    lua_pushnil(L);

    return 1;
}

static int l_Input_GetMousePos(lua_State *L)
{
    //get the current mouse positon and return it to lua
    Lua.PushVector2i(sf::Mouse::getPosition(Window));

    return 1;
}

static int l_Input_SetMousePos(lua_State *L)
{
    //if there is 1 argument
    if (lua_gettop(L) == 2)
    {
        //get the string passed in from the top of the stack
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 1);

        //check that the key is real
        sf::Mouse::setPosition(sf::Vector2i(x,y), Window);
    }

    return 0;
}

static void RegisterInput()
{
    lua_register(Lua.L(), "IsKeyPressed", l_Input_IsKeyPressed);
    lua_register(Lua.L(), "GetMousePos", l_Input_GetMousePos);
    lua_register(Lua.L(), "SetMousePos", l_Input_SetMousePos);
}

#endif // L_INPUT
