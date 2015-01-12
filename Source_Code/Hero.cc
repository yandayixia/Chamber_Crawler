#include "Character.h"
#include "Enemy.h"
#include "Human.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Orc.h"
#include "Merchant.h"
#include "Halfling.h"
#include "Dragon.h"
#include "Potion.h"
#include "Hero.h"
#include "helper.h"
#include <iostream>
#include <string>

//Hero's constructor, it will ONLY be called by its sub-classes.
//All of the aruguments will be passed to the constructor as default
//constructors. It will not take in a MyTile argument. If want to 
//specify MyTile, call ModifyTile(Tile*) to do so. It will fill 
//Character's constructor will the approperiate fields.
//examples: MaxHp = HP, DefaultATK = ATK, MyDisplay = "@".
Hero::Hero(std::string Race, int MaxHP, int HP,int ATK, int DEF): 
    Character(MaxHP, HP, ATK, ATK, DEF, DEF, 0, '@'), Race(Race) {
        for(int i = 0; i < 6; i++){
            KnowledgePool[i] = false;
        }    
    }

Hero::~Hero(){}

//returns true if target is in KnowledgePool.
bool Hero::IsKnown(std::string target){
    if(target == "BH"){
        return KnowledgePool[0];
    }else if(target == "BA"){
        return KnowledgePool[1];
    }else if(target == "BD"){
        return KnowledgePool[2];
    }else if(target == "PH"){
        return KnowledgePool[3];
    }else if(target == "WA"){
        return KnowledgePool[4];
    }else if(target == "WD"){
        return KnowledgePool[5];
    }else{
        return false;
    }
}
    
//copies the content to 
void Hero::AddtoKnowledgePool(std::string target){
    //entry 0 => BH
    //entry 1 => BA
    //entry 2 => BD
    //entry 3 => PH
    //entry 4 => WA
    //entry 5 => WD
    if(target == "BH"){
        KnowledgePool[0] = true;
    }else if(target == "BA"){
        KnowledgePool[1] = true;
    }else if(target == "BD"){
        KnowledgePool[2] = true;
    }else if(target == "PH"){
        KnowledgePool[3] = true;
    }else if(target == "WA"){
        KnowledgePool[4] = true;
    }else if(target == "WD"){
        KnowledgePool[5] = true;
    }else{
        return;
    }
}


void Hero::SeePotion(){
    bool first_time = true;
    for(int i= 0; i <= 7; i++){
        Potion * t_potion = GetTile()->PotionInRange(i);
        if(t_potion){
            if(IsKnown(t_potion->GetName())){
                if(first_time){
                    ActionMsg = ActionMsg + " sees " + t_potion->GetName();
                    first_time = false;
                }else{
                    ActionMsg = ActionMsg + " and " + t_potion->GetName();    
                }
            }else{
                if(first_time){
                    ActionMsg = ActionMsg + " and sees Unknown Potion";
                    first_time = false;
                }else{
                    ActionMsg = ActionMsg + " and Unknown Potion";
                }

            }
        }
    }
    ActionMsg = ActionMsg + ". ";  
}

//The access-or function for the new Race field.
std::string Hero::GetRace(){return Race;}

/*AttemptToHit(int dirc) attempts to attack the Entity on the tile
indicated by dirc. It returns true if the move was successful and 
false otherwise so that the player won't waste another turn.
Example: (dirc value)
7 0 1
6 @ 2
5 4 3
*/
bool Hero::AttemptToHit(int dirc) {
    // See if enemy is on tile
    // Call attack function on enemy
    // EnemyEngaged returns pointer to enemy's tile if enemy exists in tile of direction dirc
	#ifdef DEBUGATTACK
		std::cout << "Calling EnemyEngaged" << std::endl;
	#endif

    Tile* t = MyTile->EnemyEngaged(dirc);

    if (t) {
	#ifdef DEBUGATTACK
		std::cout << "Enemy is engaged: tile t exists" << std::endl;
	#endif
        Enemy* e = static_cast<Enemy *> (t->GetEntity());
	#ifdef DEBUGATTACK
		std::cout << "Enemy static casted" << std::endl;
	#endif
	e->BeenStruck(this);
	#ifdef DEBUGATTACK
		std::cout << "Enemy's beenstruck function called" << std::endl;
	#endif
        return true;
    } else {
        return false;
    }
}

