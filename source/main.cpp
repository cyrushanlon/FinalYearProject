#include <iostream>

#include <SFML/Graphics.hpp>

#include "Entity/Animatable.h"
#include "ResourceManager.h"
#include "Global.h"

//TODO
/*

virtual sizes rather than pixels so different resolutions look the same

BOTH
_________________
Anims
level loading/saving
Box2D
Settings
camera
screen shake
draw order (things that might need to be on top of other things etc) (convert map to vector?)
treat userdata as a table so we can add custom fields whenever in Lua
UI
networking

LUA
_________________
texture
window

Blockly(?) https://developers.google.com/blockly/
open source level editor(?)

Docs
*/

int main()
{
    Window.create(sf::VideoMode(1280, 720), "SFML works!");
    Window.setFramerateLimit(500);
    Window.setVerticalSyncEnabled(false);

    //calls the lua function Init()
    Lua.Initialise("spriteEditor.lua");

    //Test code
    Animatable test("test1");

    Animation walkAnim("walk", "resources/textures/character_sheet.png", sf::Vector2i(400, 600), 10, 4);
    walkAnim.SetFirstFrameTopLeft(sf::Vector2i(0, 0));
    walkAnim.SetLooping(true);
    walkAnim.Regenerate();

    Animation idleAnim("idle", "resources/textures/character_sheet.png", sf::Vector2i(400, 600), 10, 1);
    idleAnim.SetFirstFrameTopLeft(sf::Vector2i(0, 0));
    idleAnim.SetLooping(true);
    idleAnim.Regenerate();

    test.AddAnimation("walk", walkAnim);
    test.AddAnimation("idle", idleAnim);
    test.SetAnimation("walk");

    //

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
        Window.clear(sf::Color::Black);
        for( auto const& x : Drawables)
        {
            x.second->Draw(&Window);
        }
        Window.display();
    }

    return 0;
}
