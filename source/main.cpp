#include <iostream>

#include <SFML/Graphics.hpp>

#include "Components/Entity.h"
#include "ECSManager.h"
#include "ResourceManager.h"
#include "Box2D/Box2D.h"

#include "Global.h"

//TODO
/*

CPP
_________________
virtual sizes rather than pixels so different resolutions look the same
stop sound inheriting from old point class

BOTH
_________________
cameras / multiple views so things like minimaps/ui can be created
level loading/saving
Box2D
Settings
screen shake
draw order (things that might need to be on top of other things etc)
treat userdata as a table so we can add custom fields whenever in Lua
UI
networking
Joints

LUA
_________________
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

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);
    ///////////////////////////
    auto gs = gsManager.CurrentState().get();

    Entity ent2 = Entity("test2");
    ent2.AddComponent(std::make_shared<DrawableComponent>());
    DrawableComponent* comp2 = gs->GetDrawable(ent2.GetID()).get();
    comp2->SetTexture("resources/textures/metalslug_mummy37x45.png");

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    ent2.AddComponent(std::make_shared<PhysicsComponent>(bodyDef, fixtureDef, 1, 1));
    ///////////////////////////

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

/*
    Entity ent = Entity("test1");
    ent.AddComponent(std::make_shared<DrawableComponent>());
    Animation anim("walk", "resources/textures/metalslug_mummy37x45.png", sf::Vector2i(37, 45), 50, 18);
    anim.SetLooping(true);
    anim.Regenerate();
    //get game state
    //get component
    DrawableComponent* comp = gs->GetDrawable(ent.GetID()).get();
    comp->SetTexture("resources/textures/metalslug_mummy37x45.png");
    comp->Animates(true);
    comp->AddAnimation(anim);
    comp->SetAnimation("walk");
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
                {
                    Window.close();
                }
                //else
                //    Lua.HookKeyPressed();
            //if (event.type == sf::Event::KeyReleased)
            //    Lua.HookKeyReleased();
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

        //physics world
        world.Step(dt.asSeconds(), velocityIterations, positionIterations);

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
