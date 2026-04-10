#include "Entity.h"
#include <algorithm>
using namespace std;

Entity::Entity(const string& name, int hp, int maxHp, int atk, int def)
{
    this -> name = name;
    this -> hp = hp;
    this -> maxHp = maxHp;
    this -> atk = atk;
    this -> def = def;
}

string Entity::getName() const
{
    return name;
}

int Entity::getHp() const
{
    return hp;
}

int Entity::getMaxHp() const
{
    return maxHp;
}

int Entity::getAtk() const
{
    return atk;
}

int Entity::getDef() const
{
    return def;
}
