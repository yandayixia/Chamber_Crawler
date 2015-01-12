#include <iostream>
#include "Item.h"

Item::Item(char Display, bool AllowPick, bool AllowWalk, Tile* MyTile): 
	Entity(Display), AllowPick(AllowPick), AllowWalk(AllowWalk), MyTile(MyTile) {}

Item::~Item() {}

// Getter functions for AllowPick, AllowWalk and Tile
bool Item::GetAllowPick() {
	return AllowPick;
}
bool Item::GetAllowWalk() {
	return AllowWalk;
}

Tile* Item::GetTile() {
	return MyTile;
}

// Setter functions for AllowPick, AllowWalk and Tile
void Item::ModifyAllowPick(bool NewVal) {AllowPick = NewVal;}
void Item::ModifyAllowWalk(bool NewVal) {AllowWalk = NewVal;}
void Item::AttachTile(Tile* T) {MyTile = T;}
void Item::DetachTile() {MyTile = 0;} // resets MyTile field to NULL
