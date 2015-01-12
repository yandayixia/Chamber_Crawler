#include "helper.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream>

//RandomGen(int Lower, int Upper) returns a random number
//between Lower and Upper(inclusice) 
int RandomGen(int Lower, int Upper){
   int dist = Upper - Lower + 1;
   return (rand() % dist) + Lower;
}

//CalcDamage(int ATK, int DEF) reutns the damage dealt to 
//the target.
int CalcDamage(int ATK, int DEF){
    float result = 0;
	#ifdef DEBUGATTACK
		std::cout << "Result is " << result << std::endl;
	#endif
    result = 100;
	#ifdef DEBUGATTACK
		std::cout << "Result is " << result << std::endl;
	#endif
    float defloat = static_cast<float>(DEF);
    result = 100/(100 + defloat);
	#ifdef DEBUGATTACK
		std::cout << "Result is " << result << std::endl;
	#endif
    float atk_f = static_cast<float>(ATK);
    result = result * atk_f;
	#ifdef DEBUGATTACK
		std::cout << "Result is " << result << std::endl;
	#endif
	return ceil(result);
}
//IsAttackHit(int HitRate) takes in the % of hit rate out of 100
//that the attacker has and returns true if Hit.
bool IsAttackHit(int HitRate){
	if(RandomGen(1,100) <= HitRate){
		return true;
	}
    return false;
}

// NumberToString(Number) returns a string version of Number
std::string NumberToString (int Number) {
	std::stringstream ss;
	ss << Number;
	return ss.str();
}
