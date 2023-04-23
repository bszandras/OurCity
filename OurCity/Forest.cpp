#include "Forest.h"

Forest::Forest(Tile* tile) : SpecialBuilding(tile)
{
	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	//this->fireChance = 30;
	tile->fireChance += 30;

	this->age = 0; // The initial age is 0!
}

Forest::~Forest()
{
}

void Forest::grow()
{
	// TODO: Implement this function!
}

void Forest::setAge(int a)
{
	this->age = a;
}

int Forest::getAge() const
{
	return this->age;
}
