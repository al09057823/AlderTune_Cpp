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
    Entity(const string& name, int maxHp, int atk, int def);
    virtual ~Entity() = default;

    virtual string getTypeName() const = 0;

    string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getAtk() const;
    int getDef() const;

    void setCurrentHp(int hp);
    void takeDamage(int damage);
    void heal(int amount);

    bool isAlive() const;

};

#endif