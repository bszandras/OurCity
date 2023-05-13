#include "Road.h"
#include <iostream>

int Road::idCount = 0;

/// <summary>
/// �t konstruktor
/// </summary>
/// <param name="tile">A Tile, amire az utat l�tre akarjuk hozni.</param>
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
/// Visszaadja az �t azonos�t�j�t
/// </summary>
/// <returns>�t id-je</returns>
int Road::getId() const
{
	return this->id;
}

/// <summary>
/// Be�ll�tja az �t azonos�t�j�t
/// </summary>
/// <param name="id">A sz�m, amire az �t azonos�t�j�t �ll�tani szeretn�nk</param>
void Road::setId(int id)
{
	this->id = id;
}

