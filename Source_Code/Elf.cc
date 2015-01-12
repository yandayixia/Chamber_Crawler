#include "Elf.h"
#include "Drow.h"
#include "helper.h"
#include "Hero.h"
#include "Potion.h"
#include <string>
#include <iostream>

//The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
//Specific type of attacker hits this object. It calls OnTakeHit() utility
//method FIRST.
void Elf::BeenStruck(Hero* Attacker){
    Attacker->Attack(this);
    OnTakeHit();
}
//Elf's constructor.
//HAVE TO pass Elf a non-zero(either 1 or 2) GoldStash value!
Elf::Elf(int GoldStash, int HP, int ATK, int DEF):
    Enemy(HP, ATK, DEF, GoldStash, 'E'), ExtraAttack(true){}
//Elf's concrete destructor.
Elf::~Elf() {}
//Override the Attack() function so that it sets ExtraAttack to false
//BEFORE the OnStrike() function is called.
void Elf::Attack(Drow* Target){
    if(IsAttackHit(50)){
        int damage = CalcDamage(GetATK(), Target->GetDEF());
        std::string dmg = NumberToString(damage);
        ActionMsg = ActionMsg + GetDisplay() + std::string(" deals ") + dmg + " points of damage to PC. ";
        Target->ModifyHP(-1 * damage);
        OnStrike();
    }else{
        std::string hpleft = NumberToString(GetHP());
        ActionMsg = ActionMsg + GetDisplay() + " (" + hpleft + " HP) " + " missed the PC! " ;
    }
    OnStrikeAttempt();
}
//OnStrikeAttempt() is an utility Method that usually does nothing, but
//it ALWAYS called after hit/miss calculation and damage calculation to
//implement certain effects:
//Example:
//Elf, double attack. 
void Elf::OnStrikeAttempt() {
    if(ExtraAttack){
        ExtraAttack = false;
        ActionMsg = ActionMsg + " E strikes again! ";
        DoubleAttack();
    }
}

//DoubleAttack() calls IsEngaged() function AGAIN and sets the ExtraAttack 
//field to false.
void Elf::DoubleAttack(){
	if(IsEngaged()){
        //If there is something still to hit
    }else{
    	//If the hero is slain
    	//Idol
    }
}
//Override the EndTurn() function so that it is overloaded to refresh
// the ExtraAttack filed to true at the end of each turn.
void Elf::EndTurn() {
    ExtraAttack = true;
}
