#include "Gold.h"
#include "Dragon.h"
#include <map>
#include <iostream>
#include "Hero.h"
#include "helper.h"
//The Enemy::BeenStruck(... Attacker) functions specifies what happens when that
//Specific type of attacker hits this object. It calls OnTakeHit() utility
//method FIRST.
void Dragon::BeenStruck(Hero* Attacker){
    Attacker->Attack(this);
    OnTakeHit();
}
//Dragon's constructor, it ALWAYS has goldstash value 0!
//DO NOT pass Dragon a new GoldStash value!
Dragon::Dragon(int GoldStash, int HP, int ATK, int DEF):
    Enemy(HP, ATK, DEF, GoldStash, 'D') {}
//Dragon's concrete destructor. Doesn't do anything extra.
Dragon::~Dragon() {}
//MUST call SetTreasure(Item* MyTreasure) after create each 
//dragon object. It sets Treasure to MyTreasure.  
void Dragon::SetTreasure(Gold* MyTreasure){
    Treasure = MyTreasure;
    Treasure->ModifyAllowPick(false);
    return;
}
//TakeTurn() is overrided to never move the dragon.
void Dragon::TakeTurn(){
    #ifdef DEBUG
        std::cout << "---Dragon::TakeTurn() Called." << std::endl;
    #endif
    if(GetHP() > 0){
        if(IsEngaged()){
            //If successfully attacks.
        }else{
            #ifdef DEBUG
                std::cout << "---Move Dragon around." << std::endl;
            #endif
            //Dragon can ONLY move around tiles around itself that are ACTUALLY
            //around the gold pile as well.
            std::map <int, int> Choice_Dirc;
            int OptionNum = 0;
            for(int i =0; i < 8; i++){
                Tile* TempTile = MyTile->GetNeighbour(i);
                if(TempTile == 0){
                    continue;
                }else{
                    //If That tile is okay for hero to walk and:
                    //that tile doesn't have anything on it
                    if(TempTile->OkToWalk(i) && (TempTile->GetEntity() == 0)){
                        //This tile is okay for Monster to walk:
                        //If this tile is also a neighbour of the gold tile.
                        if(TempTile->IsNeighbour(Treasure->GetTile())){
                            Choice_Dirc.insert(std::pair<int,int> (OptionNum, i));
                            OptionNum++;
                            #ifdef DEBUG
                                std::cout << "---Valid Tile located!" << std::endl;
                            #endif
                        }
                    }
                }
            }
            if(OptionNum == 0){
                //If The enemy is completely surrounded and can't move, Idol
            }else if(MoveMe(Choice_Dirc[RandomGen(0,OptionNum - 1)])){
                //If move and success, Idol.
            }else{
                //If move failed, Idol.
            }
        }
        EndTurn();
    }
    return;
}
//IsEngaged() is overrided to check if the character is near 
//the dragon or the treasure. IMMEDIATELY attack if is.
bool Dragon::IsEngaged() {
    #ifdef DEBUG
        std::cout << "---Dragon::IsEngaged() Called." << std::endl;
    #endif
    //If player near Dragon itself
    Tile* PlayerTile = MyTile->IsPlayerEngaged();
    //If not, check if Player near the Dragon Hoard
    if (!PlayerTile) PlayerTile = Treasure->GetTile()->IsPlayerEngaged();
    #ifdef DEBUG
        std::cout << "---Check player engage done." << std::endl;
    #endif
    if(PlayerTile){
        #ifdef DEBUG
        std::cout << "---Player Within Ragne!!!" << std::endl;
        #endif
        //WARNING: This is assigning an Entity* to a Hero* 
        Hero* HeroPT = static_cast<Hero*>(PlayerTile->GetEntity());
        HeroPT->BeenStruck(this);
        return true;
    }else{
        return false;
    }
}
//OnDeath() is overrided to make the Treasure pickable, calls
//item.ModifyAllowPick(true).
int Dragon::OnDeath() {
    Treasure->ModifyAllowPick(true);
    this->GetTile()->DetachEntity();
    this->ModifyTile(0);
    return GetGoldStash();
}
