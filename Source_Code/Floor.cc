#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <map>

#include "Floor.h"
#include "Chamber.h"
#include "Tile.h"
#include "Character.h"
#include "Hero.h"
#include "Shade.h"
#include "Drow.h"
#include "Vampire.h"
#include "Troll.h"
#include "Goblin.h"
#include "Enemy.h"
#include "Human.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Orc.h"
#include "Merchant.h"
#include "Halfling.h"
#include "Dragon.h"
#include "helper.h"
#include "Item.h"
#include "Potion.h"
#include "Gold.h"

// Floor's constructor, called by main.
Floor::Floor(): CurrentFloor(1), MyHero(NULL), NumChambers(0), NumEnemies(20), NumPotions(10), NumGold(10), TileArr(NULL) {
	// init TileArr, all Arr
	ChamberArr = new Chamber*[5];
	EnemyArr = new Enemy*[20];
	ItemArr = new Item*[20];
}

// all Floor attributes are checked (on their existance) before deleted, just in case the 
// game is quit before they are spawned
Floor::~Floor(){
	#ifdef DEBUG
		std::cout << "Destroying TileArr..." << std::endl;
	#endif
	if (TileArr) {
		for(int row = 0;row < 25;row++){
			for(int col = 0; col<79 ; col++){
				delete TileArr[row][col];
			}
			delete [] TileArr[row];
		}
		delete [] TileArr;
	}
	#ifdef DEBUG
		std::cout << "Destroying ChamberArr..." << std::endl;
	#endif
	if (ChamberArr) {
		for(int cham = 0; cham < NumChambers; cham++){
			delete ChamberArr[cham];
		}
		delete [] ChamberArr;
	}
	#ifdef DEBUG
		std::cout << "Destroying EnemyArr..." << std::endl;
	#endif
	if (EnemyArr) {
		for(int enm = 0; enm < NumEnemies; enm++){
			delete EnemyArr[enm];
		}
		delete [] EnemyArr;
	}
	#ifdef DEBUG
		std::cout << "Destroying ItemArr..." << std::endl;
	#endif
	if (ItemArr) {
		for(int itm = 0; itm < NumPotions + NumGold; itm++){
			delete ItemArr[itm];
		}
		delete [] ItemArr;

	}
	#ifdef DEBUG
		std::cout << "Destroying Player..." << std::endl;
	#endif
	if (MyHero) delete MyHero;
}

bool first_call = true;// if this is the first time CustomInput is called.

