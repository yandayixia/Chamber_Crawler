#include "Potion.h"
#include <string>

Potion::Potion(Tile* MyTile, std::string Stat, int Strength, std::string PotionName):
	Item('P', false, false, MyTile), Stat(Stat), Strength(Strength), PotionName(PotionName){}

Potion::~Potion() {}

std::string Potion::GetName() {return PotionName;}
std::string Potion::GetStat() {return Stat;}
int Potion::GetStrength() {return Strength;}
