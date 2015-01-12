#include "Character.h"
#include "Hero.h"
#include "Tile.h"
#include "Gold.h"
#include "Item.h"
#include <iostream>
#include <string>
#include <sstream>

//Character's constructor, it will ONLY be called by its sub-classes.
//All of the aruguments will be passed to the constructor as default
//constructors. MyTile, if not specified, will be null by default.
Character::Character(int MaxHP, int HP, int DefaultATK, int ATK, int DefaultDEF, 
	int DEF, int GoldStash, char MyDisplay, Tile* MyTile):
    Entity(MyDisplay), MaxHP(MaxHP), HP(HP), DefaultATK(DefaultATK),
    ATK(ATK), DefaultDEF(DefaultDEF), DEF(DEF), GoldStash(GoldStash),
    MyTile(MyTile){}

    Character::~Character(){}

//SetMaxHP(int NewMax) sets MaxHP to NewMax, NewMax is either >= 0 or -1.
void Character::SetMaxHP(int NewMax){
	MaxHP = NewMax;
	return;
}
//ModifyHP(int Amount), Amount can be both positive or negative, 
//adds Amount to current Hp. Hp is capped at MaxHp. If MaxHP =-1,
//there will be no MaxHP limit. However, HP can never be smaller 
//than 0.
void Character::ModifyHP(int Amount){
    HP += Amount;
    //If there is no HPCap.
    if(MaxHP == -1){
    }else{
    //If there IS an HPCap.
    	if(HP > MaxHP){
    		HP = MaxHP;
    	}
    }
    //ALWAYS check lower bound.
    if(HP < 0){
    	HP = 0;
    }
    return;
}
//ModifyATK(int Amount), Amount can be both positive or negative,
//adds Amount to current ATK.
void Character::ModifyATK(int Amount){
	ATK += Amount;
	return;
}
//ModifyDEF(int Amount), Amount can be both positive or negative,
//adds Amount to current DEF.
void Character::ModifyDEF(int Amount){
    DEF += Amount;
    return;
}
//ResetAbilities() sets ATK to DefaultATK, DEF to DefaultDEF.
void Character::ResetAbilities(){
	DEF = DefaultDEF;
	ATK = DefaultATK;
	return;
}
//ModifyGoldStash(int Amount) adds Amount to GoldStash. GoldStash
//can NEVER go below zero.
void Character::ModifyGoldStash(int Amount){
	GoldStash +=Amount;
	if(GoldStash<0){
		GoldStash = 0;
	}
}
//ModifyTile(Tile* NewTile) sets MyTile filed equal to New Tile.
//To detach, passes in a null.
void Character::ModifyTile(Tile* NewTile){
    if(NewTile){
        MyTile = NewTile;
        MyTile->AttachEntity(this);
    }
}
//The access-or function for five of the fields.
int Character::GetMaxHP() {
    return MaxHP;
}
int Character::GetHP(){
    return HP;
}
int Character::GetATK(){
    return ATK;
}
int Character::GetDEF(){
    return DEF;
}
int Character::GetGoldStash(){
    return GoldStash;
}
Tile* Character::GetTile(){
    return MyTile;
}

bool Character::GetAllowWalk() {
    #ifdef DEBUG
        std::cout << "---Character::GetAllowWalk() Called!!!" <<std::endl;
    #endif
    return false;
}

//*ASCENDING LEVEL is NOT checked here in MoveMe(), it is checked in Main.cc
bool Character::MoveMe(int dirc) {
    // check: see if movable
    if ((dirc < 0) || (dirc > 7)) return false; // direction invalid
    Tile* next_tile = MyTile->OkToWalk(dirc);
    if (next_tile){
        if ((GetDisplay() == '@') && (next_tile->GetEntity()) && (next_tile->GetEntity()->GetDisplay() == 'G')) {
            ModifyGoldStash(next_tile->GetEntity()->GetValue());
	        std::string GoldAmt = static_cast<std::ostringstream*>( & (std::ostringstream() << next_tile->GetEntity()->GetValue()) )->str();
            ActionMsg = ActionMsg + std::string("You have picked up ") + next_tile->GetEntity()->GetName() + " (" + GoldAmt + " gold).";
        }
        MyTile->DetachEntity();
        MyTile = MyTile->GetNeighbour(dirc);
        MyTile->AttachEntity(this);
        return true;
    } else {
        return false;
    }
}
