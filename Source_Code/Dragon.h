#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "Enemy.h"
/*Forward declaration, make sure to include: 
"Enemy.h"
in .cc file.*/

class Hero;
class Gold;

class Dragon:public Enemy{
	Gold* Treasure;
public:
    //Dragon's constructor, it ALWAYS has goldstash value 0!
    //DO NOT pass Dragon a new GoldStash value!
    Dragon(int GoldStash=0, int HP=150, int ATK=20, int DEF=20);
    //Dragon's concrete destructor. Doesn't do anything extra.
    ~Dragon();
    //MUST call SetTreasure(Item* MyTreasure) after create each 
    //dragon object. It sets Treasure to MyTreasure.  
    void SetTreasure(Gold* MyTreasure);
    //TakeTurn() is overrided to never move the dragon.
    void TakeTurn();
    //IsEngaged() is overrided to check if the character is near 
    //the dragon or the treasure. IMMEDIATELY attack if is.
    bool IsEngaged();
    //OnDeath() is overrided to make the Treasure pickable, calls
    //item.ModifyAllowPick(true).
    int OnDeath();
    //The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
    //Specific type of attacker hits this object. It calls OnTakeHit() utility
    //method FIRST.
    void BeenStruck(Hero* Attacker);
};

#endif
