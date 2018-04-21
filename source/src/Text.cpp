#include "Text.h"

#include "Global.h"

Text::Text()
{
    this->rt = "main";

    if (!this->font.loadFromFile("arial.ttf"))
    {
        // error...
    }
    this->text.setFont(this->font);

    gsManager.CurrentState()->texts.push_back(std::shared_ptr<Text>(this));
}

void Text::SetString(std::string newString)
{
    this->text.setString(newString);
}

void Text::SetColor(int r, int g, int b, int a)
{
    this->text.setFillColor(sf::Color(r, g, b, a));
}

void Text::SetPosition(float x, float y)
{
    this->text.setPosition(x, y);
}

void Text::SetScale(float x, float y)
{
    this->text.setScale(x, y);
}

std::string Text::GetViewTarget()
{
    return this->rt;
}