// CustomInput sets IsWalkable field, then creates Entity on Tile
// based on input returns true if input is not a tile. It is called by
// the ConstructChamber function to handle non-tile character inputs
bool Floor::CustomInput (char Inp, Tile* t){
	#ifdef DEBUG
	//	std::cout << "Entered CustomInput" << std::endl;
	#endif

	Enemy* e= 0; // in case this tile has an enemy on it

	// player cannot walk on walls or void spaces
    if ((Inp == '|') || (Inp == '-') || (Inp == ' ')) {
        t->SetAllowWalk(false);
        return false;
    }else if ((Inp == '.') || (Inp == '#') || (Inp == '+') || (Inp == '\\')) {
        t->SetAllowWalk(true);
        if(Inp == '\\'){
        	Stairs = t;
        }
        return false;
    // if input does not refer to a tile    
    }else {  
	    if(first_call){
			NumPotions = 0;
			NumGold = 0;
			NumEnemies = 0;
			first_call =false;
	    }
	    // if the input is the player position
        if (Inp == '@') {
            t->AttachEntity(MyHero);
            MyHero->ModifyTile(t);
        	t->SetAllowWalk(true);
        // if the input is a potion or treasure(gold)
        } else if (Inp >= '0' && Inp <= '9') {
            if (Inp >= '0' && Inp <= '5')   {
            	Potion* p = NULL;
                if (Inp == '0') {
                	p = new Potion(t, "HP", 10, "BH");	
                } else if (Inp == '1') {
                	p = new Potion(t, "ATK", 5, "BA");
                } else if (Inp == '2') {
                	p = new Potion(t, "DEF", 5, "BD");
                } else if (Inp == '3') {
                	p = new Potion(t, "HP", -10, "PH");
                } else if (Inp == '4') {
                	p = new Potion(t, "ATK", -5, "WA");
				} else p = new Potion(t, "DEF", -5, "WD");
				// add stuff: add to arrays
            	t->SetAllowWalk(true);
				t->AttachEntity(p);
         		//std::cout << "***POTIONS!!!" << std::endl;
	            ItemArr[NumPotions+NumGold] = p;
				++NumPotions;
                return true;
            } else {
            	Gold* g = NULL;
                if (Inp == '6') g = new Gold("normal pile", t, 2);
                else if (Inp == '7') g = new Gold("small pile", t, 1);
                else if (Inp == '8') g = new Gold("merchant hoard", t, 4);
                else g = new Gold("dragon hoard", t, 6);
                g->ModifyAllowPick(true);
            	t->SetAllowWalk(true);
                t->AttachEntity(g);
                ItemArr[NumPotions+NumGold] = g;
                ++NumGold;
                return  true;
				// add stuff: add to arrays
            } // if

        // if the input is an enemy
        }else{
            if(Inp == 'H'){
            	e = new Human;
            }else if (Inp == 'W'){
            	 e = new Dwarf(RandomGen(1,2));
            }else if (Inp == 'E'){
            	e = new Elf(RandomGen(1,2));        	
            }else if (Inp == 'O'){
            	e = new Orc(RandomGen(1,2));
            }else if (Inp == 'M'){
            	e = new Merchant;
            }else if (Inp == 'D'){
                for(int i= 0; i< 8; i++){
                    Gold* temp_g = t->DragonHoardInRange(i);
                	if(temp_g){
                		e = new Dragon;
                		Dragon* temp_e = dynamic_cast<Dragon*>(e);
                        temp_e->SetTreasure(temp_g);
                	}
                }	
            }else if(Inp == 'L'){
                e = new Halfling(RandomGen(1,2)); // should be the final else case
            }
    
            if (e) {
            	e->ModifyTile(t);
            	t->AttachEntity(e);
            	t->SetAllowWalk(true);
            	EnemyArr[NumEnemies] = e;
        	    ++NumEnemies;
            }
        }
        return true;
    } // if
}

