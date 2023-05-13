#include "Road.h"
#include <iostream>

int Road::idCount = 0;

/// <summary>
/// Út konstruktor
/// </summary>
/// <param name="tile">A Tile, amire az utat létre akarjuk hozni.</param>
Road::Road(Tile* tile) : SpecialBuilding(tile)
{
	this->buildCost = 50;
	tile->fireChance = 0;
	this->maintenanceCost = 10;
	this->id = idCount;
	idCount++;
}

Road::~Road()
{
	idCount--;
}

Road::Road(Road& t) : SpecialBuilding(t)
{
	this->id = t.id;
	this->buildCost = t.buildCost;
	tile->fireChance += t.tile->fireChance;
	this->maintenanceCost = t.maintenanceCost;
}

/// <summary>
/// Visszaadja az út azonosítóját
/// </summary>
/// <returns>Út id-je</returns>
int Road::getId() const
{
	return this->id;
}

/// <summary>
/// Beállítja az út azonosítóját
/// </summary>
/// <param name="id">A szám, amire az út azonosítóját állítani szeretnénk</param>
void Road::setId(int id)
{
	this->id = id;
}

