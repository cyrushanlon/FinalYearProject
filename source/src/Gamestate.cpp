#include "Gamestate.h"

bool Gamestate::GetPaused()
{
    return this->paused;
}

void Gamestate::SetPaused(bool newPaused)
{
    this->paused = newPaused;
}
