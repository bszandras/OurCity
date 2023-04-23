#include "Road.h"
#include <iostream>

int Road::idCount = 0;

Road::Road(Tile* tile) : SpecialBuilding(tile)
{
	this->buildCost = 50;
	//this->fireChance = 0;
	tile->fireChance = 0;
	this->maintenanceCost = 10;
	this->id = idCount;
	idCount++;
}

Road::~Road()
{
	std::cout << "Road deleted" << std::endl;
	idCount--;
}

Road::Road(Road& t) : SpecialBuilding(t)
{
	this->id = t.id;
	this->buildCost = t.buildCost;
	//this->fireChance = t.fireChance;
	tile->fireChance = t.tile->fireChance;
	this->maintenanceCost = t.maintenanceCost;
}

int Road::getId() const
{
	return this->id;
}

void Road::setId(int id)
{
	this->id = id;
}

