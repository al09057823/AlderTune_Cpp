#ifndef COMBAT_H
#define COMBAT_H

#include <string>
#include "Player.h"
#include "Monster.h"
using namespace std;

class Combat: public Player, public Monster
{
private :
    Player player;
    Monster monster;
    
public :
    Combat(Player player, Monster monster);

    Player getPlayer() const;
    Monster getMonster() const;
};

#endif