/*AttemptToUse works in a similar fashion to AttemptToHit; tries to drink potion
in the direction specified by int*/
bool Hero::AttemptToUse(int dirc){
    #ifdef DEBUGITEM
        std::cout << "Attempting to use..." << std::endl;
    #endif
    Potion* p = MyTile->PotionInRange(dirc);
    if (p) {
        // if potion exists.
        #ifdef DEBUGITEM
            std::cout << "Using Potion..." << std::endl;
        #endif
        AddtoKnowledgePool(p->GetName());
        UsePotion(p);

        #ifdef DEBUGITEM
            std::cout << "Drunk potion!" << std::endl;
        #endif
        return true;
    }
    #ifdef DEBUGITEM
        std::cout << "FAILED to drink! Potion does not exist" << std::endl;
    #endif
    //if that tile doesn't exist or doesn't have a potion.
    return false;
}

//UsePotion(Potion* Target) will execute the effect of the potion.
void Hero::UsePotion(Potion* Target){
    #ifdef DEBUGITEM
        std::cout << "about to getstat" << std::endl;
    #endif
    std::string stat = Target->GetStat();
    if(stat == "HP"){
        ModifyHP(Target->GetStrength());
    }else if(stat == "ATK"){
        ModifyATK(Target->GetStrength());
    }else if(stat == "DEF"){
        ModifyDEF(Target->GetStrength());
    }else{
        return;
    }
    ActionMsg = ActionMsg + "PC uses " + Target->GetName();
    Target->GetTile()->DetachEntity();
}

//All of the Attack(Type Target)functions are VIRTUAL so that they can 
//be overrided by the subclasses. It will ALWAYS be called by a 
//BeenStruck(...) function from Enemy class and its subclasses.
//Check Attack's accuracy first, and if hit, call The hit and 
//OnAttack() methods. 
void Hero::Attack(Human* Target) {
    std::string hpleft = NumberToString(Target->GetHP());
    if(IsAttackHit(100)){
        int damage = CalcDamage(GetATK(), Target->GetDEF()) * (-1);
        Target->ModifyHP(damage);
        std::string dmg =NumberToString(damage*(-1));
        ActionMsg = ActionMsg + "PC deals " + dmg + " damage to " + Target->GetDisplay() + " (" + hpleft + " HP). ";
        OnAttack();
    }else{
        ActionMsg = ActionMsg + "PC's attack missed " + Target->GetDisplay() + " (" + hpleft + " HP). ";
    }
    if(Target->GetHP() <= 0){
		std::string gold = NumberToString(Target->OnDeath());
		ActionMsg = std::string("Player has slain ") + Target->GetDisplay() + ", earning " + gold + " gold.";
        ModifyGoldStash(Target->OnDeath());
        OnSlay();
    }
}

void Hero::Attack(Dwarf* Target) {
    std::string hpleft = NumberToString(Target->GetHP());
    if(IsAttackHit(100)){
        int damage = CalcDamage(GetATK(), Target->GetDEF()) * (-1);
        Target->ModifyHP(damage);
        std::string dmg =NumberToString(damage*(-1));
        ActionMsg = ActionMsg + "PC deals " + dmg + " damage to " + Target->GetDisplay() + " (" + hpleft + " HP). ";
        OnAttack();
    }else{
        ActionMsg = ActionMsg + "PC's attack missed " + Target->GetDisplay() + " (" + hpleft + " HP). ";
    }
    if(Target->GetHP() <= 0){
        std::string gold = NumberToString(Target->OnDeath());
        ActionMsg = std::string("Player has slain ") + Target->GetDisplay() + ", earning " + gold + " gold.";
        ModifyGoldStash(Target->OnDeath());
        OnSlay();
    }
}

void Hero::Attack(Elf* Target){
    std::string hpleft = NumberToString(Target->GetHP());
    if(IsAttackHit(100)){
        int damage = CalcDamage(GetATK(), Target->GetDEF()) * (-1);
        Target->ModifyHP(damage);
        std::string dmg =NumberToString(damage*(-1));
        ActionMsg = ActionMsg + "PC deals " + dmg + " damage to " + Target->GetDisplay() + " (" + hpleft + " HP). ";
        OnAttack();
    }else{
        ActionMsg = ActionMsg + "PC's attack missed " + Target->GetDisplay() + " (" + hpleft + " HP). ";
    }
    if(Target->GetHP() <= 0){
        std::string gold = NumberToString(Target->OnDeath());
        ActionMsg = std::string("Player has slain ") + Target->GetDisplay() + ", earning " + gold + " gold.";
        ModifyGoldStash(Target->OnDeath());
        OnSlay();
    }
}

