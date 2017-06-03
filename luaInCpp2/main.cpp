#include <lua.hpp>
#include <string>
#include <iostream>

static int l_LogOut(lua_State *L) {

    //get the number of arguments from the stack
    int n = lua_gettop(L);

    std::cout << "C++ log out: ";

    for (int i = 1; i <= n; i++)
    {
        //get the arguments from the stack
        std::string a = luaL_checkstring(L, i);
        std::cout << a << " ";
    }

    std::cout <<std::endl;

    //return the number of results
    return 0;
}

int main(int argc, char** argv)
{
    lua_State *L = luaL_newstate();

    luaL_openlibs(L);
    lua_register(L, "logout", l_LogOut);

    int err = luaL_dofile(L,"test.lua");
    if(err)
    {
        std::cout << "lua error: " << luaL_checkstring(L, -1) << std::endl;
    }

    lua_close(L);

    return 0;
}
