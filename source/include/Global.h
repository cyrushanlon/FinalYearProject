#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>

#include "GamestateManager.h"

#include "ResourceManager.h"
#include "LuaState.h"
#include "Box2D/Box2D.h"

extern sf::RenderWindow Window;

extern GamestateManager gsManager;

extern ResourceManager rscManager;

extern LuaState Lua;

extern const std::map<std::string, sf::Keyboard::Key> KeyMap;

extern b2World world;

#endif // GLOBAL_H_INCLUDED
