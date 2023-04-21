#include "Fire.h"

Fire::Fire(Tile* tile)
{
	this->tile = tile;

	burnTime = 0;
	// egy h�tig �ghet a t�z, ut�na megsz�nik
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
