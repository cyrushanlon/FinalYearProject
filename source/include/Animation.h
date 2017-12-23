#ifndef ANIMATION_H
#define ANIMATION_H

//handle multiline animations
//handle animations that dont go in order left to right(?)
//allow multiple animatables to use the same animation using resource manager(?)

#include <SFML/Graphics.hpp>

#include "Global.h"

class Animation
{
public:
    Animation(std::string pathToSheet, sf::Vector2i frameSize, int framerate, int framecount);
    virtual ~Animation();

    //void LoadFromFile(); //load anim from json file (?)

    int GetFrameRate();
    void SetFrameRate(int newFrameRate);

    int GetFrameCount();
    void SetFrameCount(int newFrameCount);

    sf::Color getBackgroundColor();
    void SetBackgroundColor(sf::Color newColor);

    sf::Vector2i getFrameSize();
    void SetFrameSize(sf::Vector2i newFrameSize);

    sf::Vector2i getFirstFrameTopLeft();
    void SetFirstFrameTopLeft(sf::Vector2i newFirstFrameTopLeft);

    std::string getSpritesheetPath();
    void SetSpritesheetPath(std::string path);

protected:

private:
    int frameRate; //the target playback speed
    int frameCount; //number of frames in the animation
    sf::Color backgroundColor; //the color of the background of the spritesheet for transparency
    sf::Vector2i frameSize; //the size of the sprite
    sf::Vector2i firstFrameTopLeft; //top left of the first frame, multiple animations could use the same spritesheet
    std::string spritesheetPath; //holds the URI to the spritesheet

    sf::Image spritesheet; //should be ref/pointer(?)

    std::vector<sf::Texture> frames;

    //could make this public so developers could reload the spritesheet when saving an image(?)
    void regenerate(); //this reacquires the frames from the sprite sheet
    void loadSpritesheet(std::string path);
};

#endif // ANIMATION_H
