#include "Hero.h"
#include "Shade.h"
#include "Enemy.h"
#include <iostream>
//The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
//they can be overrided by the subclasses. It will ALWAYS be calling 
//an Attack(...) function in the Enemy class and its subclasses.
void Shade::BeenStruck(Enemy* Attacker) { 
	#ifdef DEBUGATTACK
	std::cout << "Calling Shade BeenStruck" << std::endl;
	#endif
	Attacker->Attack(this); 
}
//Shade's constructor. It will not take in a MyTile argument. If want to 
//specify MyTile, call ModifyTile(Tile*) to do so.
Shade::Shade(int HP,int ATK, int DEF):
	Hero("Shade", HP, HP, ATK, DEF) {}
//Shade's concrete constructor. It doesn't do anything special.
Shade::~Shade() {}
/*GetScore() is overloaded for Shade to apply its +50% score bonus.*/
int Shade::GetScore() { return 1.5 * GetGoldStash(); }
