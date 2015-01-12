#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "Hero.h"
#include <string>
/*Forward declaration, make sure to include: 
"Hero.h"
in .cc file.*/
class Enemy;
extern std::string ActionMsg;

class Goblin: public Hero{
public:
    //Goblin's constructor. It will not take in a MyTile argument. 
    //If want to specify MyTile, call ModifyTile(Tile*) to do so.
    Goblin(int HP=110, int ATK=15, int DEF=20);
    //Goblin's concrete constructor. It doesn't do anything special.
    ~Goblin();
    /*OnSlay() is overrided to +5 gold per kill.*/
    void OnSlay();
    //The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
    //they can be overrided by the subclasses. It will ALWAYS be calling 
    //an Attack(...) function in the Enemy class and its subclasses.
    void BeenStruck(Enemy* Attacker);
};
#endif
