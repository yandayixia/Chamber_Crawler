#include <iostream>

#include "Hero.h"
#include "Potion.h"
#include "Tile.h"
#include "Item.h"
#include "Gold.h"
#include "Human.h"
#include "Elf.h"
#include "Dwarf.h"
#include "Orc.h"
#include "Vampire.h"
#include "Merchant.h"
#include "Dragon.h"
#include "Halfling.h"
#include "helper.h"

// only called in Floor's ConstructLevel (i.e. when floor is being built for first time)
// note: NonTileInput(char) sets IsWalkabe field
Tile::Tile (char MyDisplay): 
    Entity(MyDisplay), MyEntity(0), NumNeighbours(0), NeighboursArr(0), IsWalkable(false),
    IsChecked(false)  {
	NeighboursArr = new Tile*[8];
}

Tile* Tile::OkToWalk(int dirc) {
    #ifdef DEBUGTILE
        std::cout << "Tile::OkayToWalk() Called!!!" <<std::endl;
    #endif
    Tile *target = NeighboursArr[dirc];
    // Target will never have a tile on it
    if (!target) {
        return 0;
    }
    if (target->GetAllowWalk() && (!target->GetEntity())){
        return target;
    } else if (target->GetAllowWalk() && (target->GetEntity()) && ((target->GetEntity())->GetAllowWalk())) {
        Item* tempI =dynamic_cast<Item*>(target->GetEntity());
        if(!tempI){
            return 0;
        }
        if(tempI->GetAllowPick()){
            return target;
        }else{
            return 0;
        }
        
    } else {
        return 0;
    }

}


/*AttachEntity(Entity* Target) will attach Target to MyEntity.*/
void Tile::AttachEntity(Entity* Target) {
    MyEntity = Target;
}


/*DetachEntity() resets MyEntity back to 0.*/
void Tile::DetachEntity() {
    MyEntity = NULL;
}

/*DrawTile() prints to Cin (without adding endl) either this->GetDisplay,
or MyEntity->GetDisplay() if My Entity is not 0.*/
void Tile::DrawTile() {
    char display;
    if (!MyEntity) display = this->GetDisplay();
    else display = MyEntity->GetDisplay();
    std::cout << display;
}


/*IsPlayer_Engaged() returns the pointer to that tile if the player
is standing on one of the neighbours, or 0 otherwise. */
Tile* Tile::IsPlayerEngaged(){
    for (int i = 0; i < 8; ++i) {
        if ((NeighboursArr[i]->GetEntity()) && (NeighboursArr[i]->GetEntity()->GetDisplay() == '@')) {
            #ifdef DEBUGATTACK
                std::cout << "Returning player tile" << std::endl;
                std::cout << "*************Player FOUND!!!****************************" << std::endl;
            #endif
    		return NeighboursArr[i];
    	}
     }
    #ifdef DEBUGATTACK
        std::cout << "Player MISSED" << std::endl;
    #endif
     return 0;
}

/*EnemyEngaged() returns the pointer to that tile if there is enemy
character standing on the dirc tile, or 0 otherwise. */
Tile* Tile::EnemyEngaged(int dirc){
    char enemies[8] = {'H', 'W', 'E', 'O', 'V', 'M', 'D', 'L'};
    for (int i = 0; i < 8; ++i){
	#ifdef DEBUGATTACK
		std::cout << "EnemyEngaged iteration " << i;
		std::cout << ":  Checking Enemy display " << enemies[i] << std::endl;
	#endif
	if (NeighboursArr[dirc] && NeighboursArr[dirc]->GetEntity()) {
      		if (enemies[i] == NeighboursArr[dirc]->GetEntity()->GetDisplay()) return NeighboursArr[dirc];
	}
    }
	#ifdef DEBUGATTACK
		std::cout << "Returning NULL" << std::endl;
	#endif

    return 0;
}

//PotionInRange(int dirc) will return a pointer to the potion on the
//targeting tile indicated by dirc if that tile indeed have a potion. 
//Otherwise, return null(0)
Potion* Tile::PotionInRange(int dirc) {
    Potion* p = dynamic_cast<Potion*>(NeighboursArr[dirc]->GetEntity());
    if (p) return p;
    else return 0;
}

//GoldInRange(int dirc) will return a pointer to the potion on the
//targeting tile indicated by dirc if that tile indeed have a potion. 
//Otherwise, return null(0)
Gold* Tile::DragonHoardInRange(int dirc) {
    Gold* p = dynamic_cast<Gold*>(NeighboursArr[dirc]->GetEntity());
    if(p){
        if(p->GetValue() == 6){
            return p;
        }
        return 0;
    }
    else return 0;
}

/*AddNeighbour(Tile* Target) initializes the "NumNeighbours"-th element of 
NeighboursArr and increments NumNeighbours by one with each call.*/ 
void Tile::AddNeighbour(Tile* Target) {
    #ifdef DEBUGTILE
	/*char c;
	if (Target) c = Target->GetDisplay();
	else c = 'N'; // for NULL
	//std::cout << "assigning neighbour " << c << " to " << this->GetDisplay() << std::endl;*/
    #endif
    NeighboursArr[NumNeighbours] = Target;
    ++NumNeighbours;
}

// Gets neighbour with index which
Tile* Tile::GetNeighbour(int which) {
    if (which != -1) return NeighboursArr[which];
    else return NULL;
}

// used when initializing chamber; turns on IsDoneCheck switch so it will not
// be added to Chamber's AvailableTiles twice
void Tile::DoneCheck() {
    IsChecked = true;
}

Entity* Tile::GetEntity(){
    return MyEntity;
}

bool Tile::HasEntity() {
    if (MyEntity) return true;
    else return false;
}

void Tile::DrawEntity(){
    if (MyEntity) MyEntity->DrawEntity();
    //Return the file display '.' by default.
    else std::cout << GetDisplay();
}

//IsNeighbour(Tile* Target) returns true if Target is indeed one of
//the neibhbours of this tile object. Return false otherwise. 
bool Tile::IsNeighbour(Tile* Target){
    for(int i = 0; i < 8 ; i++){
        if(NeighboursArr[i] == Target){
            return true;
        }
    }
    return false;
}

bool Tile::GetAllowWalk() {
    #ifdef DEBUGTILE
        std::cout << "Tile::GetAllowWalk() Called!!!" <<std::endl;
    #endif
    return IsWalkable;
}

void Tile::SetAllowWalk(bool val) {IsWalkable = val;}
