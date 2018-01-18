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
Gamestate
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
Anims
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

    gsManager.CreateState("game");
    gsManager.SetState("game");

    //calls the lua function Init()
    Lua.Initialise("spriteEditor.lua");

    //Test code
    /*
    Animation walkAnim("walk", "resources/textures/metalslug_mummy37x45.png", sf::Vector2i(37, 45), 50, 18);
    walkAnim.SetFirstFrameTopLeft(sf::Vector2i(0, 0));
    walkAnim.SetLooping(true);
    //walkAnim.SetReversing(true);
    walkAnim.SetBackgroundColor(sf::Color::White);
    walkAnim.Regenerate();

    for (int x = 0; x < 1; x++)
    {
        for (int y = 0; y < 1; y++)
        {
            std::ostringstream ss;
            ss << x << " " << y;

            //Drawable* a = new Drawable("test" + ss.str(), "resources/textures/ball.png");
            //std::cout << i * 32 << " " << 0 << std::endl;
            //a->SetPos(sf::Vector2f(i * 32, 0));

            Animatable* test = new Animatable("test" + ss.str());
            test->AddAnimation("walk", walkAnim);
            test->SetAnimation("walk");
            test->SetPos(sf::Vector2f(x * 32, y * 32));

            std::cout << "test" + ss.str() << std::endl;
        }
    }
    std::cout << Drawables.size() <<std::endl;
    */
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

        auto state = gsManager.CurrentState().get();

        //first we do the C++ think
        //we might want to move this into lua so its all together, performance shouldnt be an issue
        if (!state->GetPaused()) //we dont want to think if the current state is paused
        {
            for( auto const& x : state->points)
            {
                x.second->Think(dt);
            }
            //this calls the lua think function
            Lua.Think(dt);
        }

        //Draw
        //
        Window.clear(sf::Color::Magenta);
        for( auto const& x : state->drawables)
        {
            x.second->Draw(&Window);
        }
        Window.display();
    }

    return 0;
}
