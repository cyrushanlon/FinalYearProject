#include <iostream>

#include <SFML/Graphics.hpp>

#include "Components/Entity.h"
#include "ECSManager.h"
#include "ResourceManager.h"

#include "Global.h"

//TODO
/*

virtual sizes rather than pixels so different resolutions look the same
CPP
_________________
stop sound inheriting from old point class

BOTH
_________________
cameras / multiple views so things like minimaps/ui can be created
level loading/saving
Box2D
Settings
screen shake
draw order (things that might need to be on top of other things etc) (convert map to vector?)
treat userdata as a table so we can add custom fields whenever in Lua
UI
networking

LUA
_________________
Anims //need to inherit animatable metatable from drawable metatable
keypress and release hooks
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

    gsManager.CreateState("game").get()->AddView("main", sf::FloatRect(0,0, 1280, 720));
    gsManager.SetState("game");

    ECSManager ecsManager;

    //calls the lua function Init()
    Lua.Initialise("spriteEditor.lua");

    //Test code
    auto gs = gsManager.CurrentState().get();

    Entity ent = Entity("test1");
    ent.AddComponent(std::make_shared<DrawableComponent>());
    std::shared_ptr<Animation> anim = std::make_shared<Animation>("walk", "resources/textures/metalslug_mummy37x45.png", sf::Vector2i(37, 45), 50, 18);
    anim.get()->SetLooping(true);
    anim.get()->Regenerate();
    //get game state
    //get component
    DrawableComponent* comp = gs->GetDrawable(ent.GetID()).get();
    comp->SetTexture("resources/textures/metalslug_mummy37x45.png");
    comp->Animates(true);
    comp->AddAnimation(anim);
    comp->SetAnimation("walk");

    Entity ent2 = Entity("test2");
    ent2.AddComponent(std::make_shared<DrawableComponent>());
    DrawableComponent* comp2 = gs->GetDrawable(ent2.GetID()).get();
    comp2->SetTexture("resources/textures/metalslug_mummy37x45.png");
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
                {
                    Window.close();
                }
            if (event.type == sf::Event::LostFocus)
                Lua.HookLostFocus();
            if (event.type == sf::Event::GainedFocus)
                Lua.HookGainedFocus();
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window, stops stretching
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                Window.setView(sf::View(visibleArea));
            }
        }

        //Think
        //
        sf::Time dt = deltaClock.restart();

        auto state = gsManager.CurrentState().get();

        //first we do the C++ think
        //we might want to move this into lua so its all together, performance shouldnt be an issue
        if (!state->GetPaused()) //we dont want to think if the current state is paused
        {
            ecsManager.Think(dt);
            //this calls the lua think function
            Lua.Think(dt);
        }


        //Draw
        //
        Window.clear(sf::Color::Magenta);
        Window.setView(Window.getDefaultView());


        //for each view we want to go through and see if we want to draw anything
        //this may end up expensive and should be improved
        for( auto const& view : state->views)
        {
            ecsManager.Draw(Window);
            /*
            Window.setView(view.second);
            for( auto const& x : state->drawables)
            {
                if (x.second->GetViewTarget() == view.first)
                    x.second->Draw(&Window);
            }
            */
        }
        Window.display();
    }

    return 0;
}
