#ifndef BESTIARY_H
#define BESTIARY_H

#include <string>
using namespace std;

class Bestiary 
{
private :
    string defeatedMonsters;

public :
    Bestiary(const string& defeatedMonsters);
    
    string getDefeatedMonsters() const;
};

#endif