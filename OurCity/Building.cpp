#include "Building.h"

/// <summary>
/// Building konstruktor
/// </summary>
/// <param name="tile">A tile, amire az épületet rakjuk</param>
Building::Building(Tile* tile)
{
	this->tile = tile;

	buildCost = 0;
	maintenanceCost = 0;
}

Building::~Building()
{
}

/// <summary>
/// Megadja az épület építési költségét
/// </summary>
/// <returns>Az épület építési költsége</returns>
unsigned short Building::getBuildCost()
{
	return buildCost;
}

/// <summary>
/// Beállítja az épület építési költségét.
/// </summary>
/// <param name="c">Az új építési költség</param>
void Building::setBuildCost(unsigned short cost)
{
	buildCost = cost;
}

/// <summary>
/// Megadja az épület fenntartási költségét
/// </summary>
/// <returns>Az épület fenntartási költsége</returns>
unsigned short Building::getMaintenanceCost()
{
	return maintenanceCost;
}

/// <summary>
/// Megadja az épület tûzveszélyességét
/// </summary>
/// <returns>Az épület tûzveszélyessége</returns>
short Building::getFireChance()
{
	
	return tile->fireChance;
}

/// <summary>
/// Megadja, hogy az adott épület hány Tile-t foglal el
/// </summary>
/// <returns>Az épület által elfoglalt Tile-ok száma</returns>
unsigned char Building::getTileSize()
{
	return tileSize;
}

/// <summary>
/// Ez csak a dynamic cast miatt kell, nem csinál semmit
/// </summary>
void Building::toString()
{
}

/// <summary>
/// Visszaadja a Tile-t, amin az épület van
/// </summary>
/// <returns>A Tile, amin az épület van</returns>
Tile* Building::getTile()
{
	return tile;
}
