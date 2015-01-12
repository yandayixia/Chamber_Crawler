#ifndef __FLOOR_H__
#define __FLOOR_H__

class Tile;
class Chamber;
class Enemy;
class Item;
class Hero;

// action statement that will be printed out in main loop
extern std::string ActionMsg;

class Floor {
	int CurrentFloor;
	Hero* MyHero;
	Tile * Stairs;
	int NumChambers, NumEnemies, NumPotions, NumGold;
	Tile*** TileArr;
	Chamber** ChamberArr;
	Enemy** EnemyArr;
	Item** ItemArr;

	// Called by DrawInterface(): generates all spawns for a particular chamber
	void DrawMap();
	// Called by DrawInterface(): draws the player’s stats at the bottom of the page
	void DrawStats();
    // CustomInput sets IsWalkable field, then creates Entity on Tile
	// based on input returns true if input is not a tile. It is called by
	// the ConstructChamber function
    bool CustomInput(char Inp, Tile* t);	

public:
	Floor();
	~Floor();
	// GetFloor() returns current floor.
	int GetFloor();	
	// MakeHero(race) initializes Hero (player) character. Called by main once race is obtained
	// so that correct Hero subclass (i.e. Human,...,Troll) can be spawned.
	Hero* MakeHero(std::string race);
	// ClearHero() deletes hero.
	void ClearHero();
	// ConstructLevel(in, Player) reads in the board layout input and builds
	// TileArr according to it. It also initializes each Chamber so that each
	// on-tile entity (i.e. player, item, enemy) can be spawned randomly in 
	// a chamber with a 1/5 chance. This function is intended to be called only once.
	void ConstructLevel(std::istream &in, std::istream &in2, Hero* Player);
	// PopulateChamber() spawns items and enemies on the floor, calling Chamber's
	// spawn functions
	void PopulateChamber();
	// DrawInterface() prints out the layout of the board and the player's stats
	void DrawInterface();
	// MoveEnemy() changes the position of all enemies in EnemyArr
	void MoveEnemy();
	// ClearLevel() is called to restart game or before advancing level
	void ClearLevel();
	// NextLevel() is called to advance the level by clearing objects on the Floor
	// and respawning them
	void NextLevel();
	// CheckEndGame() function checks if the game has ended.
    // It will return false if the game is still going or true if the game has
    // ended.
    //--> When player->GetHP() <= 0, game ends without printing score.(Death of hero)
    //--> When GetFloor*() >= 6. game ends and print score.(Winning) 
    bool CheckEndGame();
};

#endif
