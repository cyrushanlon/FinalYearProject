#include "Dog.h"

#include <string>
#include <iostream>

//declaration of the C++ class member variables

Dog::Dog(std::string name)
{
    this->name = name;
}

void Dog::Talk(std::string words)
{
    std::cout << "from C++: " <<this->name << " said " << words;
}

std::string Dog::GetName()
{
    return this->name;
}
