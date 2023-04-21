#pragma once
#include "TileRect.h"
class Fire
{
private:
	// itt ég a tûz
	Tile* tile;
	float propagationChance;
	// ezek játékórák
	int burnTime;
	int maxBurnTime;

	// TODO
	void Propagate();
public:
	Fire(Tile* tile);
	~Fire();
	void Update(int deltaHours);
	int getBurnTime();
	Tile* getTargetTile();
};