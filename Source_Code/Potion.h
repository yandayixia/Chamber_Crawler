#ifndef __POTION_H__
#define __POTION_H__
#include "Item.h"
#include <string>

class Potion: public Item {
	std::string Stat; // HP, DEF or ATK: the stat that the potion will have an effect on
    int Strength; // magnitude/positive-negative direction of its effect
public:
	std::string PotionName; //The Name of the Potion.
	Potion(Tile* MyTile, std::string Stat, int Strength, std::string PotionName);
	~Potion();
	std::string GetName();
	std::string GetStat();
	int GetStrength();
};

#endif
