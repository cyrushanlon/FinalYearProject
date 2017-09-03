#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "ResourceManager.h"

std::vector<Drawable*> Drawables;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");

    ResourceManager rscManager;

    Drawable newSprite(&rscManager);
    newSprite.SetTexture("resources/textures/smile.png");

    Drawable newSprite1(&rscManager);
    newSprite1.SetTexture("resources/textures/smile.png");

    Drawable newSprite2(&rscManager);
    newSprite2.SetTexture("resources/textures/smile.png");

    Drawable newSprite3(&rscManager);
    newSprite3.SetTexture("resources/textures/smile.png");

    Drawables.push_back(&newSprite);
    Drawables.push_back(&newSprite1);
    Drawables.push_back(&newSprite2);
    Drawables.push_back(&newSprite3);

    while (window.isOpen())
    {
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

        window.clear();
        for(unsigned int i = 0; i < Drawables.size(); i++)
        {
            Drawables.at(i)->Draw(&window);
        }
        window.display();
    }

    return 0;
}
