#include "Zone.h"

Zone::Zone()
{
}

Zone::~Zone()
{
}

void Zone::addTile(int tileID)
{
	tiles.push_back(tileID);
}

void Zone::removeTile(int tileID)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i] == tileID)
		{
			tiles.erase(tiles.begin() + i);
			break;
		}
	}
}
