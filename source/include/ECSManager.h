#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include <SFML/Graphics.hpp>
#include "Systems/DrawableSystem.h"

class ECSManager
{
    public:
        ECSManager();
        virtual ~ECSManager();

        void Draw(sf::RenderWindow&);
        void Think(sf::Time dt); //we want to do all think operations before we do any drawing etc

    protected:

    private:
        DrawableSystem drawableSystem;
};

#endif // ECSMANAGER_H
