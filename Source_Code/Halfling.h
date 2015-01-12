#ifndef __HALFLING_H__
#define __HALFLING_H__
#include "Enemy.h"

/*Forward declaration, make sure to include: 
"Enemy.h"
in .cc file.*/
class Hero;

class Halfling:public Enemy{
public:
    //Halfling's constructor, 
    //HAVE TO pass Halfling a new GoldStash value! (either 1 or 2)
    Halfling(int GoldStash, int HP=100, int ATK=15, int DEF=20);
    //Halfling's concrete destructor. It doesn't do anything special.
    ~Halfling();
    //The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
    //Specific type of attacker hits this object. It calls OnTakeHit() utility
    //method FIRST.
    void BeenStruck(Hero* Attacker);
};

#endif
