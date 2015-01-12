#include "Gold.h"
#include <string>

// Dragon's on-death function calls Item's ModifyAllowPick (sets it back to true)
Gold::Gold(std::string Name, Tile* MyTile, int Value):
	Item('G', true, true, MyTile), Name(Name), Value(Value) {}

Gold::~Gold() {}

std::string Gold::GetName() {return Name;}

/*GetValue() returns the amount of gold pieces this Item
has or is worth (DLC).*/
int Gold::GetValue() {return Value;}
