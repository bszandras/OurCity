#include "FireStation.h"

/// <summary>
/// T�zolt��llom�s konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a t�zolt�s�got �p�tj�k</param>
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
/// T�zolt�s�g destruktor
/// </summary>
FireStation::~FireStation()
{
	delete this->truck;
}

/// <summary>
/// Be�ll�tja a t�zolt�s�g hat�sugar�t.
/// </summary>
/// <param name="range">A t�zolt�s�g hat�sugara</param>
void FireStation::setRange(int range)
{
	this->range = range;
}

/// <summary>
/// Be�ll�tja, hogy a t�zolt�s�g �ppen bevethet�-e
/// </summary>
/// <param name="available">A t�zolt�s�g bevethet�s�ge</param>
void FireStation::setAvailable(bool available)
{
	this->available = available;
}

/// <summary>
/// Megadja a t�zolt�s�g hat�sugar�t
/// </summary>
/// <returns>A t�zolt�s�g hat�sugara</returns>
int FireStation::getRange() const
{
	return this->range;
}

/// <summary>
/// Megadja, hogy a t�zolt�s�g �ppen bevethet�-e
/// </summary>
/// <returns>A t�zolt�s�g bevethet�s�ge</returns>
bool FireStation::isAvailable() const
{
	return this->available;
}

/// <summary>
/// A t�zolt�s�g meg�p�t�se ut�n friss�ti a k�rnyez� cell�kat (cs�kkenti a t�z kialakul�s�nak es�ly�t)
/// </summary>
/// <param name="tiles">A Tile-ok, amiket friss�teni kell</param>
/// <param name="tileCount">A Tile-ok sz�ma</param>
void FireStation::UpdateAreaAfterBuilding(Tile** tiles, int tileCount)
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i]->fireChance -= 20;
		updatedTiles.push_back(tiles[i]);
	}
}

/// <summary>
/// A t�zolt�s�g lerombol�sa ut�n friss�ti a k�rnyez� cell�kat (vissza�ll�tja a t�z kialakul�s�nak es�ly�t.
/// </summary>
void FireStation::UpdateAreaAfterDestruction()
{
	for (int i = 0; i < updatedTiles.size(); i++)
	{
		updatedTiles[i]->fireChance += 20;
	}
	updatedTiles.clear();
}
