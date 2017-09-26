#include <SFML/Graphics.hpp>

#include "Entity/Drawable.h"
#include "ResourceManager.h"
#include "Global.h"

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(false);

    //used to get dt during the main loop
    sf::Clock deltaClock;

    while (window.isOpen())
    {
        //Events
        //
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::KeyReleased)
            {
                //inpManager.AddEvent(event, event.type == sf::Event::KeyPressed);
            }
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
        window.clear();
        for( auto const& x : Drawables)
        {
            x.second->Draw(&window);
        }
        window.display();
    }

    return 0;
}
