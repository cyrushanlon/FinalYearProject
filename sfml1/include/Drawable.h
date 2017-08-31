#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

class Drawable
{
    public:
        Drawable();
        virtual ~Drawable();
        virtual void Draw(sf::RenderWindow*);
        sf::Vector2f GetPos();
        void SetTexture(std::string);
    protected:

    private:
        sf::Sprite sprite;
        sf::Texture texture;
};

#endif // DRAWABLE_H
