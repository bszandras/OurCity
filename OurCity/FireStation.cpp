#include "FireStation.h"

FireStation::FireStation(Tile* tile) : SpecialBuilding(tile)
{
	//this->truck = new FireTruck(this);
	available = true;
	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	//this->fireChance = 0;
	tile->fireChance += 0;

	range = 2;
	available = true;
}

FireStation::~FireStation()
{
	//delete this->truck;
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

void FireStation::HeliStarted()
{
	available = false;
}

void FireStation::HeliArrived()
{
	available = true;
}

void FireStation::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->fireChance -= 20;
		updatedTiles.push_back(tiles[i]);
	}
	// std::cout << "updated firechances: " << tileCount << std::endl;
}

void FireStation::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->fireChance += 20;
	}
	updatedTiles.clear();
}
