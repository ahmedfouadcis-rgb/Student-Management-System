#include "Person.h"

Person::Person(string name)
{
    this->name = name;
}

string Person::getName() const
{
    return name;
}

void Person::setName(string n)
{
    name = n;
}
