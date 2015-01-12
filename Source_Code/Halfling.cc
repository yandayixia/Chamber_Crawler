#include "Halfling.h"
#include "helper.h"
#include "Hero.h"
//The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
//Specific type of attacker hits this object. It calls OnTakeHit() utility
//method FIRST.
void Halfling::BeenStruck(Hero* Attacker){
    Attacker->Attack(this);
    OnTakeHit();
}
//Halfling's constructor, 
//HAVE TO pass Halfling a new GoldStash value! (either 1 or 2)
Halfling::Halfling(int GoldStash, int HP, int ATK, int DEF):
    Enemy(HP, ATK, DEF, GoldStash, 'L') {}

//Halfling's concrete destructor. It doesn't do anything special.
Halfling::~Halfling() {}


// need to overload ALL BeenStruck functions from Enemy!
