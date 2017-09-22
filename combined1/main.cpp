#include <SFML/Graphics.hpp>

#include "Entity/Drawable.h"
#include "ResourceManager.h"
#include "Global.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");

    //create a series of test drawables
    //Drawable newSprite("newSprite", "resources/textures/smile.png");
    //Drawable newSprite1("newSprite1", "resources/textures/smile.png");
    //Drawable newSprite2("newSprite2", "resources/textures/smile.png");
    //Drawable newSprite3("newSprite3", "resources/textures/smile.png");

    //get drawable from the global drawables map using its ID and then change its position
    //Drawables["ID1"]->SetPos(sf::Vector2f(100.f, 100.f));

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
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::KeyReleased)
            {
                //inpManager.AddEvent(event, event.type == sf::Event::KeyPressed);
            }
        }

        //Think
        //
        sf::Time dt = deltaClock.restart();

        for( auto const& x : Points)
        {
            x.second->Think(dt);
        }

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
