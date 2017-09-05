#ifndef LUASTATE_H
#define LUASTATE_H

#include <lua.hpp>

class LuaState
{
    public:
        LuaState();
        virtual ~LuaState();

    protected:

    private:
        lua_State *L;
};

#endif // LUASTATE_H
