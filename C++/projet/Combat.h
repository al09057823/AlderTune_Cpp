#ifndef COMBAT_H
#define COMBAT_H

#include "Player.h"
#include "Monster.h"
#include "Act.h"
#include "bestiary.h"

#include <map>
#include <random>
#include <string>

using namespace std;

class Combat
{
private:
    Player& player;
    Monster& monster;
    Bestiary& bestiary;

    map<string, Act> actCatalog;
    mt19937 rng;

public:
    Combat(Player& player, Monster& monster, Bestiary& bestiary);

    bool start();

private:
    void initializeActCatalog();

    void showCombatStatus() const;
    void showCombatMenu() const;

    int randomDamage(int maxHp);
    void playerFight();
    bool playerAct();
    bool playerItem();
    bool playerMercy();

    void monsterTurn();

    int askChoice(int min, int max);
};

#endif