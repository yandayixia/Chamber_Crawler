#ifndef __Hero_H__
#define __Hero_H__
#include "Character.h"

/*Forward declaration, make sure to include: 
"Character.h"
"Human.h"
"Dwarf.h"
"Elf.h"
"Orc.h"
"Merchant.h"
"Halflin.h"
"Dragon.h"
<String>
in .cc file.*/
class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Halfling;
class Dragon;
class Potion;
class Enemy;

extern std::string ActionMsg;

class Hero: public Character{
    std::string Race;
    bool KnowledgePool[6];
    //entry 0 => BH
    //entry 1 => BA
    //entry 2 => BD
    //entry 3 => PH
    //entry 4 => WA
    //entry 5 => WD

public:
	//Hero's constructor, it will ONLY be called by its sub-classes.
    //All of the aruguments will be passed to the constructor as default
    //constructors. It will not take in a MyTile argument. If want to 
    //specify MyTile, call ModifyTile(Tile*) to do so. It will fill 
    //Character's constructor will the approperiate fields.
    //examples: MaxHp = HP, DefaultATK = ATK, MyDisplay = "@".
	Hero(std::string Race, int MaxHP, int HP,int ATK, int DEF);
    virtual ~Hero()=0;
	//The access-or function for the new Race field.
    std::string GetRace();
    /*AttemptToHit(int dirc) attempts to attack the Entity on the tile
    indicated by dirc. It returns true if the move was successful and 
    false otherwise so that the player won't waste another turn.
    Example: (dirc value)
    7 0 1
    6 @ 2
    5 4 3
    */
    bool AttemptToHit(int dirc);
    //AttemptToUse(int dirc) attempts to drink the Potion on the tile 
    //indicated by dirc. It returns true if the move was successful and 
    //false otherwise so that the player won't waste another turn. It 
    //calls UsePotion(Potion* Target) if it is indeed a potion.
    bool AttemptToUse(int dirc);
    //returns true if target is in KnowledgePool.
    bool IsKnown(std::string target);
    
    void AddtoKnowledgePool(std::string target);

    void SeePotion();
    //UsePotion(Potion* Target) will execute the effect of the potion.
    virtual void UsePotion(Potion* Target);
    //All of the Attack(Type Target)functions are VIRTUAL so that they can 
    //be overrided by the subclasses. It will ALWAYS be called by a 
    //BeenStruck(...) function from Enemy class and its subclasses.
    //Check Attack's accuracy first, and if hit, call The hit and 
    //OnAttack() methods. 
    virtual void Attack(Human* Target);
    virtual void Attack(Dwarf* Target);
    virtual void Attack(Elf* Target);
    virtual void Attack(Orc* Target);
    virtual void Attack(Merchant* Target);
    virtual void Attack(Halfling* Target);
    virtual void Attack(Dragon* Target);
    //The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
    //they can be overrided by the subclasses. It will ALWAYS be calling 
    //an Attack(...) function in the Enemy class and its subclasses.
    virtual void BeenStruck(Enemy* Attacker) = 0;
    /*GetScore() is an accessor wrapper function that calls GetGoldStash(),
    However it will help Shade to apply its score bonus.*/
    virtual int GetScore();
    /*OnAttack() is an utility function that will be called by the 
	Attack(...) functions evertime. It does nothing usually, but does 
	help implement those effects that activates when an attack is hit.
    Example:
    -->Vampire drain 5 HP.*/
    virtual void OnAttack();
	/*OnSlay() is an utility function that will be called by the 
	Attack(...)functions if the player is able to drop the HP of
	target to zero. It does nothing usually, but does help on
	implement those effects that activates when a monster is slain.
    Example:
    -->Goblin steal 5 gold.*/
    virtual void OnSlay();
    // Carries out Troll's +5 Health per turn effect if player is troll
    virtual void EndTurn();
};

#endif
