#ifndef __TROLL_H__
#define __TROLL_H__
/*Forward declaration, make sure to include: 
"Hero.h"
in .cc file.*/
class Hero;
class Enemy;

class Troll: public Hero{
public:
    //Troll's constructor. It will not take in a MyTile argument. 
    //If want to specify MyTile, call ModifyTile(Tile*) to do so.
    Troll(int HP=120, int ATK=25, int DEF=15);
    //Troll's concrete constructor. It doesn't do anything special.
    ~Troll();
    /*EndTurn() is overrided for the effect of +5 HP per term*/
    void EndTurn();
    //The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
    //they can be overrided by the subclasses. It will ALWAYS be calling 
    //an Attack(...) function in the Enemy class and its subclasses.
    void BeenStruck(Enemy* Attacker);
};
#endif
