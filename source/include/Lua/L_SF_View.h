#ifndef L_SF_VIEW_H
#define L_SF_VIEW_H

#include <lua.hpp>
#include "Global.h"

class ViewForLua {
public:
    ViewForLua(sf::FloatRect rect, std::string id)
    {
        this->view = sf::View(rect);
        this->id = id;

        gsManager.CurrentState().get()->AddView(id, this->view);
    }
    ViewForLua(sf::View main)
    {
        this->view = main;
        this->id = "main";
    }
    sf::View view;
    std::string id;
};

static ViewForLua* l_CheckView(int i)
{
    // This checks that the argument is a userdata with the metatable "luaL_SF_View"
    return *(ViewForLua **)luaL_checkudata(Lua.L(), i, "luaL_SF_View");
}

//we should pass the lua state in here but instead we will use the global object instead
static int l_View_Constructor(lua_State *L)
{
    //first we check how many arguments we are dealing with
    int argc = lua_gettop(L);

    //there should be 4 arguments
    if (argc != 5)
    {
        return luaL_error(L, "incorrect argument count");
    }

    //gets the 1 argument
    double x = luaL_checknumber(L, 1);
    //gets the 2 argument
    double y = luaL_checknumber(L, 2);
    //gets the 3 argument
    double xSize = luaL_checknumber(L, 3);
    //gets the 4 argument
    double ySize = luaL_checknumber(L, 4);
    //gets the 5 argument
    std::string id = luaL_checkstring(L, 5);

    //create userdata
    ViewForLua ** udata = (ViewForLua **)lua_newuserdata(L, sizeof(ViewForLua *));
    *udata = new ViewForLua(sf::FloatRect(x, y, xSize, ySize), id);

    //
    luaL_getmetatable(L, "luaL_SF_View");
    //we have to set userdata metatable in C as it is not allowed in Lua
    lua_setmetatable(L, -2);

    //return 1 so we return the userdata and clean the stack
    return 1;
}

static int l_View_Move(lua_State * l)
{
    ViewForLua* viewForLua = l_CheckView(1);

    double x = luaL_checknumber(l, 2);
    double y = luaL_checknumber(l, 3);

    viewForLua->view.move(x, y);
    gsManager.CurrentState().get()->SetView(viewForLua->id, viewForLua->view);

    return 0;
}
static int l_View_Zoom(lua_State * l)
{
    ViewForLua* viewForLua = l_CheckView(1);

    double zoom = luaL_checknumber(l, 2);

    viewForLua->view.zoom(zoom);
    gsManager.CurrentState().get()->SetView(viewForLua->id, viewForLua->view);

    return 0;
}

static int l_View_Destructor(lua_State * l)
{
    ViewForLua * view = l_CheckView(1);

    gsManager.RemoveState(view->id);

    delete view;
    return 0;
}

static void RegisterView()
{
    //defines the functions and their C counterparts
    luaL_Reg sViewRegs[] =
    {
        { "New", l_View_Constructor },
        { "Move", l_View_Move },
        { "Zoom", l_View_Zoom },
        { "__gc", l_View_Destructor },
        { NULL, NULL }
    };

    luaL_newmetatable(Lua.L(), "luaL_SF_View");

    //register the functions
    luaL_setfuncs(Lua.L(), sViewRegs, 0);
    lua_pushvalue(Lua.L(), -1);

    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(Lua.L(), -1, "__index");

    //we use setglobal to expose the metatable to Lua
    lua_setglobal(Lua.L(), "View");
}

#endif // L_SF_VIEW_H
