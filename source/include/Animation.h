#ifndef ANIMATION_H
#define ANIMATION_H

//number of frames
    // current frame
    // frame size (per frame?)
    // frame rate
    // background colour
    // target file

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(std::string pathToSheet, int framerate, sf::Vector2f frameSize);
    virtual ~Animation();

    LoadSpritesheet(std::string path);
    //public LoadFromFile(); //load anim from file (json?)

    int GetFrameRate();
    void SetFrameRate(int newFrameRate);

    sf::Color getBackgroundColor();
    void SetBackgroundColor(sf::Color newColor);

    sf::Vector2i getFrameSize();
    void SetFrameSize(sf::Vector2i newFrameSize);

protected:

private:
    int frameRate; //the target playback speed
    sf::Color backgroundColor; //the color of the background of the spritesheet for transparency
    sf::Vector2i frameSize; //the size of the sprite

    void regenerate(); //this reacquires the frames from the sprite sheet
};

#endif // ANIMATION_H
