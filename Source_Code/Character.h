#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity.h"

/*Forward declaration, make sure to include: 
"Entity.h" 
"Tile.h"
in .cc file.*/
class Tile;

extern std::string ActionMsg;

class Character:public Entity{
    int MaxHP,HP;
    int DefaultATK,ATK;
    int DefaultDEF,DEF;
    int GoldStash;
protected:
    Tile* MyTile;
    //Character's constructor, it will ONLY be called by its sub-classes.
    //All of the aruguments will be passed to the constructor as default
    //constructors. MyTile, if not specified, will be null by default.
	Character(int MaxHP, int HP, int DefaultATK, int ATK, int DefaultDEF, 
		int DEF, int GoldStash, char MyDisplay, Tile* MyTile=0);
    virtual ~Character()=0;
    //SetMaxHP(int NewMax) sets MaxHP to NewMax, NewMax is either >= 0 or -1.
    void SetMaxHP(int NewMax);
public:
	//ModifyHP(int Amount), Amount can be both positive or negative, 
	//adds Amount to current Hp. Hp is capped at MaxHp. If MaxHP =-1,
	//there will be no MaxHP limit. However, HP can never be smaller 
	//than 0.
	void ModifyHP(int Amount);
	//ModifyATK(int Amount), Amount can be both positive or negative,
	//adds Amount to current ATK.
	void ModifyATK(int Amount);
	//ModifyDEF(int Amount), Amount can be both positive or negative,
	//adds Amount to current DEF.
	void ModifyDEF(int Amount);
	//ResetAbilities() sets ATK to DefaultATK, DEF to DefaultDEF.
	void ResetAbilities();
	//ModifyGoldStash(int Amount) adds Amount to GoldStash. GoldStash
	//can NEVER go below zero.
	void ModifyGoldStash(int Amount);
	//ModifyTile(Tile* NewTile) sets MyTile filed equal to New Tile.
	//To detach, passes in a null.
	void ModifyTile(Tile* NewTile);
    //The access-or function for five of the fields.
    int GetMaxHP();
	int GetHP();
	int GetATK();
	int GetDEF();
    int GetGoldStash();
    Tile* GetTile();
    /*MoveMe(int dirc) attempts to move this object one tile to the 
    direction indicated as dirc. It returns true if the move was 
    successful and false otherwise so that the player/monster won't
    waste another turn.
    Example: (dirc value)
    7 0 1
    6 @ 2
    5 4 3
    */
    bool MoveMe(int dirc);
    // GetAllowWalk() always returns false
    bool GetAllowWalk();
    /*EndTurn() is a function that will be called at the end of every 
    turn of EVERY single object of Character's subclasses. It often
    does nothing most, but will help us carry out those "once per turn"
    effects. 
    Example:
    ->Troll Health +5 per turn
    */
    virtual void EndTurn() = 0;  
};

#endif
