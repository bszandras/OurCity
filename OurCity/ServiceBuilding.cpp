#include "ServiceBuilding.h"

/// <summary>
/// Kiszolgáló épület konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a kiszolgáló épület kerül.</param>
ServiceBuilding::ServiceBuilding(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;
	tile->fireChance += 5;
	this->tile = tile;
	this->capacity = 6;
}
