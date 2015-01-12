#ifndef __ITEM_H__
#define __ITEM_H__
#include "Entity.h"
#include "Tile.h"

class Item: public Entity{
	// Allows the item to be picked up/walked on
    bool AllowPick;
    bool AllowWalk;
    Tile* MyTile;
    
public:
	//constructor that takes in four parameters to initialize Item.
	Item(char Display, bool AllowPick, bool AllowWalk, Tile* MyTile);
	virtual ~Item();
	// Getter functions for AllowPick, AllowWalk and Tile
	bool GetAllowPick();
	bool GetAllowWalk();
	Tile* GetTile();
	// Setter functions for AllowPick, AllowWalk and Tile
	void ModifyAllowPick(bool NewVal);
	void ModifyAllowWalk(bool NewVal);
	void AttachTile(Tile* T);
	void DetachTile(); // resets MyTile field to NULL
};

#endif
