#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(Item item, const string& inventory, int kills, int spared, int victories)
{
    this -> item = item;
    this -> inventory = inventory;
    this -> kills = kills;
    this -> spared = spared;
    this -> victories = victories;
}

Item Player::getItem() const
{
    return item;
}

string Player::getInventory() const
{
    return inventory;
}

int Player::getKills() const
{
    return kills;
}

int Player::getSpared() const
{
    return spared;
}

int Player::getVictories() const
{
    return victories;
}