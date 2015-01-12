#ifndef __Merchant_H__
#define __Merchant_H__

#include "Enemy.h"
/*Forward declaration, make sure to include: 
"Enemy.h"
and to define the actual value(false) for IsHostile.
in .cc file.*/

class Hero;

class Merchant:public Enemy{
    static bool IsHostile;//False by default, but turns Ture when been
    //struck for the first time.
public:
    //Merchant's constructor, it ALWAYS has goldstash value 4!
    //DO NOT pass Merchant a new GoldStash value!
    Merchant(int GoldStash = 4, int HP=30, int ATK=70, int DEF=5);
    //Merchant's concrete destructor.
    ~Merchant();
    //OnTakeHit() is overloaded to call BecomeHostile().
    void OnTakeHit();
    //BecomeHostile() is a static method that changes IsHostile to True.
    static void BecomeHostile();
    //GetIsHostile() simply returns IsHostile. 
    static bool GetIsHostile();
    //TakeTurn() is overrided to check if the Merchants are hostile.
    void TakeTurn();
    //The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
    //Specific type of attacker hits this object. It calls OnTakeHit() utility
    //method FIRST.
    void BeenStruck(Hero* Attacker);
};

#endif
