#include "fighter.h"

Fighter::Fighter() {}

Fighter::Fighter(std::string n, int maxHp, int dmg, int def) : name(n), maxHealth(maxHp), health(maxHp), damage(dmg), defense(def){
	std::string name = n;
    int maxHealth = maxHp;
    int health = maxHealth;
    int damage = dmg;
    int defense = def;
}

std::string Fighter::toString() {
	return "Name: " + name + "\nHealth: " + std::to_string(health) + "/" + std::to_string(maxHealth) + "\nDamage: " + std::to_string(damage) + "\nDefense: " + std::to_string(defense) +"\n";
}
	



