#ifndef DOG_H
#define DOG_H

#include <lua.hpp>

#include <string>

class Dog {

public:
    Dog(std::string);

    void Talk(std::string);
    std::string GetName();

private:
    std::string name;
};

//functions below are used by lua to interact with the dog C++ type

// Create and return a Dog instance to Lua
static int l_DogNew(lua_State* L)
{
    //get the argument from the top of the stack
	std::string name = luaL_checkstring(L, 1);

    //make object for use in lua
	*reinterpret_cast<Dog**>(lua_newuserdata(L, sizeof(Dog*))) = new Dog(name);
	luaL_setmetatable(L, "Dog");

    //single argument
	return 1;
}

// delete the dog instance, used by the Lua GC
static int l_DogDelete(lua_State* L){
	delete *reinterpret_cast<Dog**>(lua_touserdata(L, 1));
	return 0;
}

// Dog talk function for use in Lua
static int l_DogTalk(lua_State* L){
    //get the dog object from the top of the stack and get the argument from the second top of the stack and call the talk member func
	(*reinterpret_cast<Dog**>(luaL_checkudata(L, 1, "Dog")))->Talk(luaL_checkstring(L, 2));
	return 0;
}

static int l_DogGetName(lua_State* L){
    //get the dog object from the top of the stack and push the result of GetName to the lua stack
	lua_pushstring(L, (*reinterpret_cast<Dog**>(luaL_checkudata(L, 1, "Dog")))->GetName().c_str());
	//return 1 as there is 1 return value
	return 1;
}

// Register Dog to Lua
static void RegisterDog(lua_State* L){
    //register the constructor function
	lua_register(L, "Dog", l_DogNew);

	luaL_newmetatable(L, "Dog");
	//register the "destructor" with the lua GC
	lua_pushcfunction(L, l_DogDelete);
	lua_setfield(L, -2, "__gc");

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
    //register the talk member func
	lua_pushcfunction(L, l_DogTalk);
	lua_setfield(L, -2, "talk");
    //register the getname member func
	lua_pushcfunction(L, l_DogGetName);
	lua_setfield(L, -2, "getName");

	lua_pop(L, 1);
}

#endif // DOG_H
