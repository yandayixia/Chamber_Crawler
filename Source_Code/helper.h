#ifndef __HELPER_H__
#define __HELPER_H__

#include <string>

//RandomGen(int Lower, int Upper) returns a random number
//between Lower and Upper(inclusice) 
int RandomGen(int Lower, int Upper);

//CalcDamage(int ATK, int DEF) reutns the damage dealt to 
//the target.
int CalcDamage(int ATK, int DEF);

//IsAttackHit(int HitRate) takes in the % of hit rate out of 100
//that the attacker has and returns true if Hit.
bool IsAttackHit(int HitRate);

// NumberToString(Number) returns a string version of Number
std::string NumberToString (int Number);

#endif
