#include "Animation.h"

#include <sstream>

#include "Global.h"

Animation::Animation()
{

}

Animation::Animation(std::string name, std::string pathToSheet, sf::Vector2i frameSize, int framerate, int framecount)
{
    this->name = name;
    this->spritesheetPath = pathToSheet;
    this->frameSize = frameSize;
    this->frameRate = framerate;
    this->frameCount = framecount;
    this->backgroundColor = sf::Color::White;

    this->SetLooping(false);
    this->SetForwards(true);
    this->SetReversing(false);

    this->currentFrame = 0;
}

Animation::~Animation()
{
    /*
    this->spritesheet.reset();
    rscManager.Unload(this->spritesheetPath);
    //unload each frame
    this->frames.clear();
    for (int i = 0; i < this->frameUris.size(); i++)
    {
        rscManager.Unload(this->frameUris.at(i));
    }
    */
}

std::string Animation::GetName()
{
    return this->name;
}

float Animation::GetFrameRate()
{
    return this->frameRate;
}
void Animation::SetFrameRate(float newFrameRate)
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

bool Animation::isForwards()
{
    return forwards;
}
void Animation::SetForwards(bool newIsForwards)
{
    this->forwards = newIsForwards;
}

bool Animation::isReversing()
{
    return reversing;
}
void Animation::SetReversing(bool newIsReversing)
{
    this->reversing = newIsReversing;
}

bool Animation::isLooping()
{
    return looping;
}
void Animation::SetLooping(bool newIsLooping)
{
    this->looping = newIsLooping;
}

int Animation::GetNextFrame()
{
    int iteration = 1;
    if (!this->isForwards())
        iteration = -1;

    int oldFrame = this->currentFrame;
    this->currentFrame += iteration;


    if (this->currentFrame >= this->frameCount)
    {
        this->currentFrame = this->frameCount - 1;
        if (this->isLooping())
        {
            if (this->isReversing())
            {
                this->SetForwards(false);
                this->currentFrame--;
            }
            else
            {
                this->currentFrame = 0;
            }
        }
    }
    else if (this->currentFrame == 0)
    {
        this->SetForwards(true);
    }

    return oldFrame;
}

sf::IntRect Animation::GetFrame(int i)
{
    return this->frames.at(i);
}
/*
std::string Animation::GetFrameURI(int i)
{
    return this->frameUris.at(i);
}
*/
void Animation::Regenerate()
{
    //clear all frames
    this->frames.clear();

    //get the spritesheet as a texture with a no background
    this->loadSpritesheet(this->getSpritesheetPath());

    //get as many rectangles in a row starting from firstFrameTopLeft of size frameSize until we have frameCount
    unsigned int x = this->firstFrameTopLeft.x;
    unsigned int y = this->firstFrameTopLeft.y;
    unsigned int noOfFrames = 0;

    bool done = false;
    while(!done)
    {
        //create the URI first so we can check if the frame has already been created
        std::stringstream ss;
        ss << x << y << this->frameSize.x << this->frameSize.y;
        std::string uri = this->spritesheetPath + ss.str();

        //if frame already exists
        if (!rscManager.Exists(uri))
        {
            //get tex from image at rect of framesize
            sf::Texture newFrame;
            const sf::IntRect rect = sf::IntRect(x, y, this->frameSize.x, this->frameSize.y);
            //newFrame.loadFromImage(*this->spritesheet.get(), rect);
            this->frames.push_back(rect);
            //add new frame to resource manager
            //rscManager.Add(newFrame, uri);
        }
        //add frame to animation
        //this->frames.push_back(rscManager.LoadTexture(uri));
        //this->frameUris.push_back(uri);

        //increment counters
        x += this->getFrameSize().x;
        noOfFrames++;
        if (x + this->frameSize.x > this->spritesheet->getSize().x)
        {
            y += this->getFrameSize().y;
            x = 0;
        }

        //check if we have enough frames or if the next frame will be out of bounds
        //what should happen if we go out of bounds? (go to next line?)
        if (noOfFrames >= this->frameCount || y + this->frameSize.y > this->spritesheet->getSize().y)
            done = true;
    }
}

void Animation::Reset()
{
    this->currentFrame = 0;
}

void Animation::loadSpritesheet(std::string path)
{
    this->spritesheetPath = path;

    //load from resource manager and remove the background
    std::shared_ptr<sf::Texture> tex = rscManager.LoadTexture(path);
    //image->createMaskFromColor(this->getBackgroundColor());
    this->spritesheet = tex;

    //this->regenerate();
}
