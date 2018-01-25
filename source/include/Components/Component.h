#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    Component(std::string ID)
    {
        this->name = ID;
    }

    std::string Name()
    {
        return this->name;
    }
private:
    std::string name;
};

#endif //COMPONENT_H
