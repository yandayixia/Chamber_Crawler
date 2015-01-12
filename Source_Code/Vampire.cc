#include "Hero.h"
#include "Vampire.h"
#include "Enemy.h"
#include "helper.h"
#include "Dwarf.h"
//The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
//they can be overrided by the subclasses. It will ALWAYS be calling 
//an Attack(...) function in the Enemy class and its subclasses.
void Vampire::BeenStruck(Enemy* Attacker) { Attacker->Attack(this); }
//Vampire's constructor. It will not take in a MyTile argument. 
//If want to specify MyTile, call ModifyTile(Tile*) to do so.
//Note, CALL SetMaxHP(-1).
Vampire::Vampire(int HP, int ATK, int DEF):
	Hero("Vampire", -1, HP, ATK, DEF) {}
//Vampire's concrete constructor. It doesn't do anything special.
Vampire::~Vampire() {}
//Dwarf targets POISONS 5 HP per hit!!!
//OnAttack is NOT called in Attack; that effect is cancelled
void Vampire::Attack(Dwarf* Target) {
    if(IsAttackHit(100)){
        Target->ModifyHP(CalcDamage(GetATK(), Target->GetDEF()) * (-1));
        ModifyHP(-5);
    }
    if(Target->GetHP() <= 0){
        ModifyGoldStash(Target->OnDeath());
        OnSlay();
    }
}
/*OnAttack() is overrided such that Vampire drain 5 HP per attack*/
void Vampire::OnAttack() {
    ModifyHP(5);
}
