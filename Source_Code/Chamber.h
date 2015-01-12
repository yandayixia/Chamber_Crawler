#ifndef __CHAMBER_H__
#define __CHAMBER_H__


class Tile;
class Hero;
class Enemy;
class Potion;
class Gold;

class Chamber{
    Tile** AvailableTiles; //An array denoting all the tiles.
    int SampleSpace; //The size of the original sample space.
public:
    /*The constructor*/
    Chamber();
    /*The destructor should call delete [] on Available_Tiles.*/
    ~Chamber();
    /*The constructor that takes in a pointer to a tile.
    InitChamber(Curr) will determine Curr's neighbours using Curr as a starting point,
    recursively calling itself on '.' neighbour tiles that lie within a chamber.
    It initializes a Chamber by 'flooding' it so that all tiles can go into the
    AvailableTiles array.*/
    void InitChamber(Tile* Curr);

    /*NOTE(Spawning): During random number generation, if an entry that has previously 
    appeared occurs again, then we reroll until a fresh entry appears*/

    /*SpawnHero() returns a pointer to the hero created.*/
    Hero* SpawnHero(Hero* MyHero);
    /*SpawnStair() returns a pointer to the stair(Item) created.*/
    Tile* SpawnStair();
    /*SpawnPotion() returns a pointer to the potion(Item) created.*/
    Item* SpawnPotion();
    /*SpawnGold() returns a pointer to the Gold(Item) created.*/
    Item* SpawnGold();
    /*SpawnEnemy() returns a pointer to the enemy(Character) created.*/
    Enemy* SpawnEnemy();
    /*Helper function that randomly generates an index referring to 
    one of the Available_Tiles.*/
    int ChooseTile();
};


#endif
