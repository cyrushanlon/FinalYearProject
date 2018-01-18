#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

class GamestateManager
{
public:
    Gamestate GetState(std::string);
private:
    std::string currentState;
    std::map<std::string, Gamestate> states;
};

#endif // GAMESTATEMANAGER_H
