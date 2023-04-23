#include "Stadium.h"
#include <iostream>

Stadium::Stadium(Tile* tile) : SpecialBuilding(tile)
{
	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	//this->fireChance = 1;
	tile->fireChance = 1;
	this->tileSize = 4;

	range = 3;
	bonusHappiness = 30;
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

void Stadium::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->happinessModifer += bonusHappiness;
		updatedTiles.push_back(tiles[i]);
	}
}

void Stadium::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->happinessModifer -= bonusHappiness;
	}
	updatedTiles.clear();
}

int Stadium::getRange() const
{
	return this->range;
}

std::vector<int> Stadium::getRangeTiles() const
{
	return this->rangeTiles;
}
