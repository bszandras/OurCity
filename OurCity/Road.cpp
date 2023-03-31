#include "Road.h"

int Road::idxCounter = 0;

Road::Road(Tile* tile) : SpecialBuilding(tile)
{
	this->buildCost = 100;
	this->fireChance = 0;
	this->maintenanceCost = 10;

	idxCounter++;
	this->idx = idxCounter;
}

int Road::getIdx() const
{
	return idx;
}