// ConstructLevel(in, Player) reads in the board layout input and builds
// TileArr according to it. It also initializes each Chamber so that each
// on-tile entity (i.e. player, item, enemy) can be spawned randomly in
// a chamber with a 1/5 chance. This function is intended to be called only once.
void Floor::ConstructLevel(std::istream &in, std::istream &in2, Hero* Player) {
	std::string line;
	bool willSpawn = true;
	bool custom = false; // determines if tile is custom input (i.e. a spawned Entity)
	TileArr = new Tile**[25];
	for (int y = 0; y < 25; ++y) {
		TileArr[y] = new Tile*[79];
	} // y-coord forloop
	int x = 0;
	char floor_base[7] = {'.', ' ', '+', '-', '|', '#', '\\'};	
// This algorithm of reading in each line assumes input is 79 * 25 and rectangular
// (i.e. all lines of 'in' are the same length)
	for (int y=0; y<25; ++y) {
		x = 0;
		getline (in, line);
		if (in.eof()) break;
		if (in.fail()) in.ignore();
		// right now, assuming that all input is valid (79 columns for each row)
		for (std::string::iterator it = line.begin(); it != line.end(); ++it, ++x) {
			bool is_base = false;
			// interesting: current = TileArr[y][x] and current = new Tile does not initialize the tile
			for (int i = 0; i < 7; ++i) {
				if (it[0] == floor_base[i]) {
					TileArr[y][x] = new Tile(it[0]);
					is_base = true;
					break;
				}
			}
			// if this tile has a spanwed input on it, put a '.' tile underneath it
			if (!is_base) {
				TileArr[y][x] = new Tile('.');
			}
		} // read-in for loop that iterates through x-coord
	} // y-coord for loop
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 79; ++j) {

			// assumes that all neighbours exist
			bool left = true;
			bool right = true;
			bool top = true;
			bool bottom = true;	

			Tile *current = TileArr[i][j];
			#ifdef DEBUGNEIGHB
				if (current) std::cout << "current's display is |" << current->GetDisplay() << "|" << std::endl;
				else std::cout << "current does not exist" << std::endl;
			#endif
	
			// determines which of 4 neighbours does not exist
			if (i-1 < 0) {
				top = false;
			} 
			if (i+1 >= 25) {
				bottom = false;
			}
			if (j-1 < 0) {
				left = false;
			} 
			if (j+1 >= 79) {
				right = false;
			}
			

			// adds tile's neighbours depending on which ones exist

			// Rename all Walkable to OktoWalk
			#ifdef DEBUGNEIGHB
				std::cout << "About to add neighbours" << std::endl;
			#endif
			if (top) {
				#ifdef DEBUGNEIGHB
					std::cout << "Top neighbour" << std::endl;
				#endif
				current->AddNeighbour(TileArr[i-1][j]); // index 0

				// adds top right neighbour
				if (right) current->AddNeighbour(TileArr[i-1][j+1]); // index 1
				else current->AddNeighbour(NULL);
			} else {
				#ifdef DEBUGNEIGHB
					std::cout << "Top neighbour off" << std::endl;
				#endif

				current->AddNeighbour(NULL);
				#ifdef DEBUGNEIGHB
					std::cout << "Neighbour 1 added" << std::endl;
				#endif
				current->AddNeighbour(NULL);
				#ifdef DEBUGNEIGHB
					std::cout << "Neighbour 2 added" << std::endl;
				#endif
			} //if


			if (right) {
				#ifdef DEBUGNEIGHB
					std::cout << "Right neighbour" << std::endl;
				#endif
				current->AddNeighbour(TileArr[i][j+1]);

				if (bottom) current->AddNeighbour(TileArr[i+1][j+1]); // index 2
				else current->AddNeighbour(NULL); // index 3
			} else  {
				#ifdef DEBUGNEIGHB
					std::cout << "Right neighbour off" << std::endl;
				#endif
				current->AddNeighbour(NULL);
				current->AddNeighbour(NULL);
			}

			if (bottom) {
				#ifdef DEBUGNEIGHB
					std::cout << "Bottom neighbour" << std::endl;
				#endif
				current->AddNeighbour(TileArr[i+1][j]);
			
				if (left) current->AddNeighbour(TileArr[i+1][j-1]); // index 4
				else current->AddNeighbour(NULL); // index 5
			} else {
				#ifdef DEBUGNEIGHB
					std::cout << "Bottom neighbour off" << std::endl;
				#endif
				current->AddNeighbour(NULL);
				current->AddNeighbour(NULL);
			}

			if (left) {
				#ifdef DEBUGNEIGHB
					std::cout << "Left neighbour" << std::endl;
				#endif
				current->AddNeighbour(TileArr[i][j-1]);

				if (top) current->AddNeighbour(TileArr[i-1][j-1]); // index 6
				else current->AddNeighbour(NULL); // index 7
			} else {
				#ifdef DEBUGNEIGHB
					std::cout << "Left neighbour off" << std::endl;
				#endif
				current->AddNeighbour(NULL);
				current->AddNeighbour(NULL);
			}
			#ifdef DEBUGNEIGHB
				std::cout << "Finished assigning neighbours: row " << i << " column " << j << std::endl;
			#endif

		} // for (x-coord)
	} // for (y-coord)
	// for-loop for spawning custom input
	for (int y=0; y<25; ++y) {
		x = 0;
		getline (in2, line);
		if (in2.eof()) break;
		if (in2.fail()) in.ignore();

		// right now, assumin2g that all input is valid (79 columns for each row)
		for (std::string::iterator it = line.begin(); it != line.end(); ++it, ++x) {
			custom = CustomInput(it[0], TileArr[y][x]); // will break if I've missed an in2put char type
			if (custom) {
				if (willSpawn) { // when first custom tile is found
					willSpawn = false;
				}
			}
		} // read-in2 for loop that iterates through x-coord
	}// y-coord for loop
    // iterates through entire TileArr
	for (int y = 0; y<25; ++y) {
		for (int x = 0; x<79; ++x) {
			Tile* curr = TileArr[y][x]; // current tile
			if ((curr->GetDisplay() == '.') && (!curr->IsChecked)) {
				// Starts a cascade of flooding on the first non-checked '.'
				// it finds
				ChamberArr[NumChambers] = new Chamber;
				ChamberArr[NumChambers]->InitChamber(curr);
				++NumChambers;
			}
		}
	}
	if (willSpawn){
		PopulateChamber();
	} // if

	DrawInterface();
}



