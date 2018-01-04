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
    Animation();
    Animation(std::string name, std::string pathToSheet, sf::Vector2i frameSize, int framerate, int framecount);
    virtual ~Animation();

    //void LoadFromFile(); //load anim from json file (?)

    float GetFrameRate();
    void SetFrameRate(float newFrameRate);

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

    bool isForwards();
    void SetForwards(bool);
    bool isReversing();
    void SetReversing(bool);
    bool isLooping();
    void SetLooping(bool);

    //returns the URI of the next frame in sequence
    std::string GetNextFrame();
    //returns the nth frame URI
    std::string GetFrame(int);

    //this reacquires the frames from the sprite sheet
    void Regenerate();

    //resets important variables
    void Reset();
protected:

private:
    std::string name;

    float frameRate; //the target playback speed
    int frameCount; //number of frames in the animation
    sf::Color backgroundColor; //the color of the background of the spritesheet for transparency
    sf::Vector2i frameSize; //the size of the sprite
    sf::Vector2i firstFrameTopLeft; //top left of the first frame, multiple animations could use the same spritesheet
    std::string spritesheetPath; //holds the URI to the spritesheet

    std::shared_ptr<sf::Image> spritesheet;

    int currentFrame;
    std::vector<std::string> frames; //holds all frame uris

    bool forwards; //starts at end and goes backwards if false
    bool reversing; //1 2 3 4 5 4 3 2 1 2 3 4 5
    bool looping; // repeats forever

    //could make this public so developers could reload the spritesheet when saving an image(?)
    void loadSpritesheet(std::string path);
};

#endif // ANIMATION_H
