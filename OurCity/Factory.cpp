#include "Factory.h"

/// <summary>
/// Ipari épület konstruktor
/// </summary>
/// <param name="tile">A Tile, amin az ipari épület van</param>
Factory::Factory(Tile* tile) : Workplace(tile)
{
	this->buildCost = 0;
	this->maintenanceCost = 0;
	tile->fireChance += 9;
	this->tile = tile;
	this->capacity = 8;
	this->range = 2;
}

/// <summary>
/// Az ipari épület kedvrontó hatásának hatósugarának beállítása
/// </summary>
/// <param name="range">Ekkora hatósugárban rontja a lakosok kedvét az ipari épület</param>
void Factory::setRange(int range)
{
	this->range = range;
}

/// <summary>
/// Az ipari épület épülése után frissíti a környezõ cellák szennyezettségét
/// </summary>
/// <param name="tiles">A frissítendõ Tile-ok</param>
/// <param name="tileCount">A frissítendõ Tile-ok száma</param>
void Factory::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->pollution += 1;
		updatedTiles.push_back(tiles[i]);
	}
}

/// <summary>
/// Az ipari épület lerombolása után frissíti a környezõ cellák szennyezettségét
/// </summary>
void Factory::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->pollution -= 1;
	}
	updatedTiles.clear();
}

/// <summary>
/// Megadja az ipari épület kedvrontó hatásának hatósugarát
/// </summary>
/// <returns>A kedvrontó hatás sugara</returns>
int Factory::getRange() const
{
	return this->range;
}