#ifndef __TILE_H__
#define __TILE_H__

#include "Entity.h"

class Entity;
class Potion;
class Hero;
class Gold;

class Tile:public Entity{
    Entity* MyEntity;
    //starts from 1 and counts to 8 as each time 
    //AddNeighbour(Tile*) is called. 
    int NumNeighbours;
    Tile** NeighboursArr; //Has size 8
    bool IsWalkable;
public:
    //Will ONLY be used when initializing Chamber from a starting file.
    bool IsChecked; 
    Tile(char display);
    // Walkable() returns IsWalkable bool field
    /*OkToWalk(int dirc) returns true if the dirction dirc indicated is 
    walkable or (is walkable and contains a pickable item) or (iswalkable 
    and contains a stair and dirc = 6.) If the Tile is not walkable, return
    null./ 
    7 0 1
    6 @ 2
    5 4 3 
    */
    Tile* OkToWalk(int dirc); 

    bool GetAllowWalk();

    void SetAllowWalk(bool val); // used when initializing custom tiles
    /*AttachEntity(Entity* Target) will attach Target to MyEntity.*/
    void AttachEntity(Entity* Target);
    /*DetachEntity() resets MyEntity back to null.*/
    void DetachEntity();
    /*DrawTile() prints to Cout (without adding endl) either this->GetDisplay,
    or MyEntity->GetDisplay() if My Entity is not null.*/
    void DrawTile();
    /*IsPlayer_Engaged() returns the pointer to that tile if the player
    is standing on one of the neighbours, or null otherwise. */
    Tile* IsPlayerEngaged();
    /*EnemyEngaged() returns the pointer to that tile if there is enemy
    character standing on the dirc tile, or null otherwise. */
    Tile* EnemyEngaged(int dirc);
    //PotionInRange(int dirc) will return a pointer to the potion on the
    //targeting tile indicated by dirc if that tile indeed have a potion. 
    //Otherwise, return null(0)
    Potion* PotionInRange(int dirc);
    /*AddNeighbour(Tile* Target) initializes the "Arr_Counter"-th element of 
    neighbours_Arr and increments Arr_Counter by one with each call.*/
    void AddNeighbour(Tile* Target);
    // Gets neighbour with index which
    Tile* GetNeighbour(int which);
    // used when initializing chamber; turns on IsChecked switch so it will not
    // be added to Chamber's AvailableTiles twice
    void DoneCheck();
    //GetEntity() returns MyEntity.
    Entity* GetEntity();
    bool HasEntity();
    //IsNeighbour(Tile* Target) returns true if Target is indeed one of
    //the neibhbours of this tile object. Return false otherwise. 
    bool IsNeighbour(Tile* Target);
    void DrawEntity();
    Gold* DragonHoardInRange(int dirc);

};

#endif
