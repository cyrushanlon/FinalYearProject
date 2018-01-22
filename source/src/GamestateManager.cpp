#include "GamestateManager.h"

void GamestateManager::SetState(std::string ID)
{
    this->currentState = ID;
}

std::shared_ptr<Gamestate> GamestateManager::CreateState(std::string ID)
{
    this->states[ID] = std::make_shared<Gamestate>();
    return this->states[ID];
}

std::shared_ptr<Gamestate> GamestateManager::GetState(std::string ID)
{
    return this->states[ID];
}

std::shared_ptr<Gamestate> GamestateManager::CurrentState()
{
    return this->states[this->currentState];
}

void GamestateManager::RemoveState(std::string ID)
{
    this->states.erase(ID);
}
