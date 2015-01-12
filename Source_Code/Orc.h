#ifndef __ORC_H__
#define __ORC_H__

#include "Enemy.h"
/*Forward declaration, make sure to include: 
"Enemy.h"
in .cc file.*/

class Hero;
class Goblin;

class Orc:public Enemy{
public:
    //Orc's constructor, 
    //HAVE TO pass Orc a new GoldStash value! (either 1 or 2)
    Orc(int GoldStash, int HP=180, int ATK=30, int DEF=25);
    //Orc's concrete destructor. It doesn't do anything special.
    ~Orc();
    //Attack(Goblin* Target) is overloaded so it does 50% more
    //damage.
    void Attack(Goblin* Target);
    //The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
    //Specific type of attacker hits this object. It calls OnTakeHit() utility
    //method FIRST.
    void BeenStruck(Hero* Attacker);
};

#endif
