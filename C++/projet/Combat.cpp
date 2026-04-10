#include "Combat.h"
#include "Monster.h"
#include "Player.h"
#include <iostream>
using namespace std;

Combat::Combat(Player player, Monster monster)
{
    this -> player = player;
    this -> monster = monster;
}

Player Combat::getPlayer() const
{
    return player;
}

Monster Combat::getMonster() const
{
    return monster;
}