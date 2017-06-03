#include "Dog.h"

#include <string>
#include <iostream>

Dog::Dog(std::string name)
{
    this->name = name;
}

void Dog::Talk(std::string words)
{
    std::cout << this->name << " said " << words;
}
