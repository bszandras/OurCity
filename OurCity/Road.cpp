#include "Road.h"

int Road::idxCounter = 0;

Road::Road(Tile* tile) : SpecialBuilding(tile)
{
	this->buildCost = 100;
	this->fireChance = 0;
	this->maintenanceCost = 10;
	this->deleted = false;

	idxCounter++;
	this->idx = idxCounter;
}

int Road::getIdx() const
{
	return idx;
}

bool Road::isDeleted() const
{
	return deleted;
}

void Road::setDeleted(bool deleted)
{
	this->deleted = deleted;
}
