#include "Gamestate.h"

Gamestate::Gamestate()
{
    this->paused = false;
}

bool Gamestate::GetPaused()
{
    return this->paused;
}

void Gamestate::SetPaused(bool newPaused)
{
    this->paused = newPaused;
}
