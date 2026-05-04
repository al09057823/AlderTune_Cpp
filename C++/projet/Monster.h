#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include <string>
#include <vector>
using namespace std;

class Monster : public Entity
{
private :
    string category;
    int mercy;
    int mercyGoal;
    vector<string> actIds;

public :
    Monster(const string& category, const string& name, int maxHp, int atk, int def, int mercyGoal, const vector<string>& actIds);

    virtual ~Monster() = default;

    string getCategory() const;
    int getMercy() const;
    int getMercyGoal() const;
    vector<string> getActIds() const;

    void changeMercy(int amount);
    bool canBeSpared() const;

    virtual int getNumberOfActs() const = 0;
    virtual string getTypeName() const override;
};

class NormalMonster : public Monster
{
public:
    NormalMonster(
        const string& name,
        int maxHp,
        int atk,
        int def,
        int mercyGoal,
        const vector<string>& actIds
    );

    int getNumberOfActs() const override;
};

class MiniBoss : public Monster
{
public:
    MiniBoss(
        const string& name,
        int maxHp,
        int atk,
        int def,
        int mercyGoal,
        const vector<string>& actIds
    );

    int getNumberOfActs() const override;
};

class Boss : public Monster
{
public:
    Boss(
        const string& name,
        int maxHp,
        int atk,
        int def,
        int mercyGoal,
        const vector<string>& actIds
    );

    int getNumberOfActs() const override;
};

#endif