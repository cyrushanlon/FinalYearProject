#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include <SFML/Graphics.hpp>
#include "Systems/DrawableSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/TextSystem.h"

class ECSManager
{
    public:
        ECSManager();
        virtual ~ECSManager();

        void Draw(sf::RenderWindow&);
        void Think(sf::Time dt); //we want to do all think operations before we do any drawing etc

    protected:

    private:
        DrawableSystem drawables;
        PhysicsSystem physics;
        TextSystem text;
};

#endif // ECSMANAGER_H
