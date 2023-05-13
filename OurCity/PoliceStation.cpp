#include "PoliceStation.h"

/// <summary>
/// Rendõrség kontruktor
/// </summary>
/// <param name="tile">A Tile, amire a rendõrség épül</param>
PoliceStation::PoliceStation(Tile* tile) : SpecialBuilding(tile)
{
	this->buildCost = 100;
	this->maintenanceCost = 30;
	tile->fireChance += 3;
	range = 30;
}

PoliceStation::~PoliceStation()
{
}

/// <summary>
/// Beállítja, hogy a rendõrség milyen sugarú területet fed le
/// </summary>
/// <param name="range"></param>
void PoliceStation::setRange(int range)
{
	this->range = range;
}

/// <summary>
/// Frissíti a környezõ cellákat rendõrség építése után (növeli a közbiztonságot)
/// </summary>
/// <param name="tiles">A frissítendõ Tile-ok</param>
/// <param name="tileCount">A frissítendõ Tile-ok száma</param>
void PoliceStation::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->publicSafety += 1;
		updatedTiles.push_back(tiles[i]);
	}
}

/// <summary>
/// Frissíti a környezõ cellákat rendõrség lerombolása után (visszaállítja a közbiztonságot)
/// </summary>
void PoliceStation::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->publicSafety -= 1;
	}
	updatedTiles.clear();
}

/// <summary>
/// Megadja, hogy mekkora a rendõrség hatósugara
/// </summary>
/// <returns>A rendõrség hatósugara</returns>
int PoliceStation::getRange() const
{
	return this->range;
}