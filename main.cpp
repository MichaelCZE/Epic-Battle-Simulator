#include <iostream>
#include <algorithm>
#include <limits>
#include "fighter.h"

Fighter fighter1;
Fighter fighter2;

std::string answer;

bool multiplayer = false;
bool gameFinished = false;

void createClass(std::string name, Fighter& fighter) {

    std::string choice;
    int pointLimit = 115;
    int currentPoints = pointLimit;

    int maxHealth;
    int damage;
    int defense;

    do {

        currentPoints = pointLimit;

        std::cout << "You now have " + std::to_string(currentPoints) + " available.\n";

        do {
            std::cout << "How many HP do you want to have?\n";
            while (!(std::cin >> maxHealth) || maxHealth < 5 || currentPoints - maxHealth < 5) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid number of HP (5-" + std::to_string(currentPoints-15) + ")" + ": ";
            }
        } while (maxHealth < 5 || currentPoints - maxHealth < 5);

        currentPoints -= maxHealth;

        std::cout << "You now have " + std::to_string(currentPoints) + " available.\n";
        do {
            std::cout << "How many damage do you want to do?\n";
            while (!(std::cin >> damage) || damage < 5 || currentPoints - damage < 5) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid amount of damage (5-" + std::to_string(currentPoints-10) + ")" + ": ";
            }
        } while (damage < 5 || currentPoints - damage < 5);

        currentPoints -= damage;

        std::cout << "You now have " + std::to_string(currentPoints) + " available.\n";
        do {
            std::cout << "How many defense do you want to have?\n";
            while (!(std::cin >> defense) || defense < 5 && currentPoints != 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid amount of defense (5-" + std::to_string(currentPoints-5) + ")" + ": ";
            }
        } while (defense < 5 && currentPoints != 0);

        currentPoints -= defense;

        do {
            if (currentPoints > 0) {
                std::cout << "You still have " + std::to_string(currentPoints) + " left.\nContinue anyway [C]\nRedistribute points [R]\n:";
                std::cin >> choice;
                std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            } 
            
            else {
                std::cout << "Do you want to\nRedistribute points [R]\nContinue [C]?";
                std::cin >> choice;
                std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            }
        } while (choice != "c" && choice != "r");

    } while (choice != "c" && currentPoints != 0);

    fighter = Fighter(name, maxHealth, damage, defense);
}

Fighter playerSelection() {

    Fighter fighter;

    std::string name;
    std::string classChoice;

    std::cout << "Select your name: ";
    std::cin >> name;

    do {

        std::cout << name + ", pick your class:\nArcher [A]\nWarrior [W]\nMage [M]\nCustom [C]\n: ";
        std::cin >> classChoice;
        std::transform(classChoice.begin(), classChoice.end(), classChoice.begin(), ::tolower);

        if (classChoice == "a") {
            fighter = Fighter(name, 100, 10, 5);
        } 
        
        else if (classChoice == "w") {
            fighter = Fighter(name, 100, 5, 10);
        } 
        
        else if (classChoice == "m") {
            fighter = Fighter(name, 90, 20, 5);
        } 
        
        else if (classChoice == "c") {
            createClass(name, fighter);
        } 
        
        else {
            std::cout << "Invalid choice. Please choose again.\n";
        }

    } while (classChoice != "a" && classChoice != "w" && classChoice != "m" && classChoice != "c");

    return fighter;
}

void modeSelect() {
    do {

        std::cout << "\nDo you want to play with two players? [Y/N]: ";
        std::cin >> answer;
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        if (answer == "y") {
            multiplayer = true;
            std::cout << "\n" + std::to_string(multiplayer) + "\n";
            std::cout << "Player 1\n";
            fighter1 = playerSelection();
            std::cout << "Player 2\n";
            fighter2 = playerSelection();
        } 
        
        else if (answer == "n") {
            fighter1 = playerSelection();
            fighter2 = Fighter("Yogos", 100, 10, 5);
        } 
        
        else {
            std::cout << "Invalid choice. Please enter 'Y' or 'N'.\n";
        }

    } while (answer != "y" && answer != "n");
}

void win(Fighter& player) {
    std::cout << "\n" + player.name + " has won the fight!\n";
    gameFinished = true;
}

void healUp(Fighter& player) {
    int heal = 1 + (rand() % 5);
    player.health += heal;
    if (player.health > player.maxHealth) {
        player.health = player.maxHealth;
        std::cout << "\n" + player.name + " fully healed up!\n";
    } 
    
    else {
        std::cout << "\n" + player.name + " healed up by " + std::to_string(heal) + " hp!\n";
    }
}

void attack(Fighter& attackingPlayer, Fighter& defendingPlayer) {
    int damage = attackingPlayer.damage - 2 + (rand() % 4);
    damage = damage - defendingPlayer.defense - 2 + (rand() % defendingPlayer.defense + 4);
    
    if (damage < 0) {
        damage = 0;
    }
    defendingPlayer.health -= damage;
    std::cout << "\n" + attackingPlayer.name + " attacks " + defendingPlayer.name + " and gives them " + std::to_string(damage) + " damage!\n";
    
    if (defendingPlayer.health > 0) {
        std::cout << "\n" + defendingPlayer.name + " now has " + std::to_string(defendingPlayer.health) + "/" + std::to_string(defendingPlayer.maxHealth) + " hp!\n";
    } 
    
    else {
        win(attackingPlayer);
    }
}

void battle(Fighter& attackingPlayer, Fighter& defendingPlayer, bool multiplayer) {

    if (gameFinished) {
        std::cout << "\n\nThanks for playing!\n\n";
    } else {

        std::string choice;

        do {

            std::cout << "\n" + attackingPlayer.name + ", do you want to\nAttack [A]\nCheck stats [C]\nHeal[H]\n:";
            std::cin >> choice;
            std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "a") {
                attack(attackingPlayer, defendingPlayer);
            } 
            
            else if (choice == "c") {
                std::cout << attackingPlayer.toString();
            } 
            
            else if (choice == "h") {
                healUp(attackingPlayer);
            }

        } while (choice != "a" && choice != "h");

        if (multiplayer) {
            battle(defendingPlayer, attackingPlayer, multiplayer);
        } 

		else {

			int aiChoice = 1 + (rand() % 2);
			if (aiChoice == 1 && !gameFinished) {
				attack(defendingPlayer, attackingPlayer);
			} 
            
            else if (aiChoice == 2 && !gameFinished) {
				healUp(defendingPlayer);
			}

			battle(attackingPlayer, defendingPlayer, multiplayer);

        }

    }

}

int main(int argc, char** argv) {

    std::cout << "Epic battle simulator 3000";
    modeSelect();
    battle(fighter1, fighter2, multiplayer);

    std::cin >> answer;
    return 0;
}
