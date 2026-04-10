#ifndef ACT_H
#define ATC_H

#include <string>
using namespace std;

class Act 
{
private :
    int id;
    string description;
    int mercyImpact;

public :
    Act(int id, const string& description, int mercyImpact);

    int getId() const;
    string getDescription() const;
    int getMercyImpact() const;
};

#endif