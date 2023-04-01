#include "Road.h"


int Road::idCount = 0;

Road::Road(Tile* tile) : SpecialBuilding(tile)
{
	this->buildCost = 50;
	this->fireChance = 0;
	this->maintenanceCost = 10;
	idCount++;
	this->id = idCount;
}

Road::~Road()
{
}

int Road::getId() const
{
	return this->id;
}

void Road::setId(int id)
{
	this->id = id;
}

