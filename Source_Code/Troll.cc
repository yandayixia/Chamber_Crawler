#include "Hero.h"
#include "Troll.h"
#include "Enemy.h"
//The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
//they can be overrided by the subclasses. It will ALWAYS be calling 
//an Attack(...) function in the Enemy class and its subclasses.
void Troll::BeenStruck(Enemy* Attacker) { Attacker->Attack(this); }
//Troll's constructor. It will not take in a MyTile argument. 
//If want to specify MyTile, call ModifyTile(Tile*) to do so.
Troll::Troll(int HP, int ATK, int DEF): 
    Hero("Troll", HP, HP, ATK, DEF) {}
//Troll's concrete constructor. It doesn't do anything special.
Troll::~Troll(){}
/*EndTurn() is overrided for the effect of +5 HP per term*/
void Troll::EndTurn(){
	if(GetHP()> 0){
        ModifyHP(5);
	}
}
