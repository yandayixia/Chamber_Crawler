#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>
/*When reading in from a file, following value cooresponds
    to the following Entity:
    .0 RH (restore health)
    .1 BA (boost attack)
    .2 BD (boost defend)
    .3 PH (poison health)
    .4 WA (wound attack)
    .5 WD (wound defend)
    .6 Normal Gold
    .7 Small Gold
    .8 Merchant Hoard
    .9 Dragon Hoard
    */
class Entity{
    char MyDisplay;
public:
    /*Constructor that takes in one argument Input that will become
    this Entity's display later.*/
    Entity(char Input);
    //pure virutal destructor.
    virtual ~Entity()=0;
    /*DrawEntity() passes MyDisplay to cout, NO std::endl is passed!*/ 
    virtual void DrawEntity();
    /*GetAllowWalk() ALWAYS return false by default.*/
    virtual bool GetAllowWalk()=0;
    //GetDisplay() simply returns MyDisplay.
    //Overloaded by tile's GetDisplay, which returns the display of its Entity
    //if there is an Entity standing on it.
    virtual char GetDisplay();
    // used when initializing customly-inputted spawns
    void SetDisplay(char Display);
    // overloaded to return Gold value and Gold name
    virtual std::string GetName();
    virtual int GetValue();
};

#endif
