#ifndef __ELF_H__
#define __ELF_H__

#include "Enemy.h"
/*Forward declaration, make sure to include: 
"Enemy.h"
in .cc file.*/

class Hero;
class Drow;


extern std::string ActionMsg;

class Elf:public Enemy{
    bool ExtraAttack;
public:
    //Elf's constructor.
    //HAVE TO pass Elf a non-zero(either 1 or 2) GoldStash value!
    Elf(int GoldStash, int HP=140, int ATK=30, int DEF=10);
    //Elf's concrete destructor.
    ~Elf();
    //Override the Attack() function so that it sets ExtraAttack to false
    //BEFORE the OnStrike() function is called.
    void Attack(Drow* Target);
    //OnStrikeAttempt() is an utility Method that usually does nothing, but
    //it ALWAYS called after hit/miss calculation and damage calculation to
    //implement certain effects:
    //Example:
    //Elf, double attack. 
    void OnStrikeAttempt();
    //ElfDoubleAttack() calls IsEngaged() function AGAIN and sets the ExtraAttack 
    //field to false.
    void DoubleAttack();
    //Override the EndTurn() function so that it is overloaded to refresh
    // the ExtraAttack filed to true at the end of each turn.
    void EndTurn();
    //The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
    //Specific type of attacker hits this object. It calls OnTakeHit() utility
    //method FIRST.
    void BeenStruck(Hero* Attacker);
};

#endif
