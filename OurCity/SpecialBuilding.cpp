#include "SpecialBuilding.h"

/// <summary>
/// Speci�lis �p�let konstruktora
/// </summary>
/// <param name="tile">A Tile, amire a speci�lis �p�letet �p�tj�k</param>
SpecialBuilding::SpecialBuilding(Tile* tile) : Building(tile)
{
	this->tile = tile;
}