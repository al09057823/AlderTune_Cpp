#ifndef BESTIARY_H
#define BESTIARY_H

#include "Monster.h"
#include <string>
#include <vector>
using namespace std;

class Bestiary 
{
private :
    vector<string> entries;

public :
    void addMonster(const Monster& monster, const string& result);
    void showBestiary() const;
};

#endif