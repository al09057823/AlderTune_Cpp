#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(const string& name)
    : Entity(name, 100, 50, 5), victories(0), kills(0), spared(0)
{
}

string Player::getTypeName() const
{
    return "Player";
}

vector<Item>& Player::getInventory()
{
    return inventory;
}

const vector<Item>& Player::getInventory() const
{
    return inventory;
}

int Player::getVictories() const
{
    return victories;
}

int Player::getKills() const
{
    return kills;
}

int Player::getSpared() const
{
    return spared;
}

void Player::setInventory(const vector<Item>& items)
{
    inventory = items;
}

void Player::addVictory()
{
    victories++;
}

void Player::addKill()
{
    kills++;
}

void Player::addSpare()
{
    spared++;
}

void Player::showStats() const
{
    cout << "\n===== STATISTIQUES DU JOUEUR =====" << endl;
    cout << "Nom : " << getName() << endl;
    cout << "HP : " << getHp() << "/" << getMaxHp() << endl;
    cout << "ATK : " << getAtk() << endl;
    cout << "DEF : " << getDef() << endl;
    cout << "Victoires : " << getVictories() << "/10" << endl;
    cout << "Monstres tues : " << getKills() << endl;
    cout << "Monstres epargnes : " << getSpared() << endl;
}

void Player::showInventory() const
{
    cout << "\n===== INVENTAIRE =====" << endl;

    if (inventory.empty())
    {
        cout << "Aucun item." << endl;
        return;
    }

    for (size_t i = 0; i < inventory.size(); i++)
    {
        cout << i + 1 << ". "
             << inventory[i].getName()
             << " | Type : " << inventory[i].getType()
             << " | Soin : " << inventory[i].getValue() << " HP"
             << " | Quantite : " << inventory[i].getQuantity()
             << endl;
    }
}

bool Player::useItem(int index)
{
    if (index < 0 || index >= static_cast<int>(inventory.size()))
    {
        cout << "Choix invalide." << endl;
        return false;
    }

    Item& item = inventory[index];

    if (!item.isAvailable())
    {
        cout << "Cet item n'est plus disponible dans votre inventaire." << endl;
        return false;
    }

    if (item.getType() == "HEAL")
    {
        int hpBefore = getHp();

        heal(item.getValue());
        item.useOne();

        cout << "Tu utilises " << item.getName() << "." << endl;
        cout << "HP : " << hpBefore << " -> " << getHp() << "/" << getMaxHp() << endl;

        return true;
    }

    cout << "Type d'item inconnu." << endl;
    return false;
}