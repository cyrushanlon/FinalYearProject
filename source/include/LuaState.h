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

        //TODO template the push vectors
        void PushVector2f(sf::Vector2f);
        void PushVector2i(sf::Vector2i);
        void PushVector2u(sf::Vector2u);
        void Think(sf::Time);
        void Initialise();
        void HookLostFocus();
        void HookGainedFocus();

    protected:

    private:
        lua_State* state;
};

#endif // LUASTATE_H
