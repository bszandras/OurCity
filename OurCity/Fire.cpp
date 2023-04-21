#include "Fire.h"

Fire::Fire(Tile* tile)
{
	this->tile = tile;

	burnTime = 0;
	// egy hétig éghet a tûz, utána megszûnik
	maxBurnTime = 7*24;
}

Fire::~Fire()
{
}

void Fire::Update(int deltaHours)
{
}

int Fire::getBurnTime()
{
	return burnTime;
}

Tile* Fire::getTargetTile()
{
	return tile;
}
