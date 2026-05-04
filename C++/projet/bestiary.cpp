#include "bestiary.h"
#include <iostream>
#include <string>

using namespace std;

void Bestiary::addMonster(const Monster& monster, const string& result)
{
    string entry;

    entry = "Nom : " + monster.getName() + "\n";
    entry += "Categorie : " + monster.getCategory() + "\n";
    entry += "HP max : " + to_string(monster.getMaxHp()) + "\n";
    entry += "ATK : " + to_string(monster.getAtk()) + "\n";
    entry += "DEF : " + to_string(monster.getDef()) + "\n";
    entry += "Resultat : " + result + "\n";

    entries.push_back(entry);
}

void Bestiary::showBestiary() const
{
    cout << "\n===== BESTIAIRE =====" << endl;

    if (entries.empty())
    {
        cout << "Aucun monstre vaincu pour le moment." << endl;
        return;
    }

    for (size_t i = 0; i < entries.size(); i++)
    {
        cout << "\nMonstre #" << i + 1 << endl;
        cout << entries[i];
    }
}