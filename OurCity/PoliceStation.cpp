#include "PoliceStation.h"

PoliceStation::PoliceStation(Tile* tile) : SpecialBuilding(tile)
{
	// Set the members of the base class
	this->buildCost = 100;
	this->maintenanceCost = 30;
	//this->fireChance = 3;
	tile->fireChance += 3;
	range = 0; // TODO: Set the range!!
	bonusHappiness = 20;
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

void PoliceStation::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->publicSafety += 1;
		updatedTiles.push_back(tiles[i]);
		// Ezzel garant�ljuk, hogy ha egy tile t�bb policestation sugaraba esik, akkor is
		// Csak egyszer n�velj�k a boldogs�got.
		if (tiles[i]->publicSafety == 1)
		{
			tiles[i]->happinessModifer += bonusHappiness;
		}
	}
}

void PoliceStation::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->publicSafety -= 1;
		// Ezzel garant�ljuk, hogy ha egy tile t�bb policestation sugaraba esik, akkor is
		// Csak egyszer cs�kkentj�k a boldogs�got.
		if (updatedTiles[i]->publicSafety == 0)
		{
			updatedTiles[i]->happinessModifer -= bonusHappiness;
		}
	}
	updatedTiles.clear();
}

int PoliceStation::getRange() const
{
	return this->range;
}

std::vector<int> PoliceStation::getRangeTiles() const
{
	return this->rangeTiles;
}
