#include "Animation.h"

Animation::Animation(std::string pathToSheet, sf::Vector2i frameSize, int framerate, int framecount)
{
    this->spritesheetPath = pathToSheet;
    this->frameSize = frameSize;
    this->frameRate = framerate;
    this->frameCount = framecount;
}

Animation::~Animation()
{
    //dtor
}

int Animation::GetFrameRate()
{
    return this->frameRate;
}
void Animation::SetFrameRate(int newFrameRate)
{
    this->frameRate = newFrameRate;
    //this->regenerate();
}

int Animation::GetFrameCount()
{
    return this->frameCount;
}
void Animation::SetFrameCount(int newFrameCount)
{
    this->frameCount = newFrameCount;
    //this->regenerate();
}

sf::Color Animation::getBackgroundColor()
{
    return this->backgroundColor;
}
void Animation::SetBackgroundColor(sf::Color newBackgroundColor)
{
    this->backgroundColor = newBackgroundColor;
    //this->regenerate();
}

sf::Vector2i Animation::getFrameSize()
{
    return this->frameSize;
}
void Animation::SetFrameSize(sf::Vector2i newFrameSize)
{
    this->frameSize = newFrameSize;
    //this->regenerate();
}

sf::Vector2i Animation::getFirstFrameTopLeft()
{
    return this->firstFrameTopLeft;
}
void Animation::SetFirstFrameTopLeft(sf::Vector2i newFirstFrameTopLeft)
{
    this->firstFrameTopLeft = newFirstFrameTopLeft;
    //this->regenerate();
}

std::string Animation::getSpritesheetPath()
{
    return this->spritesheetPath;
}
void Animation::SetSpritesheetPath(std::string path)
{
    this->spritesheetPath = path;
    //this->regenerate();
}

void Animation::regenerate()
{
    //get the spritesheet as a texture with a no background
    this->loadSpritesheet(this->getSpritesheetPath());

    //get as many rectangles in a row starting from firstFrameTopLeft of size frameSize until we have frameCount
    int x = firstFrameTopLeft.x;
    int y = firstFrameTopLeft.y;
    int noOfFrames = 0;

    bool done = false;
    while(!done) {
        sf::Texture newFrame;

        //get tex from image at rect of framesize
        newFrame.loadFromImage(this->spritesheet, sf::IntRect(x, y, this->frameSize.x, this->frameSize.y));
        this->frames.push_back(newFrame);

        //increment counters
        x += this->getFrameSize().x;
        y += this->getFrameSize().y;
        noOfFrames++;

        //check if we have enough frames or if the next frame will be out of bounds
        //what should happen if we go out of bounds?
        if (noOfFrames >= this->frameCount || x + this->frameSize.x > this->spritesheet.getSize().x || y + this->frameSize.y > this->spritesheet.getSize().y)
            done = true;
    }
}

void Animation::loadSpritesheet(std::string path)
{
    this->spritesheetPath = path;

    //load from resource manager and remove the background
    sf::Image image = *rscManager.LoadImage(path).get();
    image.createMaskFromColor(this->getBackgroundColor());
    this->spritesheet = image;

    //this->regenerate();
}
