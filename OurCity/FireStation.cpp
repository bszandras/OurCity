#include "FireStation.h"

FireStation::FireStation(Tile* tile) : SpecialBuilding(tile)
{
	this->truck = new FireTruck(this);

	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	this->fireChance = 0;

	range = 0; // TODO: Set the range!!
	available = true;
}

FireStation::~FireStation()
{
	delete this->truck;
}

void FireStation::setRange(int r)
{
	this->range = r;
}

void FireStation::setRangeTiles(std::vector<int> tiles)
{
	this->rangeTiles = tiles;
}

void FireStation::setAvailable(bool a)
{
	this->available = a;
}

int FireStation::getRange() const
{
	return this->range;
}

std::vector<int> FireStation::getRangeTiles() const
{
	return this->rangeTiles;
}

bool FireStation::isAvailable() const
{
	return this->available;
}
