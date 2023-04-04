#include "PoliceStation.h"

PoliceStation::PoliceStation(Tile* tile) : SpecialBuilding(tile)
{
	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	this->fireChance = 0;

	range = 0; // TODO: Set the range!!
}

PoliceStation::~PoliceStation()
{
}

void PoliceStation::setRange(int r)
{
	this->range = r;
}

void PoliceStation::setRangeTiles(std::vector<int> tiles)
{
	this->rangeTiles = tiles;
}

int PoliceStation::getRange() const
{
	return this->range;
}

std::vector<int> PoliceStation::getRangeTiles() const
{
	return this->rangeTiles;
}
