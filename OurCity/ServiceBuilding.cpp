#include "ServiceBuilding.h"

/// <summary>
/// Kiszolg�l� �p�let konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a kiszolg�l� �p�let ker�l.</param>
ServiceBuilding::ServiceBuilding(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;
	tile->fireChance += 5;
	this->tile = tile;
	this->capacity = 6;
}
