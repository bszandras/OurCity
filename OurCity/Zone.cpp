#include<iostream>

#include "Zone.h"

/// <summary>
/// Z�na konstruktor
/// </summary>
/// <param name="type">Z�na t�pusa</param>
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
/// Z�n�hoz ezzel lehet cell�t hozz�adni
/// </summary>
/// <param name="tileID">Cella ID-ja amivel meg lehet tal�lni a wrapper-ben</param>
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
/// Ezzel lehet a z�n�b�l cell�t kivenni
/// </summary>
/// <param name="tileID">Cella ID-ja amit ki szeretn�nk venni</param>
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
/// Ellen�rzi, hogy a kapott cella ID a z�n�hoz tartozik-e
/// </summary>
/// <param name="tileID">Ellen�rizend� ID</param>
/// <returns>Igaz ha a z�n�ban van</returns>
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
/// Cell�k sz�ma gettere
/// </summary>
/// <returns></returns>
int Zone::tileCount()
{
	return tiles.size();
}
/// <summary>
/// Z�na t�pus gettere
/// </summary>
/// <returns></returns>
int Zone::getType()
{
	return type;
}
/// <summary>
/// Z�na ad� szorz� gettere
/// </summary>
/// <returns></returns>
float Zone::getTaxRate() const
{
	return taxRate;
}
/// <summary>
/// Z�na ad�szorz� settere
/// </summary>
/// <param name="taxRate"></param>
void Zone::setTaxRate(float taxRate)
{
	this->taxRate = taxRate;
}
/// <summary>
/// Z�na ad� szorz�ra mutat� pointer gettere
/// </summary>
/// <returns></returns>
float* Zone::getTaxRateHandle()
{
	return &taxRate;
}
