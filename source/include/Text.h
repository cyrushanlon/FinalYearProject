#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>

class Text
{
public:
    Text();

    void SetString(std::string);
    void SetColor(int, int, int, int);
    void SetPosition(float, float);
    void SetScale(float, float);
    void SetViewTarget(std::string);
    std::string GetViewTarget();
    sf::Text text;
private:
    std::string rt;
    sf::Font font; //put in resource manager
};

#endif // TEXT_H
