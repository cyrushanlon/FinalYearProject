#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Window.hpp>

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();

        void AddEvent(sf::Event, bool);
    protected:

    private:

};

#endif // INPUTMANAGER_H
