#include "Enemy.h"
#include "Goblin.h"
#include "helper.h"
//The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
//they can be overrided by the subclasses. It will ALWAYS be calling 
//an Attack(...) function in the Enemy class and its subclasses.
void Goblin::BeenStruck(Enemy* Attacker) { Attacker->Attack(this); }
//Goblin's constructor. It will not take in a MyTile argument. 
//If want to specify MyTile, call ModifyTile(Tile*) to do so.
Goblin::Goblin(int HP, int ATK, int DEF):
	Hero("Goblin", HP, HP, ATK, DEF) {}
//Goblin's concrete constructor. It doesn't do anything special.
Goblin::~Goblin(){}
/*OnSlay() is overrided to +5 gold per kill.*/
void Goblin::OnSlay(){
	int goldbonus = 5;
	std::string gold = NumberToString(goldbonus);
	ActionMsg += " PC earns " + gold + " pieces of bonus gold.";
	ModifyGoldStash(goldbonus);
}
