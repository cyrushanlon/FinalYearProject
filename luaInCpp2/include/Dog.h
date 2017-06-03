#ifndef DOG_H
#define DOG_H

#include <string>

class Dog {

public:
    Dog(std::string);

    void Talk(std::string);

private:
    std::string name;
};

#endif // DOG_H
