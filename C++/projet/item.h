#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;


class Player;

class Item
{
private:
    string name;
    string type;
    int value;
    int quantity;

public:
    Item();
    Item(const string& name, const string& type, int value, int quantity);

    string getName() const;
    string getType() const;
    int getValue() const;
    int getQuantity() const;
    
};

#endif