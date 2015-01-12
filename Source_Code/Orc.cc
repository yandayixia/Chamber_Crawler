#include "Enemy.h"
#include "Orc.h"
#include "Goblin.h"
#include "helper.h"
#include "Hero.h"
//The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
//Specific type of attacker hits this object. It calls OnTakeHit() utility
//method FIRST.
void Orc::BeenStruck(Hero* Attacker){
    Attacker->Attack(this);
    OnTakeHit();
}
//Orc's constructor, 
//HAVE TO pass Orc a new GoldStash value! (either 1 or 2)
Orc::Orc(int GoldStash, int HP, int ATK, int DEF):
	Enemy(HP, ATK, DEF, GoldStash, 'O') {}
//Orc's concrete destructor. It doesn't do anything special.
Orc::~Orc() {}
//Attack(Goblin* Target) is overloaded so it does 50% more
//damage.
void Orc::Attack(Goblin* Target){
    if(IsAttackHit(50)){
        int damage = CalcDamage(GetATK(), Target->GetDEF()) * 1.5;
        Target->ModifyHP(-1 * damage);
        std::string dmg = NumberToString(damage);
        ActionMsg = ActionMsg + GetDisplay() + std::string(" deals ") + dmg + " points of damage to PC. ";
        OnStrike();
    }else{
        std::string hpleft = NumberToString(GetHP());
        ActionMsg = ActionMsg + GetDisplay() + " (" + hpleft + " HP) " + " missed the PC! " ;
    }
    OnStrikeAttempt();
}
