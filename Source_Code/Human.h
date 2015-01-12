#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "Enemy.h"

/*Forward declaration, make sure to include: 
"Enemy.h"
in .cc file.*/
class Hero;
class Tile;

class Human:public Enemy{
public:
    //Human's constructor, human ALWAYS holds Normal(val=2) value. DO
    //NOT pass human a different GoldStash value!
    Human(int GoldStash=2, int HP=140, int ATK=20, int DEF=20);
    //Human's concrete destructor. It doesn't do anything special.
    ~Human();
    //OnDeath() is overrided to return DOUBLE the amount of GoldStash
    //this object is holding.
    int OnDeath();
    //The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
    //Specific type of attacker hits this object. It calls OnTakeHit() utility
    //method FIRST.
    void BeenStruck(Hero* Attacker);
};

#endif
