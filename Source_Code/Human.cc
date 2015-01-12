#include "Human.h"
#include "Hero.h"
#include "Tile.h"

//Human's constructor, human ALWAYS holds Normal(val=2) value. DO
//NOT pass human a different GoldStash value!

Human::Human(int GoldStash, int HP, int ATK, int DEF): 
	Enemy(HP, ATK, DEF, GoldStash, 'H') {}
void Human::BeenStruck(Hero* Attacker){
    Attacker->Attack(this);
    OnTakeHit();
}

//Human's concrete destructor. It doesn't do anything special.
Human::~Human(){}
//OnDeath() is overrided to return DOUBLE the amount of GoldStash
//this object is holding.
int Human::OnDeath() {
	GetTile()->DetachEntity();
    ModifyTile(0);
	return GetGoldStash() * 2;
}
