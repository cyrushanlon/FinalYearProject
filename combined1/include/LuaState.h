#ifndef LUASTATE_H
#define LUASTATE_H

#include <lua.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

class LuaState
{
    public:
        LuaState();
        virtual ~LuaState();
        lua_State* L();

        void PushVector2f(sf::Vector2f);
        void CallLuaThink(sf::Time);

    protected:

    private:
        lua_State* state;
};

#endif // LUASTATE_H
