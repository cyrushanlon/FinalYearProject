#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "Gamestate.h"

class GamestateManager
{
public:
    void SetState(std::string);
    std::shared_ptr<Gamestate> CreateState(std::string ID);
    std::shared_ptr<Gamestate> GetState(std::string);
    std::shared_ptr<Gamestate> CurrentState();
private:
    std::string currentState;
    std::map<std::string, std::shared_ptr<Gamestate> > states;
};

#endif // GAMESTATEMANAGER_H
