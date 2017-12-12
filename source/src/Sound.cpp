#include "Sound.h"

#include "Global.h"

Sound::Sound(std::string ID) : Point(ID) //call base constructor
{
    Sounds[this->ID] = this;
}

Sound::Sound(std::string ID, std::string soundPath) : Sound(ID)//call other constructor
{
    this->SetBuffer(soundPath);
}

Sound::~Sound()
{
    rscManager.Unload(this->soundUri);
}

void Sound::SetBuffer(std::string uri)
{
    //dont really want a local version of the sound but sometimes we may want to have some special sound specific behaviour
    this->buffer = *rscManager.LoadSoundBuffer(uri).get();
    this->soundUri = uri;

    this->sound.setBuffer(this->buffer);
}

void Sound::Play()
{
    this->sound.play();
}
