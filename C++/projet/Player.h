#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player
{
private:
    string name;
    int hp;

public:
    Player(const string& name, int hp);

    string getName() const;
    int getHp() const;

    void afficher() const;
};

#endif