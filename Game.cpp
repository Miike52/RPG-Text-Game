#include <iostream>
#include <string>

using namespace std;

class Character {
public:
    string name;
    string characterClass;
    string gender;
    int healthPoints = 100;
    int attackDamage = 10;

    Character(string n, string cls, string g) : name(n), characterClass(cls), gender(g) {}

    void attack(Character &monster) {
        cout << name << " attacks " << monster.name << " for " << attackDamage << " damage!" << endl;
        monster.healthPoints -= attackDamage;
    }
};

class Monster {
public:
    string name;
    int healthPoints;
    int attackDamage;

    Monster(string n, int hp, int ad) : name(n), healthPoints(hp), attackDamage(ad) {}
};

void introduction(Character &player) {
    if (player.characterClass == "Warrior") {
        cout << "As a fierce Warrior, you fight for honor and strength." << endl;
    } else if (player.characterClass == "Mage") {
        cout << "As a wise Mage, you wield the powers of the arcane." << endl;
    } else if (player.characterClass == "Dwarf") {
        cout << "As a sturdy Dwarf, you are known for your craftsmanship and bravery." << endl;
    } else if (player.characterClass == "Elf") {
        cout << "As a graceful Elf, you excel in agility and magic." << endl;
    } else if (player.characterClass == "Rogue") {
        cout << "As a cunning Rogue, you rely on stealth and agility." << endl;
    }
}

int main() {
    string name, characterClass, gender;
    const string artifactName = "Ancient Crystal";
    const string artifactLocation = "Temple of Ancients";

    cout << "Welcome to the RPG Text Game!" << endl;
    cout << "Enter your character's name: ";
    getline(cin, name);

    cout << "Choose your character class (Warrior, Mage, Dwarf, Elf, Rogue): ";
    getline(cin, characterClass);

    cout << "Choose your character's gender (male, female, other): ";
    getline(cin, gender);

    Character player(name, characterClass, gender);
    introduction(player);

    cout << "Your mission is to retrieve the " << artifactName << " located in the " << artifactLocation << "!" << endl;

    for (int round = 1; round <= 10; ++round) {
        Monster monster("Monster " + to_string(round), 100, 5 + (round - 1) * 2);
        
        cout << "\nRound " << round << ": A " << monster.name << " appears!" << endl;

        while (player.healthPoints > 0 && monster.healthPoints > 0) {
            player.attack(monster);
            cout << monster.name << " has " << monster.healthPoints << " HP left." << endl;

            if (monster.healthPoints > 0) {
                cout << monster.name << " attacks " << player.name << " for " << monster.attackDamage << " damage!" << endl;
                player.healthPoints -= monster.attackDamage;
                cout << player.name << " has " << player.healthPoints << " HP left." << endl;
            }
        }

        if (player.healthPoints <= 0) {
            cout << "You have been defeated! Game Over!" << endl;
            return 0;
        } else {
            cout << "You have defeated " << monster.name << "!" << endl;
            player.attackDamage += 5; // Increase player damage after defeating a monster
        }
    }

    cout << "\nCongratulations, " << player.name << "! You have defeated all monsters and retrieved the " << artifactName << "!" << endl;

    return 0;
}
