#include "Potion.h"
#include "Enemy.h"
#include "Drow.h"
#include <string>
//The BeenStruck(Enemy Attacker)functions are VIRTUAL so that  
//they can be overrided by the subclasses. It will ALWAYS be calling 
//an Attack(...) function in the Enemy class and its subclasses.
void Drow::BeenStruck(Enemy* Attacker) { Attacker->Attack(this); }
//Drow's constructor. It will not take in a MyTile argument. If want to 
//specify MyTile, call ModifyTile(Tile*) to do so. 
Drow::Drow(int HP,int ATK, int DEF):
    Hero("Drow", HP, HP, ATK, DEF) {}
//Drow's concrete constructor. It doesn't do anything special.
Drow::~Drow() {}
//UsePotion() is overrided to multiply the effectiveness by 1.5
void Drow::UsePotion(Potion* Target){
    std::string stat = Target->GetStat();
    if(stat == "HP"){
        ModifyHP(1.5 * Target->GetStrength());
    }else if(stat == "ATK"){
        ModifyATK(1.5 * Target->GetStrength());
    }else if(stat == "DEF"){
        ModifyDEF(1.5 * Target->GetStrength());
    }else{
        return;
    }
    ActionMsg = ActionMsg + "PC uses " + Target->GetName();
    Target->GetTile()->DetachEntity();
}
