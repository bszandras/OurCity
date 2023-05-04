#include "Factory.h"

Factory::Factory(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;
	//this->fireChance = 9;
	tile->fireChance += 9;
	this->tile = tile;
	this->capacity = 8;
	this->tax = 0;
	this->range = 2;
	//this->updatedTiles.erase(updatedTiles.begin(), updatedTiles.end());
}

void Factory::setRange(int r)
{
	this->range = r;
}

void Factory::setRangeTiles(std::vector<int> tiles)
{
	//this->rangeTiles = tiles;
}

void Factory::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		//tiles[i]->happinessModifer -= minusHappiness;
		tiles[i]->pollution += 1;
		updatedTiles.push_back(tiles[i]);
	}
}

void Factory::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		//updatedTiles[i]->happinessModifer += minusHappiness;
		updatedTiles[i]->pollution -= 1;
	}
	updatedTiles.clear();
}

int Factory::getRange() const
{
	return this->range;
}

std::vector<int> Factory::getRangeTiles() const
{
	return this->rangeTiles;
}
