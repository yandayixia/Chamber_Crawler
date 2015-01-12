#include "Entity.h"
#include <iostream>
/*Constructor that takes in one argument Input that could potentially
become this Entity's display later.*/
Entity::Entity(char Input): MyDisplay(Input) {}
/*GetDisplay() returns MyDisplay to caller*/
void Entity::DrawEntity(){
    std::cout << MyDisplay;
}
Entity::~Entity() {}
/*GetAllowWalk() ALWAYS return false by default.*/
bool Entity::GetAllowWalk() { 
	#ifdef DEBUG
		std::cout << "Entity Allow Walk called" << std::endl;
	#endif
	return false;
}
//GetDisplay() simply returns MyDisplay.
char Entity::GetDisplay(){
	return MyDisplay;
}

void Entity::SetDisplay(char display) {MyDisplay = display;}

std::string Entity::GetName() {
	std::string Name = "Entity";
	return Name;
}
int Entity::GetValue() {return 0;}
