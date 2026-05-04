#include "Combat.h"

#include <iostream>
#include <limits>

using namespace std;

Combat::Combat(Player& player, Monster& monster, Bestiary& bestiary)
    : player(player), monster(monster), bestiary(bestiary), rng(random_device{}())
{
    initializeActCatalog();
}

void Combat::initializeActCatalog()
{
    actCatalog["COMPLIMENT"] = Act(
        "COMPLIMENT",
        "Tu complimentes le monstre. Il rougit un peu.",
        25
    );

    actCatalog["DISCUSS"] = Act(
        "DISCUSS",
        "Tu discutes calmement avec le monstre. Il semble t'ecouter.",
        20
    );

    actCatalog["JOKE"] = Act(
        "JOKE",
        "Tu racontes une blague absurde. Le monstre ne comprend pas, mais il rit quand meme.",
        30
    );

    actCatalog["DANCE"] = Act(
        "DANCE",
        "Tu fais une danse ridicule. Le monstre applaudit timidement.",
        25
    );

    actCatalog["OBSERVE"] = Act(
        "OBSERVE",
        "Tu observes le monstre. Il se sent enfin compris.",
        15
    );

    actCatalog["PET"] = Act(
        "PET",
        "Tu essaies de caresser le monstre. Etrangement, ca marche.",
        30
    );

    actCatalog["OFFER_SNACK"] = Act(
        "OFFER_SNACK",
        "Tu offres un snack imaginaire. Le monstre apprecie l'intention.",
        35
    );

    actCatalog["REASON"] = Act(
        "REASON",
        "Tu expliques pourquoi se battre ne sert a rien. Le monstre reflechit.",
        25
    );

    actCatalog["INSULT"] = Act(
        "INSULT",
        "Tu insultes le monstre. Il devient furieux.",
        -30
    );

    actCatalog["THREATEN"] = Act(
        "THREATEN",
        "Tu menaces le monstre. Il se crispe et refuse de t'ecouter.",
        -25
    );
}

void Combat::showCombatStatus() const
{
    cout << "\n===== COMBAT =====" << endl;
    cout << player.getName() << " HP : "
         << player.getHp() << "/" << player.getMaxHp() << endl;

    cout << monster.getName() << " HP : "
         << monster.getHp() << "/" << monster.getMaxHp() << endl;

    cout << "Mercy : "
         << monster.getMercy() << "/" << monster.getMercyGoal() << endl;
}

void Combat::showCombatMenu() const
{
    cout << "\nQue veux-tu faire ?" << endl;
    cout << "1. FIGHT" << endl;
    cout << "2. ACT" << endl;
    cout << "3. ITEM" << endl;
    cout << "4. MERCY" << endl;
    cout << "Choix : ";
}

int Combat::askChoice(int min, int max)
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

int Combat::randomDamage(int maxHp)
{
    uniform_int_distribution<int> distribution(0, maxHp);
    return distribution(rng);
}

void Combat::playerFight()
{
    int damage = randomDamage(monster.getMaxHp());

    cout << "\nTu attaques " << monster.getName() << " !" << endl;

    if (damage == 0)
    {
        cout << "Coup rate ! Aucun degat." << endl;
    }
    else
    {
        monster.takeDamage(damage);
        cout << "Tu infliges " << damage << " degats." << endl;
    }

    if (!monster.isAlive())
    {
        cout << monster.getName() << " a ete vaincu." << endl;
    }
}

bool Combat::playerAct()
{
    vector<string> actIds = monster.getActIds();
    int numberOfActs = monster.getNumberOfActs();

    cout << "\n===== ACT =====" << endl;

    for (int i = 0; i < numberOfActs && i < static_cast<int>(actIds.size()); i++)
    {
        cout << i + 1 << ". " << actIds[i] << endl;
    }

    cout << "Choisis une action ACT : ";
    int choice = askChoice(1, numberOfActs);

    string selectedActId = actIds[choice - 1];

    if (actCatalog.find(selectedActId) == actCatalog.end())
    {
        cout << "Action inconnue dans le catalogue : " << selectedActId << endl;
        return false;
    }

    Act selectedAct = actCatalog[selectedActId];

    cout << "\n" << selectedAct.getId() << endl;

    int beforeMercy = monster.getMercy();
    monster.changeMercy(selectedAct.getMercyImpact());

    cout << "Mercy : "
         << beforeMercy << " -> "
         << monster.getMercy() << "/"
         << monster.getMercyGoal() << endl;

    return true;
}

bool Combat::playerItem()
{
    cout << "\n===== ITEM =====" << endl;

    player.showInventory();

    vector<Item>& inventory = player.getInventory();

    if (inventory.empty())
    {
        cout << "Tu n'as aucun item." << endl;
        return false;
    }

    cout << "Choisis un item a utiliser : ";
    int choice = askChoice(1, static_cast<int>(inventory.size()));

    return player.useItem(choice - 1);
}

bool Combat::playerMercy()
{
    cout << "\nTu tentes d'epargner " << monster.getName() << "." << endl;

    if (monster.canBeSpared())
    {
        cout << monster.getName() << " accepte d'arreter le combat." << endl;
        return true;
    }

    cout << "La Mercy n'est pas encore assez élevée." << endl;
    return false;
}

void Combat::monsterTurn()
{
    if (!monster.isAlive())
    {
        return;
    }

    cout << "\n--- Tour de " << monster.getName() << " ---" << endl;

    int damage = randomDamage(player.getMaxHp());

    if (damage == 0)
    {
        cout << monster.getName() << " rate son attaque." << endl;
    }
    else
    {
        player.takeDamage(damage);
        cout << monster.getName() << " inflige "
             << damage << " degats." << endl;
    }

    if (!player.isAlive())
    {
        cout << "\nTu es tombe a 0 HP..." << endl;
        cout << "Defaite immediate." << endl;
    }
}

bool Combat::start()
{
    cout << "\nUn combat commence contre "
         << monster.getName()
         << " [" << monster.getCategory() << "] !"
         << endl;

    while (player.isAlive() && monster.isAlive())
    {
        showCombatStatus();
        showCombatMenu();

        int choice = askChoice(1, 4);
        bool turnConsumed = false;
        bool sparedMonster = false;

        if (choice == 1)
        {
            playerFight();
            turnConsumed = true;
        }
        else if (choice == 2)
        {
            turnConsumed = playerAct();
        }
        else if (choice == 3)
        {
            turnConsumed = playerItem();
        }
        else if (choice == 4)
        {
            sparedMonster = playerMercy();

            if (sparedMonster)
            {
                player.addVictory();
                player.addSpare();
                bestiary.addMonster(monster, "Epargne");
                return true;
            }

            turnConsumed = true;
        }

        if (!monster.isAlive())
        {
            player.addVictory();
            player.addKill();
            bestiary.addMonster(monster, "Tue");
            return true;
        }

        if (turnConsumed)
        {
            monsterTurn();
        }
    }

    return player.isAlive();
}