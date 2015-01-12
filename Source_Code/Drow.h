#ifndef __Drow_H__
#define __Drow_H__
#include "Hero.h"
/*Forward declaration, make sure to include: 
"Hero.h"
in .cc file.*/
class Hero;
class Enemy;
class Potion;


extern std::string ActionMsg;


class Drow: public Hero{
public:
    //Drow's constructor. It will not take in a MyTile argument. If want to 
    //specify MyTile, call ModifyTile(Tile*) to do so. 
    Drow(int HP=150,int ATK=25, int DEF=15);
    //Drow's concrete constructor. It doesn't do anything special.
    ~Drow();
    //UsePotion() is overrided to multiply the effectiveness by 1.5
    void UsePotion(Potion* Target);
    //The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
    //they can be overrided by the subclasses. It will ALWAYS be calling 
    //an Attack(...) function in the Enemy class and its subclasses.
    void BeenStruck(Enemy* Attacker);
};

#endif
