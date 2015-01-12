#include "Dwarf.h"
#include "helper.h"
#include "Hero.h"

//Dwarf's constructor.
//HAVE TO pass dwarf a non-zero(either 1 or 2) GoldStash value!
Dwarf::Dwarf(int GoldStash, int HP, int ATK, int DEF): 
	Enemy(HP, ATK, DEF, GoldStash, 'W') {}
//Dwarf's concrete constructor. It doesn't do anything special.
Dwarf::~Dwarf() {}

//The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
//Specific type of attacker hits this object. It calls OnTakeHit() utility
//method FIRST.
void Dwarf::BeenStruck(Hero* Attacker){
    Attacker->Attack(this);
    OnTakeHit();
}
