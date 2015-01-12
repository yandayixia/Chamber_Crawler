#ifndef __GOLD_H__
#define __GOLD_H__
#include "Item.h"
#include <string>

class Gold: public Item {
    std::string Name;
    int Value;
public:
	Gold(std::string Name, Tile* MyTile, int Value);
	~Gold();
	/*GetValue() returns the amount of gold pieces this Item
	has or is worth (DLC).*/
	int GetValue();
	std::string GetName();
};

#endif
