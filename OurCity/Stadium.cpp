#include "Stadium.h"

Stadium::Stadium(Tile* tile) : SpecialBuilding(tile)
{
	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	this->fireChance = 0;
	this->tileSize = 4;

	range = 0; // TODO: Set the range!!
}

Stadium::~Stadium()
{
}

void Stadium::setRange(int r)
{
	this->range = r;
}

void Stadium::setRangeTiles(std::vector<int> tiles)
{
	this->rangeTiles = tiles;
}

int Stadium::getRange() const
{
	return this->range;
}

std::vector<int> Stadium::getRangeTiles() const
{
	return this->rangeTiles;
}
