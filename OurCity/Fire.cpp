#include "Fire.h"
#include <random>



Fire::Fire(Tile* tile)
{
	this->tile = tile;

	burnTime = 0;
	// 7 napig �ghet egy t�z
	maxBurnTime = 7;
}

Fire::~Fire()
{
}

void Fire::Update(int deltaDays)
{
	burnTime += deltaDays;
	// ha 2 napn�l kevesebb ideje �g a t�z nem b�ntetj�k a j�t�kost
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
	
	// 50% es�ly terjed�sre
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
