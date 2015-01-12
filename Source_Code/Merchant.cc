#include "Merchant.h"
#include "Hero.h"
#include "Tile.h"
#include "helper.h"
#include <iostream>
#include <map>
bool Merchant::IsHostile = false;

//The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
//Specific type of attacker hits this object. It calls OnTakeHit() utility
//method FIRST.
void Merchant::BeenStruck(Hero* Attacker){
    Attacker->Attack(this);
    OnTakeHit();
}
//Merchant's constructor, it ALWAYS has goldstash value 4!
//DO NOT pass Merchant a new GoldStash value!
Merchant::Merchant(int GoldStash, int HP, int ATK, int DEF):
    Enemy(HP, ATK, DEF, GoldStash, 'M') {}
//Merchant's concrete destructor.
Merchant::~Merchant() {}
//OnTakeHit() is overloaded to call BecomeHostile().
void Merchant::OnTakeHit() {BecomeHostile();}
//BecomeHostile() is a static method that changes IsHostile to True.
void Merchant::BecomeHostile(){
    IsHostile = true;
	return;
}
//GetIsHostile() simply returns IsHostile. 
bool Merchant::GetIsHostile() {return IsHostile;}
//TakeTurn() is overrided to check if the Merchants are hostile.
void Merchant::TakeTurn() {
    if(GetHP() > 0){
        if (IsHostile) {
            if(IsEngaged()){
            	//If successfully attacks.
                return;
            }
        }
        #ifdef DEBUG
        std::cout << "---Not Hostile, Move around." <<std::endl;
        #endif
    	//Else randomly moves around.
        std::map <int, int> Choice_Dirc;
        int OptionNum = 0;
        for(int i =0; i < 8; i++){
            Tile* TempTile = MyTile->GetNeighbour(i);
            if(TempTile == 0){
                continue;
            }else{
                //If That tile is okay for hero to walk and:
                //that tile doesn't have anything on it
                if(TempTile->OkToWalk(i) && (TempTile->GetDisplay() != '#') && (TempTile->GetDisplay() != '+') && (TempTile->GetEntity() == 0)){
                    //This tile is okay for Monster to walk:
                    Choice_Dirc.insert(std::pair<int,int> (OptionNum, i));
                    OptionNum++;
                }
            }
        }
        if(OptionNum == 0){
            //If The enemy is completely surrounded and can't move, Idol
        }else if(MoveMe(Choice_Dirc[RandomGen(0,OptionNum - 1)])){
            //If move and success, Idol.
        }else{
            //If can't move, Idol
        }
    }
    #ifdef DEBUG
    std::cout << "---Movement Complete." <<std::endl;
    #endif
}
