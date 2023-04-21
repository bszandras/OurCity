#include "Fire.h"
#include <random>



Fire::Fire(Tile* tile)
{
	this->tile = tile;

	burnTime = 0;
	// 7 napig éghet egy tûz
	maxBurnTime = 7;
}

Fire::~Fire()
{
}

void Fire::Update(int deltaDays)
{
	burnTime += deltaDays;
	// ha 2 napnál kevesebb ideje ég a tûz nem büntetjük a játékost
	if (burnTime > 2)
	{
		Propagate();
	}
	else
	{
		needsToPropagate = false;
	}
}
void Fire::Propagate()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
	
	// 50% esély terjedésre
	double f = dis(gen);
	if (f < 0.5)
	{
		needsToPropagate = true;
	}
	else
	{
		needsToPropagate = false;
	}
}

int Fire::getBurnTime()
{
	return burnTime;
}

int Fire::getMaxBurnTime()
{
	return maxBurnTime;
}

Tile* Fire::getTargetTile()
{
	return tile;
}

bool Fire::shouldPropagate()
{
	return needsToPropagate;
}
