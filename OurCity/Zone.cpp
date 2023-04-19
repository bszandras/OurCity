#include<iostream>

#include "Zone.h"

Zone::Zone(unsigned char type)
{
	this->type = type;
	this->taxRate = 1.0;
}

Zone::~Zone()
{
}

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

std::vector<int> Zone::getTiles() const
{
	return tiles;
}
int Zone::tileCount()
{
	return tiles.size();
}

double Zone::getTaxRate() const
{
	return taxRate;
}

void Zone::setTaxRate(double taxRate)
{
	this->taxRate = taxRate;
}
