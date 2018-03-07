#include "Gamestate.h"

Gamestate::Gamestate()
{
    this->paused = false;
}

std::shared_ptr<DrawableComponent> Gamestate::GetDrawable(std::string parent)
{
    for (int i = 0; i < this->drawableComponents.size(); i++)
    {
        auto cur = this->drawableComponents.at(i);
        if (cur.get()->GetParent() == parent)
            return cur;
    }
    return nullptr;
}

bool Gamestate::GetPaused()
{
    return this->paused;
}

void Gamestate::SetPaused(bool newPaused)
{
    this->paused = newPaused;
}

sf::View Gamestate::GetView(std::string ID)
{
    for (int i = 0; i < this->views.size(); i++)
    {
        auto cur = this->views.at(i);
        if (cur.first == ID) //found
        {
            return cur.second;
        }
    }
}

void Gamestate::AddView(std::string ID, sf::View view)
{
    //sf::View view(rect);
    this->views.push_back({ID, view});
}

void Gamestate::RemoveView(std::string ID)
{
    for (int i = 0; i < this->views.size(); i++)
    {
        auto cur = this->views.at(i);
        if (cur.first == ID) //found
        {
            //there is no std function that takes just an index, an iterator must be used
            this->views.erase(this->views.begin() + i);
            return;
        }
    }
}

void Gamestate::SetView(std::string ID, sf::View view)
{
    for (int i = 0; i < this->views.size(); i++)
    {
        auto cur = this->views.at(i);
        if (cur.first == ID) //found
        {
            //there is no std function that takes just an index, an iterator must be used
            this->views[i].second = view;
            return;
        }
    }
}

void Gamestate::MoveViewToTop(std::string ID)
{

}

void Gamestate::MoveViewToBot(std::string ID)
{

}

void Gamestate::MoveViewUp(std::string ID)
{

}

void Gamestate::MoveViewDown(std::string ID)
{

}
