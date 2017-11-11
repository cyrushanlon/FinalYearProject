#include <iostream>

#include <SFML/Graphics.hpp>

#include "Entity/Drawable.h"
#include "ResourceManager.h"
#include "Global.h"

//TODO
/*

virtual sizes rather than pixels so different resolutions look the same

BOTH
_________________
level loading/saving
Box2D
Settings
camera
screen shake
draw order (things that might need to be on top of other things etc) (convert map to vector?)
Anims
treat userdata as a table so we can add custom fields whenever in Lua
UI
networking

LUA
_________________
texture
window

Blockly(?) https://developers.google.com/blockly/

Docs
*/

int main()
{
    Window.create(sf::VideoMode(1280, 720), "SFML works!");
    Window.setFramerateLimit(500);
    Window.setVerticalSyncEnabled(false);

    //calls the lua function Init()
    Lua.Initialise();

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
            if (event.type == sf::Event::LostFocus)
                Lua.HookLostFocus();
            if (event.type == sf::Event::GainedFocus)
                Lua.HookGainedFocus();
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
        Lua.Think(dt);

        //Draw
        //
        Window.clear(sf::Color::White);
        for( auto const& x : Drawables)
        {
            x.second->Draw(&Window);
        }
        Window.display();
    }

    return 0;
}
