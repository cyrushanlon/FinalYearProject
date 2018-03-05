#ifndef SOUND_H
#define SOUND_H

#include<SFML/Audio.hpp>

class Sound
{
public:
    const std::string ID;

    Sound(std::string); //call base constructor
    Sound(std::string, std::string);//call other constructor

    virtual ~Sound();

    //Sound only, we dont want these to be virtual
    void Play();

    void SetBuffer(std::string);
    sf::SoundBuffer GetTexture();
    sf::Sound GetSound();
protected:

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
    std::string soundUri; //used in the dtor to free the resource
};

#endif // SOUND_H
