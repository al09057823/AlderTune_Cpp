#include "Entity.h"
#include <algorithm>
using namespace std;

Entity::Entity(const string& name, int maxHp, int atk, int def)
    : name(name), hp(maxHp), maxHp(maxHp), atk(atk), def(def)
{
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

void Entity::setCurrentHp(int newHp)
{
    if (newHp < 0)
    {
        hp = 0;
    }
    else if (newHp > maxHp)
    {
        hp = maxHp;
    }
    else
    {
        hp = newHp;
    }
}

void Entity::takeDamage(int damage)
{
    if (damage < 0)
    {
        damage = 0;
    }

    setCurrentHp(hp - damage);
}

void Entity::heal(int amount)
{
    if (amount < 0)
    {
        amount = 0;
    }

    setCurrentHp(hp + amount);
}

bool Entity::isAlive() const
{
    return hp > 0;
}