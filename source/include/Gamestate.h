#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>

#include "Sound.h"

#include "Components/DrawableComponent.h"
#include "Components/PhysicsComponent.h"

class Gamestate
{
public:
    Gamestate();
    //holds the sounds
    std::map<std::string, Sound*> sounds;

    std::shared_ptr<DrawableComponent> GetDrawable(std::string);
    //we need a map of each type of component, with a vector for drawables so we can have a draw order
    std::vector<std::shared_ptr<DrawableComponent>> drawableComponents;
    std::map<std::string, int> drawableComponentsLocations;
    std::vector<std::shared_ptr<PhysicsComponent>> physicsComponents;

    //each gamestate will have its own set of views so rather than using another manager etc we hold them here
    std::vector<std::pair<std::string,sf::View>> views;

    bool GetPaused();
    void SetPaused(bool);

    //views
    sf::View GetView(std::string ID);
    void AddView(std::string ID, sf::View);
    void RemoveView(std::string ID);
    void SetView(std::string ID, sf::View view);

    void MoveViewToTop(std::string ID);
    void MoveViewToBot(std::string ID);
    void MoveViewUp(std::string ID);
    void MoveViewDown(std::string ID);

private:

    //allow for pausing
    bool paused;
};

#endif // GAMESTATE_H
