#ifndef LUASTATE_H
#define LUASTATE_H

#include <lua.hpp>
#include <SFML/System/Vector2.hpp>

class LuaState
{
    public:
        LuaState();
        virtual ~LuaState();
        lua_State* L();

        void PushVector2f(sf::Vector2f);

    protected:

    private:
        lua_State* state;
};

#endif // LUASTATE_H
