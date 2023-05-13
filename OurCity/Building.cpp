#include "Building.h"

/// <summary>
/// Building konstruktor
/// </summary>
/// <param name="tile">A tile, amire az �p�letet rakjuk</param>
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
/// Megadja az �p�let �p�t�si k�lts�g�t
/// </summary>
/// <returns>Az �p�let �p�t�si k�lts�ge</returns>
unsigned short Building::getBuildCost()
{
	return buildCost;
}

/// <summary>
/// Be�ll�tja az �p�let �p�t�si k�lts�g�t.
/// </summary>
/// <param name="c">Az �j �p�t�si k�lts�g</param>
void Building::setBuildCost(unsigned short cost)
{
	buildCost = cost;
}

/// <summary>
/// Megadja az �p�let fenntart�si k�lts�g�t
/// </summary>
/// <returns>Az �p�let fenntart�si k�lts�ge</returns>
unsigned short Building::getMaintenanceCost()
{
	return maintenanceCost;
}

/// <summary>
/// Megadja az �p�let t�zvesz�lyess�g�t
/// </summary>
/// <returns>Az �p�let t�zvesz�lyess�ge</returns>
short Building::getFireChance()
{
	
	return tile->fireChance;
}

/// <summary>
/// Megadja, hogy az adott �p�let h�ny Tile-t foglal el
/// </summary>
/// <returns>Az �p�let �ltal elfoglalt Tile-ok sz�ma</returns>
unsigned char Building::getTileSize()
{
	return tileSize;
}

/// <summary>
/// Ez csak a dynamic cast miatt kell, nem csin�l semmit
/// </summary>
void Building::toString()
{
}

/// <summary>
/// Visszaadja a Tile-t, amin az �p�let van
/// </summary>
/// <returns>A Tile, amin az �p�let van</returns>
Tile* Building::getTile()
{
	return tile;
}
