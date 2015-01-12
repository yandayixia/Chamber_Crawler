#ifndef __DWARF_H__
#define __DWARF_H__

#include "Enemy.h"
/*Forward declaration, make sure to include: 
"Enemy.h"
in .cc file.*/

class Dwarf:public Enemy{
public:
    //Dwarf's constructor.
    //HAVE TO pass dwarf a non-zero(either 1 or 2) GoldStash value!
    Dwarf(int GoldStash, int HP=120, int ATK=20, int DEF=30);
    //Dwarf's concrete constructor. It doesn't do anything special.
    ~Dwarf();
    //The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
    //Specific type of attacker hits this object. It calls OnTakeHit() utility
    //method FIRST.
    void BeenStruck(Hero* Attacker);
};

#endif
