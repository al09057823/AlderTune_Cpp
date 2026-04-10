#include "bestiary.h"
#include <iostream>
using namespace std;

Bestiary::Bestiary(const string& defeatedMonsters)
{
    this -> defeatedMonsters = defeatedMonsters;
}

string Bestiary::getDefeatedMonsters() const
{
    return defeatedMonsters;
}