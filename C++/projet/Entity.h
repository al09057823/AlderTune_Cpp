#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity
{
private:
    string name;
    int hp;
    int maxHp;
    int atk;
    int def;

public:
    Entity(const string& name, int hp, int maxHp, int atk, int def);

    string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getAtk() const;
    int getDef() const;

};

#endif