void Hero::Attack(Orc* Target) {
    std::string hpleft = NumberToString(Target->GetHP());
    if(IsAttackHit(100)){
        int damage = CalcDamage(GetATK(), Target->GetDEF()) * (-1);
        Target->ModifyHP(damage);
        std::string dmg =NumberToString(damage*(-1));
        ActionMsg = ActionMsg + "PC deals " + dmg + " damage to " + Target->GetDisplay() + " (" + hpleft + " HP). ";
        OnAttack();
    }else{
        ActionMsg = ActionMsg + "PC's attack missed " + Target->GetDisplay() + " (" + hpleft + " HP). ";
    }
    if(Target->GetHP() <= 0){
        std::string gold = NumberToString(Target->OnDeath());
        ActionMsg = std::string("Player has slain ") + Target->GetDisplay() + ", earning " + gold + " gold.";
        ModifyGoldStash(Target->OnDeath());
        OnSlay();
    }
}

void Hero::Attack(Merchant* Target) {
    std::string hpleft = NumberToString(Target->GetHP());
    if(IsAttackHit(100)){
        int damage = CalcDamage(GetATK(), Target->GetDEF()) * (-1);
        Target->ModifyHP(damage);
        std::string dmg =NumberToString(damage*(-1));
        ActionMsg = ActionMsg + "PC deals " + dmg + " damage to " + Target->GetDisplay() + " (" + hpleft + " HP). ";
        OnAttack();
    }else{
        ActionMsg = ActionMsg + "PC's attack missed " + Target->GetDisplay() + " (" + hpleft + " HP). ";
    }
    if(Target->GetHP() <= 0){
        std::string gold = NumberToString(Target->OnDeath());
        ActionMsg = std::string("Player has slain ") + Target->GetDisplay() + ", earning " + gold + " gold.";
        ModifyGoldStash(Target->OnDeath());
        OnSlay();
    }
}

void Hero::Attack(Halfling* Target) {
    std::string hpleft = NumberToString(Target->GetHP());
    if(IsAttackHit(50)){
        int damage = CalcDamage(GetATK(), Target->GetDEF()) * (-1);
        Target->ModifyHP(damage);
        std::string dmg =NumberToString(damage*(-1));
        ActionMsg = ActionMsg + "PC deals " + dmg + " damage to " + Target->GetDisplay() + " (" + hpleft + " HP). ";
        OnAttack();
    }else{
        ActionMsg = ActionMsg + "PC's attack missed " + Target->GetDisplay() + " (" + hpleft + " HP). ";
    }
    if(Target->GetHP() <= 0){
        std::string gold = NumberToString(Target->OnDeath());
        ActionMsg = std::string("Player has slain ") + Target->GetDisplay() + ", earning " + gold + " gold.";
        ModifyGoldStash(Target->OnDeath());
        OnSlay();
    }
}

void Hero::Attack(Dragon* Target){
    std::string hpleft = NumberToString(Target->GetHP());
    if(IsAttackHit(100)){
        int damage = CalcDamage(GetATK(), Target->GetDEF()) * (-1);
        Target->ModifyHP(damage);
        std::string dmg =NumberToString(damage*(-1));
        ActionMsg = ActionMsg + "PC deals " + dmg + " damage to " + Target->GetDisplay() + " (" + hpleft + " HP). ";
        OnAttack();
    }else{
        ActionMsg = ActionMsg + "PC's attack missed " + Target->GetDisplay() + " (" + hpleft + " HP). ";
    }
    if(Target->GetHP() <= 0){
        ModifyGoldStash(Target->OnDeath());
        ActionMsg = std::string("Player has slain ") + Target->GetDisplay() + ".";
        OnSlay();
    }
}
/*GetScore() is an accessor wrapper function that calls GetGoldStash(),
However it will help Shade to apply its score bonus.*/
int Hero::GetScore() { return GetGoldStash(); }
/*OnAttack() is an utility function that will be called by the 
Attack(...) functions evertime. It does nothing usually, but does 
help implement those effects that activates when an attack is hit.
Example:
-->Vampire drain 5 HP.*/
void Hero::OnAttack() {}
/*OnSlay() is an utility function that will be called by the 
Attack(...)functions if the player is able to drop the HP of
target to zero. It does nothing usually, but does help on
implement those effects that activates when a monster is slain.
Example:
-->Goblin steal 5 gold.*/
void Hero::OnSlay() {}

void Hero::EndTurn() {}
