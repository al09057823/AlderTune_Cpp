#include "Act.h"
#include <iostream> 
using namespace std;

Act::Act(int id, const string& description, int mercyImpact)
{
    this -> id = id;
    this -> description = description;
    this -> mercyImpact = mercyImpact;
}

int Act::getId() const
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