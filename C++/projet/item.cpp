#include "item.h"
#include "Player.h"

Item::Item() 
    : name(""), type("HEAL"), value(0), quantity(0)
{
}

Item::Item(const string& name, const string& type, int value, int quantity)
    : name(name), type(type), value(value), quantity(quantity)
{
}

string Item::getName() const
{
    return name;
}

string Item::getType() const
{
    return type;
}

int Item::getValue() const
{
    return value;
}

int Item::getQuantity() const
{
    return quantity;
}

void Item::setQuantity(int newQuantity)
{
    if (newQuantity < 0)
    {
        quantity = 0;
    }
    else
    {
        quantity = newQuantity;
    }
}

bool Item::isAvailable() const
{
    return quantity > 0;
}

void Item::useOne()
{
    if (quantity > 0)
    {
        quantity--;
    }
}