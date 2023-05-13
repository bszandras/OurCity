#include "FireStation.h"

/// <summary>
/// Tûzoltóállomás konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a tûzoltóságot építjük</param>
FireStation::FireStation(Tile* tile) : SpecialBuilding(tile)
{
	this->truck = new FireTruck(this);

	this->buildCost = 100;
	this->maintenanceCost = 30;
	tile->fireChance += 0;

	range = 2;
	available = true;
}

/// <summary>
/// Tûzoltóság destruktor
/// </summary>
FireStation::~FireStation()
{
	delete this->truck;
}

/// <summary>
/// Beállítja a tûzoltóság hatósugarát.
/// </summary>
/// <param name="range">A tûzoltóság hatósugara</param>
void FireStation::setRange(int range)
{
	this->range = range;
}

/// <summary>
/// Beállítja, hogy a tûzoltóság éppen bevethetõ-e
/// </summary>
/// <param name="available">A tûzoltóság bevethetõsége</param>
void FireStation::setAvailable(bool available)
{
	this->available = available;
}

/// <summary>
/// Megadja a tûzoltóság hatósugarát
/// </summary>
/// <returns>A tûzoltóság hatósugara</returns>
int FireStation::getRange() const
{
	return this->range;
}

/// <summary>
/// Megadja, hogy a tûzoltóság éppen bevethetõ-e
/// </summary>
/// <returns>A tûzoltóság bevethetõsége</returns>
bool FireStation::isAvailable() const
{
	return this->available;
}

/// <summary>
/// A tûzoltóság megépítése után frissíti a környezõ cellákat (csökkenti a tûz kialakulásának esélyét)
/// </summary>
/// <param name="tiles">A Tile-ok, amiket frissíteni kell</param>
/// <param name="tileCount">A Tile-ok száma</param>
void FireStation::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->fireChance -= 20;
		updatedTiles.push_back(tiles[i]);
	}
}

/// <summary>
/// A tûzoltóság lerombolása után frissíti a környezõ cellákat (visszaállítja a tûz kialakulásának esélyét.
/// </summary>
void FireStation::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->fireChance += 20;
	}
	updatedTiles.clear();
}
