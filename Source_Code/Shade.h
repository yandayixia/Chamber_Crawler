#ifndef __Shade_H__
#define __Shade_H__
/*Forward declaration, make sure to include: 
"Hero.h"
in .cc file.*/
class Hero;
class Enemy;

class Shade: public Hero{
public:
	//Shade's constructor. It will not take in a MyTile argument. If want to 
    //specify MyTile, call ModifyTile(Tile*) to do so.
	Shade(int HP=125,int ATK=25, int DEF=25);
    //Shade's concrete constructor. It doesn't do anything special.
    ~Shade();
    /*GetScore() is overloaded for Shade to apply its +50% score bonus.*/
    int GetScore();
    //The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
    //they can be overrided by the subclasses. It will ALWAYS be calling 
    //an Attack(...) function in the Enemy class and its subclasses.
    void BeenStruck(Enemy* Attacker);
};

#endif