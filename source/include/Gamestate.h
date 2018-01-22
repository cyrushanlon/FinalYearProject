#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Drawable.h"
#include "Point.h"
#include "Sound.h"

class Gamestate
{
public:
    Gamestate();
    //std::map<std::string, Drawable*> GetDrawables();
    //std::map<std::string, Point*> GetPoints();
    //std::map<std::string, Sound*> GetSounds();

    //hold everything that we want to process
    //convert to vectors of shared pointers
    //should probably be private
    std::map<std::string, Drawable*> drawables;
    std::map<std::string, Point*> points;
    std::map<std::string, Sound*> sounds;
    //each gamestate will have its own set of views so rather than using another manager etc we hold them here
    std::vector<std::pair<std::string,sf::View>> views;

    bool GetPaused();
    void SetPaused(bool);

    //views
    sf::View GetView(std::string ID);
    void AddView(std::string ID, sf::FloatRect);
    void RemoveView(std::string ID);
    void SetView(std::string ID, sf::View view);

    void MoveViewToTop(std::string ID);
    void MoveViewToBot(std::string ID);
    void MoveViewUp(std::string ID);
    void MoveViewDown(std::string ID);

private:

    //allow for pausing
    bool paused;
};

#endif // GAMESTATE_H
