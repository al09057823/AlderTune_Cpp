#ifndef MONSTER_H
#define MONSTER_H

#include <string>
using namespace std;

class Monster
{
private :
    string category;
    int mercy;
    int mercyGoal;
    string actList;

public :
    Monster(const string& category, int mercy, int mercyGoal, const string& actList);
    
    string getCategory() const;
    int getMercy() const;
    int getMercyGoal() const;
    string getActList() const;
};

#endif