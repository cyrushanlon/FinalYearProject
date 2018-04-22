#include <iostream>

#include <SFML/Graphics.hpp>

#include "Components/Entity.h"
#include "ECSManager.h"
#include "ResourceManager.h"
#include "ContactListener.h"
#include "Box2D/Box2D.h"

#include "Global.h"

//TODO
/*
physics shapes
EXAMPLES
physics callback
text

EXTRAS
LEVEL LOADING
SETTINGS
VIRTUAL SIZES
WINDOW + INIT

screen shake
draw order (things that might need to be on top of other things etc)
treat userdata as a table so we can add custom fields whenever in Lua
UI
networking
Joints

LUA
_________________
texture
window

Blockly(?) https://developers.google.com/blockly/
open source level editor(?)

Docs
*/

int main(int argc, char* argv[])
{
    std::string path = "fall.lua";
    if (argc == 2)
    {
        path = argv[1];
    }
    else
    {
        std::cout << "Usage:" << argv[0] << " path to lua file" << std::endl;
        //return 1;
    }

    Window.create(sf::VideoMode(1280, 720), path);
    Window.setFramerateLimit(500);
    Window.setVerticalSyncEnabled(false);

    gsManager.CreateState("game").get()->AddView("main", sf::View(sf::FloatRect(0,0, 1280, 720)));
    gsManager.SetState("game");

    ECSManager ecsManager;

    //update rates for box2d
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    //box2d callback handler
    ContactListener contactListener;
    world.SetContactListener(&contactListener);

    //calls the lua function Init()
    Lua.Initialise(path.c_str());

    /*/Test code
    b2BodyDef groundBodyDef;

    b2FixtureDef floorfixture;

    Entity floor = Entity("floor");
    std::shared_ptr<DrawableComponent> floorDraw = std::static_pointer_cast<DrawableComponent>(floor.AddComponent(std::make_shared<DrawableComponent>()));
    floorDraw.get()->SetTexture("resources/textures/floor.png");

    std::shared_ptr<PhysicsComponent> floorPhys = std::static_pointer_cast<PhysicsComponent>(floor.AddComponent(std::make_shared<PhysicsComponent>(groundBodyDef, floorfixture, 50, 10)));
    floorPhys.get()->SetBodyTransform(b2Vec2(0, -20));
    ///////////////////////////
    auto gs = gsManager.CurrentState().get();

    //
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    Entity ent1 = Entity("test1");
    ent1.AddComponent(std::make_shared<DrawableComponent>());
    DrawableComponent* comp1 = gs->GetDrawable(ent1.GetID()).get();
    comp1->SetTexture("resources/textures/box.png");

    std::shared_ptr<PhysicsComponent> otherPhys = std::static_pointer_cast<PhysicsComponent>(ent1.AddComponent(std::make_shared<PhysicsComponent>(bodyDef, fixtureDef, 4, 4)));
    otherPhys.get()->SetBodyTransform(b2Vec2(2, 15));
    //

    Entity ent2 = Entity("test2");
    ent2.AddComponent(std::make_shared<DrawableComponent>());
    DrawableComponent* comp2 = gs->GetDrawable(ent2.GetID()).get();
    comp2->SetTexture("resources/textures/box.png");

    std::shared_ptr<PhysicsComponent> otherPhys2 = std::static_pointer_cast<PhysicsComponent>(ent2.AddComponent(std::make_shared<PhysicsComponent>(bodyDef, fixtureDef, 4, 4)));
    otherPhys2.get()->SetBodyTransform(b2Vec2(0, 10));

    ///////////////////////////

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
                else
                {
                    Lua.HookKeyPressed(event.key.code);
                }
            if (event.type == sf::Event::KeyReleased)
                Lua.HookKeyReleased(event.key.code);

            if (event.type == sf::Event::MouseButtonPressed)
                Lua.HookMousePressed(event.mouseButton.button == sf::Mouse::Left);
            if (event.type == sf::Event::MouseButtonReleased)
                Lua.HookMouseReleased(event.mouseButton.button == sf::Mouse::Left);

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
        Window.clear(bgColor);
        //Window.setView(Window.getDefaultView());
        ecsManager.Draw(Window);
        Window.display();
    }

    return 0;
}
