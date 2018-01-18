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

    bool GetPaused();
    void SetPaused(bool);
private:

    //allow for pausing
    bool paused;
};

#endif // GAMESTATE_H
