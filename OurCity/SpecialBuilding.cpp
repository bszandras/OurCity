#include "SpecialBuilding.h"

/// <summary>
/// Speciális épület konstruktora
/// </summary>
/// <param name="tile">A Tile, amire a speciális épületet építjük</param>
SpecialBuilding::SpecialBuilding(Tile* tile) : Building(tile)
{
	this->tile = tile;
}