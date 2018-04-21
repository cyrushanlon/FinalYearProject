#ifndef L_TEXT
#define L_TEXT

#include "Text.h"

static Text* l_CheckText(int i)
{
    return *(Text **)luaL_checkudata(Lua.L(), i, "luaL_Text");
}

static int l_Text_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 0 argument

    //create userdata
    Text ** udata = (Text **)lua_newuserdata(L, sizeof(Text *));
    *udata = new Text();

    //
    luaL_getmetatable(L, "luaL_Text");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_Text_Destructor(lua_State * l)
{
    Text * t = l_CheckText(1);
    delete t;

    return 0;
}

static int l_Text_SetString(lua_State * l)
{
    Text* text = l_CheckText(1);

    std::string str = luaL_checkstring(l, 2);

    text->SetString(str);

    return 0;
}

static int l_Text_SetPos(lua_State * l)
{
    Text* text = l_CheckText(1);

    double x = luaL_checknumber(l, 2);
    double y = luaL_checknumber(l, 3);

    text->SetPosition(x, y);

    return 0;
}

static int l_Text_SetScale(lua_State * l)
{
    Text* text = l_CheckText(1);

    double x = luaL_checknumber(l, 2);
    double y = luaL_checknumber(l, 3);

    text->SetScale(x, y);

    return 0;
}

static int l_Text_SetColor(lua_State * l)
{
    Text* text = l_CheckText(1);

    double r = luaL_checknumber(l, 2);
    double g = luaL_checknumber(l, 3);
    double b = luaL_checknumber(l, 4);
    double a = luaL_checknumber(l, 5);

    text->SetColor(r, g, b, a);

    return 0;
}

static void RegisterText()
{
    //defines the functions and their C counterparts
    luaL_Reg sTextRegs[] =
    {
        { "New", l_Text_Constructor },
        { "SetString", l_Text_SetString },
        { "SetPos", l_Text_SetPos },
        { "SetScale", l_Text_SetScale },
        { "SetColor", l_Text_SetColor },
        { "__gc", l_Text_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_Text");

    //register the functions
    luaL_setfuncs(Lua.L(), sTextRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "Text");
}

#endif // L_TEXT
