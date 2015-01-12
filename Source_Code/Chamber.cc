#include <iostream>

#include "Tile.h"
#include "Item.h"
#include "Potion.h"
#include "Gold.h"
#include "Hero.h"
#include "Enemy.h"
#include "Human.h"
#include "Elf.h"
#include "Dwarf.h"
#include "Halfling.h"
#include "Orc.h"
#include "Merchant.h"
#include "Chamber.h"
#include "helper.h"

Chamber::Chamber(): AvailableTiles(NULL), SampleSpace(0) {
	AvailableTiles = new Tile*[25*79];	
}

Chamber::~Chamber() {}

/*Helper function that randomly generates an index referring to 
one of the Available_Tiles.*/
int Chamber::ChooseTile() {
	int chosen = -1;
	while(1) {
		int samp = SampleSpace-1;
		chosen = RandomGen(0, samp);

		// if there is no entity (Character or Item) on the chosen tile
		if (!AvailableTiles[chosen]->HasEntity()) break; 
	}
	return chosen;
}

/* InitChamber(Curr) will determine Curr's neighbours using Curr as a starting point,
recursively calling itself on '.' neighbour tiles that lie within a chamber.
It initializes a Chamber by 'flooding' it so that all tiles can go into the
AvailableTiles array. */
void Chamber::InitChamber(Tile* Curr) {
    #ifdef DEBUG
        std::cout << "---InitChamber Called!" << std::endl;
    #endif

	AvailableTiles[SampleSpace] = Curr;

    #ifdef DEBUG
        std::cout << "----curr registered!" << std::endl;
    #endif

    // marks the tile as checked    
	Curr->DoneCheck();

    #ifdef DEBUG
        std::cout << "----curr checked!" << std::endl;
    #endif
	++SampleSpace;
    #ifdef DEBUG
        std::cout << "---SampleSpace++!" << std::endl;
    #endif

	// may want to generalize using NumNeighbours
	for (int i = 0; i < 8; ++i) {
		Tile* neighb = Curr->GetNeighbour(i);
		if (neighb->GetDisplay() == '.' && !neighb->IsChecked) {
			InitChamber(neighb);
		}
	}
	#ifdef DEBUG
        std::cout << "---Chamber Constructed!!!" << std::endl;
    #endif
	
}


/*During random number generation, if an entry that has previously 
appeared occurs again, then we reroll until a fresh entry appears*/
/*SpawnHero() returns a pointer to the hero(Character) created.*/ 
// MyHero has already been spawned
Hero* Chamber::SpawnHero(Hero* MyHero) {
	int chosen_tile = ChooseTile();
	AvailableTiles[chosen_tile]->AttachEntity(static_cast<Entity*>(MyHero));

	// pointer arithmetic
	MyHero->ModifyTile(AvailableTiles[chosen_tile]);
	return MyHero;
}

/*SpawnStair() returns a pointer to the stair(Item) created.*/
Tile* Chamber::SpawnStair() {
	int chosen_tile = ChooseTile();

	// makes the Stairs pickable and walkable
	Tile* stairs = AvailableTiles[chosen_tile];
	stairs->SetDisplay('\\');
	stairs->SetAllowWalk(true);

	#ifdef DEBUG
		std::cout << "Returning stairs" << std::endl;
	#endif

	return stairs;
};


/*SpawnPotion() returns a pointer to the potion(Item) created.*/
Item* Chamber::SpawnPotion() {

	int chosen_tile = ChooseTile();
	int chosen_potion = RandomGen(1,6);

	// makes the Potion pickable, but not walkable

	Potion* p = 0;

	Tile* t = AvailableTiles[chosen_tile];

	if (chosen_potion == 1) p = new Potion(t, "HP", 10, "BH");
	else if (chosen_potion == 2) p = new Potion(t, "ATK", 5, "BA");
	else if (chosen_potion == 3) p = new Potion(t, "DEF", 5, "BD");
	else if (chosen_potion == 4) p = new Potion(t, "HP", -10, "PH");
	else if (chosen_potion == 5) p = new Potion(t, "ATK", -5, "WA");
	else p = new Potion(t, "DEF", -5, "WD");

	t->AttachEntity(p);

	return p;
}


/*SpawnGold() returns a pointer to the Gold(Item) created.*/
Item* Chamber::SpawnGold(){
	int chosen_tile = ChooseTile();

	Gold* g = NULL;
	Tile* t = AvailableTiles[chosen_tile];

	int gold_range = RandomGen(1,8);

	// normal (5/8), small (2/8), Dragon Hoard (1/8)
	if (gold_range >= 1 && gold_range <= 5) g = new Gold("normal pile", t, 2);
	else if (gold_range >= 6 && gold_range <= 7) g = new Gold("small pile", t, 1);
	else {
		g = new Gold("dragon hoard", t, 6);
	}
	AvailableTiles[chosen_tile]->AttachEntity(g);
	g->ModifyAllowPick(false);
	return g;
}

/*SpawnEnemy() returns a pointer to the enemy(Character) created.*/
Enemy* Chamber::SpawnEnemy() {
	int chosen_tile = ChooseTile();
	int enemy_range = RandomGen(1,18);
	/*
	Human: 4/18
	Dwarf: 3/18
	Halfling: 5/18
	Elf, Orc, Merchant: 2/18
	*/
	Enemy* e = 0;
	if (enemy_range >= 1 && enemy_range <= 4) {
		e = new Human;
	} else if (enemy_range >= 5 && enemy_range <= 7) {
		e = new Dwarf(RandomGen(1,2));
	} else if (enemy_range >= 8 && enemy_range <= 12) {
		e = new Halfling(RandomGen(1,2));
	} else if (enemy_range >= 13 && enemy_range <= 14) {
		e = new Elf(RandomGen(1,2));
	} else if (enemy_range >= 15 && enemy_range <= 16) {
		e = new Orc(RandomGen(1,2));
	} else {
		e = new Merchant;
	}

	e->ModifyTile(AvailableTiles[chosen_tile]);
    #ifdef DEBUG
        std::cout << "---New Enemy correctly constructed." <<std::endl;
    #endif
	return e;
}
