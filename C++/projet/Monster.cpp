#include "Monster.h"
#include <iostream>
using namespace std;

Monster::Monster(const string& name, const string& category, int MaxHp, int atk, int def, int mercyGoal, const vector<string>& actIds)
    : Entity(name, MaxHp, atk, def), category(category), mercy(0), mercyGoal(mercyGoal), actIds(actIds)
{
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

vector<string> Monster::getActIds() const
{
    return actIds;
}

void Monster::changeMercy(int amount)
{
    mercy += amount;

    if (mercy < 0)
    {
        mercy = 0;
    }
    else if (mercy > mercyGoal)
    {
        mercy = mercyGoal;
    }
}

bool Monster::canBeSpared() const
{
    return mercy >= mercyGoal;
}

string Monster::getTypeName() const
{
    return "Monster";
}


NormalMonster::NormalMonster(const string& name, int maxHp, int atk, int def, int mercyGoal, const vector<string>& actIds)
    : Monster(name, "NORMAL", maxHp, atk, def, mercyGoal, actIds)   
{
}

int NormalMonster::getNumberOfActs() const
{
    return 2;
}

MiniBoss::MiniBoss(const string& name, int maxHp, int atk, int def, int mercyGoal, const vector<string>& actIds)    
    : Monster(name, "MINIBOSS", maxHp, atk, def, mercyGoal, actIds)
{
}

int MiniBoss::getNumberOfActs() const
{
    return 3;
}


Boss::Boss(const string& name, int maxHp, int atk, int def, int mercyGoal, const vector<string>& actIds)
    : Monster(name, "BOSS", maxHp, atk, def, mercyGoal, actIds)
{
}

int Boss::getNumberOfActs() const
{
    return 4;
}