#include "Zone.h"

Zone::Zone(unsigned char type)
{
	this->type = type;
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
		for (int i = 0; i < tiles.size(); i++)
		{
			tiles.erase(tiles.begin() + i);
			return true;
		}
	}
}

bool Zone::isTileInZone(int tileID) const
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i] == tileID)
			return true;
	}
	return false;
}

std::vector<int> Zone::getTiles() const
{
	return tiles;
}