#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <chrono>  // For timer (sleep)
#include <thread>  // For sleep
#include <conio.h> // For detecting keypresses (Windows)

using namespace std;

class Monster; // Forward declaration

class Character {
public:
    string name;
    string characterClass;
    string gender;
    int healthPoints = 100;
    int attackDamage = 10;

    Character(string n, string cls, string g) : name(n), characterClass(cls), gender(g) {}

    void attack(Monster& monster); // Declare it here for Monster
};

class Monster {
public:
    string name;
    int healthPoints;
    int attackDamage;

    Monster(string n, int hp, int ad) : name(n), healthPoints(hp), attackDamage(ad) {}
};

// Define attack outside of class Character
void Character::attack(Monster& monster) {
    cout << name << " attacks " << monster.name << " for " << attackDamage << " damage!" << endl;
    monster.healthPoints -= attackDamage;
    if (monster.healthPoints < 0) monster.healthPoints = 0; // Avoid negative HP
    cout << endl; // Add extra space between each output
    cout << endl;
}

// Random Encounter Function
void randomEncounter(Character& player) {
    // 30% chance of finding something
    int encounterChance = rand() % 100;

    if (encounterChance < 30) { // 30% probability for an encounter
        int rewardType = rand() % 2; // Decide if it's health or attack damage

        if (rewardType == 0) {
            // Temporary health boost
            int healthBoost = 20;
            player.healthPoints += healthBoost;
            cout << "You found an enchanted potion! Temporary health boost of " << healthBoost << " HP!" << endl;
        }
        else {
            // Attack damage boost
            int damageBoost = 5;
            player.attackDamage += damageBoost;
            cout << "You discovered a powerful artifact! Your attack damage increases by " << damageBoost << "!" << endl;
        }
    }
    else {
        cout << "No encounter this time. Continue on your quest!" << endl;
    }
    cout << endl; // Add extra space between each output
}

void introduction(Character& player) {
    if (player.characterClass == "Warrior") {
        cout << "As a fierce Warrior, you fight for honor and strength." << endl;
    }
    else if (player.characterClass == "Mage") {
        cout << "As a wise Mage, you wield the powers of the arcane." << endl;
    }
    else if (player.characterClass == "Dwarf") {
        cout << "As a sturdy Dwarf, you are known for your craftsmanship and bravery." << endl;
    }
    else if (player.characterClass == "Elf") {
        cout << "As a graceful Elf, you excel in agility and magic." << endl;
    }
    else if (player.characterClass == "Rogue") {
        cout << "As a cunning Rogue, you rely on stealth and agility." << endl;
    }
    else {
        cout << "Unknown class! Defaulting to Adventurer." << endl;
        player.characterClass = "Adventurer"; // Add default case to avoid unexpected behavior
    }
    cout << endl; // Add extra space after introduction
}

// Delay Function
void delay(float seconds) {
    this_thread::sleep_for(chrono::milliseconds(static_cast<int>(seconds * 1000)));
}

// Pause Function: Press ESC to pause the game
void checkPause() {
    if (_kbhit()) { // Check if a key has been pressed
        char key = _getch(); // Get the pressed key
        if (key == 27) { // ESC key ASCII code is 27
            cout << "\nGame Paused. Press any key to continue...\n" << endl;
            _getch(); // Wait for any key to continue
        }
    }
}

// Function to automatically pause after each round with a custom message
void roundPause() {
    cout << "Hooray, you've won the round! Ready for the next encounter?" << endl;
    cout << "Press any key to continue..." << endl;
    _getch(); // Wait for player to press any key
    cout << endl; // Add extra space after pause
}

// Function to replenish health by 30% after each round
void replenishHealth(Character& player) {
    int maxHealth = 100;
    int healthRegen = static_cast<int>(maxHealth * 0.3); // 30% of max health
    player.healthPoints += healthRegen;

    // Ensure player's health doesn't exceed max health (100 HP)
    if (player.healthPoints > maxHealth) {
        player.healthPoints = maxHealth;
    }

    cout << "Your health has been replenished by 30%! You now have " << player.healthPoints << " HP." << endl;
    cout << endl; // Add extra space after health replenishment
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    string name, characterClass, gender;
    const string artifactName = "Ancient Crystal";
    const string artifactLocation = "Temple of Ancients";

    // Monster names inspired by "Lord of the Rings"
    vector<string> monsterNames = {
        "Gorgoth the Fierce",
        "Tharok the Cunning",
        "Zaroth the Dark",
        "Eldrin the Vile",
        "Morgrin the Ruthless",
        "Fenrir the Shadow",
        "Durak the Savage",
        "Kaldor the Malevolent",
        "Balgaroth the Terrible",
        "Valthor the Unyielding"
    };

    cout << "Welcome to the RPG Text Game!" << endl;
    cout << "Enter your character's name: ";
    getline(cin, name);

    cout << "Choose your character class (Warrior, Mage, Dwarf, Elf, Rogue): ";
    getline(cin, characterClass);

    cout << "Choose your character's gender (Male, Female, Other): ";
    getline(cin, gender);

    cout << endl;

    Character player(name, characterClass, gender);
    introduction(player);

    cout << "Your mission is to retrieve the " << artifactName << " located in the " << artifactLocation << "!" << endl;
    cout << endl; // Add extra space after mission

    delay(1.5); // Add a delay before the first round begins

    for (int round = 1; round <= 10; ++round) {
        Monster monster(monsterNames[round - 1], 100, 5 + (round - 1) * 2);

        cout << "\nRound " << round << ": A " << monster.name << " appears!" << endl;
        cout << endl; // Add extra space before battle

        while (player.healthPoints > 0 && monster.healthPoints > 0) {
            checkPause(); // Check if ESC was pressed to pause the game

            player.attack(monster);
            cout << monster.name << " has " << monster.healthPoints << " HP left." << endl;

            if (monster.healthPoints > 0) {
                cout << monster.name << " attacks " << player.name << " for " << monster.attackDamage << " damage!" << endl;
                player.healthPoints -= monster.attackDamage;
                if (player.healthPoints < 0) player.healthPoints = 0; // Avoid negative HP
                cout << player.name << " has " << player.healthPoints << " HP left." << endl;
            }

            delay(1.5); // Add 1.5-second delay between attacks
            cout << endl; // Add extra space between actions
        }

        if (player.healthPoints <= 0) {
            cout << "You have been defeated! Game Over!" << endl;
            return 0;
        }
        else {
            cout << "You have defeated " << monster.name << "!" << endl;
            player.attackDamage += 5; // Increase player damage after defeating a monster
        }

        delay(1.5); // Add 1.5-second delay after round
        cout << endl; // Extra space after round
        randomEncounter(player); // Chance for a random encounter
        delay(1.5); // Delay after the random encounter

        // Replenish health after each round
        replenishHealth(player);

        // Add a pause after each round with a message
        roundPause();
    }

    cout << "\nCongratulations, " << player.name << "! You have defeated all monsters and retrieved the " << artifactName << "!" << endl;
    cout << endl; // Add extra space at the end

    return 0;
}

