#include "Act.h"
#include <iostream> 
using namespace std;

Act::Act()
    : id(""), description(""), mercyImpact(0)
{
}

Act::Act(const string& id, const string& description, int mercyImpact)
    : id(id), description(description), mercyImpact(mercyImpact)
{
}

string Act::getId() const
{
    return id;
}

string Act::getDescription() const
{
    return description;
}

int Act::getMercyImpact() const
{
    return mercyImpact;
}