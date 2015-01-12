#ifndef __FLAG_H__
#define __FLAG_H__

using namespace std;

#include <string>

/* The following class applies special effects relevant to Potions, Enemies,
the player's race and the Dragon Hoard.
*/

class Flag: public Entity {

	/* 
	The flags that will be implemented are:
	[FlagIndex]. [FlagName]

	1. Attack_Dodge
	2. Bad_Blood
	3. Quick_Attack
	4. Fast_Defender
	5. Racial_Slayer
	6. Group_Alert
	7. Change_Stat: for the potions
	8. Boost_Score
	9. Boost_Potion
	10. Health_Steal
	11. Health_Regen
	12. Steal_Gold
	13. Add_Gold

	[FlagTarget]: definition
	0. Player HP is the target
	1. Player Atk
	2. Player Def
	3. Player gold
	*/

	string FlagName;
	int FlagStrength, FlagIndex, FlagTarget;
   public:
   	Flag(int name, int strength, int index, int target);
   	int GetIndex();
   	int GetStrength();
   	int GetTarget();
   	string GetName();
};

#endif