void Floor::PopulateChamber() {
    //***************SELECT HERO'S SPAWNING ROOM & TILE************************
	int hero_chamber = RandomGen(0,4);
	// if MyHero doesn't exist, SpawnHero will create a new hero
	#ifdef DEBUGSYSTEM
		std::cout << "Spawning player location" << std::endl;
	#endif
	MyHero = ChamberArr[hero_chamber]->SpawnHero(MyHero);
    //***************SELECT STAIR'S SPAWNING ROOM & TILE************************
	int stair_chamber = RandomGen(0,4);
	#ifdef DEBUGSYSTEM
		std::cout << "Spawning stair location" << std::endl;
	#endif
	while (hero_chamber == stair_chamber) {
			stair_chamber = RandomGen(0,4);
	}
	Stairs = ChamberArr[stair_chamber]->SpawnStair();
    //***************SELECT POTION'S SPAWNING ROOM & TILE************************
    #ifdef DEBUGSYSTEM
		std::cout << "Spawning potions" << std::endl;
	#endif
	for (int i = 0; i < NumPotions; ++i) {
		int potion_chamber = RandomGen(0,4);
		// potion type (1/6 chance) will be decided in Chamber's SpawnPotion()
		ItemArr[i] = ChamberArr[potion_chamber]->SpawnPotion();
	}
    //***************SELECT Gold'S SPAWNING ROOM & TILE************************
    #ifdef DEBUGSYSTEM
		std::cout << "Spawning gold" << std::endl;
	#endif
	for (int i = NumPotions; i < NumPotions + NumGold; ++i) {
		int gold_chamber = RandomGen(0,4);
		ItemArr[i] = ChamberArr[gold_chamber]->SpawnGold();
		ItemArr[i]->ModifyAllowPick(true);
	}
	//***************SPAWNING DRAGON BESIDES DRAGON HOARD************************
	#ifdef DEBUGSYSTEM
		std::cout << "Spawning dragon" << std::endl;
	#endif

	int dragons = 0;
	// checking each gold to spawn dragon
	for (int i = NumPotions; i < NumPotions + NumGold; ++i) {
		Gold* gld = dynamic_cast<Gold*>(ItemArr[i]);

       		if (gld && (gld->GetValue() == 6)) {
			Tile* HoardTile = ItemArr[i]->GetTile();
			// Spawn dragon:
			// Check chosen tile's neighbours. If neighbour is walkable, spawn there
			// otherwise keep rolling
			Dragon* d = new Dragon;
			d->SetTreasure(gld); // location of Dragon hoard
			std::map<int,int> Choice_Dirc;
			int OptionNum = 0;
			for(int i =0; i < 8; i++){
			    Tile* TempTile = HoardTile->GetNeighbour(i);
			        if(TempTile == 0){
			    	    continue;
			        }else{
			    	//If That tile can be walked on and:
			    	//that tile doesn't have anything on it
			    	if(TempTile && TempTile->GetAllowWalk() && (TempTile->GetEntity() == 0)){
			    		Choice_Dirc.insert(std::pair<int,int> (OptionNum, i));
						#ifdef DEBUGSYSTEM
							std::cout << "OptionNum incremented" << std::endl;
						#endif
			    		OptionNum++;
			    	}
			    }
			}
			if (OptionNum == 0) {}
			else {
				int chosen = RandomGen(0, OptionNum-1);
				int dragon_tile = Choice_Dirc[chosen]; 
				// insert the mapping to i here
				d->ModifyTile(HoardTile->GetNeighbour(dragon_tile));
				EnemyArr[dragons] = d;
				++dragons;
				HoardTile->GetNeighbour(dragon_tile)->AttachEntity(d);
			}
		}
	}
	#ifdef DEBUGSYSTEM
		std::cout << "Spawning other enemies" << std::endl;
	#endif
	for (int i = dragons; i < NumEnemies; ++i) {
		int enemy_chamber = RandomGen(0,4);
		EnemyArr[i] = ChamberArr[enemy_chamber]->SpawnEnemy();
	}

}

