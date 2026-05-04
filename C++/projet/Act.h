#ifndef ACT_H
#define ACT_H

#include <string>
using namespace std;

class Act 
{
private :
    string id;
    string description;
    int mercyImpact;

public :
    Act();
    Act(const string& id, const string& description, int mercyImpact);

    string getId() const;
    string getDescription() const;
    int getMercyImpact() const;
};

#endif