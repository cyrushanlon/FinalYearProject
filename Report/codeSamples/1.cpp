
static int l_sin (lua_State *L) 
{
    double d = lua_tonumber(L, 1);  /* get argument */
    lua_pushnumber(L, sin(d));  /* push result */
    return 1;  /* number of results */
}
void registerSin(lua_State *L) 
{
    lua_pushcfunction(l, l_sin);
    lua_setglobal(l, "mysin");
}