void Floor::DrawMap() {
	for (int y = 0; y < 25; ++y) {

		for (int x = 0; x < 79; ++x) {
			TileArr[y][x]->DrawTile();
		}

		std::cout << std::endl;
	}
}
	
void Floor::DrawStats() {
	// Floor x starts at 70th character 
	// Need accessor functions: getRace, getGold, getHP, getAtk, getDef
	// Need board to store Action
	std::cout << "Race: " << std::left << std::setw(7) << MyHero->GetRace() << std::setfill(' ') << " Gold: ";
	std::cout << std::left << std::setw(5) << MyHero->GetGoldStash() << std::setfill(' ');
	std::cout << std::right << std::setw(51) << "Floor " << CurrentFloor << std::setfill(' ') << std::endl;
	std::cout << "HP: " << MyHero->GetHP() << std::endl;
	std::cout << "Atk: " << MyHero->GetATK() << std::endl;
	std::cout << "Def: " << MyHero->GetDEF() << std::endl;
	// note: Action is printed out in main loop
}


// clear the character himself too?
// **need a clearHero. Player, stairs, potion, gold, enemies
void Floor::ClearLevel() {
	MyHero->GetTile()->DetachEntity(); // not deleted; want to transfer player to next level
	Stairs->SetDisplay('.');
    for (int i = 0; i < NumGold + NumPotions; ++i) {
	}	
	for (int i = 0; i < NumGold + NumPotions; ++i) {
		Tile* temp_t = ItemArr[i]->GetTile();
		if(temp_t != 0){
			temp_t->DetachEntity();	
		}
		delete ItemArr[i];
		ItemArr[i] = 0;
	}
	for(int i = 0; i < NumEnemies ; ++i){
		EnemyArr[i]->GetTile()->DetachEntity();
		delete EnemyArr[i];
		EnemyArr[i] = 0;
	}
}


// called when player quits game
void Floor::ClearHero () {
	if (MyHero) delete MyHero;
	MyHero = NULL;
}
	


void Floor::DrawInterface() {
		DrawMap();
		DrawStats();
}


void Floor::NextLevel() {
		ClearLevel();
		PopulateChamber();
		++CurrentFloor;
		MyHero->ResetAbilities();
}

void Floor::MoveEnemy() {
	for (int i = 0; i < NumEnemies; ++i) {
		#ifdef DEBUG
			std::cout << "Moving enemy " << i << std::endl;
			if (EnemyArr[i]) std::cout << "enemy exists" << std::endl;
			else std::cout << "enemy does not exist" << std::endl;
		#endif
		EnemyArr[i]->TakeTurn();
		#ifdef DEBUG
			std::cout << "End iteration" << std::endl;
		#endif
	}
}

//void SpawnEntity(Tile*, int);


Hero* Floor::MakeHero(std::string race) {
	if (race == "Shade") MyHero = new Shade;
	else if (race == "Drow") MyHero = new Drow;
	else if (race == "Vampire") MyHero = new Vampire;
	else if (race == "Troll") MyHero = new Troll;
	else MyHero = new Goblin;
	return MyHero;
}

int Floor::GetFloor() {return CurrentFloor;}

// CheckEndGame() function checks if the game has ended.
// It will return false if the game is still going or true if the game has
// ended.
//--> When player->GetHP() <= 0, game ends without printing score.(Death of hero)
//--> When GetFloor*() >= 6. game ends and print score.(Winning) 
bool Floor::CheckEndGame() {
	MyHero -> EndTurn();
    if (MyHero -> GetHP() <= 0) {
        std::cout << "You have been slain!" << std::endl;
        return true;
    } else if (CurrentFloor >= 6) {
        std::cout << "Congratulations! You have beat the game." << std::endl;
        std::cout << "You have: " << MyHero->GetGoldStash() << " gold" << std::endl;
        std::cout << "Your score is: " << MyHero->GetScore() << std::endl;
	    return true;
    }
    return false;
}
