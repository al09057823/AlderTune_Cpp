#include "Monster.h"
#include <iostream>
using namespace std;

Monster::Monster(const string& category, int mercy, int mercyGoal, const string& actList)
{
    this -> category = category;
    this -> mercy = mercy;
    this -> mercyGoal = mercyGoal;
    this -> actList = actList;
}

string Monster::getCategory() const
{
    return category;
}

int Monster::getMercy() const
{
    return mercy;
}

int Monster::getMercyGoal() const
{
    return mercyGoal;
}

string Monster::getActList() const
{
    return actList;
}