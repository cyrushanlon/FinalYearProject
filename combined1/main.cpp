#include <SFML/Graphics.hpp>

#include "Entity/Drawable.h"
#include "ResourceManager.h"
#include "Global.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");

    ResourceManager rscManager;

    Drawable newSprite(&rscManager, "resources/textures/smile.png");
    newSprite.SetPos(sf::Vector2f(100.f, 100.f));

    Drawable newSprite1(&rscManager, "resources/textures/smile.png");
    Drawable newSprite2(&rscManager, "resources/textures/smile.png");
    Drawable newSprite3(&rscManager, "resources/textures/smile.png");

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

        for(unsigned int i = 0; i < Points.size(); i++)
        {
            Points.at(i)->Think(dt);
        }

        //Draw
        //
        window.clear();
        for(unsigned int i = 0; i < Drawables.size(); i++)
        {
            Drawables.at(i)->Draw(&window);
        }
        window.display();
    }

    return 0;
}
