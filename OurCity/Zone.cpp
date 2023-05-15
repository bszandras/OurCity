#include<iostream>

#include "Zone.h"

/// <summary>
/// Zóna konstruktor
/// </summary>
/// <param name="type">Zóna típusa</param>
/// <returns></returns>
Zone::Zone(unsigned char type)
{
	this->type = type;
	this->taxRate = 1.0;
}

Zone::~Zone()
{
}
/// <summary>
/// Zónához ezzel lehet cellát hozzáadni
/// </summary>
/// <param name="tileID">Cella ID-ja amivel meg lehet találni a wrapper-ben</param>
/// <returns></returns>
bool Zone::addTile(int tileID)
{
	if(this->isTileInZone(tileID))
		return false;
	else
	{
		tiles.push_back(tileID);
		return true;
	}
}
/// <summary>
/// Ezzel lehet a zónából cellát kivenni
/// </summary>
/// <param name="tileID">Cella ID-ja amit ki szeretnénk venni</param>
/// <returns></returns>
bool Zone::removeTile(int tileID)
{
	if (!isTileInZone(tileID))
		return false;
	else
	{
		for(size_t i = 0; i < tiles.size(); i++)
		{
			if(tiles[i] == tileID)
			{
				tiles.erase(tiles.begin() + i);
				return true;
			}
		}
	}
}
/// <summary>
/// Ellenõrzi, hogy a kapott cella ID a zónához tartozik-e
/// </summary>
/// <param name="tileID">Ellenõrizendõ ID</param>
/// <returns>Igaz ha a zónában van</returns>
bool Zone::isTileInZone(int tileID) const
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i] == tileID)
		{
			return true;
		}
	}
	return false;
}
/// <summary>
/// Cella ID-k gettere
/// </summary>
/// <returns></returns>
std::vector<int> Zone::getTiles() const
{
	return tiles;
}
/// <summary>
/// Cellák száma gettere
/// </summary>
/// <returns></returns>
int Zone::tileCount()
{
	return tiles.size();
}
/// <summary>
/// Zóna típus gettere
/// </summary>
/// <returns></returns>
int Zone::getType()
{
	return type;
}
/// <summary>
/// Zóna adó szorzó gettere
/// </summary>
/// <returns></returns>
float Zone::getTaxRate() const
{
	return taxRate;
}
/// <summary>
/// Zóna adószorzó settere
/// </summary>
/// <param name="taxRate"></param>
void Zone::setTaxRate(float taxRate)
{
	this->taxRate = taxRate;
}
/// <summary>
/// Zóna adó szorzóra mutató pointer gettere
/// </summary>
/// <returns></returns>
float* Zone::getTaxRateHandle()
{
	return &taxRate;
}
