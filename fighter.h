#ifndef FIGHTER_H
#define FIGHTER_H

#include <string>

class Fighter {
    public:
        std::string name;
        int maxHealth;
        int health;
        int damage;
        int defense;

        Fighter();
        Fighter(std::string name, int maxHealth, int damage, int defense);

        std::string toString();
};

#endif
