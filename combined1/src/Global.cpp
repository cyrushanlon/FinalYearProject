#include "Global.h"

std::map<std::string, Drawable*> Drawables;
std::map<std::string, Point*> Points;

ResourceManager rscManager;

LuaState Lua;
