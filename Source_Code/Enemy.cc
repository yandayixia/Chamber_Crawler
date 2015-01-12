#include "Enemy.h"
#include "Character.h" 

#include "Hero.h"
#include "Shade.h"
#include "Drow.h"
#include "Vampire.h"
#include "Troll.h"
#include "Goblin.h"

#include "Tile.h"
#include "helper.h"
#include <map>
#include <iostream>
#include <sstream>
//Enemy's constructor, it will ONLY be called by its sub-classes.
//All of the aruguments will be passed to the constructor as default
//constructors, and MaxHP, defaultATK will be assignmentd to HP, ATK
//respectively. Also, Enmey would always has a predetermined goldstash. 
//MyTile will be null by default.
Enemy::Enemy(int HP, int ATK, int DEF, int GoldStash, char MyDisplay):
Character(HP, HP, ATK, ATK, DEF, DEF, GoldStash, MyDisplay, 0){};

Enemy::~Enemy() {}

//TakeTurn() will be called by Floor.MoveEnemy to start an enemy's turn.
//It will call IsEngaged() to decide whether to: 
//(False) call MoveMe(int random0->7) or
//(true) does nothing. (Attacking is imbeded in IsEngaged.)
//Then it will call EndTurn().
void Enemy::TakeTurn(){
    #ifdef DEBUG
        std::cout << "---TakeTurn() Called." <<std::endl;
    #endif
    if(GetHP() > 0){
        if(IsEngaged()){
        	//If successfully attacks.
            #ifdef DEBUG
            std::cout << "---Hero Engaged and attacked." <<std::endl;
            #endif
        }else{
            #ifdef DEBUG
            std::cout << "---Not Engaged, Move around." <<std::endl;
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
            #ifdef DEBUG
            std::cout << "---Movement Complete." <<std::endl;
            #endif
        }
        EndTurn();
        return;
    }
    #ifdef DEBUG
        std::cout << "Enemy Diabled!" <<std::endl;
    #endif
    return;
}

//IsEngaged() will return true AND attack the hero if he is within 
//melee range. It return false otherwise.
bool Enemy::IsEngaged(){
    #ifdef DEBUG
	std::cout << "Enemy: Checking player engagement" << std::endl;
    #endif
    Tile* PlayerTile = MyTile->IsPlayerEngaged();
    #ifdef DEBUG
	std::cout << "     Check done" << std::endl;
    #endif
    if(PlayerTile != 0){
    	//WARNING: This is assigning an Entity* to a Hero* 
	    #ifdef DEBUG
		    std::cout << "Hero typecast" << std::endl;
	    #endif
        Hero* HeroPT = static_cast<Hero*>(PlayerTile->GetEntity());
	    #ifdef DEBUG
		    std::cout << "attacking hero" << std::endl;
	    #endif
        HeroPT->BeenStruck(this);
        return true;
    }else{
    	return false;
    }
}

//The Attack(... Target) functions specifies what happens when that
//Specific type of target is struck by this particular object. They 
//will ALWAYS be called by the is Enemy::BeenStruck function of Hero class
//or its sub classes. It calls OnStrik() Utility function.
void Enemy::Attack(Shade* Target){
    if(IsAttackHit(50)){
        int damage = CalcDamage(GetATK(), Target->GetDEF());
	    std::string dmg = NumberToString(damage);
        ActionMsg = ActionMsg + GetDisplay() + std::string(" deals ") + dmg + " points of damage to PC. ";
        Target->ModifyHP(-1 * damage);
        OnStrike();
    }else{
        std::string hpleft = NumberToString(GetHP());
        ActionMsg = ActionMsg + GetDisplay() + " (" + hpleft + " HP) " + " missed the PC! " ;
    }
    OnStrikeAttempt();
}
void Enemy::Attack(Drow* Target){
    if(IsAttackHit(50)){
        int damage = CalcDamage(GetATK(), Target->GetDEF());
        std::string dmg = NumberToString(damage);
        ActionMsg = ActionMsg + GetDisplay() + std::string(" deals ") + dmg + " points of damage to PC. ";
        Target->ModifyHP(-1 * damage);
        OnStrike();
    }else{
        std::string hpleft = NumberToString(GetHP());
        ActionMsg = ActionMsg + GetDisplay() + " (" + hpleft + " HP) " + " missed the PC! " ;
    }
    OnStrikeAttempt();
}
void Enemy::Attack(Vampire* Target){
    if(IsAttackHit(50)){
        int damage = CalcDamage(GetATK(), Target->GetDEF());
        std::string dmg = NumberToString(damage);
        ActionMsg = ActionMsg + GetDisplay() + std::string(" deals ") + dmg + " points of damage to PC. ";
        Target->ModifyHP(-1 * damage);
        OnStrike();
    }else{
        std::string hpleft = NumberToString(GetHP());
        ActionMsg = ActionMsg + GetDisplay() + " (" + hpleft + " HP) " + " missed the PC! " ;
    }
    OnStrikeAttempt();
}
void Enemy::Attack(Troll* Target){
    if(IsAttackHit(50)){
        int damage = CalcDamage(GetATK(), Target->GetDEF());
        std::string dmg = NumberToString(damage);
        ActionMsg = ActionMsg + GetDisplay() + std::string(" deals ") + dmg + " points of damage to PC. ";
        Target->ModifyHP(-1 * damage);
        OnStrike();
    }else{
        std::string hpleft = NumberToString(GetHP());
        ActionMsg = ActionMsg + GetDisplay() + " (" + hpleft + " HP) " + " missed the PC! " ;
    }
    OnStrikeAttempt();
}
void Enemy::Attack(Goblin* Target){
    if(IsAttackHit(50)){
        int damage = CalcDamage(GetATK(), Target->GetDEF());
        Target->ModifyHP(-1 * damage);
        std::string dmg = NumberToString(damage);
        ActionMsg = ActionMsg + GetDisplay() + std::string(" deals ") + dmg + " points of damage to PC. ";
        OnStrike();
    }else{
        std::string hpleft = NumberToString(GetHP());
        ActionMsg = ActionMsg + GetDisplay() + " (" + hpleft + " HP) " + " missed the PC! " ;
    }
    OnStrikeAttempt();
}
//OnDeath() is an utility Method that returns the amount of goldstash
//this enemy object has. 
int Enemy::OnDeath(){
    //Detach it from the board.
    this->GetTile()->DetachEntity();
    this->ModifyTile(0);
    return this->GetGoldStash();
}
//OnStrike() is an utility Method that usually does nothing, but will
//be overrided to fullfill certain monster's speical abilities.
//Example:
//Elf: ExtraAttack Ability.
void Enemy::OnStrike(){
    return;
}
//OnStrikeAttempt() is an utility Method that usually does nothing, but
//it ALWAYS called after hit/miss calculation and damage calculation to
//implement certain effects:
//Example:
//Elf, double attack. 
void Enemy::OnStrikeAttempt(){
    return;
}
//OnTakeHit() is an utility Method that usually does nothing, but will
//be overrided to fullfill certain monster's special abilities.
//Example:
//Merchant: Turns hostile once taken a hit.
void Enemy::OnTakeHit(){
	return;
}

void Enemy::EndTurn() {}
