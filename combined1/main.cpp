#include <iostream>

#include <SFML/Graphics.hpp>

#include "Entity/Drawable.h"
#include "ResourceManager.h"
#include "Global.h"


int main()
{
    Window.create(sf::VideoMode(800, 640), "SFML works!");
    Window.setFramerateLimit(500);
    Window.setVerticalSyncEnabled(false);

    //calls the lua function Init()
    Lua.CallLuaInitialise();

    //used to get dt during the main loop
    sf::Clock deltaClock;

    while (Window.isOpen())
    {
        //Events
        //
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    Window.close();

        }

        //Think
        //
        sf::Time dt = deltaClock.restart();

        //first we do the C++ think
        //we might want to move this into lua so its all together, performance shouldnt be an issue
        for( auto const& x : Points)
        {
            x.second->Think(dt);
        }
        //this calls the lua think function
        Lua.CallLuaThink(dt);

        //Draw
        //
        Window.clear();
        for( auto const& x : Drawables)
        {
            x.second->Draw(&Window);
        }
        Window.display();
    }

    return 0;
}
