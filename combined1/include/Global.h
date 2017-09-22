#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <map>

#include "Drawable.h"
#include "Point.h"
#include "ResourceManager.h"
#include "LuaState.h"

//TODO
//change to map with ID as key
extern std::map<std::string, Drawable*> Drawables;
extern std::map<std::string, Point*> Points;

extern ResourceManager rscManager;

extern LuaState Lua;

#endif // GLOBAL_H_INCLUDED
