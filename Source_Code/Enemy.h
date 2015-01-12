#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"
#include <string>

/*Forward declaration, make sure to include: 
"Character.h" 
in .cc file.*/

class Hero;

class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

extern std::string ActionMsg;

class Enemy:public Character{
protected:
    //Enemy's constructor, it will ONLY be called by its sub-classes.
    //All of the aruguments will be passed to the constructor as default
    //constructors, and MaxHP, defaultATK will be assignmentd to HP, ATK
    //respectively. Also, Enmey would always has a predetermined goldstash. 
    //MyTile will be null by default.
    Enemy(int HP, int ATK, int DEF, int GoldStash, char MyDisplay);
    
public:
    //Purely virtual desturctor.
    virtual ~Enemy()=0;
    //TakeTurn() will be called by Floor.MoveEnemy to start an enemy's turn.
    //It will call IsEngaged() to decide whether to: 
    //(False) call MoveMe(int random0->7) or
    //(true) does nothing. (Attacking is imbeded in IsEngaged.)
    //Then it will call EndTurn().
	virtual void TakeTurn();
    //IsEngaged() will return true AND attack the hero if he is within 
    //melee range. It return false otherwise.
    virtual bool IsEngaged();
    //The Attack(... Target) functions specifies what happens when that
    //Specific type of target is struck by this particular object. They 
    //will ALWAYS be called by the is BeenStruck function of Hero class
    //or its sub classes. It calls OnStrik() Utility function.
    virtual void Attack(Shade* Target);
    virtual void Attack(Drow* Target);
    virtual void Attack(Vampire* Target);
    virtual void Attack(Troll* Target);
    virtual void Attack(Goblin* Target);
    //The BeenStruck(... Attacker) functions specifies what happens when that
    //Specific type of attacker hits this object. It calls OnTakeHit() utility
    //method FIRST.
    virtual void BeenStruck(Hero* Attacker)= 0;
    //OnDeath() is an utility Method that returns the amount of goldstash
    //this enemy object has. 
    virtual int OnDeath();
    //OnStrike() is an utility Method that usually does nothing, but will
    //be overrided to fullfill certain monster's speical abilities. (Not 
    //attucally used in the base game.)
    //Example:
    //Vampire, If hit, Drain HP. 
    virtual void OnStrike();
    //OnStrikeAttempt() is an utility Method that usually does nothing, but
    //it ALWAYS called after hit/miss calculation and damage calculation to
    //implement certain effects:
    //Example:
    //Elf, double attack. 
    virtual void OnStrikeAttempt();
    //OnTakeHit() is an utility Method that usually does nothing, but will
    //be overrided to fullfill certain monster's special abilities.
    //Example:
    //Merchant: Turns hostile once taken a hit.
    virtual void OnTakeHit();

    virtual void EndTurn();
};

#endif
