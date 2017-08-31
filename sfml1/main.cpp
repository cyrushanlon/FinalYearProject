#include <SFML/Graphics.hpp>
#include "Drawable.h"

std::vector<Drawable> Drawables;

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

    Drawable newSprite;
    newSprite.SetTexture("resources/textures/smile.png");

    Drawables.push_back(newSprite);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for(int i = 0; i < Drawables.size(); i++)
        {
            Drawables.at(i).Draw(&window);
        }
        window.display();
    }

    return 0;
}
