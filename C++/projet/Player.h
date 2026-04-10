#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "item.h"
using namespace std;

class Player
{
private: 
    Item item;
    string inventory;
    int kills;
    int spared;
    int victories;

public:
    Player(Item item, const string& inventory, int kills, int spared, int victories);

    Item getItem() const;
    string getInventory() const;
    int getKills() const;
    int getSpared() const;
    int getVictories() const;
};

#endif