#include <lua.hpp>
#include <string>
#include <iostream>

#include "Dog.h"

//used by lua to output a series of variables
static int l_LogOut(lua_State *L) {

    //get the number of arguments from the stack
    int n = lua_gettop(L);

    std::cout << "from C++: ";

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

int Add(lua_State* L, int x, int y)
{
    //grab the function with the name add
    lua_getglobal(L, "add");
    //push the 2 arguments to the stack
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    //call the function with 2 arguments and 1 return value
    lua_call(L, 2, 1);
    //get the result of the function call and cast it to an int
    int result = (int)lua_tointeger(L, -1);
    //pop removes the result from the stack
    lua_pop(L, 1);

    return result;
}

int main(int argc, char** argv)
{
    //initialise lua
    lua_State *L = luaL_newstate();

    //load the standard library
    luaL_openlibs(L);
    //register a C++ function with lua
    lua_register(L, "logout", l_LogOut);
    //register the dog class
    RegisterDog(L);

    //run the script
    int err = luaL_dofile(L,"test.lua");
    if(err)
    {
        std::cout << "lua error: " << luaL_checkstring(L, -1) << std::endl;
    }

    //call the lua function called add from C++
    std::cout << "from C++: " << Add(L, 15, 35) << std::endl;

    lua_close(L);

    return 0;
}
