#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>

#include "Drawable.h"
#include "Point.h"
#include "Sound.h"

#include "ResourceManager.h"
#include "LuaState.h"

extern sf::RenderWindow Window;

extern std::map<std::string, Drawable*> Drawables;
extern std::map<std::string, Point*> Points;

extern std::map<std::string, Sound*> Sounds;

extern ResourceManager rscManager;

extern LuaState Lua;

extern const std::map<std::string, sf::Keyboard::Key> KeyMap;

#endif // GLOBAL_H_INCLUDED
