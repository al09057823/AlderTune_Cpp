#include "Player.h"
#include "Monster.h"
#include "Combat.h"
#include "bestiary.h"
#include "item.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <limits>

using namespace std;

string trim(const string& text)
{
    size_t start = text.find_first_not_of(" \t\r\n");
    size_t end = text.find_last_not_of(" \t\r\n");

    if (start == string::npos)
    {
        return "";
    }

    return text.substr(start, end - start + 1);
}

vector<string> split(const string& line, char separator)
{
    vector<string> parts;
    string part;
    stringstream ss(line);

    while (getline(ss, part, separator))
    {
        parts.push_back(trim(part));
    }

    return parts;
}

int askChoice(int min, int max)
{
    int choice;

    while (true)
    {
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entree invalide. Reessaie : ";
        }
        else if (choice < min || choice > max)
        {
            cout << "Choix invalide. Reessaie : ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

vector<Item> loadItemsFromCsv(const string& filename)
{
    vector<Item> items;
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Erreur : impossible d'ouvrir le fichier " << filename << endl;
        exit(1);
    }

    string line;

    // Ignore la ligne d'en-tete
    getline(file, line);

    while (getline(file, line))
    {
        if (trim(line).empty())
        {
            continue;
        }

        vector<string> parts = split(line, ';');

        if (parts.size() != 4)
        {
            cout << "Ligne mal formee dans " << filename << " : " << line << endl;
            continue;
        }

        string name = parts[0];
        string type = parts[1];
        int value = stoi(parts[2]);
        int quantity = stoi(parts[3]);

        items.push_back(Item(name, type, value, quantity));
    }

    return items;
}

Monster* createMonsterFromParts(const vector<string>& parts)
{
    string category = parts[0];
    string name = parts[1];
    int hp = stoi(parts[2]);
    int atk = stoi(parts[3]);
    int def = stoi(parts[4]);
    int mercyGoal = stoi(parts[5]);

    vector<string> actIds;

    for (size_t i = 6; i < parts.size(); i++)
    {
        if (parts[i] != "-")
        {
            actIds.push_back(parts[i]);
        }
    }

    if (category == "NORMAL")
    {
        return new NormalMonster(name, hp, atk, def, mercyGoal, actIds);
    }
    else if (category == "MINIBOSS")
    {
        return new MiniBoss(name, hp, atk, def, mercyGoal, actIds);
    }
    else if (category == "BOSS")
    {
        return new Boss(name, hp, atk, def, mercyGoal, actIds);
    }

    cout << "Categorie inconnue pour le monstre : " << category << endl;
    return nullptr;
}

vector<Monster*> loadMonstersFromCsv(const string& filename)
{
    vector<Monster*> monsters;
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Erreur : impossible d'ouvrir le fichier " << filename << endl;
        exit(1);
    }

    string line;

    // Ignore la ligne d'en-tete
    getline(file, line);

    while (getline(file, line))
    {
        if (trim(line).empty())
        {
            continue;
        }

        vector<string> parts = split(line, ';');

        if (parts.size() != 10)
        {
            cout << "Ligne mal formee dans " << filename << " : " << line << endl;
            continue;
        }

        Monster* monster = createMonsterFromParts(parts);

        if (monster != nullptr)
        {
            monsters.push_back(monster);
        }
    }

    if (monsters.empty())
    {
        cout << "Erreur : aucun monstre charge." << endl;
        exit(1);
    }

    return monsters;
}

void showMainMenu()
{
    cout << "\n===== MENU PRINCIPAL =====" << endl;
    cout << "1. Bestiaire" << endl;
    cout << "2. Demarrer un combat" << endl;
    cout << "3. Statistiques du personnage" << endl;
    cout << "4. Items" << endl;
    cout << "5. Quitter" << endl;
    cout << "Choix : ";
}

void showEnding(const Player& player)
{
    cout << "\n===== FIN DE PARTIE =====" << endl;

    if (player.getKills() == 10 && player.getSpared() == 0)
    {
        cout << "Fin Genocidaire." << endl;
        cout << "Tu as tue tous les monstres rencontres." << endl;
    }
    else if (player.getSpared() == 10 && player.getKills() == 0)
    {
        cout << "Fin Pacifiste." << endl;
        cout << "Tu as epargne tous les monstres rencontres." << endl;
    }
    else
    {
        cout << "Fin Neutre." << endl;
        cout << "Tu as parfois combattu, parfois epargne." << endl;
    }
}

