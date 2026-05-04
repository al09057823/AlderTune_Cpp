#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "item.h"
#include <vector>
#include <string>

using namespace std;

class Player : public Entity
{
private:
    vector<Item> inventory;
    int victories;
    int kills;
    int spared;

public:
    Player(const string& name);

    string getTypeName() const override;

    vector<Item>& getInventory();
    const vector<Item>& getInventory() const;

    int getVictories() const;
    int getKills() const;
    int getSpared() const;

    void setInventory(const vector<Item>& items);

    void addVictory();
    void addKill();
    void addSpare();

    void showStats() const;
    void showInventory() const;
    bool useItem(int index);
};

#endif