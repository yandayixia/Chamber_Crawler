#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
/*Forward declaration, make sure to include: 
"Hero.h"
in .cc file.*/
class Hero;
class Enemy;
class Dwarf;

class Vampire: public Hero{
public:
    //Vampire's constructor. It will not take in a MyTile argument. 
    //If want to specify MyTile, call ModifyTile(Tile*) to do so.
    //Note, CALL SetMaxHP(-1).
    Vampire(int HP=50, int ATK=25, int DEF=25);
    //Vampire's concrete constructor. It doesn't do anything special.
    ~Vampire();
    //Dwarf targets POISONS 5 HP per hit!!!
    void Attack(Dwarf* Target);
    /*OnAttack() is overrided such that Vampire drain 5 HP per attack*/
    void OnAttack();
    //The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
    //they can be overrided by the subclasses. It will ALWAYS be calling 
    //an Attack(...) function in the Enemy class and its subclasses.
    void BeenStruck(Enemy* Attacker);
};

#endif