void useItemOutsideCombat(Player& player)
{
    player.showInventory();

    if (player.getInventory().empty())
    {
        return;
    }

    cout << "\nVeux-tu utiliser un item ?" << endl;
    cout << "1. Oui" << endl;
    cout << "2. Non" << endl;
    cout << "Choix : ";

    int choice = askChoice(1, 2);

    if (choice == 2)
    {
        return;
    }

    cout << "Numero de l'item : ";
    int itemChoice = askChoice(1, static_cast<int>(player.getInventory().size()));

    player.useItem(itemChoice - 1);
}

Monster* cloneMonster(const Monster* original)
{
    vector<string> acts = original->getActIds();

    if (original->getCategory() == "NORMAL")
    {
        return new NormalMonster(
            original->getName(),
            original->getMaxHp(),
            original->getAtk(),
            original->getDef(),
            original->getMercyGoal(),
            acts
        );
    }
    else if (original->getCategory() == "MINIBOSS")
    {
        return new MiniBoss(
            original->getName(),
            original->getMaxHp(),
            original->getAtk(),
            original->getDef(),
            original->getMercyGoal(),
            acts
        );
    }
    else
    {
        return new Boss(
            original->getName(),
            original->getMaxHp(),
            original->getAtk(),
            original->getDef(),
            original->getMercyGoal(),
            acts
        );
    }
}

void startRandomCombat(Player& player, vector<Monster*>& monsters, Bestiary& bestiary)
{
    static mt19937 rng(random_device{}());

    uniform_int_distribution<int> distribution(0, static_cast<int>(monsters.size()) - 1);
    int index = distribution(rng);

    Monster* monster = cloneMonster(monsters[index]);

    Combat combat(player, *monster, bestiary);
    bool playerWon = combat.start();

    delete monster;

    if (!playerWon)
    {
        cout << "\nGAME OVER." << endl;
    }
}

void showGameSummary(const Player& player)
{
    cout << "\n===== PARTIE CHARGEE =====" << endl;
    cout << "Joueur : " << player.getName() << endl;
    cout << "HP : " << player.getHp() << "/" << player.getMaxHp() << endl;
    cout << "\nItems disponibles :" << endl;

    const vector<Item>& inventory = player.getInventory();

    if (inventory.empty())
    {
        cout << "Aucun item." << endl;
        return;
    }

    for (size_t i = 0; i < inventory.size(); i++)
    {
        cout << "- " << inventory[i].getName()
             << " x" << inventory[i].getQuantity()
             << " (" << inventory[i].getValue() << " HP)"
             << endl;
    }
}

int main()
{
    cout << "===== ALTERDUNE =====" << endl;

    string playerName;
    cout << "Entre le nom de ton personnage : ";
    getline(cin, playerName);

    if (playerName.empty())
    {
        playerName = "Player";
    }

    Player player(playerName);

    vector<Item> items = loadItemsFromCsv("items.csv");
    vector<Monster*> monsters = loadMonstersFromCsv("monsters.csv");

    player.setInventory(items);

    Bestiary bestiary;

    showGameSummary(player);

    bool running = true;

    while (running && player.isAlive() && player.getVictories() < 10)
    {
        showMainMenu();

        int choice = askChoice(1, 5);

        if (choice == 1)
        {
            bestiary.showBestiary();
        }
        else if (choice == 2)
        {
            startRandomCombat(player, monsters, bestiary);
        }
        else if (choice == 3)
        {
            player.showStats();
        }
        else if (choice == 4)
        {
            useItemOutsideCombat(player);
        }
        else if (choice == 5)
        {
            running = false;
        }
    }

    if (player.getVictories() >= 10)
    {
        showEnding(player);
    }
    else if (!player.isAlive())
    {
        cout << "\nLa partie est terminee : tu as perdu." << endl;
    }
    else
    {
        cout << "\nTu as quitte la partie." << endl;
    }

    for (Monster* monster : monsters)
    {
        delete monster;
    }

    return 0;
}